优化方案：统一缓存文件 + LRU 策略
方案对比
方案	优点	缺点
❌ 每个好友一个文件	简单	文件数量爆炸，大量小文件 I/O 性能差
✅ 统一缓存文件	减少文件数量，批量 I/O 性能好	需要额外的索引管理
✅ 纯数据库方案	无额外文件，查询灵活	频繁 DB 访问可能影响性能
推荐方案：内存 + 数据库 二级缓存

┌─────────────────────────────────────────────────────────────┐
│                    简化的二级缓存架构                        │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│  ┌─────────────────┐              ┌─────────────────┐      │
│  │   内存缓存 LRU  │ ← 需要时 →    │   数据库(SQLite)│      │
│  │  (最近20个聊天)  │              │  (所有历史消息)  │      │
│  └─────────────────┘              └─────────────────┘      │
│                                                             │
│  • 仅缓存活跃聊天的消息                                       │
│  • LRU淘汰策略，限制内存占用                                  │
│  • 切换聊天时：内存命中直接用，未命中从DB加载                 │
│  • 无需磁盘缓存，减少IO复杂度                                │
│                                                             │
└─────────────────────────────────────────────────────────────┘
实现代码

```c++
// ChatSessionMgr.h
class ChatSessionMgr : public QObject, public Singleton<ChatSessionMgr>
{
    Q_OBJECT
public:
    // 切换聊天对象
    void switchChat(int friendUid);
    

    // 添加消息到当前聊天
    void addMessage(std::shared_ptr<MsgItem> msg);
    
    // 获取当前聊天对象
    int getCurrentChatUid() const { return _currentChatUid; }
    
    // 获取当前聊天的未读数
    int getUnreadCount(int friendUid);

private:
    ChatSessionMgr();
    

    // 从数据库加载聊天记录
    void loadChatFromDB(int friendUid);
    
    // 保存当前聊天到缓存
    void saveCurrentChat();

private:
    int _currentChatUid = -1;
    

    // 内存缓存：friendUid → 消息列表（最多保留20个活跃聊天）
    QMap<int, QVector<std::shared_ptr<MsgItem>>> _chatCache;
    
    // LRU队列：记录访问顺序
    QList<int> _lruQueue;
    
    // 最大缓存聊天数
    static constexpr int MAX_CACHED_CHATS = 20;

};
```

```c++
// ChatSessionMgr.cpp
ChatSessionMgr::ChatSessionMgr()
{
}

void ChatSessionMgr::switchChat(int friendUid)
{
    // 如果已经是当前聊天，不做处理
    if (_currentChatUid == friendUid) {
        return;
    }
    

    // 保存当前聊天状态
    saveCurrentChat();
    
    // 切换到新聊天
    _currentChatUid = friendUid;
    
    // 更新 LRU 队列
    _lruQueue.removeAll(friendUid);
    _lruQueue.prepend(friendUid);	//前插
    
    // 检查是否在缓存中
    if (_chatCache.contains(friendUid)) {
        // 缓存命中，直接使用
        emit sigChatLoaded(_chatCache[friendUid]);
    } else {
        // 缓存未命中，从数据库加载
        loadChatFromDB(friendUid);	//加载的时候应该加载多少？加载20条信息。
    }
    
    // 清理过期缓存（LRU）
    while (_lruQueue.size() > MAX_CACHED_CHATS) {
        int oldUid = _lruQueue.takeLast();
        _chatCache.remove(oldUid);
    }

}

void ChatSessionMgr::saveCurrentChat()
{
    if (_currentChatUid == -1) return;
    

    // 当前聊天的消息已经在内存中，无需额外保存
    // 因为 _msg_model 中的消息和 _chatCache 是引用同一份数据

}

void ChatSessionMgr::loadChatFromDB(int friendUid)
{
    // 从数据库加载最近50条消息
    auto messages = MsgDB::GetInstance()->loadMessages(friendUid, 50);
    

    // 加入缓存
    _chatCache[friendUid] = messages;
    
    // 通知UI更新
    emit sigChatLoaded(messages);

}

void ChatSessionMgr::addMessage(std::shared_ptr<MsgItem> msg)
{
    if (_currentChatUid == -1) return;
    

    // 添加到内存缓存
    _chatCache[_currentChatUid].append(msg);	//LRU缓存什么时候更新？每次调用switchChatdlg时就更新lru队列。保证内存中存储3个msg缓存
    
    // 异步写入数据库（不阻塞UI）
    QTimer::singleShot(0, [msg, this]() {
        MsgDB::GetInstance()->insertMessage(msg);
    });

}
```

ChatWidget 中的使用

```c++
// ChatWidget.h
class ChatWidget : public QWidget
{
    ...
private slots:
    // 聊天列表点击事件
    void onChatItemClicked(const QModelIndex& index);
    

    // 聊天加载完成
    void onChatLoaded(const QVector<std::shared_ptr<MsgItem>>& messages);

private:
    int _currentChatUid = -1;  // 当前聊天对象
};

// ChatWidget.cpp
void ChatWidget::UI_Init()
{
    ...
    // 连接聊天列表点击事件
    connect(ui->chat_listView, &QListView::clicked, this, &ChatWidget::onChatItemClicked);
    

    // 连接聊天管理器信号
    connect(ChatSessionMgr::GetInstance().get(), &ChatSessionMgr::sigChatLoaded,
            this, &ChatWidget::onChatLoaded);

}

void ChatWidget::onChatItemClicked(const QModelIndex& index)
{
    // 获取点击的好友UID
    int friendUid = _chat_model->data(index, ChatModel::UidRole).toInt();
    

    // 切换聊天对象
    ChatSessionMgr::GetInstance()->switchChat(friendUid);

}

void ChatWidget::onChatLoaded(const QVector<std::shared_ptr<MsgItem>>& messages)
{
    // 清空当前消息列表
    _msg_model->clear();
    

    // 加载新消息
    for (const auto& msg : messages) {
        _msg_model->addMessage(msg);
    }
    
    // 滚动到底部
    ui->msg_listView->scrollToBottom();

}
```

数据库设计优化

-- 聊天消息表（添加索引优化）
CREATE TABLE chat_messages (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    user_id INTEGER NOT NULL,
    friend_uid INTEGER NOT NULL,
    content TEXT NOT NULL,
    sender_uid INTEGER NOT NULL,
    sender_name TEXT,
    sender_avatar TEXT,
    msg_type INTEGER DEFAULT 0,
    is_self INTEGER NOT NULL,
    timestamp INTEGER NOT NULL,
    created_at DATETIME DEFAULT CURRENT_TIMESTAMP
);

-- 复合索引：快速查询某好友的消息
CREATE INDEX idx_chat ON chat_messages(user_id, friend_uid, timestamp DESC);

-- 复合索引：快速查询未读消息
CREATE INDEX idx_unread ON chat_messages(user_id, friend_uid, is_self);

-- 未读计数表（缓存未读数，避免 COUNT 查询）
CREATE TABLE unread_count (
    user_id INTEGER NOT NULL,
    friend_uid INTEGER NOT NULL,
    count INTEGER DEFAULT 0,
    PRIMARY KEY(user_id, friend_uid)
);
性能优化要点
策略	说明
限制内存缓存	只缓存最近20个活跃聊天，约 20×50×200B ≈ 200KB
数据库分页加载	每次只加载50条，滚动到底部时再加载更多
索引优化	(user_id, friend_uid, timestamp) 复合索引
异步写入	发送/接收消息后异步写DB，不阻塞UI
预加载	应用启动时预加载最近3个活跃聊天
总结
推荐方案：内存(LRU) + 数据库

无磁盘缓存文件：避免文件系统压力
内存占用可控：LRU策略限制缓存数量
数据库作为最终存储：所有消息持久化
切换聊天响应快：缓存命中率高（通常用户只活跃于少数聊天）
这种方案在上千个好友的场景下依然表现良好，因为：

用户同时活跃的聊天通常不会超过20个
数据库索引足够快（几毫秒级）
内存占用可控
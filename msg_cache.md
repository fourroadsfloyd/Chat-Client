实现总结
1. ChatSessionMgr (ChatSessionMgr.h / ChatSessionMgr.cpp)

单例会话管理器
├── 内存缓存: QMap<int, QVector<MsgItem>>
├── 当前会话: _current_friend_uid
└── 信号通知:
    ├── sig_messageReceived  - 收到消息
    ├── sig_messageSent      - 发送消息
    └── sig_sessionChanged   - 会话切换
2. ChatWidget 集成 (chatwidget.cpp:133-137)

// 连接信号
connect(ChatSessionMgr::GetInstance(), &ChatSessionMgr::sig_messageReceived,
        this, &ChatWidget::slot_messageReceived);
connect(ChatSessionMgr::GetInstance(), &ChatSessionMgr::sig_messageSent,
        this, &ChatWidget::slot_messageSent);
3. 使用方式
切换会话 (chatwidget.cpp:152)


ChatSessionMgr::GetInstance()->switchSession(friendUid, _msg_model);
添加消息


// 收到消息
ChatSessionMgr::GetInstance()->addMessage(friendUid, msg);

// 发送消息
ChatSessionMgr::GetInstance()->addSentMessage(friendUid, msg);
4. 消息流程

点击好友 → switchSession()
           ├─ 保存当前会话到缓存
           ├─ 清空 Model
           ├─ 加载新会话从缓存/数据库
           └─ 发出 sig_sessionChanged

收到消息 → addMessage()
           ├─ 添加到缓存
           └─ 发出 sig_messageReceived
              └→ ChatWidget 收到后判断是否当前会话
                  └→ 是则实时显示
消息现在在内存中缓存，切换会话时不会丢失。后续可添加 SQLite 数据库持久化。
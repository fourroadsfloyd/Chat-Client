#ifndef CHATSESSIONMGR_H
#define CHATSESSIONMGR_H

#include <QObject>
#include <QMap>
#include <QVector>
#include <memory>
#include "ui/chat/MsgListModel.h"
#include "data/UserStructInfo.h"
#include "tool/singleton.h"

// 聊天会话管理器 - 单例
// 负责管理多个好友的聊天消息缓存，实现切换会话时消息的保存与恢复
class ChatSessionMgr : public QObject, public Singleton<ChatSessionMgr> {
    Q_OBJECT
public:
    friend class Singleton<ChatSessionMgr>;

    // 切换聊天会话时调用
    // 保存当前会话，并加载新会话的消息到 model
    void switchSession(int friendUid, const QString& friendName, const QString& friendAvatar, MsgListModel* model);

    // 获取当前聊天好友的信息
    int currentFriendUid() const { return _current_friend_uid; }

    QString currentFriendName() const { return _current_friend_name; }

    QString currentFriendAvatar() const { return _current_friend_avatar; }

    // 收到新消息时调用 (对方发送的)
    void addMessage(int friendUid, std::shared_ptr<MsgModel::MsgItem> msg);

    // 发送消息时调用 (自己发送的)
    void addSentMessage(int friendUid, std::shared_ptr<MsgModel::MsgItem> msg);

    // 获取指定好友的所有消息
    const QVector<std::shared_ptr<MsgModel::MsgItem>>& getMessages(int friendUid) const;

    // 清空指定会话的消息
    void clearSession(int friendUid);

    // 清空所有会话
    void clearAllSessions();

signals:
    // 收到新消息时发出 (friendUid, msg)
    void sig_messageReceived(int friendUid, std::shared_ptr<MsgModel::MsgItem> msg);

    // 发送消息后发出 (friendUid, msg)
    void sig_messageSent(int friendUid, std::shared_ptr<MsgModel::MsgItem> msg);

    // 会话切换时发出 (oldFriendUid, newFriendUid)
    void sig_sessionChanged(int oldFriendUid, int newFriendUid);

private:
    ChatSessionMgr() : _current_friend_uid(0) {}

    // 清理超出数量限制的旧消息
    void trimSessionMessages(int friendUid);

private:
    // 每个会话在内存中保留的最大消息数量
    static constexpr int MAX_MSG_COUNT_PER_SESSION = 200;

    // 内存缓存: friendUid -> 消息列表
    QMap<int, QVector<std::shared_ptr<MsgModel::MsgItem>>> _cached_sessions;

    // 当前会话的好友信息
    int _current_friend_uid;
    QString _current_friend_name;
    QString _current_friend_avatar;

};

#endif // CHATSESSIONMGR_H

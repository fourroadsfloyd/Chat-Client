#include "ChatSessionMgr.h"
#include "data/usermgr.h"

void ChatSessionMgr::trimSessionMessages(int friendUid)
{
    if (!_cached_sessions.contains(friendUid)) {
        return;
    }

    auto& msgs = _cached_sessions[friendUid];
    if (msgs.size() > MAX_MSG_COUNT_PER_SESSION) {
        // 删除最旧的消息（前面的消息）
        int removeCount = msgs.size() - MAX_MSG_COUNT_PER_SESSION;
        msgs.erase(msgs.begin(), msgs.begin() + removeCount);
    }
}

void ChatSessionMgr::switchSession(int friendUid, const QString& friendName, const QString& friendAvatar, MsgListModel* model)
{
    if (!model) return;

    // 如果是同一个会话，不需要切换
    if (friendUid == _current_friend_uid) {
        return;
    }

    int oldFriendUid = _current_friend_uid;

    // 1. 保存当前会话的消息到缓存
    if (_current_friend_uid != 0) {
        QVector<std::shared_ptr<MsgModel::MsgItem>> currentMsgs;
        for (int i = 0; i < model->rowCount(); ++i) {
            currentMsgs.append(model->getMessage(i));
        }
        _cached_sessions[_current_friend_uid] = currentMsgs;
        // 保存后清理超出限制的消息
        trimSessionMessages(_current_friend_uid);
    }

    // 2. 清空当前 model
    model->clear();

    // 3. 加载新会话的消息
    if (_cached_sessions.contains(friendUid)) {
        // 从缓存加载
        const auto& msgs = _cached_sessions[friendUid];
        for (const auto& msg : msgs) {
            model->addMessage(msg);
        }
    } else {
        // 首次打开该会话，缓存中没有数据
        // TODO: 这里可以从数据库加载历史消息
        // 目前先创建空的消息列表
        _cached_sessions[friendUid] = QVector<std::shared_ptr<MsgModel::MsgItem>>();
    }

    // 4. 更新当前会话的好友信息
    _current_friend_uid = friendUid;
    _current_friend_name = friendName;
    _current_friend_avatar = friendAvatar;

    // 5. 发出会话切换信号
    emit sig_sessionChanged(oldFriendUid, friendUid);
}

void ChatSessionMgr::addMessage(int friendUid, std::shared_ptr<MsgModel::MsgItem> msg)
{
    if (!msg) return;

    // 添加到缓存
    _cached_sessions[friendUid].append(msg);

    // 清理超出限制的消息
    trimSessionMessages(friendUid);

    // 如果是当前会话，同时添加到 model (实时显示)
    if (friendUid == _current_friend_uid) {
        // 需要在 ChatWidget 中连接信号来处理实时显示
        // 或者通过信号槽机制通知 ChatWidget 更新
    }

    // 发出信号通知有新消息
    emit sig_messageReceived(friendUid, msg);

    // TODO: 同时保存到数据库
}

void ChatSessionMgr::addSentMessage(int friendUid, std::shared_ptr<MsgModel::MsgItem> msg)
{
    if (!msg) return;

    // 添加到缓存
    _cached_sessions[friendUid].append(msg);

    // 清理超出限制的消息
    trimSessionMessages(friendUid);

    // 如果是当前会话，同时添加到 model (实时显示)
    if (friendUid == _current_friend_uid)
    {
        // 需要在 ChatWidget 中连接信号来处理实时显示
        // 或者通过信号槽机制通知 ChatWidget 更新
    }

    // 发出信号通知消息已发送
    emit sig_messageSent(friendUid, msg);

    // TODO: 同时保存到数据库
}

const QVector<std::shared_ptr<MsgModel::MsgItem>>& ChatSessionMgr::getMessages(int friendUid) const
{
    static QVector<std::shared_ptr<MsgModel::MsgItem>> empty;
    if (_cached_sessions.contains(friendUid)) {
        return _cached_sessions[friendUid];
    }
    return empty;
}

void ChatSessionMgr::clearSession(int friendUid)
{
    _cached_sessions.remove(friendUid);

    // 如果清空的是当前会话，重置当前会话标记
    if (friendUid == _current_friend_uid) {
        _current_friend_uid = 0;
    }
}

void ChatSessionMgr::clearAllSessions()
{
    _cached_sessions.clear();
    _current_friend_uid = 0;
}

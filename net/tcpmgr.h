#ifndef TCPMGR_H
#define TCPMGR_H

#include "global.h"
#include "tool/singleton.h"
#include "data/UserStructInfo.h"
#include <functional>
#include <QObject>
#include <QTcpSocket>

class TcpMgr : public QObject, public Singleton<TcpMgr>, public std::enable_shared_from_this<TcpMgr>{
    Q_OBJECT

public:
    ~TcpMgr() = default;

    void CloseConnection();

private:
    friend class Singleton<TcpMgr>;
    TcpMgr();

    void initHandlers();

    void handleMsg(ReqId id, int len, QByteArray data);

private:
    QTcpSocket _socket;
    QString _host;
    uint16_t _port;
    QByteArray _buffer;
    bool _b_recv_pending;
    quint16 _message_id;
    quint16 _message_len;
    QMap<ReqId, std::function<void(ReqId id, int len, QByteArray data)>> _handlers;

signals:
    void sig_con_success(bool bsuccess);

    void sig_send_data(ReqId reqId, QByteArray dataBytes);

    void sig_swich_chatdlg();
    void sig_login_failed(int);
    void sig_user_search(std::shared_ptr<SearchInfo>);
    void sig_user_search_no_user();
    void sig_id_notify_add_friend_req(std::shared_ptr<AddFriendInfo> info);
    void sig_id_auth_friend_rsp(std::shared_ptr<ContactInfo> info);
    void sig_notify_auth_friend_req(std::shared_ptr<ContactInfo> info);
    void sig_chatlistview_addItem(std::shared_ptr<ChatModel::ChatItem> item);

    // 接收到聊天消息
    void sig_text_chat_msg(std::shared_ptr<MsgModel::MsgItem> msg, int fromUid);

    // void sig_notify_offline();
    // void sig_connection_closed();

public slots:
    void slot_tcp_connect(ServerInfo);

    void slot_send_data(ReqId reqId, QByteArray dataBytes);
};


#endif // TCPMGR_H

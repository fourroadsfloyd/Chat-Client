#include "tcpmgr.h"
#include "data/usermgr.h"
#include <QAbstractSocket>
#include <QJsonArray>

TcpMgr::TcpMgr():_host(""),_port(0),_b_recv_pending(false),_message_id(0),_message_len(0)
{
    //tcp层连接成功的回调
    QObject::connect(&_socket, &QTcpSocket::connected, [&]() {
        AsyncLog::getInstance().log(LogLevel::LogINFO, "Client and ChatServer linked successfully");
        // 连接建立后发送消息
        emit sig_con_success(true);
    });

    QObject::connect(&_socket, &QTcpSocket::readyRead, [&]() {

        AsyncLog::getInstance().log(LogLevel::LogINFO, "receive ChatServer rsp");

        // 当有数据可读时，读取所有数据
        // 读取所有数据并追加到缓冲区
        _buffer.append(_socket.readAll());

        QDataStream stream(&_buffer, QIODevice::ReadOnly);
        stream.setVersion(QDataStream::Qt_6_9);

        forever
        {
            //先解析头部
            if(!_b_recv_pending)
            {
                // 检查缓冲区中的数据是否足够解析出一个消息头（消息ID + 消息长度）
                if (_buffer.size() < static_cast<int>(sizeof(quint16) * 2)) {
                    return; // 数据不够，等待更多数据
                }

                // 预读取消息ID和消息长度，但不从缓冲区中移除
                stream >> _message_id >> _message_len;  //将_buffer中的数据传入_message_id和_message_len

                //将buffer 中的前四个字节移除
                _buffer = _buffer.mid(sizeof(quint16) * 2);

                // 输出读取的数据
                qDebug() << "Message ID:" << _message_id << ", Length:" << _message_len;

            }

            //buffer剩余长读是否满足消息体长度，不满足则退出继续等待接受
            if(_buffer.size() < _message_len){
                _b_recv_pending = true;
                return;
            }

            _b_recv_pending = false;
            // 读取消息体
            QByteArray messageBody = _buffer.mid(0, _message_len);
            qDebug() << "receive body msg is " << messageBody ;

            _buffer = _buffer.mid(_message_len);

            AsyncLog::getInstance().log(LogLevel::LogINFO, "invoke ChatServer rsp handler");

            handleMsg(ReqId(_message_id),_message_len, messageBody);
        }

    });

    QObject::connect(&_socket, QOverload<QAbstractSocket::SocketError>::of(&QTcpSocket::errorOccurred), [&](QAbstractSocket::SocketError socketError) {
      Q_UNUSED(socketError)
      qDebug() << "Error:" << _socket.errorString();
    });

    // 处理连接断开
    QObject::connect(&_socket, &QTcpSocket::disconnected, [&]() {
        qDebug() << "Disconnected from server.";
    });

    QObject::connect(this, &TcpMgr::sig_send_data, this, &TcpMgr::slot_send_data);

    initHandlers();
}

void TcpMgr::initHandlers()
{
    _handlers.insert(ID_CHAT_LOGIN_RSP, [this](ReqId id, int len, QByteArray data){
        Q_UNUSED(id);
        Q_UNUSED(len);

        //qDebug()<< "handle id is "<< id << " data is " << data;
        // 将QByteArray转换为QJsonDocument
        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);

        // 检查转换是否成功
        if(jsonDoc.isNull())
        {
            qDebug() << "Failed to create QJsonDocument.";
            return;
        }

        QJsonObject jsonObj = jsonDoc.object();

        if(!jsonObj.contains("error"))
        {
            int err = ErrorCodes::Error_Json;
            qDebug() << "Login Failed, err is Json Parse Err" << err ;
            emit sig_login_failed(err);
            return;
        }

        int err = jsonObj["error"].toInt();
        if(err != ErrorCodes::Success)
        {
            qDebug() << "Login Failed, err is " << err ;
            emit sig_login_failed(err);
            return;
        }

        //填充该用户的个人信息
        UserMgr::GetInstance()->SetToken(jsonObj["token"].toString());
        UserMgr::GetInstance()->SetUid(jsonObj["uid"].toInt());
        UserMgr::GetInstance()->SetName(jsonObj["name"].toString());
        UserMgr::GetInstance()->SetEmail(jsonObj["email"].toString());
        UserMgr::GetInstance()->SetAvatarPath(jsonObj["icon"].toString());

        //填充其他用户向该用户的好友申请列表
        QJsonArray applyArray = jsonObj["apply_list"].toArray();

        for (const QJsonValue& value : applyArray)
        {
            QJsonObject obj = value.toObject();

            auto info = std::make_shared<AddFriendInfo>(
                    obj["uid"].toInt(),
                    obj["icon"].toString(),
                    obj["name"].toString(),
                    obj["email"].toString(),
                    obj["status"].toInt()
                );

            UserMgr::GetInstance()->SetApplyList(info);
        }

        //填充该用户的联系人列表
        QJsonArray contactArray = jsonObj["friend_list"].toArray();

        for (const QJsonValue& value : contactArray)
        {
            QJsonObject obj = value.toObject();

            auto info = std::make_shared<ContactInfo>(
                    obj["uid"].toInt(),
                    obj["icon"].toString(),
                    obj["name"].toString(),
                    obj["email"].toString()
                );

            UserMgr::GetInstance()->SetContactList(info);
        }

        emit sig_swich_chatdlg();
    });

    _handlers.insert(ID_SEARCH_USER_RSP, [this](ReqId id, int len, QByteArray data){
        if(id != ReqId::ID_SEARCH_USER_RSP) return;
        //报文有问题
        if(len <= 0) return;

        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);

        // 检查转换是否成功
        if(jsonDoc.isNull()) return;

        QJsonObject jsonObj = jsonDoc.object();

        int err = jsonObj["error"].toInt();
        if(err == ErrorCodes::NoFindUser)
        {
            qDebug() << "Login Failed, err is " << err ;
            emit sig_user_search_no_user();
            return;
        }

        auto search_info = std::make_shared<SearchInfo>(jsonObj["uid"].toInt(), jsonObj["icon"].toString(),
                                                        jsonObj["name"].toString(), jsonObj["email"].toString());

        emit sig_user_search(search_info);
    });

    _handlers.insert(ID_ADD_FRIEND_RSP, [](ReqId id, int len, QByteArray data){
        //Q_UNUSED(this);

        if(id != ReqId::ID_ADD_FRIEND_RSP) return;
        //报文有问题
        if(len <= 0) return;

        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);

        // 检查转换是否成功
        if(jsonDoc.isNull()) return;

        QJsonObject jsonObj = jsonDoc.object();

        int err = jsonObj["error"].toInt();
        if(err != ErrorCodes::Success)
        {
            qDebug() << "AddFriend Failed, err is " << err;
        }

    });

    _handlers.insert(ID_NOTIFY_ADD_FRIEND_REQ, [this](ReqId id, int len, QByteArray data){
        if(id != ID_NOTIFY_ADD_FRIEND_REQ) return;
        if(len <= 0 ) return;

        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);

        if(jsonDoc.isNull()) return; // 检查转换是否成功

        QJsonObject obj = jsonDoc.object();

        auto info = std::make_shared<AddFriendInfo>(
                obj["uid"].toInt(),
                obj["icon"].toString(),
                obj["name"].toString(),
                obj["email"].toString(),
                obj["status"].toInt()
            );

        //qDebug() << "B id = " << UserMgr::GetInstance()->GetUid() << " receive A = " << info->_uid << " add friend request";

        UserMgr::GetInstance()->SetApplyList(info);

        //向model发送信号
        emit sig_id_notify_add_friend_req(info);
    });

    _handlers.insert(ID_AUTH_FRIEND_RSP, [this](ReqId id, int len, QByteArray data){

        if(id != ID_AUTH_FRIEND_RSP) return;    //报文有问题

        if(len <= 0) return;

        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);

        // 检查转换是否成功
        if(jsonDoc.isNull()) return;

        QJsonObject jsonObj = jsonDoc.object();

        int err = jsonObj["error"].toInt();
        if(err != ErrorCodes::Success)
        {
            qDebug() << "Auth apply Friend Failed, err is " << err;
        }

        auto info = std::make_shared<ContactInfo>(
                jsonObj["uid"].toInt(),
                jsonObj["icon"].toString(),
                jsonObj["name"].toString(),
                jsonObj["email"].toString()
            );

        UserMgr::GetInstance()->SetContactList(info);   //将通过好友申请的好友添加到联系人列表

        auto item = std::make_shared<ChatModel::ChatItem>(info->_name, "", QDateTime::currentDateTime(), info);

        //向model发送信号
        emit sig_id_auth_friend_rsp(info);

        emit sig_chatlistview_addItem(item);    //添加到ChatListView
    });

    _handlers.insert(ID_NOTIFY_AUTH_FRIEND_REQ, [this](ReqId id, int len, QByteArray data){
        if(id != ID_NOTIFY_AUTH_FRIEND_REQ) return;    //报文有问题

        if(len <= 0) return;

        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);

        // 检查转换是否成功
        if(jsonDoc.isNull()) return;

        QJsonObject jsonObj = jsonDoc.object();

        int err = jsonObj["error"].toInt();
        if(err != ErrorCodes::Success)
        {
            qDebug() << "Auth apply Friend Failed, err is " << err;
        }

        auto info = std::make_shared<ContactInfo>(
            jsonObj["uid"].toInt(),
            jsonObj["icon"].toString(),
            jsonObj["name"].toString(),
            jsonObj["email"].toString()
            );

        UserMgr::GetInstance()->SetContactList(info);   //将通过好友申请的好友添加到联系人列表

        auto item = std::make_shared<ChatModel::ChatItem>(info->_name, "", QDateTime::currentDateTime(), info);

        //向model发送信号
        emit sig_notify_auth_friend_req(info);

        emit sig_chatlistview_addItem(item);    //添加到ChatListView
    });

    _handlers.insert(ReqId::ID_NOTIFY_TEXT_CHAT_MSG_REQ, [this](ReqId id, int len, QByteArray data){
        if(id != ID_NOTIFY_TEXT_CHAT_MSG_REQ) return;    //报文有问题

        if(len <= 0) return;

        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);

        // 检查转换是否成功
        if(jsonDoc.isNull()) return;

        QJsonObject jsonObj = jsonDoc.object();

        int err = jsonObj["error"].toInt();
        if(err != ErrorCodes::Success)
        {
            qDebug() << "Msg receive Failed, err is " << err;
            return;
        }

        // 解析消息内容
        // 服务器返回格式: {"fromuid": 123, "msg_array": [{"content": "xxx", "msgid": "xxx"}]}
        int fromUid = jsonObj["from_uid"].toInt();
        QJsonArray msgArray = jsonObj["text_array"].toArray();

        // 获取发送者信息（从好友列表中查找）
        auto contact = UserMgr::GetInstance()->findUserByUid(fromUid);
        if (!contact) {
            qDebug() << "Cannot find contact with uid: " << fromUid;
            return;
        }

        QString senderName = contact->_name;
        QString senderAvatar = contact->_avatarpath;

        // 获取当前时间
        QString currentTime = QDateTime::currentDateTime().toString("hh:mm:ss");

        // 处理每条消息
        for (const auto& msgValue : msgArray) {
            QJsonObject msgObj = msgValue.toObject();
            QString content = msgObj["content"].toString();

            // 创建消息对象
            auto msgItem = std::make_shared<MsgModel::MsgItem>();
            msgItem->type = MsgModel::MsgItem::TextMessage;
            msgItem->content = content;
            msgItem->sender = senderName;
            msgItem->avatar = senderAvatar;
            msgItem->senderUid = fromUid;
            msgItem->time = currentTime;
            msgItem->isSelf = false;  // 接收的消息

            // 发射信号，通知 ChatWidget 或 ChatSessionMgr
            emit sig_text_chat_msg(msgItem, fromUid);
        }
    });
}

void TcpMgr::handleMsg(ReqId id, int len, QByteArray data)
{
    auto find_iter = _handlers.find(id);
    if(find_iter == _handlers.end())
    {
        qDebug()<< "not found id ["<< id << "] to handle";
        return ;
    }

    find_iter.value()(id,len,data);
}

void TcpMgr::slot_tcp_connect(ServerInfo si)
{
    //qDebug() << "slot_tcp_connect: host is" << si.Host << ", port is" << si.Port;
    // 尝试连接到服务器
    _host = si.Host;
    _port = static_cast<uint16_t>(si.Port.toUInt());
    _socket.connectToHost(si.Host, _port);
}

//LoginDialog发送登录信号，TcpMgr发送登录信息
void TcpMgr::slot_send_data(ReqId reqId, QByteArray dataBytes)
{
    AsyncLog::getInstance().log(LogLevel::LogINFO, "in slot_send_data");

    uint16_t id = reqId;

    // 计算长度（使用网络字节序转换）
    quint16 len = static_cast<quint16>(dataBytes.length());

    // 创建一个QByteArray用于存储要发送的所有数据
    QByteArray block;
    QDataStream stream(&block, QIODevice::WriteOnly);

    // 设置数据流使用网络字节序
    stream.setByteOrder(QDataStream::BigEndian);

    // 写入ID和长度
    stream << id << len;

    // 添加字符串数据
    block.append(dataBytes);

    // 发送数据
    _socket.write(block);

}




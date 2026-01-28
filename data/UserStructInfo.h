#ifndef USERSTRUCTINFO_H
#define USERSTRUCTINFO_H

#include <QIcon>
#include <QString>
#include <QDateTime>
#include <QPixmap>


//self
class RootUserInfo{
public:
    RootUserInfo(int uid, QString avatarpath, QString name, QString email)
        : _uid(uid), _avatarpath(avatarpath), _name(name), _email(email) {}

    int _uid;
    QString _avatarpath;
    QString _name;
    QString _email;
};

//搜索用户时，服务器提供的用户信息
class SearchInfo{
public:

    SearchInfo(int uid, QString avatarpath, QString name, QString email)
        : _uid(uid), _avatarpath(avatarpath), _name(name), _email(email) {}

    int _uid;
    QString _avatarpath;
    QString _name;
    QString _email;
};

//向自己发送好友申请的用户信息，以及该申请的状态
class AddFriendInfo{
public:
    AddFriendInfo(int uid, QString avatarpath, QString name, QString email, int status)
        : _uid(uid), _avatarpath(avatarpath), _name(name), _email(email), _status(status) {}

    int _uid;
    QString _avatarpath;
    QString _name;
    QString _email;
    int _status;    //0:未处理 1:处理
};

//用户联系人信息
class ContactInfo{
public:
    ContactInfo(int uid, QString avatarpath, QString name, QString email)
        : _uid(uid), _avatarpath(avatarpath), _name(name), _email(email) {}

    int _uid;
    QString _avatarpath;
    QString _name;
    QString _email;
};

//联系人列表model角色
namespace ContactModel{
    enum ContactRole {
        AvatarRole = Qt::UserRole + 1,
        NameRole,
        UidRole,
        EmailRole
    };
}

//搜索列表model角色
namespace SerachModel{
    enum SearchRole{
        AvatarRole = Qt::UserRole + 1,
        NameRole,
        UidRole,
        EmailRole
    };
}

//好友申请列表model角色
namespace AddFriendModel{
        enum AddFriendRole{
        AvatarRole = Qt::UserRole + 1,
        NameRole,
        EmailRole,
        UidRole,
        StatusRole
    };
}

//聊天列表model格式
namespace ChatModel {
    // 聊天项数据结构
    struct ChatItem {
        QString name;           // 联系人名字
        QString lastMessage;    // 最后一条消息
        QDateTime time;         // 消息时间
        int unreadCount;        // 未读消息数
        bool isMuted;           // 是否静音

        std::shared_ptr<ContactInfo> contactInfo = nullptr; //记录当前用户的信息

        ChatItem(const QString &name = "",
                 const QString &message = "",
                 const QDateTime &dt = QDateTime::currentDateTime(),
                 std::shared_ptr<ContactInfo> info = nullptr)
            : name(name)
            , lastMessage(message)
            , time(dt)
            , unreadCount(0)
            , isMuted(false)
            , contactInfo(info)
        {
        }
    };

    // 自定义数据角色
    enum ChatRole{
        AvatarRole,                     // 头像
        NameRole,                        // 名字
        MessageRole,                     // 消息
        TimeRole,                        // 时间
        UnreadCountRole,                 // 未读数
        IsMutedRole,                      // 是否静音

        UidRole,
        EmailRole
    };
}

//用户聊天model格式
namespace MsgModel{
    // 消息数据结构
    struct MsgItem {
        enum MsgType {
            TextMessage,
            ImageMessage,
            FileMessage,
            HybridMessage
        };

        MsgType type;
        QString content;      // 文本内容或文件路径
        QString sender;       // 发送者名称
        QString avatar;       // 发送者头像路径
        int senderUid;        // 发送者UID
        QString time;         // 时间
        bool isSelf;          // 是否是自己发送的

        MsgItem() : type(TextMessage), senderUid(0), isSelf(false) {}
    };

    // 消息角色定义
    enum MsgRole{
        TypeRole,
        ContentRole,
        SenderRole,
        AvatarRole,
        SenderUidRole,
        TimeRole,
        IsSelfRole
    };
}

struct MsgInfo {
    QString msgFlag;//"text,image,file"
    QString content;//表示文件和图像的url,文本信息
    QPixmap pixmap;//文件和图片的缩略图
};




#endif // USERSTRUCTINFO_H

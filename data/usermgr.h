#ifndef USERMGR_H
#define USERMGR_H
#include <QObject>
#include <memory>
#include "tool/singleton.h"
#include "data/UserStructInfo.h"

class UserMgr:public QObject,public Singleton<UserMgr>,
                public std::enable_shared_from_this<UserMgr> {
    Q_OBJECT
public:
    friend class Singleton<UserMgr>;
    ~UserMgr() = default;

    void SetToken(QString token);
    QString GetToken();
    void SetAvatarPath(QString path);
    QString GetAvatarPath();
    void SetName(QString name);
    QString GetName();
    void SetUid(int uid);
    int GetUid();
    void SetEmail(QString email);
    QString GetEmail();

    std::shared_ptr<RootUserInfo> GetRootUser();

    void SetContactList(std::shared_ptr<ContactInfo> info);
    const QVector<std::shared_ptr<ContactInfo>>& GetContactList();

    void SetApplyList(std::shared_ptr<AddFriendInfo> info);
    const QVector<std::shared_ptr<AddFriendInfo>>& GetApplyList();

    std::shared_ptr<ContactInfo> findUserByUid(int uid);
    std::shared_ptr<ContactInfo> findUserByEmail(const QString& email);
    std::shared_ptr<ContactInfo> findUserByName(const QString& name);

private:
    UserMgr();

    std::shared_ptr<RootUserInfo> rootUser;

    QString _token;

    QVector<std::shared_ptr<ContactInfo>> _ContactList; //用户的联系人列表

    QVector<std::shared_ptr<AddFriendInfo>> _ApplyList;  //向自己发送好友申请的用户列表

};

#endif // USERMGR_H

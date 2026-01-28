#include "usermgr.h"

UserMgr::UserMgr()
{
    this->_ApplyList.clear();
    this->_ContactList.clear();

    // 初始化 rootUser，避免空指针访问
    rootUser = std::make_shared<RootUserInfo>(0, "", "", "");
}

void UserMgr::SetToken(QString token)
{
    _token = token;
}

QString UserMgr::GetToken()
{
    return _token;
}

void UserMgr::SetAvatarPath(QString path)
{
    rootUser->_avatarpath = path;
}

QString UserMgr::GetAvatarPath()
{
    return rootUser->_avatarpath;
}

void UserMgr::SetName(QString name)
{
    rootUser->_name = name;
}

QString UserMgr::GetName()
{
    return rootUser->_name;
}

void UserMgr::SetUid(int uid)
{
    rootUser->_uid = uid;
}

int UserMgr::GetUid()
{
    return rootUser->_uid;
}

void UserMgr::SetEmail(QString email)
{
    rootUser->_email = email;
}

QString UserMgr::GetEmail()
{
    return rootUser->_email;
}

std::shared_ptr<RootUserInfo> UserMgr::GetRootUser()
{
    return rootUser;
}

void UserMgr::SetContactList(std::shared_ptr<ContactInfo> info)
{
    _ContactList.append(info);
}

const QVector<std::shared_ptr<ContactInfo>>& UserMgr::GetContactList()
{
    return _ContactList;
}

void UserMgr::SetApplyList(std::shared_ptr<AddFriendInfo> info)
{
    _ApplyList.append(info);
}

const QVector<std::shared_ptr<AddFriendInfo>>& UserMgr::GetApplyList()
{
    return _ApplyList;
}

std::shared_ptr<ContactInfo> UserMgr::findUserByUid(int uid)
{
    for (auto& contact : _ContactList) {
        if (contact->_uid == uid) {
            return contact;
        }
    }
    return nullptr;
}

std::shared_ptr<ContactInfo> UserMgr::findUserByEmail(const QString& email)
{
    for (auto& contact : _ContactList) {
        if (contact->_email == email) {
            return contact;
        }
    }
    return nullptr;
}

std::shared_ptr<ContactInfo> UserMgr::findUserByName(const QString& name)
{
    for (auto& contact : _ContactList) {
        if (contact->_name == name) {
            return contact;
        }
    }
    return nullptr;
}



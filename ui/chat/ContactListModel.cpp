#include "ContactListModel.h"
#include "data/usermgr.h"
#include "net/tcpmgr.h"

using namespace ContactModel;

ContactListModel::ContactListModel(QObject *parent)
    : QAbstractListModel(parent)
{
    connect(TcpMgr::GetInstance().get(), &TcpMgr::sig_id_auth_friend_rsp, this, [this](std::shared_ptr<ContactInfo> info){
        // qDebug() << "B will add A to ContactList";
        // qDebug() << "B id = " << UserMgr::GetInstance()->GetUid()
        //          << "A id = " << info->_uid;

        this->slot_id_auth_friend_rsp(info);
    });

    connect(TcpMgr::GetInstance().get(), &TcpMgr::sig_notify_auth_friend_req, this, [this](std::shared_ptr<ContactInfo> info){
        // qDebug() << "A will add B to ContactList";
        // qDebug() << "A id = " << UserMgr::GetInstance()->GetUid()
        //          << "B id = " << info->_uid;

        this->slot_id_auth_friend_rsp(info);
    });
}

int ContactListModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_list.count();
}

QVariant ContactListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_list.count())
        return QVariant();

    std::shared_ptr<ContactInfo> contact = m_list.at(index.row());

    switch (role) {
    case AvatarRole:
        return contact->_avatarpath;

    case NameRole:
        return contact->_name;

    case UidRole:
        return contact->_uid;

    case EmailRole:
        return contact->_email;

    default:
        return QVariant();
    }
}

void ContactListModel::addContact(std::shared_ptr<ContactInfo> contact)
{
    if (!contact) return;

    int row = m_list.count();
    beginInsertRows(QModelIndex(), row, row);
    m_list.append(contact);
    endInsertRows();
}

void ContactListModel::setContacts(const QList<std::shared_ptr<ContactInfo>>& contacts)
{
    beginResetModel();
    m_list = contacts;
    endResetModel();
}

void ContactListModel::clear()
{
    beginResetModel();
    m_list.clear();
    endResetModel();
}

void ContactListModel::sortByWord()
{
    beginResetModel();
    std::sort(m_list.begin(), m_list.end(),
              [](const std::shared_ptr<ContactInfo>& a, const std::shared_ptr<ContactInfo>& b) {
                  return a->_name < b->_name;  // 按名字字母排序
              });
    endResetModel();
}

std::shared_ptr<ContactInfo> ContactListModel::getContact(int row) const
{
    if (row < 0 || row >= m_list.count())
        return nullptr;

    return m_list.at(row);
}

void ContactListModel::slot_id_auth_friend_rsp(std::shared_ptr<ContactInfo> info)
{
    this->addContact(info);
    this->sortByWord();
}

#include "ApplyFriendListModel.h"
#include "net/tcpmgr.h"

using namespace AddFriendModel;

ApplyFriendListModel::ApplyFriendListModel(QObject *parent)
    : QAbstractListModel{parent}
{

    connect(TcpMgr::GetInstance().get(), &TcpMgr::sig_id_notify_add_friend_req, this , &ApplyFriendListModel::slot_id_notify_add_friend_req);

}

int ApplyFriendListModel::rowCount(const QModelIndex &parent) const
{
    if(parent.isValid())
    {
        return 0;
    }

    return m_list.count();
}

QVariant ApplyFriendListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_list.count())
        return QVariant();

    std::shared_ptr<AddFriendInfo> apply = m_list.at(index.row());

    switch (role) {
    case AvatarRole:
        return apply->_avatarpath;

    case NameRole:
        return apply->_name;

    case UidRole:
        return apply->_uid;

    case EmailRole:
        return apply->_email;

    case StatusRole:
        return apply->_status;

    default:
        return QVariant();
    }
}

void ApplyFriendListModel::addApplyFriend(std::shared_ptr<AddFriendInfo> apply)
{
    if (!apply) return;

    int row = m_list.count();
    beginInsertRows(QModelIndex(), row, row);
    m_list.append(apply);
    endInsertRows();
}

void ApplyFriendListModel::setApplyFriends(const QList<std::shared_ptr<AddFriendInfo> > &applys)
{
    beginResetModel();
    m_list = applys;
    endResetModel();

    //qDebug() << "m_list ="<< m_list.size();
}

void ApplyFriendListModel::sortByStatus()
{
    beginResetModel();
    std::sort(m_list.begin(), m_list.end(),
              [](const std::shared_ptr<AddFriendInfo>& a, const std::shared_ptr<AddFriendInfo>& b) {
                  return a->_status < b->_status;  // status=0，申请未处理的排前面
              });
    endResetModel();
}

void ApplyFriendListModel::updateStatus(const QModelIndex &index, int status)
{
    if (!index.isValid() || index.row() >= m_list.count()) {
        return;  // 无效索引，退出
    }

    // 更新状态
    m_list[index.row()]->_status = status;

    // 通知视图该项的数据改变（指定角色 StatusRole）
    emit dataChanged(index, index, {StatusRole});

    // 如果状态改变后需要重新排序（status=0 排前面），调用排序
    sortByStatus();
}

void ApplyFriendListModel::slot_id_notify_add_friend_req(std::shared_ptr<AddFriendInfo> info)
{
    this->addApplyFriend(info);
    this->sortByStatus();

}

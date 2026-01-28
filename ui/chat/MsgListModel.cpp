#include "MsgListModel.h"

using namespace MsgModel;

MsgListModel::MsgListModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int MsgListModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return m_messages.count();
}

QVariant MsgListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_messages.size())
        return QVariant();

    auto msg = m_messages[index.row()];

    switch (role) {
        case MsgRole::TypeRole:
            return static_cast<int>(msg->type);
        case MsgRole::ContentRole:
            return msg->content;
        case MsgRole::SenderRole:
            return msg->sender;
        case MsgRole::AvatarRole:
            return msg->avatar;
        case MsgRole::SenderUidRole:
            return msg->senderUid;
        case MsgRole::TimeRole:
            return msg->time;
        case MsgRole::IsSelfRole:
            return msg->isSelf;
        default:
            return QVariant();
    }
}

void MsgListModel::addMessage(std::shared_ptr<MsgItem> msg)
{
    if (!msg) return;

    beginInsertRows(QModelIndex(), m_messages.size(), m_messages.size());
    m_messages.append(msg);
    endInsertRows();
}

void MsgListModel::clear()
{
    beginResetModel();
    m_messages.clear();
    endResetModel();
}

std::shared_ptr<MsgModel::MsgItem> MsgListModel::getMessage(int index) const
{
    if (index < 0 || index >= m_messages.size())
        return nullptr;
    return m_messages[index];
}

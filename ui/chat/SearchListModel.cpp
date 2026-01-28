#include "SearchListModel.h"

using namespace SerachModel;

SearchListModel::SearchListModel(QObject *parent)
    : QAbstractListModel(parent)
{}

int SearchListModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_list.count();
}

QVariant SearchListModel::data(const QModelIndex &index, int role) const
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

void SearchListModel::addSearch(std::shared_ptr<ContactInfo> contact)
{
    if (!contact) return;

    int row = m_list.count();
    beginInsertRows(QModelIndex(), row, row);
    m_list.append(contact);
    endInsertRows();
}

void SearchListModel::clear()
{
    beginResetModel();
    m_list.clear();
    endResetModel();
}

void SearchListModel::sortByWord()
{
    beginResetModel();
    std::sort(m_list.begin(), m_list.end(),
              [](const std::shared_ptr<ContactInfo>& a, const std::shared_ptr<ContactInfo>& b) {
                  return a->_name < b->_name;  // 按名字字母排序
              });
    endResetModel();
}

std::shared_ptr<ContactInfo> SearchListModel::getContact(int row) const
{
    if (row < 0 || row >= m_list.count())
        return nullptr;

    return m_list.at(row);
}

int SearchListModel::getCount()
{
    return m_list.size();
}

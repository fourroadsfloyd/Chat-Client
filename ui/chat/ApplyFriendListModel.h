#ifndef APPLYFRIENDLISTMODEL_H
#define APPLYFRIENDLISTMODEL_H

#include "data/UserStructInfo.h"
#include <QAbstractListModel>

class ApplyFriendListModel : public QAbstractListModel {
    Q_OBJECT
public:
    explicit ApplyFriendListModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // 数据操作
    void addApplyFriend(std::shared_ptr<AddFriendInfo> apply);
    void setApplyFriends(const QList<std::shared_ptr<AddFriendInfo>>& applys);

    void sortByStatus();

    void updateStatus(const QModelIndex &index, int status);

private:
    QList<std::shared_ptr<AddFriendInfo>> m_list;

private slots:
    void slot_id_notify_add_friend_req(std::shared_ptr<AddFriendInfo> info);
};

#endif // APPLYFRIENDLISTMODEL_H

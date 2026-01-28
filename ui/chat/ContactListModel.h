#ifndef CONTACTLISTMODEL_H
#define CONTACTLISTMODEL_H

#include <QAbstractListModel>
#include <QList>
#include <QVariant>
#include "data/UserStructInfo.h"

class ContactListModel : public QAbstractListModel {
    Q_OBJECT

public:
    explicit ContactListModel(QObject *parent = nullptr);

    // QAbstractListModel 接口
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // 数据操作
    void addContact(std::shared_ptr<ContactInfo> contact);
    void setContacts(const QList<std::shared_ptr<ContactInfo>>& contacts);
    void clear();
    void sortByWord();

    // 查找
    std::shared_ptr<ContactInfo> getContact(int row) const;

private:
    QList<std::shared_ptr<ContactInfo>> m_list;

private slots:
    void slot_id_auth_friend_rsp(std::shared_ptr<ContactInfo> info);

};

#endif // CONTACTLISTMODEL_H

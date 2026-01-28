#ifndef SEARCHLISTMODEL_H
#define SEARCHLISTMODEL_H

#include <QAbstractListModel>
#include "data/UserStructInfo.h"

class SearchListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit SearchListModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void addSearch(std::shared_ptr<ContactInfo> contact);

    void clear();

    void sortByWord();

    std::shared_ptr<ContactInfo> getContact(int row) const;

    int getCount();

private:
    QList<std::shared_ptr<ContactInfo>> m_list;
};

#endif // SEARCHLISTMODEL_H

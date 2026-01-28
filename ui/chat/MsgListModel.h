#ifndef MSGLISTMODEL_H
#define MSGLISTMODEL_H

#include <QAbstractListModel>
#include <QVector>
#include <QSharedPointer>
#include "data/UserStructInfo.h"

class MsgListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit MsgListModel(QObject *parent = nullptr);

    // QAbstractListModel 接口
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // 添加消息到列表
    void addMessage(std::shared_ptr<MsgModel::MsgItem> msg);

    // 清空消息列表
    void clear();

    // 获取指定索引的消息
    std::shared_ptr<MsgModel::MsgItem> getMessage(int index) const;

private:
    QVector<std::shared_ptr<MsgModel::MsgItem>> m_messages;
};

#endif // MSGLISTMODEL_H

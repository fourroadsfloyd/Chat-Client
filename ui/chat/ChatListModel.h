#ifndef CHATLISTMODEL_H
#define CHATLISTMODEL_H

#include <QAbstractListModel>
#include <QPixmap>
#include <QDateTime>
#include <QList>

#include "data/UserStructInfo.h"

class ChatListModel : public QAbstractListModel {
public:
    ChatListModel(QObject* parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // 数据操作方法
    void addChatItem(std::shared_ptr<ChatModel::ChatItem> item);
    void addChatItem(const QString &name, const QString &message, const QString &time);

    // 查找指定 uid 的聊天项索引，返回 -1 表示未找到
    int findChatItemByUid(int uid) const;

    // 添加或获取聊天项（如果已存在则不添加），返回索引
    int getOrAddChatItem(int uid, const QString &name, const QString &avatar, const QString &email);

    void sortByTime();

    QString formatTime(const QDateTime &time) const;

private:
    QList<std::shared_ptr<ChatModel::ChatItem>> m_chatItems;    //model中存在多少个ChatItem对象

};

#endif // CHATLISTMODEL_H

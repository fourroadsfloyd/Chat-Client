#ifndef APPLYFRIENDITEMDELEGATE_H
#define APPLYFRIENDITEMDELEGATE_H

#include "data/UserStructInfo.h"
#include <QStyledItemDelegate>
#include <QFont>
#include <QIcon>
#include <QHash>

class ApplyFriendItemDelegate : public QStyledItemDelegate{
    Q_OBJECT
public:
    explicit ApplyFriendItemDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    QRect buttonRect(const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:
    QFont m_nameFont;
    QIcon m_defaultAvatarIcon;

    mutable QHash<QString, QIcon> m_iconCache;  // 头像图标缓存

    int m_iconSize = 40;                // 头像尺寸
    int m_spacing = 12;                   // 间距
    int m_padding = 10;                   // 边距

signals:

    void sig_agree_apply(std::shared_ptr<AddFriendInfo> info);
};

#endif // APPLYFRIENDITEMDELEGATE_H

#ifndef CONTACTITEMDELEGATE_H
#define CONTACTITEMDELEGATE_H

#include <QStyledItemDelegate>
#include <QIcon>
#include <QFont>
#include <QHash>

class ContactItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit ContactItemDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;

    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index) const override;

private:
    QIcon m_defaultAvatarIcon;           // 默认头像图标
    QFont m_nameFont;                     // 预创建的名字字体
    mutable QHash<QString, QIcon> m_iconCache;  // 头像图标缓存

    static constexpr int m_avatarSize = 40;                // 头像尺寸
    static constexpr int m_spacing = 12;                   // 间距
    static constexpr int m_padding = 10;                   // 边距
};

#endif // CONTACTITEMDELEGATE_H

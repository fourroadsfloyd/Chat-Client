#ifndef SEARCHITEMDELEGATE_H
#define SEARCHITEMDELEGATE_H

#include <QStyledItemDelegate>

class SearchItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit SearchItemDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;

    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index) const override;

private:
    QIcon m_defaultAvatarIcon;           // 默认头像图标
    QFont m_nameFont;                     // 预创建的名字字体
    mutable QHash<QString, QIcon> m_iconCache;  // 头像图标缓存

    int m_avatarSize = 40;                // 头像尺寸
    int m_spacing = 12;                   // 间距
    int m_padding = 10;                   // 边距
};
#endif // SEARCHITEMDELEGATE_H

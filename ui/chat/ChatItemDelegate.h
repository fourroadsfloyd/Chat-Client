#ifndef CHATITEMDELEGATE_H
#define CHATITEMDELEGATE_H

#include <QStyledItemDelegate>
#include <QFont>
#include <QFontMetrics>
#include <QHash>
#include <QPixmap>

class ChatItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit ChatItemDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;

    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index) const override;

protected:
    // 绘制相关的方法（允许子类访问）
    void paintBackground(QPainter *painter, const QStyleOptionViewItem &option) const;
    void paintAvatar(QPainter *painter, const QRect &iconRect, const QString &icon) const;
    void paintName(QPainter *painter, const QRect &nameRect, const QString &name) const;
    void paintMessage(QPainter *painter, const QRect &messageRect, const QString &message) const;
    void paintTime(QPainter *painter, const QRect &timeRect, const QString &time) const;
    void paintBadge(QPainter *painter, const QRect &badgeRect, int unreadCount) const;
    void paintMuteIcon(QPainter *painter, const QRect &muteRect) const;
    void paintDivider(QPainter *painter, const QRect &rect, int textLeft) const;


protected:

    // 预设字体
    QFont m_nameFont;
    QFont m_messageFont;
    QFont m_timeFont;
    QFont m_badgeFont;

    // 预设 FontMetrics
    QFontMetrics m_nameFontMetrics;
    QFontMetrics m_messageFontMetrics;
    QFontMetrics m_timeFontMetrics;
    QFontMetrics m_badgeFontMetrics;

    // 头像缓存（cacheKey -> 处理好的圆角头像）
    mutable QHash<QString, QIcon> m_iconCache;

    // 布局参数（统一定义）
    static constexpr int PADDING = 10;          //编译期常量，编译期计算，const是运行期常量
    static constexpr int AVATAR_SIZE = 50;
    static constexpr int SPACING = 10;
    static constexpr int ITEM_HEIGHT = 70;
    static constexpr int BADGE_SIZE = 20;
    static constexpr int MUTE_ICON_SIZE = 16;
    static constexpr int AVATAR_RADIUS = 5;

};

#endif // CHATITEMDELEGATE_H

#ifndef MSGITEMDELEGATE_H
#define MSGITEMDELEGATE_H

#include <QStyledItemDelegate>
#include <QFont>
#include <QFontMetricsF>
#include <QHash>
#include <QIcon>

class MsgItemDelegate : public QStyledItemDelegate {
    Q_OBJECT
public:
    explicit MsgItemDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;

    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index) const override;

protected:
    // 绘制相关方法
    void paintSelfMessage(QPainter *painter, const QRect &rect,
                         const QString &avatar, const QString &sender,
                         const QString &content, const QString &time) const;
    void paintOtherMessage(QPainter *painter, const QRect &rect,
                          const QString &avatar, const QString &sender,
                          const QString &content, const QString &time) const;
    void paintAvatar(QPainter *painter, const QRect &avatarRect, const QString &avatar) const;

protected:
    // 字体
    QFont m_contentFont;
    QFont m_timeFont;
    QFont m_senderFont;

    // FontMetrics
    QFontMetricsF m_contentFontMetrics;
    QFontMetricsF m_timeFontMetrics;
    QFontMetricsF m_senderFontMetrics;

    // 头像缓存
    mutable QHash<QString, QIcon> m_iconCache;

    // 布局参数
    static constexpr int PADDING = 15;
    static constexpr int MAX_WIDTH = 250;
    static constexpr int BUBBLE_RADIUS = 8;
    static constexpr int SPACING = 5;
    static constexpr int AVATAR_SIZE = 40;
    static constexpr int SCROLLBAR_WIDTH = 12;  // 预留滚动条宽度
};

#endif // MSGITEMDELEGATE_H

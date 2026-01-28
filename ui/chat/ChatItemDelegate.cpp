#include "ChatItemDelegate.h"
#include "data/UserStructInfo.h"
#include <QPainter>
#include <QPainterPath>

using namespace ChatModel;

ChatItemDelegate::ChatItemDelegate(QObject *parent)
    : QStyledItemDelegate(parent),
    m_nameFontMetrics(m_nameFont),
    m_messageFontMetrics(m_messageFont),
    m_timeFontMetrics(m_timeFont),
    m_badgeFontMetrics(m_badgeFont)
{
    // 初始化字体
    m_nameFont.setPointSize(11);
    m_nameFont.setBold(true);

    m_messageFont.setPointSize(9);
    m_messageFont.setBold(false);

    m_timeFont.setPointSize(8);

    m_badgeFont.setPointSize(8);
    m_badgeFont.setBold(true);


    // 更新 FontMetrics（因为字体已改）
    m_nameFontMetrics = QFontMetrics(m_nameFont);
    m_messageFontMetrics = QFontMetrics(m_messageFont);
    m_timeFontMetrics = QFontMetrics(m_timeFont);
    m_badgeFontMetrics = QFontMetrics(m_badgeFont);
}

void ChatItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                             const QModelIndex &index) const
{
    if (!index.isValid())
        return;

    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);

    // 1. 绘制背景
    paintBackground(painter, option);

    // 2. 从模型获取数据
    QString name = index.data(ChatRole::NameRole).toString();
    QString message = index.data(ChatRole::MessageRole).toString();
    QString time = index.data(ChatRole::TimeRole).toString();
    QString avatarPath = index.data(ChatRole::AvatarRole).toString();
    int unreadCount = index.data(ChatRole::UnreadCountRole).toInt();
    bool isMuted = index.data(ChatRole::IsMutedRole).toBool();

    QRect rect = option.rect;

    // 3. 计算布局关键坐标（只计算依赖窗口宽度的部分）
    const int avatarLeft = rect.left() + PADDING;
    const int avatarTop = rect.top() + PADDING;
    const int textLeft = avatarLeft + AVATAR_SIZE + SPACING;
    const int textRight = rect.right() - PADDING - 80; // 为时间和未读数预留
    const int rightAreaStart = textRight + SPACING;
    const int verticalCenter = rect.top() + rect.height() / 2;

    // 构建各区域矩形（复用计算好的坐标）
    QRect avatarRect(avatarLeft, avatarTop, AVATAR_SIZE, AVATAR_SIZE);
    QRect nameRect(textLeft, avatarTop, textRight - textLeft, 20);
    QRect messageRect(textLeft, avatarTop + 25, textRight - textLeft, 20);
    QRect timeRect(rightAreaStart, avatarTop, rect.right() - rightAreaStart - PADDING, 20);
    QRect badgeRect(rect.right() - PADDING - BADGE_SIZE, verticalCenter - BADGE_SIZE / 2, BADGE_SIZE, BADGE_SIZE);
    QRect muteRect(rect.right() - PADDING - MUTE_ICON_SIZE, verticalCenter - MUTE_ICON_SIZE / 2, MUTE_ICON_SIZE, MUTE_ICON_SIZE);

    // 4. 绘制各元素
    paintAvatar(painter, avatarRect, avatarPath);
    paintName(painter, nameRect, name);
    paintMessage(painter, messageRect, message);
    paintTime(painter, timeRect, time);

    if (unreadCount > 0 && !isMuted) {
        paintBadge(painter, badgeRect, unreadCount);
    }

    if (isMuted) {
        paintMuteIcon(painter, muteRect);
    }

    paintDivider(painter, rect, textLeft);

    painter->restore();
}

QSize ChatItemDelegate::sizeHint(const QStyleOptionViewItem &option,
                                 const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);
    return QSize(option.rect.width(), ITEM_HEIGHT);
}

// ==================== 私有绘制方法实现 ====================

void ChatItemDelegate::paintBackground(QPainter *painter, const QStyleOptionViewItem &option) const
{
    QColor bgColor;
    if (option.state & QStyle::State_Selected) {
        bgColor = QColor(230, 230, 230);
    } else if (option.state & QStyle::State_MouseOver) {
        bgColor = QColor(245, 245, 245);
    } else {
        bgColor = Qt::white;
    }
    painter->fillRect(option.rect, bgColor);
}

void ChatItemDelegate::paintAvatar(QPainter *painter, const QRect &iconRect, const QString &icon) const
{
    // 绘制头像（使用缓存）
    QIcon avatarIcon;
    if (!icon.isEmpty())
    {
        // 从缓存获取
        avatarIcon = m_iconCache.value(icon);
        if (avatarIcon.isNull()) 
        {
            // 缓存未命中，创建并缓存
            avatarIcon = QIcon(icon);
            if (!avatarIcon.isNull())
            {
                m_iconCache[icon] = avatarIcon;
            }
        }
    }

    avatarIcon.paint(painter, iconRect);
}

void ChatItemDelegate::paintName(QPainter *painter, const QRect &nameRect, const QString &name) const
{
    painter->setPen(Qt::black);
    painter->setFont(m_nameFont);
    QString elidedName = m_nameFontMetrics.elidedText(name, Qt::ElideRight, nameRect.width());
    painter->drawText(nameRect, Qt::AlignLeft | Qt::AlignVCenter, elidedName);
}

void ChatItemDelegate::paintMessage(QPainter *painter, const QRect &messageRect, const QString &message) const
{
    painter->setPen(QColor(120, 120, 120));
    painter->setFont(m_messageFont);
    QString elidedMessage = m_messageFontMetrics.elidedText(message, Qt::ElideRight, messageRect.width());
    painter->drawText(messageRect, Qt::AlignLeft | Qt::AlignVCenter, elidedMessage);
}

void ChatItemDelegate::paintTime(QPainter *painter, const QRect &timeRect, const QString &time) const
{
    painter->setPen(QColor(150, 150, 150));
    painter->setFont(m_timeFont);
    painter->drawText(timeRect, Qt::AlignRight | Qt::AlignVCenter, time);
}

void ChatItemDelegate::paintBadge(QPainter *painter, const QRect &badgeRect, int unreadCount) const
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(QColor(255, 69, 58)); // 红色
    painter->drawEllipse(badgeRect);

    painter->setPen(Qt::white);
    painter->setFont(m_badgeFont);
    QString countText = unreadCount > 99 ? "99+" : QString::number(unreadCount);
    painter->drawText(badgeRect, Qt::AlignCenter, countText);
}

void ChatItemDelegate::paintMuteIcon(QPainter *painter, const QRect &muteRect) const
{
    painter->setPen(QColor(150, 150, 150));
    painter->setFont(m_timeFont);
    painter->drawText(muteRect, Qt::AlignCenter, "🔇");
}

void ChatItemDelegate::paintDivider(QPainter *painter, const QRect &rect, int textLeft) const
{
    painter->setPen(QColor(230, 230, 230));
    painter->drawLine(rect.left() + textLeft, rect.bottom(),
                      rect.right(), rect.bottom());
}



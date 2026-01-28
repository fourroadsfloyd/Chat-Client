#include "MsgItemDelegate.h"
#include "data/UserStructInfo.h"
#include <QPainter>
#include <QPainterPath>
#include <QTextDocument>
#include <QTextOption>
#include <QAbstractTextDocumentLayout>

using namespace MsgModel;

MsgItemDelegate::MsgItemDelegate(QObject *parent)
    : QStyledItemDelegate(parent),
      m_contentFontMetrics(m_contentFont),
      m_timeFontMetrics(m_timeFont),
      m_senderFontMetrics(m_senderFont)
{
    // 初始化字体
    m_contentFont.setPointSize(10);
    m_senderFont.setPointSize(9);
    m_senderFont.setBold(true);
    m_timeFont.setPointSize(8);

    // 更新 FontMetrics
    m_contentFontMetrics = QFontMetricsF(m_contentFont);
    m_timeFontMetrics = QFontMetricsF(m_timeFont);
    m_senderFontMetrics = QFontMetricsF(m_senderFont);
}

void MsgItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                             const QModelIndex &index) const
{
    if (!index.isValid())
        return;

    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);

    // 绘制背景
    painter->fillRect(option.rect, QColor(240, 240, 240));

    // 获取数据
    QString content = index.data(MsgRole::ContentRole).toString();
    QString sender = index.data(MsgRole::SenderRole).toString();
    QString avatar = index.data(MsgRole::AvatarRole).toString();
    QString time = index.data(MsgRole::TimeRole).toString();
    bool isSelf = index.data(MsgRole::IsSelfRole).toBool();

    if (isSelf)
    {
        paintSelfMessage(painter, option.rect, avatar, sender, content, time);
    }
    else
    {
        paintOtherMessage(painter, option.rect, avatar, sender, content, time);
    }

    painter->restore();
}

QSize MsgItemDelegate::sizeHint(const QStyleOptionViewItem &option,
                                 const QModelIndex &index) const
{
    QString content = index.data(MsgRole::ContentRole).toString();
    bool isSelf = index.data(MsgRole::IsSelfRole).toBool();
    std::ignore = isSelf;

    // ScrollBarAlwaysOn 时，viewport 宽度已经是减去滚动条后的宽度
    // 直接使用 option.rect.width() 作为可用宽度

    // 使用 QFontMetrics 计算文本实际宽度（动态）
    int textWidth = this->m_contentFontMetrics.horizontalAdvance(content);
    int actualBubbleWidth = qMin(option.rect.width() / 2, textWidth) + PADDING * 2;

    // 创建 QTextDocument 用于计算高度
    QTextDocument doc;
    doc.setDefaultFont(m_contentFont);
    doc.setPlainText(content);
    doc.setTextWidth(actualBubbleWidth - PADDING * 2);
    int contentHeight = qCeil(doc.documentLayout()->documentSize().height()) + PADDING * 2;

    int avatarHeight = AVATAR_SIZE;
    int senderHeight = m_senderFontMetrics.height() + SPACING; // 发送方和接收方都有名字
    int timeHeight = m_timeFontMetrics.height() + SPACING;

    int totalHeight = senderHeight + contentHeight + timeHeight;
    return QSize(option.rect.width(), qMax(avatarHeight, totalHeight) + PADDING * 2);
}

void MsgItemDelegate::paintSelfMessage(QPainter *painter, const QRect &rect,
                                       const QString &avatar, const QString &sender,
                                       const QString &content, const QString &time) const
{
    // ScrollBarAlwaysOn 时，viewport 宽度已经是减去滚动条后的宽度
    // 直接使用 rect.width() 作为可用宽度

    int right = rect.right() - PADDING;
    int top = rect.top() + PADDING;

    // 绘制自己的头像（右侧）
    QRect avatarRect(right - AVATAR_SIZE, top, AVATAR_SIZE, AVATAR_SIZE);
    paintAvatar(painter, avatarRect, avatar);

    // 计算文本实际需要的气泡宽度（动态）
    // 使用 QFontMetrics 获取文本实际宽度（不换行时的自然宽度）
    int textWidth = this->m_contentFontMetrics.horizontalAdvance(content);
    int actualBubbleWidth = qMin(rect.width() / 2, textWidth) + PADDING * 2;

    // 创建 QTextDocument 用于绘制（需要知道实际宽度来计算高度）
    QTextDocument doc;
    doc.setDefaultFont(m_contentFont);
    doc.setPlainText(content);

    // 设置文本宽度用于布局（计算高度）
    doc.setTextWidth(actualBubbleWidth);
    int bubbleHeight = qCeil(doc.documentLayout()->documentSize().height()) + PADDING * 2;

    // 绘制发送者名称（在头像左侧，右对齐）
    int senderRight = avatarRect.left() - SPACING;
    int senderWidth = this->m_senderFontMetrics.horizontalAdvance(sender);
    QRect senderRect(senderRight - senderWidth, top,
                     senderWidth, m_senderFontMetrics.height());
    painter->setPen(QColor(100, 100, 100));
    painter->setFont(m_senderFont);
    painter->drawText(senderRect, Qt::AlignRight | Qt::AlignVCenter, sender);

    // 绘制气泡（蓝色，自己的消息）
    int bubbleRight = senderRight;
    int bubbleTop = senderRect.bottom() + SPACING;
    QRect bubbleRect(bubbleRight - actualBubbleWidth, bubbleTop, actualBubbleWidth, bubbleHeight);

    QPainterPath path;
    path.addRoundedRect(bubbleRect, BUBBLE_RADIUS, BUBBLE_RADIUS);
    painter->fillPath(path, QColor(135, 206, 250));

    // 绘制文本
    painter->translate(bubbleRect.left() + SPACING, bubbleRect.top() + PADDING);
    doc.drawContents(painter);
    painter->translate(-bubbleRect.left() - SPACING, -bubbleRect.top() - PADDING);

    // 绘制时间（在气泡下方，右对齐）
    QRect timeRect(bubbleRight - actualBubbleWidth, bubbleRect.bottom() + SPACING,
                   actualBubbleWidth, m_timeFontMetrics.height());
    painter->setPen(QColor(150, 150, 150));
    painter->setFont(m_timeFont);
    painter->drawText(timeRect, Qt::AlignRight | Qt::AlignTop, time);
}

void MsgItemDelegate::paintOtherMessage(QPainter *painter, const QRect &rect,
                                        const QString &avatar, const QString &sender,
                                        const QString &content, const QString &time) const
{
    // ScrollBarAlwaysOn 时，viewport 宽度已经是减去滚动条后的宽度
    // 直接使用 rect.width() 作为可用宽度

    int left = rect.left() + PADDING;
    int top = rect.top() + PADDING;

    // 绘制对方头像（左侧）
    QRect avatarRect(left, top, AVATAR_SIZE, AVATAR_SIZE);
    paintAvatar(painter, avatarRect, avatar);

    // 绘制发送者名称（在头像右侧）
    QRect senderRect(left + AVATAR_SIZE + SPACING, top,
                     rect.width() - AVATAR_SIZE - SPACING * 2, m_senderFontMetrics.height());
    painter->setPen(QColor(100, 100, 100));
    painter->setFont(m_senderFont);
    painter->drawText(senderRect, Qt::AlignLeft | Qt::AlignVCenter, sender);

    // 计算文本实际需要的气泡宽度（动态）
    // 使用 QFontMetrics 获取文本实际宽度（不换行时的自然宽度）
    int textWidth = this->m_contentFontMetrics.horizontalAdvance(content);
    int actualBubbleWidth = qMin(rect.width() / 2, textWidth) + PADDING * 2;

    // 创建 QTextDocument 用于绘制（需要知道实际宽度来计算高度）
    QTextDocument doc;
    doc.setDefaultFont(m_contentFont);
    doc.setPlainText(content);

    // 重新设置文本宽度为实际宽度
    doc.setTextWidth(actualBubbleWidth);
    int bubbleHeight = qCeil(doc.documentLayout()->documentSize().height()) + PADDING * 2;

    // 绘制气泡（白色，对方的消息）
    int bubbleLeft = left + AVATAR_SIZE + SPACING;
    int bubbleTop = senderRect.bottom() + SPACING;
    QRect bubbleRect(bubbleLeft, bubbleTop, actualBubbleWidth, bubbleHeight);

    QPainterPath path;
    path.addRoundedRect(bubbleRect, BUBBLE_RADIUS, BUBBLE_RADIUS);
    painter->fillPath(path, Qt::white);

    // 绘制文本
    painter->translate(bubbleRect.left() + SPACING, bubbleRect.top() + PADDING);
    doc.drawContents(painter);
    painter->translate(-bubbleRect.left() - SPACING, -bubbleRect.top() - PADDING);

    // 绘制时间（在气泡下方，左对齐）
    QRect timeRect(bubbleLeft, bubbleRect.bottom() + SPACING,
                   actualBubbleWidth, m_timeFontMetrics.height());
    painter->setPen(QColor(150, 150, 150));
    painter->setFont(m_timeFont);
    painter->drawText(timeRect, Qt::AlignLeft | Qt::AlignTop, time);
}

void MsgItemDelegate::paintAvatar(QPainter *painter, const QRect &avatarRect, const QString &avatar) const
{
    QIcon avatarIcon;
    if (!avatar.isEmpty())
    {
        // 从缓存获取
        avatarIcon = m_iconCache.value(avatar);
        if (avatarIcon.isNull())
        {
            // 缓存未命中，创建并缓存
            avatarIcon = QIcon(avatar);
            if (!avatarIcon.isNull())
            {
                m_iconCache[avatar] = avatarIcon;
            }
        }
    }

    // 绘制头像
    if (!avatarIcon.isNull())
    {
        // 绘制圆角矩形头像
        QPainterPath path;
        path.addRoundedRect(avatarRect, AVATAR_SIZE / 4, AVATAR_SIZE / 4);
        painter->setClipPath(path);
        avatarIcon.paint(painter, avatarRect);
        painter->setClipping(false);
    }
    else
    {
        // 没有头像时绘制默认圆角矩形头像
        QPainterPath path;
        path.addRoundedRect(avatarRect, AVATAR_SIZE / 4, AVATAR_SIZE / 4);
        painter->fillPath(path, QColor(200, 200, 200));
    }
}

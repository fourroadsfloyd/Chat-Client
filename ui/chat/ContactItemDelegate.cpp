#include "ContactItemDelegate.h"
#include "data/UserStructInfo.h"
#include <QPainter>
#include <QPixmap>

using namespace ContactModel;

ContactItemDelegate::ContactItemDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
    // 预创建字体对象
    m_nameFont.setPointSize(11);

    // 创建默认头像图标
    QPixmap defaultPixmap(m_avatarSize, m_avatarSize);
    defaultPixmap.fill(QColor(100, 149, 237));  // 矢车菊蓝

    QPainter painter(&defaultPixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::white);
    QFont font;
    font.setPointSize(14);
    font.setBold(true);
    painter.setFont(font);
    painter.drawText(defaultPixmap.rect(), Qt::AlignCenter, "?");
    painter.end();

    m_defaultAvatarIcon = QIcon(defaultPixmap);
}

void ContactItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                                 const QModelIndex &index) const
{
    if (!index.isValid())
        return;

    painter->save();

    QRect rect = option.rect;

    // 绘制背景
    if (option.state & QStyle::State_MouseOver)
    {
        painter->fillRect(rect, QColor(230,230,230));  // 悬停时用浅灰色
    }

    // 获取数据
    QString name = index.data(ContactRole::NameRole).toString();
    QString avatarPath = index.data(ContactRole::AvatarRole).toString();

    // 布局
    int avatarX = rect.left() + m_padding;
    int avatarY = rect.top() + (rect.height() - m_avatarSize) / 2;
    QRect avatarRect(avatarX, avatarY, m_avatarSize, m_avatarSize);

    int textX = avatarX + m_avatarSize + m_spacing;
    QRect textRect(textX, rect.top(), rect.width() - textX - m_padding, rect.height());

    // 绘制头像（使用缓存）
    QIcon avatarIcon;
    if (!avatarPath.isEmpty())
    {
        // 从缓存获取
        avatarIcon = m_iconCache.value(avatarPath);
        if (avatarIcon.isNull())
        {
            // 缓存未命中，创建并缓存
            avatarIcon = QIcon(avatarPath);
            if (!avatarIcon.isNull())
            {
                m_iconCache[avatarPath] = avatarIcon;
            }
        }
    }

    if (avatarIcon.isNull())
    {
        avatarIcon = m_defaultAvatarIcon;
    }
    avatarIcon.paint(painter, avatarRect);

    // 绘制名字（使用预创建的字体）
    painter->setPen(option.state & QStyle::State_MouseOver ? Qt::black : Qt::black);
    painter->setFont(m_nameFont);
    painter->drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, name);

    // 绘制分隔线
    painter->setPen(QColor(230, 230, 230));
    painter->drawLine(rect.left() + m_padding, rect.bottom() - 1,
                      rect.right() - m_padding, rect.bottom() - 1);

    painter->restore();
}

QSize ContactItemDelegate::sizeHint(const QStyleOptionViewItem &option,
                                     const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);
    return QSize(200, 60);
}

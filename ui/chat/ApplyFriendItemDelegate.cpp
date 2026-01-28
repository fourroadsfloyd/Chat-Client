#include "ApplyFriendItemDelegate.h"
#include "data/UserStructInfo.h"
#include <QPainter>
#include <QRect>


using namespace AddFriendModel;

ApplyFriendItemDelegate::ApplyFriendItemDelegate(QObject* parent) : QStyledItemDelegate(parent)
{
    // 预创建字体对象
    m_nameFont.setPointSize(11);

    // 创建默认头像图标
    QPixmap defaultPixmap(m_iconSize, m_iconSize);
    defaultPixmap.fill(QColor(100, 149, 237));  // 矢车菊蓝

    QPainter painter(&defaultPixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::black);
    QFont font;
    font.setPointSize(15);
    font.setBold(true);
    painter.setFont(font);
    painter.drawText(defaultPixmap.rect(), Qt::AlignCenter, "?");
    painter.end();

    m_defaultAvatarIcon = QIcon(defaultPixmap);
}

void ApplyFriendItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(!index.isValid())
    {
        return;
    }

    painter->save();    //保存画笔

    QRect rect = option.rect;

    //绘制背景
    if (option.state & QStyle::State_MouseOver)
    {
        painter->fillRect(rect, QColor(230,230,230));  // 悬停时用浅灰色
    }

    QString name = index.data(AddFriendRole::NameRole).toString();
    QString icon = index.data(AddFriendRole::AvatarRole).toString();
    QString uid = index.data(AddFriendRole::UidRole).toString();
    QString email = index.data(AddFriendRole::EmailRole).toString();
    int status = index.data(AddFriendRole::StatusRole).toInt();

    //确定头像的x轴起点和y轴起点，但需要注意，QRect的坐标系是y轴向下
    int iconX = rect.left() + m_padding;
    int iconY = rect.top() + (rect.height() - m_iconSize) / 2;
    QRect iconRect(iconX, iconY, m_iconSize, m_iconSize);

    //确定文本矩形框的大小
    int icon_name_height = rect.height() - 2 * m_padding - m_spacing;
    int icon_name_width = 100;  //按钮的宽度和头像的宽度一致
    int email_height = rect.height() - 2 * m_padding;
    int email_width = 300;

    //确定uid矩形框的大小
    int uidX = rect.left() + m_padding + m_iconSize + m_spacing;
    int uidY = iconY;
    QRect uidRect(uidX, uidY, icon_name_width, icon_name_height);

    //确定名字矩形框的大小
    int nameX = uidX;
    int nameY = uidY + 2 * m_spacing;
    QRect nameRect(nameX, nameY, icon_name_width, icon_name_height);

    //确定email矩形框的大小
    int emailX = uidX + icon_name_width + m_spacing;
    int emailY = rect.top() + 2 * m_padding;
    QRect emailRect(emailX, emailY, email_width, email_height);

    // 绘制头像（使用缓存）
    QIcon avatarIcon;
    if (!icon.isEmpty())
    {
        // 从缓存获取
        avatarIcon = m_iconCache.value(icon);
        if (avatarIcon.isNull()) {
            // 缓存未命中，创建并缓存
            avatarIcon = QIcon(icon);
            if (!avatarIcon.isNull())
            {
                m_iconCache[icon] = avatarIcon;
            }
        }
    }

    if (avatarIcon.isNull())
    {
        avatarIcon = m_defaultAvatarIcon;
    }
    avatarIcon.paint(painter, iconRect);

    // 绘制名字（使用预创建的字体）
    painter->setPen(option.state & QStyle::State_MouseOver ? Qt::black : Qt::black);
    painter->setFont(m_nameFont);
    painter->drawText(uidRect, Qt::AlignLeft, "ID: " + uid);
    painter->drawText(nameRect, Qt::AlignLeft, "Name: " + name);
    painter->drawText(emailRect, Qt::AlignLeft, "Email :" + email);

    // 根据 status 绘制按钮或文本
    if (status == 0)
    {
        // 未处理：绘制按钮（矩形 + 文本“同意”）
        int buttonWidth = 80;
        int buttonHeight = 30;
        int buttonX = emailX + email_width + m_spacing;  // 按钮在 email 右侧
        int buttonY = rect.top() + (rect.height() - buttonHeight) / 2;
        QRect buttonRect(buttonX, buttonY, buttonWidth, buttonHeight);

        // 绘制按钮背景（浅蓝）
        painter->fillRect(buttonRect, QColor(0, 200, 0));
        painter->setPen(Qt::white);
        painter->drawRect(buttonRect);  // 边框
        painter->drawText(buttonRect, Qt::AlignCenter, "同意");

        // 存储按钮区域（用于视图点击检测）
        // 注意：这里假设委托有成员变量 m_buttonRects 或类似，但实际需要视图处理
    }
    else if (status == 1)
    {
        // 已处理：绘制文本“已处理”
        int processedX = emailX + email_width + m_spacing;
        int processedY = rect.top() + 2 * m_padding;
        QRect processedRect(processedX, processedY, 100, email_height);  // 固定宽度
        painter->setPen(Qt::gray);
        painter->drawText(processedRect, Qt::AlignCenter, "已处理");
    }

    // 绘制分隔线
    painter->setPen(QColor(230, 230, 230));
    painter->drawLine(rect.left() + m_padding, rect.bottom() - 1,
                      rect.right() - m_padding, rect.bottom() - 1);

    painter->restore();
}

QSize ApplyFriendItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);

    return QSize(0,60);
}

// 新增方法：返回按钮区域（用于视图检测点击）
QRect ApplyFriendItemDelegate::buttonRect(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (!index.isValid()) return QRect();

    int status = index.data(AddFriendRole::StatusRole).toInt();
    if (status != 0) return QRect();  // 只有 status=0 时有按钮

    QRect rect = option.rect;
    int email_width = 300;
    int emailX = rect.left() + m_padding + m_iconSize + m_spacing + 100 + m_spacing;  // 基于 emailRect 计算
    int buttonWidth = 80;
    int buttonHeight = 30;
    int buttonX = emailX + email_width + m_spacing;
    int buttonY = rect.top() + (rect.height() - buttonHeight) / 2;
    return QRect(buttonX, buttonY, buttonWidth, buttonHeight);
}

#include "ClickedBtn.h"
#include <QVariant>
#include "global.h"
#include <QKeyEvent>

ClickedBtn::ClickedBtn(QWidget *parent):QPushButton (parent)
{
    //setCursor(Qt::PointingHandCursor); // 设置光标为小手
    setFocusPolicy(Qt::NoFocus);

    setState("normal", "hover");
}

void ClickedBtn::setState(QString normal, QString hover)
{
    _hover = hover;
    _normal = normal;

    setProperty("state", normal);
    repolish(this);
    update();
}

void ClickedBtn::enterEvent(QEnterEvent *event)
{
    setProperty("state",_hover);
    repolish(this);
    update();
    QPushButton::enterEvent(event);
}

void ClickedBtn::leaveEvent(QEvent *event)
{
    setProperty("state",_normal);
    repolish(this);
    update();
    QPushButton::leaveEvent(event);
}




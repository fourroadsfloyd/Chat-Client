/******************************************************************************
 *
 * @file       timerbtn.h
 * @brief      按钮倒计时
 *
 * @author     ysk
 * @date       2026/01/05
 * @history
 *****************************************************************************/

#ifndef TIMERBTN_H
#define TIMERBTN_H
#include <QPushButton>
#include <QTimer>

class TimerBtn : public QPushButton{
    Q_OBJECT
public:
    TimerBtn(QWidget *parent = nullptr);
    ~TimerBtn();

    void mouseReleaseEvent(QMouseEvent *e) override;

private:
    QTimer* _timer;

    int _counter;

};

#endif // TIMERBTN_H

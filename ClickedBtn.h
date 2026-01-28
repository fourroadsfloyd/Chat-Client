#ifndef CLICKEDBTN_H
#define CLICKEDBTN_H

#include <QPushButton>

class ClickedBtn : public QPushButton {
    Q_OBJECT
public:
    ClickedBtn(QWidget *parent = nullptr);
    ~ClickedBtn() = default;

    void setState(QString normal, QString hover);

protected:
    void enterEvent(QEnterEvent *event) override; // 鼠标进入

    void leaveEvent(QEvent *event) override; // 鼠标离开

private:
    QString _normal;
    QString _hover;
};

#endif // CLICKEDBTN_H

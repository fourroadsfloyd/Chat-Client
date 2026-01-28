/******************************************************************************
 *
 * @file       registerdialog.h
 * @brief      注册界面类
 *
 * @author     ysk
 * @date       2025/12/30
 * @history
 *****************************************************************************/

#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>
#include "global.h"
#include <QTimer>

namespace Ui {
class RegisterDialog;
}

class RegisterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterDialog(QWidget *parent = nullptr);
    ~RegisterDialog();

private: //成员函数
    void showTip(QString str, bool flag);

    void initHttpHandlers();

    void AddTipErr(TipErr te, QString tips);

    void DelTipErr(TipErr te);

    bool checkUserValid();

    bool checkEmailValid();

    bool checkPassValid();

    bool checkVerifyValid();

    bool checkConfirmValid();

    void ChangeTipPage();

private: //成员变量
    Ui::RegisterDialog *ui;

    QMap<ReqId, std::function<void(const QJsonObject&)>> _handlers;

    QMap<TipErr, QString> _tip_errs;

    QTimer* _countdown_timer;

    int _countdown;

private slots:
    void on_btn_get_clicked();

    void slot_reg_mod_finish(ReqId id, QString res, ErrorCodes err);

    void on_btn_confirm_clicked();

    void on_btn_confirm_2_clicked();

signals:
    void switchLogin();
};

#endif // REGISTERDIALOG_H

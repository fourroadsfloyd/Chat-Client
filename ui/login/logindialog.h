/******************************************************************************
 *
 * @file       logindialog.h
 * @brief      登录界面类
 *
 * @author     ysk
 * @date       2025/12/30
 * @history
 *****************************************************************************/

#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include "global.h"

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

private:

    void initHandlers();

    void enableBtn(bool enabled);

    bool checkUserValid();

    bool checkPasswdValid();

    void AddTipErr(TipErr te, QString tips);

    void DelTipErr(TipErr te);

    void showTip(QString str, bool flag);

private:
    Ui::LoginDialog *ui;

    QMap<TipErr, QString> _tip_errs;

    QMap<ReqId, std::function<void(const QJsonObject&)>> _handlers;

    int _uid;   //用户的uid，唯一标识符

    QString _token; //StatusServer分配的token，与ChatServer建立长连接时的验证标识，可能后续还有作用

signals:
    void switchRegister();

    void switchReset();

    void sig_connect_tcp(ServerInfo);

private slots:
    void slot_forget_pwd();

    void slot_login_mod_finish(ReqId id, QString res, ErrorCodes err);

    void on_btn_login_clicked();

    void slot_tcp_con_finish(bool bsuccess);

    void slot_login_failed(int);
};

#endif // LOGINDIALOG_H

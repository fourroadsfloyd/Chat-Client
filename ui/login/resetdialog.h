#ifndef RESETDIALOG_H
#define RESETDIALOG_H

#include <QDialog>
#include "global.h"

namespace Ui {
class ResetDialog;
}

class ResetDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ResetDialog(QWidget *parent = nullptr);
    ~ResetDialog();

private:
    void initHandlers();

    bool checkUserValid();

    bool checkEmailValid();

    bool checkPasswdValid();

    bool checkVerifyValid();

    void AddTipErr(TipErr te, QString tips);

    void DelTipErr(TipErr te);

    void showTip(QString s, bool flag);

private:
    Ui::ResetDialog *ui;

    QMap<ReqId, std::function<void(const QJsonObject&)>> _handlers;

    QMap<TipErr, QString> _tip_errs;

signals:
    void switchLogin();

public slots:
    void slot_reset_mod_finish(ReqId id, QString res, ErrorCodes err);

private slots:
    void on_btn_confirm_clicked();
    void on_btn_get_clicked();
};

#endif // RESETDIALOG_H

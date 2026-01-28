#ifndef ADDFRIENDERRORDIALOG_H
#define ADDFRIENDERRORDIALOG_H

#include <QDialog>

namespace Ui {
class AddFriendErrorDialog;
}

class AddFriendErrorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddFriendErrorDialog(QWidget *parent = nullptr);
    ~AddFriendErrorDialog();

private slots:
    void on_btn_addfriend_close_clicked();

private:
    Ui::AddFriendErrorDialog *ui;
};

#endif // ADDFRIENDERRORDIALOG_H

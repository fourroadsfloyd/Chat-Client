#ifndef ADDFRIENDDIALOG_H
#define ADDFRIENDDIALOG_H

#include "data/UserStructInfo.h"
#include <QDialog>

namespace Ui {
class AddFriendDialog;
}

class AddFriendDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddFriendDialog(QWidget *parent = nullptr);
    ~AddFriendDialog();

    void setUiData(std::shared_ptr<SearchInfo> info);

private:
    Ui::AddFriendDialog *ui;

    int _applyFriend_Uid;   //为什么这里有一个申请的uid呢？

private slots:
    void on_btn_addfriend_clicked();

};

#endif // ADDFRIENDDIALOG_H

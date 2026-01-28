#include "AddFriendErrorDialog.h"
#include "ui_AddFriendErrorDialog.h"

AddFriendErrorDialog::AddFriendErrorDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddFriendErrorDialog)
{
    ui->setupUi(this);
}

AddFriendErrorDialog::~AddFriendErrorDialog()
{
    delete ui;
}

void AddFriendErrorDialog::on_btn_addfriend_close_clicked()
{
    this->close();
}


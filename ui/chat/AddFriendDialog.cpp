#include "ui/chat/AddFriendDialog.h"
#include "ui_AddFriendDialog.h"
#include "net/tcpmgr.h"
#include "data/usermgr.h"

AddFriendDialog::AddFriendDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddFriendDialog)
{
    ui->setupUi(this);
}

AddFriendDialog::~AddFriendDialog()
{
    delete ui;
}

//将找到的用户的信息在界面中显示
void AddFriendDialog::setUiData(std::shared_ptr<SearchInfo> info)
{
    _applyFriend_Uid = info->_uid;

    qDebug() << "icon is " << info->_avatarpath;

    ui->btn_icon->setIcon(QIcon(info->_avatarpath));
    ui->btn_icon->setIconSize(QSize(50,50));

    ui->label_email->setText(info->_email);
    ui->label_name->setText(info->_name);
    ui->label_uid->setText(QString::number(info->_uid));
}

void AddFriendDialog::on_btn_addfriend_clicked()
{
    //将自己和对方的uid都写入到json中
    QJsonObject jsonobj;

    jsonobj["from_uid"] = UserMgr::GetInstance()->GetUid();
    jsonobj["to_uid"] = this->_applyFriend_Uid;

    QJsonDocument doc(jsonobj);
    QString jsonString = doc.toJson(QJsonDocument::Indented);

    qDebug() << "A send the apply to B";

    emit TcpMgr::GetInstance()->sig_send_data(ID_ADD_FRIEND_REQ, jsonString.toUtf8());

    this->close();
}



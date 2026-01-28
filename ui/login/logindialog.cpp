#include "ui/login/logindialog.h"
#include "ui_logindialog.h"
#include "net/httpmgr.h"
#include "net/tcpmgr.h"
#include <QPushButton>


LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    ui->edit_pwd->setEchoMode(QLineEdit::Password);

    connect(ui->btn_register, &QPushButton::clicked, this, &LoginDialog::switchRegister);

    ui->label_forget->SetState("normal","hover","","selected","selected_hover","");
    ui->label_forget->setCursor(Qt::PointingHandCursor);
    connect(ui->label_forget, &ClickedLabel::clicked, this, &LoginDialog::slot_forget_pwd);

    connect(ui->edit_user,&QLineEdit::editingFinished,this,[this](){
        checkUserValid();
    });

    connect(ui->edit_pwd, &QLineEdit::editingFinished, this, [this](){
        checkPasswdValid();
    });

    connect(HttpMgr::GetInstance().get(), &HttpMgr::sig_login_mod_finish, this, &LoginDialog::slot_login_mod_finish);

    //连接tcp连接请求的信号和槽函数
    connect(this, &LoginDialog::sig_connect_tcp, TcpMgr::GetInstance().get(), &TcpMgr::slot_tcp_connect);
    //连接tcp管理者发出的连接成功信号
    connect(TcpMgr::GetInstance().get(), &TcpMgr::sig_con_success, this, &LoginDialog::slot_tcp_con_finish);

    //连接tcp管理者发出的登陆失败信号
    connect(TcpMgr::GetInstance().get(), &TcpMgr::sig_login_failed, this, &LoginDialog::slot_login_failed);

    this->initHandlers();
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::initHandlers()
{
    //注册获取登录回包逻辑
    _handlers.insert(ReqId::ID_LOGIN_USER, [this](QJsonObject jsonObj){
        int error = jsonObj["error"].toInt();
        if(error != ErrorCodes::Success){
            showTip(tr("参数错误"),false);
            //enableBtn(true);
            return;
        }

        //发送信号通知tcpMgr发送长链接
        ServerInfo si;
        si.Uid = jsonObj["uid"].toInt();
        si.Host = jsonObj["host"].toString();
        si.Port = jsonObj["port"].toString();
        si.Token = jsonObj["token"].toString();

        _uid = si.Uid;
        _token = si.Token;

        AsyncLog::getInstance().log(LogLevel::LogINFO, "LoginDialog initHandlers, emit sig_connect_tcp");

        emit sig_connect_tcp(si);
    });
}

void LoginDialog::on_btn_login_clicked()
{
    AsyncLog::getInstance().log(LogLevel::LogINFO, "click logindialog btn_login");

    if(!checkUserValid())   return;

    if(!checkPasswdValid()) return;

    //enableBtn(false);

    QJsonObject json_obj;

    json_obj["email"] = ui->edit_user->text();
    json_obj["pwd"] = ui->edit_pwd->text();

    HttpMgr::GetInstance()->PostHttpReq(gate_url_prefix + "/user_login",
                                        json_obj,
                                        ReqId::ID_LOGIN_USER,
                                        Modules::LOGINMOD);
}

void LoginDialog::slot_forget_pwd()
{
    emit switchReset();
}

void LoginDialog::slot_login_mod_finish(ReqId id, QString res, ErrorCodes err)
{
    if(err != ErrorCodes::Success)
    {
        showTip(tr("网络请求错误"),false);
        return;
    }

    // 解析 JSON 字符串,res需转化为QByteArray
    QJsonDocument jsonDoc = QJsonDocument::fromJson(res.toUtf8());
    //json解析错误
    if(jsonDoc.isNull()){
        showTip(tr("json解析错误"),false);
        return;
    }

    //json解析错误
    if(!jsonDoc.isObject()){
        showTip(tr("json解析错误"),false);
        return;
    }

    AsyncLog::getInstance().log(LogLevel::LogINFO, "slot_login_mod_finish");

    //调用对应的逻辑,根据id回调。
    _handlers[id](jsonDoc.object());
}

//tcp连接成功后，发送登录请求
void LoginDialog::slot_tcp_con_finish(bool bsuccess)
{
    if(bsuccess)
    {
        AsyncLog::getInstance().log(LogLevel::LogINFO, "in slot_tcp_con_finish");

        showTip(tr("聊天服务连接成功，正在登录..."),true);
        QJsonObject jsonObj;
        jsonObj["uid"] = _uid;
        jsonObj["token"] = _token;

        QJsonDocument doc(jsonObj);
        QString jsonString = doc.toJson(QJsonDocument::Indented);

        //发送tcp请求给chat server
        emit TcpMgr::GetInstance()->sig_send_data(ReqId::ID_CHAT_LOGIN, jsonString.toUtf8());
    }
    else
    {
        showTip(tr("网络异常"),false);
        //enableBtn(true);
    }
}

void LoginDialog::slot_login_failed(int err)
{
    QString result = QString("登录失败, err is %1")
                         .arg(err);
    showTip(result,false);
    //enableBtn(true);
}

void LoginDialog::enableBtn(bool enabled)
{
    ui->btn_login->setEnabled(enabled);
    ui->btn_register->setEnabled(enabled);
}

bool LoginDialog::checkUserValid()
{
    if(ui->edit_user->text() == ""){
        AddTipErr(TipErr::TIP_USER_ERR, tr("邮箱不能为空"));
        return false;
    }

    DelTipErr(TipErr::TIP_USER_ERR);
    return true;
}

bool LoginDialog::checkPasswdValid()
{
    auto pass = ui->edit_pwd->text();

    if(pass.length() < 6 || pass.length()>15)
    {
        //提示长度不准确
        AddTipErr(TipErr::TIP_PWD_ERR, tr("密码长度应为6~15"));
        return false;
    }

    // 创建一个正则表达式对象，按照上述密码要求
    // 这个正则表达式解释：
    // ^[a-zA-Z0-9!@#$%^&*]{6,15}$ 密码长度至少6，可以是字母、数字和特定的特殊字符
    QRegularExpression regExp("^[a-zA-Z0-9!@#$%^&*]{6,15}$");
    bool match = regExp.match(pass).hasMatch();
    if(!match){
        //提示字符非法
        AddTipErr(TipErr::TIP_PWD_ERR, tr("不能包含非法字符"));
        return false;;
    }

    DelTipErr(TipErr::TIP_PWD_ERR);

    return true;
}

void LoginDialog::AddTipErr(TipErr te, QString tips)
{
    _tip_errs[te] = tips;
    showTip(tips, false);
}

void LoginDialog::DelTipErr(TipErr te)
{
    _tip_errs.remove(te);
    if(_tip_errs.empty()){
        ui->label_errtip_login->clear();
        return;
    }

    showTip(_tip_errs.first(), false);
}

void LoginDialog::showTip(QString str, bool flag)
{
    if(flag)
    {
        ui->label_errtip_login->setProperty("state","normal");
    }
    else
    {
        ui->label_errtip_login->setProperty("state","err");
    }
    ui->label_errtip_login->setText(str);
    repolish(ui->label_errtip_login);
}




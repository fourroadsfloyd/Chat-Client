#include "ui/login/registerdialog.h"
#include "ui_registerdialog.h"
#include "net/httpmgr.h"

RegisterDialog::RegisterDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RegisterDialog), _countdown(3)
{
    ui->setupUi(this);
    ui->edit_pwd->setEchoMode(QLineEdit::Password);
    ui->edit_pwd_again->setEchoMode(QLineEdit::Password);

    this->initHttpHandlers();

    connect(ui->btn_cancel, &QPushButton::clicked, [this](){
        this->_countdown_timer->stop(); //跳转到其他界面时，一定要关闭这个界面的网络连接，计时器等
        emit switchLogin();
    });

    connect(HttpMgr::GetInstance().get(), &HttpMgr::sig_reg_mod_finish, this, &RegisterDialog::slot_reg_mod_finish);

    connect(ui->edit_user,&QLineEdit::editingFinished,this,[this](){
        checkUserValid();
    });

    connect(ui->edit_email, &QLineEdit::editingFinished, this, [this](){
        checkEmailValid();
    });

    connect(ui->edit_pwd, &QLineEdit::editingFinished, this, [this](){
        checkPassValid();
    });

    connect(ui->edit_pwd_again, &QLineEdit::editingFinished, this, [this](){
        checkConfirmValid();
    });

    connect(ui->edit_verify, &QLineEdit::editingFinished, this, [this](){
        checkVerifyValid();
    });

    ui->visible_pwd->setCursor(Qt::PointingHandCursor);
    ui->visible_pwd_again->setCursor(Qt::PointingHandCursor);

    ui->visible_pwd->SetState("unvisible","unvisible_hover","","visible",
                               "visible_hover","");

    ui->visible_pwd_again->SetState("unvisible","unvisible_hover","","visible",
                                  "visible_hover","");
    //连接点击事件

    connect(ui->visible_pwd, &ClickedLabel::clicked, this, [this]() {
        auto state = ui->visible_pwd->GetCurState();
        if(state == ClickLbState::Normal){
            ui->edit_pwd->setEchoMode(QLineEdit::Password);
        }else{
            ui->edit_pwd->setEchoMode(QLineEdit::Normal);
        }
        //qDebug() << "Label was clicked!";
    });

    connect(ui->visible_pwd_again, &ClickedLabel::clicked, this, [this]() {
        auto state = ui->visible_pwd_again->GetCurState();
        if(state == ClickLbState::Normal){
            ui->edit_pwd_again->setEchoMode(QLineEdit::Password);
        }else{
            ui->edit_pwd_again->setEchoMode(QLineEdit::Normal);
        }
        //qDebug() << "Label was clicked!";
    });

    //创建定时器
    _countdown_timer = new QTimer(this);
    // 连接信号和槽
    connect(_countdown_timer, &QTimer::timeout, this, [this](){
        if(_countdown==0){
            _countdown_timer->stop();
            emit switchLogin();
            return;
        }
        _countdown--;
    });

}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}

void RegisterDialog::initHttpHandlers()
{
    _handlers.insert(ReqId::ID_GET_VERIFY_CODE, [this](const QJsonObject& jsonObj){
        int error = jsonObj["error"].toInt();
        if(error != ErrorCodes::Success)
        {
            showTip(tr("参数错误"), false);
            return;
        }

        showTip(tr("验证码已发送到邮箱，注意查收"), true);
    });

    //注册注册用户回包逻辑
    _handlers.insert(ReqId::ID_REG_USER, [this](const QJsonObject& jsonObj){

        int error = jsonObj["error"].toInt();
        if(error != ErrorCodes::Success){
            showTip(tr("参数错误"),false);
            return;
        }

        //一个新的界面，提示登录成功，3s返回登录界面
        ChangeTipPage();
    });
}

void RegisterDialog::AddTipErr(TipErr te, QString tips)
{
    _tip_errs[te] = tips;
    showTip(tips, false);
}

void RegisterDialog::DelTipErr(TipErr te)
{
    _tip_errs.remove(te);
    if(_tip_errs.empty()){
        ui->label_errortip->clear();
        return;
    }

    showTip(_tip_errs.last(), false);
}

bool RegisterDialog::checkUserValid()
{
    if(ui->edit_user->text() == ""){
        AddTipErr(TipErr::TIP_USER_ERR, tr("用户名不能为空"));
        return false;
    }

    DelTipErr(TipErr::TIP_USER_ERR);
    return true;
}

bool RegisterDialog::checkEmailValid()
{
    //验证邮箱的地址正则表达式
    auto email = ui->edit_email->text();
    // 邮箱地址的正则表达式
    QRegularExpression regex(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)");
    bool match = regex.match(email).hasMatch(); // 执行正则表达式匹配
    if(!match){
        //提示邮箱不正确
        AddTipErr(TipErr::TIP_EMAIL_ERR, tr("邮箱地址不正确"));
        return false;
    }

    DelTipErr(TipErr::TIP_EMAIL_ERR);
    return true;
}

bool RegisterDialog::checkPassValid()
{
    auto pass = ui->edit_pwd->text();
    auto confirm = ui->edit_pwd_again->text();

    if(pass.length() < 6 || pass.length()>15){
        //提示长度不准确
        AddTipErr(TipErr::TIP_PWD_ERR, tr("密码长度应为6~15"));
        return false;
    }

    // 创建一个正则表达式对象，按照上述密码要求
    // 这个正则表达式解释：
    // ^[a-zA-Z0-9!@#$%^&*]{6,15}$ 密码长度至少6，可以是字母、数字和特定的特殊字符
    QRegularExpression regExp("^[a-zA-Z0-9!@#$%^&*.]{6,15}$");
    bool match = regExp.match(pass).hasMatch();
    if(!match){
        //提示字符非法
        AddTipErr(TipErr::TIP_PWD_ERR, tr("不能包含非法字符"));
        return false;;
    }

    DelTipErr(TipErr::TIP_PWD_ERR);

    if(pass != confirm){
        //提示密码不匹配
        AddTipErr(TipErr::TIP_PWD_CONFIRM, tr("密码和确认密码不匹配"));
        return false;
    }else{
        DelTipErr(TipErr::TIP_PWD_CONFIRM);
    }
    return true;
}

bool RegisterDialog::checkVerifyValid()
{
    auto pass = ui->edit_verify->text();
    if(pass.isEmpty()){
        AddTipErr(TipErr::TIP_VERIFY_ERR, tr("验证码不能为空"));
        return false;
    }

    DelTipErr(TipErr::TIP_VERIFY_ERR);
    return true;
}

bool RegisterDialog::checkConfirmValid()
{
    auto pass = ui->edit_pwd->text();
    auto confirm = ui->edit_pwd_again->text();

    if(confirm.length() < 6 || confirm.length() > 15 ){
        //提示长度不准确
        AddTipErr(TipErr::TIP_CONFIRM_ERR, tr("密码长度应为6~15"));
        return false;
    }

    // 创建一个正则表达式对象，按照上述密码要求
    // 这个正则表达式解释：
    // ^[a-zA-Z0-9!@#$%^&*]{6,15}$ 密码长度至少6，可以是字母、数字和特定的特殊字符
    QRegularExpression regExp("^[a-zA-Z0-9!@#$%^&*.]{6,15}$");
    bool match = regExp.match(confirm).hasMatch();
    if(!match){
        //提示字符非法
        AddTipErr(TipErr::TIP_CONFIRM_ERR, tr("不能包含非法字符"));
        return false;
    }

    DelTipErr(TipErr::TIP_CONFIRM_ERR);

    if(pass != confirm){
        //提示密码不匹配
        AddTipErr(TipErr::TIP_PWD_CONFIRM, tr("确认密码和密码不匹配"));
        return false;
    }else{
        DelTipErr(TipErr::TIP_PWD_CONFIRM);
    }
    return true;
}

void RegisterDialog::ChangeTipPage()
{
    _countdown_timer->stop();

    ui->stackedWidget->setCurrentWidget(ui->page_2);

    _countdown_timer->start(1000);  //启动1s的定时器
}

void RegisterDialog::showTip(QString str, bool flag)
{
    if(flag)
    {
        ui->label_errortip->setProperty("state","normal");
    }
    else
    {
        ui->label_errortip->setProperty("state","err");
    }
    ui->label_errortip->setText(str);
    repolish(ui->label_errortip);
}

void RegisterDialog::on_btn_get_clicked()
{
    AsyncLog::getInstance().log(LogLevel::LogINFO, "点击注册界面获取验证码按钮");

    //验证邮箱的地址正则表达式
    auto email = ui->edit_email->text();
    // 邮箱地址的正则表达式
    static QRegularExpression regex(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)");
    bool match = regex.match(email).hasMatch(); // 执行正则表达式匹配
    if(match)
    {
        QJsonObject json_obj;
        json_obj["email"] = email;  //如果email格式匹配，就写入到json字段中

        AsyncLog::getInstance().log(LogLevel::LogINFO, "由on_btn_get_clicked进入PostHttpReq");

        HttpMgr::GetInstance()->PostHttpReq(QUrl(gate_url_prefix + "/get_verifycode"),
                                            json_obj,
                                            ReqId::ID_GET_VERIFY_CODE,
                                            Modules::REGISTERMOD);
        //发送http请求获取验证码
    }else
    {
        //提示邮箱不正确
        showTip(tr("邮箱地址不正确"), false);
    }
}

void RegisterDialog::on_btn_confirm_clicked()   //确定按钮
{
    if(ui->edit_user->text() == ""){
        showTip(tr("用户名不能为空"), false);
        return;
    }

    if(ui->edit_email->text() == ""){
        showTip(tr("邮箱不能为空"), false);
        return;
    }

    if(ui->edit_pwd->text() == ""){
        showTip(tr("密码不能为空"), false);
        return;
    }

    if(ui->edit_pwd_again->text() == ""){
        showTip(tr("确认密码不能为空"), false);
        return;
    }

    if(ui->edit_pwd_again->text() != ui->edit_pwd->text()){
        showTip(tr("密码和确认密码不匹配"), false);
        return;
    }

    if(ui->edit_verify->text() == ""){
        showTip(tr("验证码不能为空"), false);
        return;
    }

    QJsonObject json_obj;
    json_obj["user"] = ui->edit_user->text();
    json_obj["email"] = ui->edit_email->text();
    json_obj["passwd"] = ui->edit_pwd->text();
    json_obj["confirm"] = ui->edit_pwd_again->text();
    json_obj["verifycode"] = ui->edit_verify->text();

    HttpMgr::GetInstance()->PostHttpReq(QUrl(gate_url_prefix + "/user_register"),
                                        json_obj,
                                        ReqId::ID_REG_USER,
                                        Modules::REGISTERMOD);
}

void RegisterDialog::slot_reg_mod_finish(ReqId id, QString res, ErrorCodes err)
{   
    if(err != ErrorCodes::Success)
    {
        showTip(tr("网络请求错误"), false);
        return;
    }

    // 解析 JSON 字符串,res需转化为QByteArray
    QJsonDocument jsonDoc = QJsonDocument::fromJson(res.toUtf8());
    //json解析错误
    if(jsonDoc.isNull())
    {
        showTip(tr("json解析错误"), false);
        return;
    }

    //json解析错误
    if(!jsonDoc.isObject())
    {
        showTip(tr("json解析错误"), false);
        return;
    }

    //调用对应的逻辑,根据id回调。
    _handlers.value(id)(jsonDoc.object());

    return;
}

void RegisterDialog::on_btn_confirm_2_clicked()
{
    _countdown_timer->stop();

    emit switchLogin();
}


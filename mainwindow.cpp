#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "net/tcpmgr.h"
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 使用 QStackedWidget 作为唯一 centralWidget，避免反复 setCentralWidget
    _stacked_widget = new QStackedWidget(this);
    setCentralWidget(_stacked_widget);

    // 只创建一次各个对话框，复用实例
    _login_dialog = new LoginDialog(this);
    _login_dialog->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);

    _register_dialog = new RegisterDialog(this);
    _register_dialog->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);

    _reset_dialog = new ResetDialog(this);
    _reset_dialog->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);

    // 加入到 stack
    _stacked_widget->addWidget(_login_dialog);
    _stacked_widget->addWidget(_register_dialog);
    _stacked_widget->addWidget(_reset_dialog);

    // 默认显示登录界面
    _stacked_widget->setCurrentWidget(_login_dialog);

    // 只连接一次信号（不会重复连接）
    connect(_login_dialog, &LoginDialog::switchRegister, this, &MainWindow::slotSwitchReg);
    connect(_login_dialog, &LoginDialog::switchReset, this, &MainWindow::slotSwitchReset);
    connect(_register_dialog, &RegisterDialog::switchLogin, this, &MainWindow::slotSwitchLog);
    connect(_reset_dialog, &ResetDialog::switchLogin, this, &MainWindow::slotSwitchLog);
    connect(TcpMgr::GetInstance().get(), &TcpMgr::sig_swich_chatdlg, this, &MainWindow::slotSwitchChat);

    _chat_widget = new ChatWidget(nullptr);
    _chat_widget->show();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotSwitchReg()
{
    _stacked_widget->setCurrentWidget(_register_dialog);
}

void MainWindow::slotSwitchLog()
{
    _stacked_widget->setCurrentWidget(_login_dialog);
}

void MainWindow::slotSwitchReset()
{
    _stacked_widget->setCurrentWidget(_reset_dialog);
}

void MainWindow::slotSwitchChat()
{
    //qDebug() << "ready in chatwidget";
    _chat_widget = new ChatWidget(nullptr);
    _chat_widget->show();
    this->close();
}



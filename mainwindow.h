/******************************************************************************
 *
 * @file       mainwindow.h
 * @brief      main window
 *
 * @author     ysk
 * @date       2025/12/29
 * @history
 *****************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui/login/logindialog.h"
#include "ui/login/registerdialog.h"
#include "ui/login/resetdialog.h"
#include "ui/chat/ChatWidget.h"
#include <QMainWindow>
#include <QStackedWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QStackedWidget* _stacked_widget = nullptr;
    LoginDialog* _login_dialog = nullptr;
    RegisterDialog* _register_dialog = nullptr;
    ResetDialog* _reset_dialog = nullptr;
    ChatWidget* _chat_widget = nullptr;

public slots:
    void slotSwitchReg();

    void slotSwitchLog();

    void slotSwitchReset();

    void slotSwitchChat();

};
#endif // MAINWINDOW_H

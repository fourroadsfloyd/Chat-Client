/********************************************************************************
** Form generated from reading UI file 'logindialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINDIALOG_H
#define UI_LOGINDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "clickedlabel.h"

QT_BEGIN_NAMESPACE

class Ui_LoginDialog
{
public:
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QGridLayout *gridLayout;
    QLabel *label_png;
    QLabel *label_errtip_login;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer_6;
    QLabel *label_user;
    QLineEdit *edit_user;
    QSpacerItem *horizontalSpacer_7;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_8;
    QLabel *label_pwd;
    QLineEdit *edit_pwd;
    QSpacerItem *horizontalSpacer_9;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer;
    ClickedLabel *label_forget;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btn_login;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *btn_register;
    QSpacerItem *horizontalSpacer_4;

    void setupUi(QDialog *LoginDialog)
    {
        if (LoginDialog->objectName().isEmpty())
            LoginDialog->setObjectName("LoginDialog");
        LoginDialog->resize(350, 500);
        LoginDialog->setMinimumSize(QSize(350, 500));
        LoginDialog->setMaximumSize(QSize(350, 500));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/res/wx.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        LoginDialog->setWindowIcon(icon);
        horizontalLayout = new QHBoxLayout(LoginDialog);
        horizontalLayout->setObjectName("horizontalLayout");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(7);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(5, 5, 5, 5);
        widget = new QWidget(LoginDialog);
        widget->setObjectName("widget");
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName("gridLayout");
        label_png = new QLabel(widget);
        label_png->setObjectName("label_png");
        label_png->setPixmap(QPixmap(QString::fromUtf8(":/res/wx.png")));
        label_png->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout->addWidget(label_png, 0, 0, 1, 1);

        label_errtip_login = new QLabel(widget);
        label_errtip_login->setObjectName("label_errtip_login");
        label_errtip_login->setMinimumSize(QSize(0, 20));
        label_errtip_login->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout->addWidget(label_errtip_login, 1, 0, 1, 1);


        verticalLayout->addWidget(widget);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_6);

        label_user = new QLabel(LoginDialog);
        label_user->setObjectName("label_user");
        label_user->setMinimumSize(QSize(0, 40));
        label_user->setMaximumSize(QSize(16777215, 40));

        horizontalLayout_7->addWidget(label_user);

        edit_user = new QLineEdit(LoginDialog);
        edit_user->setObjectName("edit_user");
        edit_user->setMinimumSize(QSize(0, 30));
        edit_user->setMaximumSize(QSize(16777215, 30));

        horizontalLayout_7->addWidget(edit_user);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_7);


        verticalLayout->addLayout(horizontalLayout_7);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_8);

        label_pwd = new QLabel(LoginDialog);
        label_pwd->setObjectName("label_pwd");
        label_pwd->setMinimumSize(QSize(0, 40));
        label_pwd->setMaximumSize(QSize(16777215, 40));

        horizontalLayout_6->addWidget(label_pwd);

        edit_pwd = new QLineEdit(LoginDialog);
        edit_pwd->setObjectName("edit_pwd");
        edit_pwd->setMinimumSize(QSize(0, 30));
        edit_pwd->setMaximumSize(QSize(16777215, 30));

        horizontalLayout_6->addWidget(edit_pwd);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_9);


        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer);

        label_forget = new ClickedLabel(LoginDialog);
        label_forget->setObjectName("label_forget");
        label_forget->setMinimumSize(QSize(0, 40));
        label_forget->setMaximumSize(QSize(16777215, 40));
        label_forget->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        horizontalLayout_5->addWidget(label_forget);


        verticalLayout->addLayout(horizontalLayout_5);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        btn_login = new QPushButton(LoginDialog);
        btn_login->setObjectName("btn_login");
        btn_login->setMinimumSize(QSize(100, 30));

        horizontalLayout_3->addWidget(btn_login);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_5);

        btn_register = new QPushButton(LoginDialog);
        btn_register->setObjectName("btn_register");
        btn_register->setMinimumSize(QSize(100, 30));

        horizontalLayout_2->addWidget(btn_register);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(horizontalLayout_2);


        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(LoginDialog);

        QMetaObject::connectSlotsByName(LoginDialog);
    } // setupUi

    void retranslateUi(QDialog *LoginDialog)
    {
        LoginDialog->setWindowTitle(QCoreApplication::translate("LoginDialog", "Ppao", nullptr));
        label_png->setText(QString());
        label_errtip_login->setText(QString());
        label_user->setText(QCoreApplication::translate("LoginDialog", "\351\202\256\347\256\261\357\274\232", nullptr));
        label_pwd->setText(QCoreApplication::translate("LoginDialog", "\345\257\206\347\240\201\357\274\232", nullptr));
        label_forget->setText(QCoreApplication::translate("LoginDialog", "\345\277\230\350\256\260\345\257\206\347\240\201", nullptr));
        btn_login->setText(QCoreApplication::translate("LoginDialog", "\347\231\273\351\231\206", nullptr));
        btn_register->setText(QCoreApplication::translate("LoginDialog", "\346\263\250\345\206\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginDialog: public Ui_LoginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDIALOG_H

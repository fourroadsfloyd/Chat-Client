/********************************************************************************
** Form generated from reading UI file 'registerdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTERDIALOG_H
#define UI_REGISTERDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "clickedlabel.h"
#include "timerbtn.h"

QT_BEGIN_NAMESPACE

class Ui_RegisterDialog
{
public:
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QVBoxLayout *verticalLayout_3;
    QLabel *label;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_errortip;
    QHBoxLayout *horizontalLayout;
    QLabel *label_user;
    QLineEdit *edit_user;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_email;
    QLineEdit *edit_email;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_pwd;
    QLineEdit *edit_pwd;
    ClickedLabel *visible_pwd;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_pwd_again;
    QLineEdit *edit_pwd_again;
    ClickedLabel *visible_pwd_again;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_verify;
    QLineEdit *edit_verify;
    TimerBtn *btn_get;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *btn_confirm;
    QPushButton *btn_cancel;
    QWidget *page_2;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer;
    QLabel *label_2;
    QLabel *label_3;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_9;
    QPushButton *btn_confirm_2;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QDialog *RegisterDialog)
    {
        if (RegisterDialog->objectName().isEmpty())
            RegisterDialog->setObjectName("RegisterDialog");
        RegisterDialog->resize(350, 505);
        RegisterDialog->setMinimumSize(QSize(350, 500));
        RegisterDialog->setMaximumSize(QSize(350, 505));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/res/wx.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        RegisterDialog->setWindowIcon(icon);
        horizontalLayout_2 = new QHBoxLayout(RegisterDialog);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(7);
        verticalLayout->setObjectName("verticalLayout");
        stackedWidget = new QStackedWidget(RegisterDialog);
        stackedWidget->setObjectName("stackedWidget");
        page = new QWidget();
        page->setObjectName("page");
        verticalLayout_3 = new QVBoxLayout(page);
        verticalLayout_3->setObjectName("verticalLayout_3");
        label = new QLabel(page);
        label->setObjectName("label");
        label->setPixmap(QPixmap(QString::fromUtf8(":/res/wx.png")));
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_3->addWidget(label);

        widget = new QWidget(page);
        widget->setObjectName("widget");
        horizontalLayout_8 = new QHBoxLayout(widget);
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        label_errortip = new QLabel(widget);
        label_errortip->setObjectName("label_errortip");
        label_errortip->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_8->addWidget(label_errortip);


        verticalLayout_3->addWidget(widget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(7);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(-1, 0, 0, 0);
        label_user = new QLabel(page);
        label_user->setObjectName("label_user");
        label_user->setMinimumSize(QSize(0, 30));
        label_user->setMaximumSize(QSize(16777215, 30));

        horizontalLayout->addWidget(label_user);

        edit_user = new QLineEdit(page);
        edit_user->setObjectName("edit_user");
        edit_user->setMinimumSize(QSize(0, 30));
        edit_user->setMaximumSize(QSize(16777215, 30));

        horizontalLayout->addWidget(edit_user);


        verticalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        label_email = new QLabel(page);
        label_email->setObjectName("label_email");
        label_email->setMinimumSize(QSize(0, 30));
        label_email->setMaximumSize(QSize(16777215, 30));

        horizontalLayout_5->addWidget(label_email);

        edit_email = new QLineEdit(page);
        edit_email->setObjectName("edit_email");
        edit_email->setMinimumSize(QSize(0, 30));
        edit_email->setMaximumSize(QSize(16777215, 30));

        horizontalLayout_5->addWidget(edit_email);


        verticalLayout_3->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        label_pwd = new QLabel(page);
        label_pwd->setObjectName("label_pwd");
        label_pwd->setMinimumSize(QSize(0, 30));
        label_pwd->setMaximumSize(QSize(16777215, 30));

        horizontalLayout_6->addWidget(label_pwd);

        edit_pwd = new QLineEdit(page);
        edit_pwd->setObjectName("edit_pwd");
        edit_pwd->setMinimumSize(QSize(0, 30));
        edit_pwd->setMaximumSize(QSize(16777215, 30));

        horizontalLayout_6->addWidget(edit_pwd);

        visible_pwd = new ClickedLabel(page);
        visible_pwd->setObjectName("visible_pwd");
        visible_pwd->setMinimumSize(QSize(20, 20));
        visible_pwd->setMaximumSize(QSize(20, 20));

        horizontalLayout_6->addWidget(visible_pwd);


        verticalLayout_3->addLayout(horizontalLayout_6);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label_pwd_again = new QLabel(page);
        label_pwd_again->setObjectName("label_pwd_again");
        label_pwd_again->setMinimumSize(QSize(0, 30));
        label_pwd_again->setMaximumSize(QSize(16777215, 30));

        horizontalLayout_4->addWidget(label_pwd_again);

        edit_pwd_again = new QLineEdit(page);
        edit_pwd_again->setObjectName("edit_pwd_again");
        edit_pwd_again->setMinimumSize(QSize(0, 30));
        edit_pwd_again->setMaximumSize(QSize(16777215, 30));

        horizontalLayout_4->addWidget(edit_pwd_again);

        visible_pwd_again = new ClickedLabel(page);
        visible_pwd_again->setObjectName("visible_pwd_again");
        visible_pwd_again->setMinimumSize(QSize(20, 20));
        visible_pwd_again->setMaximumSize(QSize(20, 20));

        horizontalLayout_4->addWidget(visible_pwd_again);


        verticalLayout_3->addLayout(horizontalLayout_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_verify = new QLabel(page);
        label_verify->setObjectName("label_verify");
        label_verify->setMinimumSize(QSize(0, 30));
        label_verify->setMaximumSize(QSize(16777215, 30));

        horizontalLayout_3->addWidget(label_verify);

        edit_verify = new QLineEdit(page);
        edit_verify->setObjectName("edit_verify");
        edit_verify->setMinimumSize(QSize(0, 30));
        edit_verify->setMaximumSize(QSize(16777215, 30));

        horizontalLayout_3->addWidget(edit_verify);

        btn_get = new TimerBtn(page);
        btn_get->setObjectName("btn_get");
        btn_get->setMinimumSize(QSize(0, 30));
        btn_get->setMaximumSize(QSize(16777215, 30));

        horizontalLayout_3->addWidget(btn_get);


        verticalLayout_3->addLayout(horizontalLayout_3);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        btn_confirm = new QPushButton(page);
        btn_confirm->setObjectName("btn_confirm");
        btn_confirm->setMinimumSize(QSize(0, 30));
        btn_confirm->setMaximumSize(QSize(16777215, 30));

        horizontalLayout_7->addWidget(btn_confirm);

        btn_cancel = new QPushButton(page);
        btn_cancel->setObjectName("btn_cancel");
        btn_cancel->setMinimumSize(QSize(0, 30));
        btn_cancel->setMaximumSize(QSize(16777215, 30));

        horizontalLayout_7->addWidget(btn_cancel);


        verticalLayout_3->addLayout(horizontalLayout_7);

        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        verticalLayout_2 = new QVBoxLayout(page_2);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        label_2 = new QLabel(page_2);
        label_2->setObjectName("label_2");
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        label_2->setFont(font);
        label_2->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_2->addWidget(label_2);

        label_3 = new QLabel(page_2);
        label_3->setObjectName("label_3");
        label_3->setFont(font);
        label_3->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_2->addWidget(label_3);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_3);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        btn_confirm_2 = new QPushButton(page_2);
        btn_confirm_2->setObjectName("btn_confirm_2");
        btn_confirm_2->setMinimumSize(QSize(100, 50));
        btn_confirm_2->setMaximumSize(QSize(100, 50));

        horizontalLayout_9->addWidget(btn_confirm_2);


        verticalLayout_2->addLayout(horizontalLayout_9);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);

        stackedWidget->addWidget(page_2);

        verticalLayout->addWidget(stackedWidget);


        horizontalLayout_2->addLayout(verticalLayout);


        retranslateUi(RegisterDialog);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(RegisterDialog);
    } // setupUi

    void retranslateUi(QDialog *RegisterDialog)
    {
        RegisterDialog->setWindowTitle(QCoreApplication::translate("RegisterDialog", "Register", nullptr));
        label->setText(QString());
        label_errortip->setText(QString());
        label_user->setText(QCoreApplication::translate("RegisterDialog", "\347\224\250\346\210\267\357\274\232", nullptr));
        label_email->setText(QCoreApplication::translate("RegisterDialog", "\351\202\256\347\256\261\357\274\232", nullptr));
        label_pwd->setText(QCoreApplication::translate("RegisterDialog", "\345\257\206\347\240\201\357\274\232", nullptr));
        visible_pwd->setText(QString());
        label_pwd_again->setText(QCoreApplication::translate("RegisterDialog", "\347\241\256\350\256\244\357\274\232", nullptr));
        visible_pwd_again->setText(QString());
        label_verify->setText(QCoreApplication::translate("RegisterDialog", "\351\252\214\350\257\201\347\240\201\357\274\232", nullptr));
        btn_get->setText(QCoreApplication::translate("RegisterDialog", "\350\216\267\345\217\226", nullptr));
        btn_confirm->setText(QCoreApplication::translate("RegisterDialog", "\347\241\256\350\256\244", nullptr));
        btn_cancel->setText(QCoreApplication::translate("RegisterDialog", "\345\217\226\346\266\210", nullptr));
        label_2->setText(QCoreApplication::translate("RegisterDialog", "\346\263\250\345\206\214\346\210\220\345\212\237\357\274\201", nullptr));
        label_3->setText(QCoreApplication::translate("RegisterDialog", "\345\260\206\345\234\2503s\345\220\216\350\267\263\350\275\254\345\210\260\347\231\273\345\275\225\347\225\214\351\235\242", nullptr));
        btn_confirm_2->setText(QCoreApplication::translate("RegisterDialog", "\347\241\256\345\256\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RegisterDialog: public Ui_RegisterDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTERDIALOG_H

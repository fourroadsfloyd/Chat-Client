/********************************************************************************
** Form generated from reading UI file 'resetdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RESETDIALOG_H
#define UI_RESETDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include "timerbtn.h"

QT_BEGIN_NAMESPACE

class Ui_ResetDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout_3;
    QSpacerItem *verticalSpacer;
    QLabel *label;
    QSpacerItem *verticalSpacer_2;
    QLabel *label_err;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_2;
    QLineEdit *edit_user;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_5;
    QLineEdit *edit_email;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_3;
    QLineEdit *edit_verify;
    TimerBtn *btn_get;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_4;
    QLineEdit *edit_pwd;
    QHBoxLayout *horizontalLayout_9;
    QPushButton *btn_confirm;
    QPushButton *btn_return;

    void setupUi(QDialog *ResetDialog)
    {
        if (ResetDialog->objectName().isEmpty())
            ResetDialog->setObjectName("ResetDialog");
        ResetDialog->resize(350, 500);
        ResetDialog->setMinimumSize(QSize(350, 500));
        ResetDialog->setMaximumSize(QSize(350, 500));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/res/wx.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ResetDialog->setWindowIcon(icon);
        verticalLayout_2 = new QVBoxLayout(ResetDialog);
        verticalLayout_2->setSpacing(5);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(5, 5, 5, 5);
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(5);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(5, 5, 5, 5);
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        label = new QLabel(ResetDialog);
        label->setObjectName("label");
        label->setPixmap(QPixmap(QString::fromUtf8(":/res/wx.png")));
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_3->addWidget(label);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_2);

        label_err = new QLabel(ResetDialog);
        label_err->setObjectName("label_err");
        label_err->setMinimumSize(QSize(200, 0));
        label_err->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_3->addWidget(label_err);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        label_2 = new QLabel(ResetDialog);
        label_2->setObjectName("label_2");
        QFont font;
        font.setPointSize(10);
        label_2->setFont(font);

        horizontalLayout_5->addWidget(label_2);

        edit_user = new QLineEdit(ResetDialog);
        edit_user->setObjectName("edit_user");
        edit_user->setMinimumSize(QSize(200, 30));
        edit_user->setMaximumSize(QSize(16777215, 30));

        horizontalLayout_5->addWidget(edit_user);


        verticalLayout_3->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        label_5 = new QLabel(ResetDialog);
        label_5->setObjectName("label_5");
        label_5->setFont(font);

        horizontalLayout_6->addWidget(label_5);

        edit_email = new QLineEdit(ResetDialog);
        edit_email->setObjectName("edit_email");
        edit_email->setMinimumSize(QSize(200, 30));
        edit_email->setMaximumSize(QSize(275, 30));

        horizontalLayout_6->addWidget(edit_email);


        verticalLayout_3->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        label_3 = new QLabel(ResetDialog);
        label_3->setObjectName("label_3");

        horizontalLayout_7->addWidget(label_3);

        edit_verify = new QLineEdit(ResetDialog);
        edit_verify->setObjectName("edit_verify");
        edit_verify->setMinimumSize(QSize(0, 29));
        edit_verify->setMaximumSize(QSize(271, 30));

        horizontalLayout_7->addWidget(edit_verify);

        btn_get = new TimerBtn(ResetDialog);
        btn_get->setObjectName("btn_get");
        btn_get->setMinimumSize(QSize(60, 30));
        btn_get->setMaximumSize(QSize(60, 30));

        horizontalLayout_7->addWidget(btn_get);


        verticalLayout_3->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        label_4 = new QLabel(ResetDialog);
        label_4->setObjectName("label_4");

        horizontalLayout_8->addWidget(label_4);

        edit_pwd = new QLineEdit(ResetDialog);
        edit_pwd->setObjectName("edit_pwd");
        edit_pwd->setMinimumSize(QSize(0, 30));
        edit_pwd->setMaximumSize(QSize(16777215, 30));

        horizontalLayout_8->addWidget(edit_pwd);


        verticalLayout_3->addLayout(horizontalLayout_8);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        btn_confirm = new QPushButton(ResetDialog);
        btn_confirm->setObjectName("btn_confirm");
        btn_confirm->setMinimumSize(QSize(100, 30));
        btn_confirm->setMaximumSize(QSize(100, 30));

        horizontalLayout_9->addWidget(btn_confirm);

        btn_return = new QPushButton(ResetDialog);
        btn_return->setObjectName("btn_return");
        btn_return->setMinimumSize(QSize(100, 30));
        btn_return->setMaximumSize(QSize(100, 30));

        horizontalLayout_9->addWidget(btn_return);


        verticalLayout_3->addLayout(horizontalLayout_9);


        verticalLayout_2->addLayout(verticalLayout_3);


        retranslateUi(ResetDialog);

        QMetaObject::connectSlotsByName(ResetDialog);
    } // setupUi

    void retranslateUi(QDialog *ResetDialog)
    {
        ResetDialog->setWindowTitle(QCoreApplication::translate("ResetDialog", "Reset", nullptr));
        label->setText(QString());
        label_err->setText(QString());
        label_2->setText(QCoreApplication::translate("ResetDialog", "\347\224\250\346\210\267\345\220\215\357\274\232", nullptr));
        label_5->setText(QCoreApplication::translate("ResetDialog", "\351\202\256\347\256\261\357\274\232", nullptr));
        label_3->setText(QCoreApplication::translate("ResetDialog", "\351\252\214\350\257\201\347\240\201\357\274\232", nullptr));
        btn_get->setText(QCoreApplication::translate("ResetDialog", "\350\216\267\345\217\226", nullptr));
        label_4->setText(QCoreApplication::translate("ResetDialog", "\346\226\260\345\257\206\347\240\201\357\274\232", nullptr));
        btn_confirm->setText(QCoreApplication::translate("ResetDialog", "\347\241\256\350\256\244", nullptr));
        btn_return->setText(QCoreApplication::translate("ResetDialog", "\350\277\224\345\233\236", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ResetDialog: public Ui_ResetDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESETDIALOG_H

/********************************************************************************
** Form generated from reading UI file 'AddFriendDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDFRIENDDIALOG_H
#define UI_ADDFRIENDDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AddFriendDialog
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QWidget *widget_5;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *btn_icon;
    QWidget *widget_6;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_name;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout_3;
    QWidget *widget_4;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QLabel *label_2;
    QLabel *label_uid;
    QSpacerItem *horizontalSpacer_2;
    QWidget *widget_7;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label;
    QLabel *label_email;
    QSpacerItem *horizontalSpacer_4;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *btn_addfriend;
    QSpacerItem *horizontalSpacer_6;

    void setupUi(QDialog *AddFriendDialog)
    {
        if (AddFriendDialog->objectName().isEmpty())
            AddFriendDialog->setObjectName("AddFriendDialog");
        AddFriendDialog->resize(330, 376);
        verticalLayout = new QVBoxLayout(AddFriendDialog);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(AddFriendDialog);
        widget->setObjectName("widget");
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        widget_5 = new QWidget(widget);
        widget_5->setObjectName("widget_5");
        horizontalLayout_2 = new QHBoxLayout(widget_5);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(70, 40, 10, 40);
        btn_icon = new QPushButton(widget_5);
        btn_icon->setObjectName("btn_icon");
        btn_icon->setMinimumSize(QSize(70, 70));
        btn_icon->setMaximumSize(QSize(70, 70));

        horizontalLayout_2->addWidget(btn_icon);


        horizontalLayout->addWidget(widget_5);

        widget_6 = new QWidget(widget);
        widget_6->setObjectName("widget_6");
        verticalLayout_2 = new QVBoxLayout(widget_6);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(5, 60, 50, 60);
        label_name = new QLabel(widget_6);
        label_name->setObjectName("label_name");

        verticalLayout_2->addWidget(label_name);


        horizontalLayout->addWidget(widget_6);


        verticalLayout->addWidget(widget);

        widget_2 = new QWidget(AddFriendDialog);
        widget_2->setObjectName("widget_2");
        verticalLayout_3 = new QVBoxLayout(widget_2);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        widget_4 = new QWidget(widget_2);
        widget_4->setObjectName("widget_4");
        horizontalLayout_3 = new QHBoxLayout(widget_4);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        label_2 = new QLabel(widget_4);
        label_2->setObjectName("label_2");
        label_2->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_3->addWidget(label_2);

        label_uid = new QLabel(widget_4);
        label_uid->setObjectName("label_uid");

        horizontalLayout_3->addWidget(label_uid);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);


        verticalLayout_3->addWidget(widget_4);

        widget_7 = new QWidget(widget_2);
        widget_7->setObjectName("widget_7");
        horizontalLayout_4 = new QHBoxLayout(widget_7);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);

        label = new QLabel(widget_7);
        label->setObjectName("label");
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_4->addWidget(label);

        label_email = new QLabel(widget_7);
        label_email->setObjectName("label_email");

        horizontalLayout_4->addWidget(label_email);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);


        verticalLayout_3->addWidget(widget_7);


        verticalLayout->addWidget(widget_2);

        widget_3 = new QWidget(AddFriendDialog);
        widget_3->setObjectName("widget_3");
        horizontalLayout_6 = new QHBoxLayout(widget_3);
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_5);

        btn_addfriend = new QPushButton(widget_3);
        btn_addfriend->setObjectName("btn_addfriend");
        btn_addfriend->setMinimumSize(QSize(50, 50));
        btn_addfriend->setMaximumSize(QSize(50, 50));
        btn_addfriend->setSizeIncrement(QSize(0, 0));

        horizontalLayout_6->addWidget(btn_addfriend);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_6);


        verticalLayout->addWidget(widget_3);


        retranslateUi(AddFriendDialog);

        QMetaObject::connectSlotsByName(AddFriendDialog);
    } // setupUi

    void retranslateUi(QDialog *AddFriendDialog)
    {
        AddFriendDialog->setWindowTitle(QCoreApplication::translate("AddFriendDialog", "Dialog", nullptr));
        btn_icon->setText(QString());
        label_name->setText(QString());
        label_2->setText(QCoreApplication::translate("AddFriendDialog", "UID:", nullptr));
        label_uid->setText(QString());
        label->setText(QCoreApplication::translate("AddFriendDialog", "Email:", nullptr));
        label_email->setText(QString());
        btn_addfriend->setText(QCoreApplication::translate("AddFriendDialog", "\346\267\273\345\212\240", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddFriendDialog: public Ui_AddFriendDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDFRIENDDIALOG_H

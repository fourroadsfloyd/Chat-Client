/********************************************************************************
** Form generated from reading UI file 'AddFriendErrorDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDFRIENDERRORDIALOG_H
#define UI_ADDFRIENDERRORDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AddFriendErrorDialog
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *label_addfriend_err_tip;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *btn_addfriend_close;

    void setupUi(QDialog *AddFriendErrorDialog)
    {
        if (AddFriendErrorDialog->objectName().isEmpty())
            AddFriendErrorDialog->setObjectName("AddFriendErrorDialog");
        AddFriendErrorDialog->resize(323, 249);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/res/wx.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        AddFriendErrorDialog->setWindowIcon(icon);
        verticalLayout = new QVBoxLayout(AddFriendErrorDialog);
        verticalLayout->setObjectName("verticalLayout");
        widget = new QWidget(AddFriendErrorDialog);
        widget->setObjectName("widget");
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName("horizontalLayout");
        label_addfriend_err_tip = new QLabel(widget);
        label_addfriend_err_tip->setObjectName("label_addfriend_err_tip");
        QFont font;
        font.setPointSize(14);
        label_addfriend_err_tip->setFont(font);
        label_addfriend_err_tip->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout->addWidget(label_addfriend_err_tip);


        verticalLayout->addWidget(widget);

        widget_2 = new QWidget(AddFriendErrorDialog);
        widget_2->setObjectName("widget_2");
        horizontalLayout_2 = new QHBoxLayout(widget_2);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        btn_addfriend_close = new QPushButton(widget_2);
        btn_addfriend_close->setObjectName("btn_addfriend_close");
        btn_addfriend_close->setMinimumSize(QSize(70, 60));
        btn_addfriend_close->setMaximumSize(QSize(70, 60));

        horizontalLayout_2->addWidget(btn_addfriend_close);


        verticalLayout->addWidget(widget_2);


        retranslateUi(AddFriendErrorDialog);

        QMetaObject::connectSlotsByName(AddFriendErrorDialog);
    } // setupUi

    void retranslateUi(QDialog *AddFriendErrorDialog)
    {
        AddFriendErrorDialog->setWindowTitle(QCoreApplication::translate("AddFriendErrorDialog", "ErrTip", nullptr));
        label_addfriend_err_tip->setText(QCoreApplication::translate("AddFriendErrorDialog", "\350\257\245\347\224\250\346\210\267\344\270\215\345\255\230\345\234\250\357\274\201", nullptr));
        btn_addfriend_close->setText(QCoreApplication::translate("AddFriendErrorDialog", "\345\205\263\351\227\255", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddFriendErrorDialog: public Ui_AddFriendErrorDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDFRIENDERRORDIALOG_H

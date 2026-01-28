/********************************************************************************
** Form generated from reading UI file 'ChatWidget.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATWIDGET_H
#define UI_CHATWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "clickedbtn.h"
#include "msginput.h"

QT_BEGIN_NAMESPACE

class Ui_ChatWidget
{
public:
    QHBoxLayout *horizontalLayout_2;
    QWidget *first_bar;
    QVBoxLayout *verticalLayout_3;
    QPushButton *root_icon;
    QPushButton *chat_icon;
    QPushButton *contact_icon;
    QSpacerItem *verticalSpacer;
    QWidget *second_bar;
    QVBoxLayout *verticalLayout;
    QWidget *search_widget;
    QHBoxLayout *horizontalLayout;
    QLineEdit *edit_search;
    QSpacerItem *horizontalSpacer_3;
    ClickedBtn *btn_search;
    QStackedWidget *second_stackedWidget;
    QWidget *first_widget;
    QVBoxLayout *verticalLayout_4;
    QListView *chat_list_view;
    QWidget *second_widget;
    QVBoxLayout *verticalLayout_5;
    QWidget *newfriend_widget;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *pushButton;
    QPushButton *btn_applyList;
    QWidget *widget;
    QVBoxLayout *verticalLayout_8;
    QListView *contact_list_view;
    QWidget *third_bar;
    QVBoxLayout *verticalLayout_2;
    QStackedWidget *third_stackWidget;
    QWidget *init_widget;
    QWidget *ApplyFriend_widget;
    QVBoxLayout *verticalLayout_11;
    QListView *apply_list_view;
    QWidget *chat_widget;
    QVBoxLayout *verticalLayout_6;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_username;
    QWidget *msg_widget;
    QHBoxLayout *horizontalLayout_9;
    QListView *msg_listView;
    QWidget *toolbar_widget;
    QHBoxLayout *horizontalLayout_3;
    ClickedBtn *btn_emoji;
    ClickedBtn *btn_file;
    QSpacerItem *horizontalSpacer_2;
    QWidget *input_widget;
    QVBoxLayout *verticalLayout_7;
    MsgInput *edit_input;
    QWidget *send_widget;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer;
    QPushButton *btn_send;
    QWidget *contact_widget;
    QVBoxLayout *verticalLayout_9;
    QWidget *detail_widget;
    QVBoxLayout *verticalLayout_12;
    QWidget *widget_4;
    QVBoxLayout *verticalLayout_13;
    QSpacerItem *verticalSpacer_3;
    QWidget *widget_5;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *contact_icon_2;
    QLabel *contact_name;
    QWidget *widget_6;
    QVBoxLayout *verticalLayout_10;
    QLabel *contact_uid;
    QLabel *contact_email;
    QWidget *widget_7;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *btn_sendMsg;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QWidget *ChatWidget)
    {
        if (ChatWidget->objectName().isEmpty())
            ChatWidget->setObjectName("ChatWidget");
        ChatWidget->resize(939, 705);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/res/wx.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ChatWidget->setWindowIcon(icon);
        horizontalLayout_2 = new QHBoxLayout(ChatWidget);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        first_bar = new QWidget(ChatWidget);
        first_bar->setObjectName("first_bar");
        first_bar->setMinimumSize(QSize(70, 0));
        first_bar->setMaximumSize(QSize(70, 16777215));
        verticalLayout_3 = new QVBoxLayout(first_bar);
        verticalLayout_3->setSpacing(20);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(-1, 10, -1, -1);
        root_icon = new QPushButton(first_bar);
        root_icon->setObjectName("root_icon");
        root_icon->setMinimumSize(QSize(0, 50));
        root_icon->setMaximumSize(QSize(16777215, 50));

        verticalLayout_3->addWidget(root_icon);

        chat_icon = new QPushButton(first_bar);
        chat_icon->setObjectName("chat_icon");
        chat_icon->setMinimumSize(QSize(0, 50));
        chat_icon->setMaximumSize(QSize(16777215, 50));

        verticalLayout_3->addWidget(chat_icon);

        contact_icon = new QPushButton(first_bar);
        contact_icon->setObjectName("contact_icon");
        contact_icon->setMinimumSize(QSize(0, 50));
        contact_icon->setMaximumSize(QSize(16777215, 50));

        verticalLayout_3->addWidget(contact_icon);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);


        horizontalLayout_2->addWidget(first_bar);

        second_bar = new QWidget(ChatWidget);
        second_bar->setObjectName("second_bar");
        second_bar->setMinimumSize(QSize(240, 0));
        second_bar->setMaximumSize(QSize(240, 16777215));
        second_bar->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        verticalLayout = new QVBoxLayout(second_bar);
        verticalLayout->setSpacing(9);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        search_widget = new QWidget(second_bar);
        search_widget->setObjectName("search_widget");
        search_widget->setMinimumSize(QSize(0, 50));
        search_widget->setMaximumSize(QSize(16777215, 50));
        horizontalLayout = new QHBoxLayout(search_widget);
        horizontalLayout->setSpacing(5);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setSizeConstraint(QLayout::SizeConstraint::SetDefaultConstraint);
        horizontalLayout->setContentsMargins(5, 15, 5, 0);
        edit_search = new QLineEdit(search_widget);
        edit_search->setObjectName("edit_search");
        edit_search->setMinimumSize(QSize(190, 30));
        edit_search->setMaximumSize(QSize(190, 30));
        edit_search->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);

        horizontalLayout->addWidget(edit_search);

        horizontalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        btn_search = new ClickedBtn(search_widget);
        btn_search->setObjectName("btn_search");
        btn_search->setMinimumSize(QSize(30, 30));
        btn_search->setMaximumSize(QSize(30, 30));

        horizontalLayout->addWidget(btn_search);


        verticalLayout->addWidget(search_widget);

        second_stackedWidget = new QStackedWidget(second_bar);
        second_stackedWidget->setObjectName("second_stackedWidget");
        first_widget = new QWidget();
        first_widget->setObjectName("first_widget");
        verticalLayout_4 = new QVBoxLayout(first_widget);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        chat_list_view = new QListView(first_widget);
        chat_list_view->setObjectName("chat_list_view");

        verticalLayout_4->addWidget(chat_list_view);

        second_stackedWidget->addWidget(first_widget);
        second_widget = new QWidget();
        second_widget->setObjectName("second_widget");
        verticalLayout_5 = new QVBoxLayout(second_widget);
        verticalLayout_5->setSpacing(0);
        verticalLayout_5->setObjectName("verticalLayout_5");
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        newfriend_widget = new QWidget(second_widget);
        newfriend_widget->setObjectName("newfriend_widget");
        newfriend_widget->setMinimumSize(QSize(0, 50));
        newfriend_widget->setMaximumSize(QSize(16777215, 50));
        horizontalLayout_5 = new QHBoxLayout(newfriend_widget);
        horizontalLayout_5->setSpacing(0);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalLayout_5->setContentsMargins(10, 0, 10, 0);
        pushButton = new QPushButton(newfriend_widget);
        pushButton->setObjectName("pushButton");
        pushButton->setMinimumSize(QSize(0, 50));
        pushButton->setMaximumSize(QSize(50, 50));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/res/add_friend.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton->setIcon(icon1);
        pushButton->setIconSize(QSize(50, 50));

        horizontalLayout_5->addWidget(pushButton);

        btn_applyList = new QPushButton(newfriend_widget);
        btn_applyList->setObjectName("btn_applyList");
        btn_applyList->setMinimumSize(QSize(0, 50));
        btn_applyList->setMaximumSize(QSize(16777215, 50));

        horizontalLayout_5->addWidget(btn_applyList);


        verticalLayout_5->addWidget(newfriend_widget);

        widget = new QWidget(second_widget);
        widget->setObjectName("widget");
        verticalLayout_8 = new QVBoxLayout(widget);
        verticalLayout_8->setSpacing(0);
        verticalLayout_8->setObjectName("verticalLayout_8");
        verticalLayout_8->setContentsMargins(0, 0, 0, 0);
        contact_list_view = new QListView(widget);
        contact_list_view->setObjectName("contact_list_view");

        verticalLayout_8->addWidget(contact_list_view);


        verticalLayout_5->addWidget(widget);

        second_stackedWidget->addWidget(second_widget);

        verticalLayout->addWidget(second_stackedWidget);


        horizontalLayout_2->addWidget(second_bar);

        third_bar = new QWidget(ChatWidget);
        third_bar->setObjectName("third_bar");
        verticalLayout_2 = new QVBoxLayout(third_bar);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 10, 0, 0);
        third_stackWidget = new QStackedWidget(third_bar);
        third_stackWidget->setObjectName("third_stackWidget");
        init_widget = new QWidget();
        init_widget->setObjectName("init_widget");
        third_stackWidget->addWidget(init_widget);
        ApplyFriend_widget = new QWidget();
        ApplyFriend_widget->setObjectName("ApplyFriend_widget");
        verticalLayout_11 = new QVBoxLayout(ApplyFriend_widget);
        verticalLayout_11->setObjectName("verticalLayout_11");
        apply_list_view = new QListView(ApplyFriend_widget);
        apply_list_view->setObjectName("apply_list_view");

        verticalLayout_11->addWidget(apply_list_view);

        third_stackWidget->addWidget(ApplyFriend_widget);
        chat_widget = new QWidget();
        chat_widget->setObjectName("chat_widget");
        verticalLayout_6 = new QVBoxLayout(chat_widget);
        verticalLayout_6->setSpacing(0);
        verticalLayout_6->setObjectName("verticalLayout_6");
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        widget_3 = new QWidget(chat_widget);
        widget_3->setObjectName("widget_3");
        widget_3->setMinimumSize(QSize(0, 30));
        widget_3->setMaximumSize(QSize(16777215, 30));
        horizontalLayout_8 = new QHBoxLayout(widget_3);
        horizontalLayout_8->setSpacing(0);
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        horizontalLayout_8->setContentsMargins(15, 0, 0, 0);
        label_username = new QLabel(widget_3);
        label_username->setObjectName("label_username");
        label_username->setMinimumSize(QSize(0, 30));
        label_username->setMaximumSize(QSize(16777215, 30));
        QFont font;
        font.setPointSize(12);
        label_username->setFont(font);

        horizontalLayout_8->addWidget(label_username);


        verticalLayout_6->addWidget(widget_3);

        msg_widget = new QWidget(chat_widget);
        msg_widget->setObjectName("msg_widget");
        horizontalLayout_9 = new QHBoxLayout(msg_widget);
        horizontalLayout_9->setSpacing(0);
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        horizontalLayout_9->setContentsMargins(0, 0, 0, 0);
        msg_listView = new QListView(msg_widget);
        msg_listView->setObjectName("msg_listView");

        horizontalLayout_9->addWidget(msg_listView);


        verticalLayout_6->addWidget(msg_widget);

        toolbar_widget = new QWidget(chat_widget);
        toolbar_widget->setObjectName("toolbar_widget");
        toolbar_widget->setMinimumSize(QSize(0, 40));
        toolbar_widget->setMaximumSize(QSize(16777215, 40));
        horizontalLayout_3 = new QHBoxLayout(toolbar_widget);
        horizontalLayout_3->setSpacing(15);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(10, 0, 0, 0);
        btn_emoji = new ClickedBtn(toolbar_widget);
        btn_emoji->setObjectName("btn_emoji");
        btn_emoji->setMinimumSize(QSize(40, 40));
        btn_emoji->setMaximumSize(QSize(40, 40));

        horizontalLayout_3->addWidget(btn_emoji);

        btn_file = new ClickedBtn(toolbar_widget);
        btn_file->setObjectName("btn_file");
        btn_file->setMinimumSize(QSize(40, 40));
        btn_file->setMaximumSize(QSize(40, 40));

        horizontalLayout_3->addWidget(btn_file);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);


        verticalLayout_6->addWidget(toolbar_widget);

        input_widget = new QWidget(chat_widget);
        input_widget->setObjectName("input_widget");
        input_widget->setMinimumSize(QSize(0, 200));
        input_widget->setMaximumSize(QSize(16777215, 200));
        verticalLayout_7 = new QVBoxLayout(input_widget);
        verticalLayout_7->setSpacing(0);
        verticalLayout_7->setObjectName("verticalLayout_7");
        verticalLayout_7->setContentsMargins(0, 0, 0, 0);
        edit_input = new MsgInput(input_widget);
        edit_input->setObjectName("edit_input");
        edit_input->setMinimumSize(QSize(0, 50));

        verticalLayout_7->addWidget(edit_input);

        send_widget = new QWidget(input_widget);
        send_widget->setObjectName("send_widget");
        send_widget->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        horizontalLayout_4 = new QHBoxLayout(send_widget);
        horizontalLayout_4->setSpacing(5);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(0, 0, 10, 5);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        btn_send = new QPushButton(send_widget);
        btn_send->setObjectName("btn_send");
        btn_send->setMinimumSize(QSize(0, 30));
        btn_send->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_4->addWidget(btn_send);


        verticalLayout_7->addWidget(send_widget);


        verticalLayout_6->addWidget(input_widget);

        third_stackWidget->addWidget(chat_widget);
        contact_widget = new QWidget();
        contact_widget->setObjectName("contact_widget");
        verticalLayout_9 = new QVBoxLayout(contact_widget);
        verticalLayout_9->setObjectName("verticalLayout_9");
        detail_widget = new QWidget(contact_widget);
        detail_widget->setObjectName("detail_widget");
        verticalLayout_12 = new QVBoxLayout(detail_widget);
        verticalLayout_12->setObjectName("verticalLayout_12");
        verticalLayout_12->setContentsMargins(100, 100, 100, 100);
        widget_4 = new QWidget(detail_widget);
        widget_4->setObjectName("widget_4");
        verticalLayout_13 = new QVBoxLayout(widget_4);
        verticalLayout_13->setSpacing(0);
        verticalLayout_13->setObjectName("verticalLayout_13");
        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_13->addItem(verticalSpacer_3);

        widget_5 = new QWidget(widget_4);
        widget_5->setObjectName("widget_5");
        widget_5->setMinimumSize(QSize(0, 80));
        widget_5->setMaximumSize(QSize(16777215, 80));
        horizontalLayout_6 = new QHBoxLayout(widget_5);
        horizontalLayout_6->setSpacing(20);
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalLayout_6->setContentsMargins(50, 0, 50, 0);
        contact_icon_2 = new QPushButton(widget_5);
        contact_icon_2->setObjectName("contact_icon_2");
        contact_icon_2->setMinimumSize(QSize(80, 80));
        contact_icon_2->setMaximumSize(QSize(80, 80));

        horizontalLayout_6->addWidget(contact_icon_2);

        contact_name = new QLabel(widget_5);
        contact_name->setObjectName("contact_name");
        contact_name->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_6->addWidget(contact_name);


        verticalLayout_13->addWidget(widget_5);

        widget_6 = new QWidget(widget_4);
        widget_6->setObjectName("widget_6");
        widget_6->setMinimumSize(QSize(0, 120));
        widget_6->setMaximumSize(QSize(16777215, 120));
        verticalLayout_10 = new QVBoxLayout(widget_6);
        verticalLayout_10->setObjectName("verticalLayout_10");
        contact_uid = new QLabel(widget_6);
        contact_uid->setObjectName("contact_uid");
        contact_uid->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_10->addWidget(contact_uid);

        contact_email = new QLabel(widget_6);
        contact_email->setObjectName("contact_email");
        contact_email->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_10->addWidget(contact_email);


        verticalLayout_13->addWidget(widget_6);

        widget_7 = new QWidget(widget_4);
        widget_7->setObjectName("widget_7");
        horizontalLayout_7 = new QHBoxLayout(widget_7);
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_4);

        btn_sendMsg = new QPushButton(widget_7);
        btn_sendMsg->setObjectName("btn_sendMsg");
        btn_sendMsg->setMinimumSize(QSize(0, 50));
        btn_sendMsg->setMaximumSize(QSize(16777215, 50));

        horizontalLayout_7->addWidget(btn_sendMsg);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_5);


        verticalLayout_13->addWidget(widget_7);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_13->addItem(verticalSpacer_2);


        verticalLayout_12->addWidget(widget_4);


        verticalLayout_9->addWidget(detail_widget);

        third_stackWidget->addWidget(contact_widget);

        verticalLayout_2->addWidget(third_stackWidget);


        horizontalLayout_2->addWidget(third_bar);


        retranslateUi(ChatWidget);

        second_stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ChatWidget);
    } // setupUi

    void retranslateUi(QWidget *ChatWidget)
    {
        ChatWidget->setWindowTitle(QCoreApplication::translate("ChatWidget", "Ppao", nullptr));
        root_icon->setText(QString());
        chat_icon->setText(QString());
        contact_icon->setText(QString());
        btn_search->setText(QString());
        pushButton->setText(QString());
        btn_applyList->setText(QCoreApplication::translate("ChatWidget", "\346\226\260\347\232\204\346\234\213\345\217\213", nullptr));
        label_username->setText(QCoreApplication::translate("ChatWidget", "WTT", nullptr));
        btn_emoji->setText(QString());
        btn_file->setText(QString());
        btn_send->setText(QCoreApplication::translate("ChatWidget", "\345\217\221\351\200\201", nullptr));
        contact_icon_2->setText(QString());
        contact_name->setText(QString());
        contact_uid->setText(QString());
        contact_email->setText(QString());
        btn_sendMsg->setText(QCoreApplication::translate("ChatWidget", "\345\217\221\346\266\210\346\201\257", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChatWidget: public Ui_ChatWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATWIDGET_H

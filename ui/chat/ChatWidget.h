#ifndef CHATWIDGET_H
#define CHATWIDGET_H

#include <QWidget>
#include <QLabel>

#include "ChatListModel.h"
#include "ChatItemDelegate.h"
#include "ContactItemDelegate.h"
#include "SearchPopup.h"
#include "AddFriendDialog.h"
#include "data/UserStructInfo.h"
#include "AddFriendErrorDialog.h"
#include "ui/chat/ContactListModel.h"
#include "ui/chat/ApplyFriendListModel.h"
#include "ui/chat/ApplyFriendItemDelegate.h"
#include "ui/chat/MsgListModel.h"
#include "ui/chat/MsgItemDelegate.h"
#include "ChatSessionMgr.h"

QT_BEGIN_NAMESPACE

namespace Ui {
class ChatWidget;
}

QT_END_NAMESPACE

class ChatWidget : public QWidget {
    Q_OBJECT

public:
    ChatWidget(QWidget *parent = nullptr);
    ~ChatWidget();

    void UI_Init();    //进入chatdialog后不会因为不同用户给发生改变的组件，对这些组件进行初始化

    bool eventFilter(QObject *watched, QEvent *event);

    void setupChatList();

    void setupContactList();

    void setupApplyList();

    // 更新好友申请红点
    void updateApplyFriendBadge();


private:
    Ui::ChatWidget *ui;

    ChatListModel* _chat_model = nullptr;
    ChatItemDelegate* _chat_delegate = nullptr;

    ContactListModel* _contact_model = nullptr;
    ContactItemDelegate* _contact_delegate = nullptr;

    ApplyFriendListModel* _applyfriend_model = nullptr;
    ApplyFriendItemDelegate* _applyfriend_delegate = nullptr;

    MsgListModel* _msg_model = nullptr;
    MsgItemDelegate* _msg_delegate = nullptr;

    SearchPopup* _search_popup = nullptr;  // 搜索弹出窗口

    AddFriendDialog* _addFriend_dialog = nullptr;

    AddFriendErrorDialog* _addFriendError_dialog = nullptr;

    QLabel* m_badgeLabel = nullptr;  // 红点提示标签

private slots:
    //最左侧页面切换
    void on_chat_icon_clicked();
    void on_contact_icon_clicked();

    //搜索未添加的用户
    void on_btn_search_clicked();
    void slot_user_search(std::shared_ptr<SearchInfo> info);

    void on_btn_applyList_clicked();

    void slot_agree_apply(int toUid);

    void on_btn_sendMsg_clicked();  //联系人详情界面的发送信息按钮，用来跳转到聊天界面

    // 测试函数：添加假消息数据
    //void testAddMessages();

    void on_btn_send_clicked();

    // ChatSessionMgr 信号槽
    void slot_messageReceived(int friendUid, std::shared_ptr<MsgModel::MsgItem> msg);
    void slot_messageSent(int friendUid, std::shared_ptr<MsgModel::MsgItem> msg);

signals:
    void sig_agree_apply(int toUid);

};
#endif // CHATWIDGET_H

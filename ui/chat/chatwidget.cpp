#include "ChatWidget.h"

#include "ui_ChatWidget.h"
#include "MsgInput.h"

#include "global.h"
#include "net/tcpmgr.h"
#include "data/usermgr.h"

#include <QJsonArray>
#include <QAction>
#include <QButtonGroup>
#include <QRandomGenerator>
#include <QDateTime>
#include <QLabel>
#include <QMouseEvent>
#include <QIcon>
#include <QScrollBar>

ChatWidget::ChatWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ChatWidget)
    , _chat_model(new ChatListModel(this)), _chat_delegate(new ChatItemDelegate(this))
    , _contact_model(new ContactListModel(this))
    , _contact_delegate(new ContactItemDelegate(this))
    , _applyfriend_model(new ApplyFriendListModel(this))
    , _applyfriend_delegate(new ApplyFriendItemDelegate(this))
    , _msg_model(new MsgListModel(this))
    , _msg_delegate(new MsgItemDelegate(this))
    , _search_popup(new SearchPopup(this))
    , _addFriend_dialog(new AddFriendDialog(this))
    , _addFriendError_dialog(new AddFriendErrorDialog(this))
{
    ui->setupUi(this);

    scrollBarStyle_enter = QString("QScrollBar:vertical { background: rgba(0, 0, 0, 0.05); width: 8px; border-radius: 4px;}"
                                   "QScrollBar::handle:vertical { background: rgba(0, 0, 0, 0.3); min-height: 20px; border-radius: 4px; }");

    scrollBarStyle_leave = QString("QScrollBar:vertical { background: rgba(0, 0, 0, 0.05); width: 8px; border-radius: 4px; }"
                                   "QScrollBar::handle:vertical { background: transparent; }");

    this->UI_Init();

    this->setupChatList();

    this->setupContactList();

    this->setupApplyList();

    this->setupMsgList();

    // 添加测试数据
    testAddMessages();
}

ChatWidget::~ChatWidget()
{
    delete ui;
}

bool ChatWidget::eventFilter(QObject *watched, QEvent *event)
{
    // 检查事件是否是鼠标悬浮进入或离开
    if (watched == ui->chat_list_view->viewport())
    {
        if (event->type() == QEvent::Enter)
        {
            // 鼠标悬浮，显示滚动条
            ui->chat_list_view->verticalScrollBar()->setStyleSheet(scrollBarStyle_enter);
        }
        else if (event->type() == QEvent::Leave)
        {
            // 鼠标离开，隐藏滚动条
            ui->chat_list_view->verticalScrollBar()->setStyleSheet(scrollBarStyle_leave);
        }
    }

    // 检查事件是否是鼠标悬浮进入或离开
    if (watched == ui->contact_list_view->viewport())
    {
        if (event->type() == QEvent::Enter)
        {
            // 鼠标悬浮，显示滚动条
            ui->contact_list_view->verticalScrollBar()->setStyleSheet(scrollBarStyle_enter);
        }
        else if (event->type() == QEvent::Leave)
        {
            // 鼠标离开，隐藏滚动条
            ui->contact_list_view->verticalScrollBar()->setStyleSheet(scrollBarStyle_leave);
        }
    }

    // msg_listView 滚动条显示/隐藏控制
    if (watched == ui->msg_listView->viewport())
    {
        if (event->type() == QEvent::Enter)
        {
            // 鼠标进入 viewport，显示滚动条
            ui->msg_listView->verticalScrollBar()->setStyleSheet(scrollBarStyle_enter);
        }
        else if (event->type() == QEvent::Leave)
        {
            // 鼠标离开 viewport，隐藏滚动条
            ui->msg_listView->verticalScrollBar()->setStyleSheet(scrollBarStyle_leave);
        }
    }

    if (watched == ui->apply_list_view->viewport() && event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        QPoint pos = mouseEvent->pos();
        QModelIndex index = ui->apply_list_view->indexAt(pos);
        if (index.isValid())
        {
            // 创建 QStyleOptionViewItem 并初始化
            QStyleOptionViewItem option;
            option.initFrom(ui->apply_list_view);  // 初始化字体、调色板等
            option.rect = ui->apply_list_view->visualRect(index);  // 设置项的实际矩形

            // 获取按钮区域
            QRect buttonRect = _applyfriend_delegate->buttonRect(option, index);
            if (buttonRect.contains(pos))
            {
                int toUid = _applyfriend_model->data(index, AddFriendModel::UidRole).toInt();
                //qDebug() << "auth in eventfilter, A id = " << toUid;
                emit this->sig_agree_apply(toUid);
                _applyfriend_model->updateStatus(index, 1); // 更新模型状态为 1（已处理）
            }
        }
    }

    return QWidget::eventFilter(watched, event);    //继续分发事件
}

void ChatWidget::UI_Init()
{
    this->setWindowIcon(QIcon(":/res/wx.png"));

    QString avatarPath = UserMgr::GetInstance()->GetAvatarPath();
    ui->root_icon->setIcon(QIcon(avatarPath));
    ui->root_icon->setIconSize(QSize(50, 50));

    ui->edit_search->setMaxLength(50);

    QAction* searchAction = new QAction(ui->edit_search);
    searchAction->setIcon(QIcon(":/res/search.png"));
    ui->edit_search->addAction(searchAction, QLineEdit::LeadingPosition);
    ui->edit_search->setPlaceholderText(QStringLiteral("搜索"));
    ui->edit_search->setClearButtonEnabled(true);

    QButtonGroup* btnGrp = new QButtonGroup(this);
    btnGrp->addButton(ui->chat_icon);
    btnGrp->addButton(ui->contact_icon);

    ui->chat_icon->setCheckable(true);
    ui->contact_icon->setCheckable(true);

    // 初始化两态（未选中/选中）
    ui->chat_icon->setProperty("type", "nav");
    ui->contact_icon->setProperty("type", "nav");

    // 给 state 起两个名字：normal(灰) / selected(绿)
    ui->chat_icon->setProperty("state", "selected");
    ui->contact_icon->setProperty("state", "normal");

    connect(btnGrp, &QButtonGroup::buttonToggled, this, [](QAbstractButton* btn, bool checked){
        btn->setProperty("state", checked ? "selected" : "normal");
        btn->style()->unpolish(btn);
        btn->style()->polish(btn);
        btn->update();
    });

    ui->chat_icon->setChecked(true);

    ui->second_stackedWidget->setCurrentWidget(ui->first_widget);

    ui->third_stackWidget->setCurrentWidget(ui->chat_widget);

    // 连接 edit_search 的文本改变信号，当输入时自动弹出并更新搜索结果
    connect(ui->edit_search, &QLineEdit::textChanged, this, [this](const QString &text) {
        if (!text.isEmpty() && _search_popup)
        {
            auto info = UserMgr::GetInstance()->findUserByEmail(text);
            if(info) _search_popup->updateList(info);
            info = UserMgr::GetInstance()->findUserByName(text);
            if(info) _search_popup->updateList(info);
            info = UserMgr::GetInstance()->findUserByUid(text.toInt());
            if(info) _search_popup->updateList(info);

            _search_popup->showPopup(ui->edit_search);
        }
        else if (_search_popup)
        {
            _search_popup->hidePopup();
        }
    });

    //当点击添加用户的按钮时，发现该用户不存在时的处理
    connect(TcpMgr::GetInstance().get(), &TcpMgr::sig_user_search_no_user, this, [this](){
        _addFriendError_dialog->show();
    });

    //当点击添加用户的按钮时，搜索到了该用户，将该用户的信息展示出来，且有一个添加好友的按钮
    connect(TcpMgr::GetInstance().get(), &TcpMgr::sig_user_search, this, &ChatWidget::slot_user_search);

    connect(this, &ChatWidget::sig_agree_apply, this, &ChatWidget::slot_agree_apply);

    // 连接 ChatSessionMgr 信号
    connect(ChatSessionMgr::GetInstance().get(), &ChatSessionMgr::sig_messageReceived,
            this, &ChatWidget::slot_messageReceived);
    connect(ChatSessionMgr::GetInstance().get(), &ChatSessionMgr::sig_messageSent,
            this, &ChatWidget::slot_messageSent);

    // 连接 TcpMgr 接收聊天消息信号
    connect(TcpMgr::GetInstance().get(), &TcpMgr::sig_text_chat_msg, this, [](std::shared_ptr<MsgModel::MsgItem> msg, int fromUid) {
        // 将接收到的消息添加到 ChatSessionMgr
        ChatSessionMgr::GetInstance()->addMessage(fromUid, msg);
    });

    // 初始化好友申请红点
    updateApplyFriendBadge();
}

void ChatWidget::setupChatList()
{
    ui->chat_list_view->setModel(_chat_model);
    ui->chat_list_view->setItemDelegate(_chat_delegate);

    ui->chat_list_view->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->chat_list_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    ui->chat_list_view->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

    ui->chat_list_view->viewport()->installEventFilter(this);

    connect(ui->chat_list_view, &QListView::clicked, this, [this](const QModelIndex& index){
        int friendUid = _chat_model->data(index, ChatModel::ChatRole::UidRole).toInt();
        QString friendAvatar = _chat_model->data(index, ChatModel::ChatRole::AvatarRole).toString();
        QString friendName = _chat_model->data(index, ChatModel::ChatRole::NameRole).toString();

        // 使用 ChatSessionMgr 切换会话，传入好友信息
        ChatSessionMgr::GetInstance()->switchSession(friendUid, friendName, friendAvatar, _msg_model);

        ui->label_username->setText(ChatSessionMgr::GetInstance()->currentFriendName());

        ui->third_stackWidget->setCurrentWidget(ui->chat_widget);
    });
}

void ChatWidget::setupContactList()
{
    ui->contact_list_view->setModel(_contact_model);
    ui->contact_list_view->setItemDelegate(_contact_delegate);

    ui->contact_list_view->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->contact_list_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    //将用户的联系人列表打到contact_model中，以便委托绘制
    _contact_model->setContacts(UserMgr::GetInstance()->GetContactList());

    ui->contact_list_view->viewport()->installEventFilter(this);

    //点击联系人列表，进入到联系人的详情页
    connect(ui->contact_list_view, &QListView::clicked, this, [this](const QModelIndex& index){
        ui->contact_icon_2->setIcon(QIcon(_contact_model->data(index, ContactModel::AvatarRole).toString()));
        ui->contact_icon_2->setIconSize(QSize(ui->contact_icon_2->width(), ui->contact_icon_2->height()));
        ui->contact_name->setText(_contact_model->data(index, ContactModel::NameRole).toString());
        ui->contact_uid->setText(_contact_model->data(index, ContactModel::UidRole).toString());
        // TODO: 如果有 contact_email 控件，设置 email
        ui->contact_email->setText(_contact_model->data(index, ContactModel::EmailRole).toString());
        ui->third_stackWidget->setCurrentWidget(ui->contact_widget);
    });
}

void ChatWidget::setupApplyList()
{
    ui->apply_list_view->setModel(_applyfriend_model);
    ui->apply_list_view->setItemDelegate(_applyfriend_delegate);

    ui->apply_list_view->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->apply_list_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    ui->apply_list_view->viewport()->installEventFilter(this);  // 添加：安装事件过滤器

    _applyfriend_model->setApplyFriends(UserMgr::GetInstance()->GetApplyList());
}

void ChatWidget::setupMsgList()
{
    // 初始化消息列表
    ui->msg_listView->setModel(_msg_model);
    ui->msg_listView->setItemDelegate(_msg_delegate);

    ui->msg_listView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);    //直接占位，仅在事件过滤器中设置轨道和滑轮的颜色，以及滑轮出现的时机

    ui->msg_listView->setResizeMode(QListView::Adjust);     // 允许 item 自适应大小
    ui->msg_listView->setUniformItemSizes(false);           // 允许不同 item 有不同尺寸

    // 安装 viewport 事件监听器，用于显示/隐藏滚动条
    ui->msg_listView->viewport()->installEventFilter(this);
}

// 更新好友申请红点
void ChatWidget::updateApplyFriendBadge()
{
    // 获取未处理的好友申请数量
    const auto& applyList = UserMgr::GetInstance()->GetApplyList();
    int unreadCount = 0;

    for (const auto& apply : applyList)
    {
        if (apply->_status == 0)
        {  // 0: 未处理
            unreadCount++;
        }
    }

    // 创建或更新红点标签
    if (unreadCount > 0) {
        if (!m_badgeLabel) {
            m_badgeLabel = new QLabel(ui->contact_icon->parentWidget());
            m_badgeLabel->setFixedSize(16, 16);
            m_badgeLabel->setAlignment(Qt::AlignCenter);
            m_badgeLabel->setStyleSheet(
                    "QLabel {"
                    "   background-color: #ff3b30;"
                    "   color: white;"
                    "   border-radius: 8px;"
                    "   font-size: 10px;"
                    "   font-weight: bold;"
                    "}"
                );
        }

        // 更新位置（在联系人图标右上角）
        QPoint iconPos = ui->contact_icon->pos();
        int iconWidth = ui->contact_icon->width();
        m_badgeLabel->move(iconPos.x() + iconWidth - 8, iconPos.y() - 2);

        // 更新显示的数字
        if (unreadCount > 99) {
            m_badgeLabel->setText("99+");
        } else {
            m_badgeLabel->setText(QString::number(unreadCount));
        }
        m_badgeLabel->show();
    } else {
        // 隐藏红点
        if (m_badgeLabel) {
            m_badgeLabel->hide();
        }
    }
}

//最左侧列表的聊天按钮
void ChatWidget::on_chat_icon_clicked()
{
    ui->second_stackedWidget->setCurrentWidget(ui->first_widget);
    //ui->third_stackWidget->setCurrentWidget(ui->init_widget);

}

//最左侧列表的联系人按钮
void ChatWidget::on_contact_icon_clicked()
{
    ui->second_stackedWidget->setCurrentWidget(ui->second_widget);
    ui->third_stackWidget->setCurrentWidget(ui->init_widget);
}

void ChatWidget::on_btn_search_clicked()
{
    if(ui->edit_search->text().isEmpty()) return;   //搜索框为空

    if(!_search_popup->isEmpty()) return;    //说明已经是联系人了，不要额外添加

    QJsonObject json_obj;
    json_obj["searchkey"] = ui->edit_search->text(); //可能是email 或 uid

    QJsonDocument doc(json_obj);
    QString jsonString = doc.toJson(QJsonDocument::Indented);

    emit TcpMgr::GetInstance()->sig_send_data(ReqId::ID_SEARCH_USER_REQ, jsonString.toUtf8());
}

//搜索用户，tcp中发送的信号对应的槽函数
void ChatWidget::slot_user_search(std::shared_ptr<SearchInfo> info)
{
    _addFriend_dialog->setUiData(info);
    _addFriend_dialog->show();
}

void ChatWidget::on_btn_applyList_clicked()
{
    ui->third_stackWidget->setCurrentWidget(ui->ApplyFriend_widget);
}

void ChatWidget::slot_agree_apply(int toUid)
{
    QJsonObject json_obj;
    json_obj["from_uid"] = UserMgr::GetInstance()->GetUid();
    json_obj["to_uid"] = toUid;

    QJsonDocument doc(json_obj);
    QString jsonString = doc.toJson(QJsonDocument::Indented);

    // qDebug() << "B send the auth request";
    // qDebug() << "B id = " << UserMgr::GetInstance()->GetUid()
    //          << "A id = " << toUid;

    emit TcpMgr::GetInstance()->sig_send_data(ReqId::ID_AUTH_FRIEND_REQ, jsonString.toUtf8());
}

//联系人的详细信息中的发信息按钮，点击后跳转到聊天界面
void ChatWidget::on_btn_sendMsg_clicked()
{
    qDebug() << "=== on_btn_sendMsg_clicked ===";

    // 从联系人详情页获取好友信息
    QString uidText = ui->contact_uid->text();
    QString friendName = ui->contact_name->text();

    qDebug() << "uidText:" << uidText << "name:" << friendName;

    int friendUid = uidText.toInt();

    if (friendUid == 0) {
        qDebug() << "Invalid friend uid:" << friendUid;
        return;
    }

    // 从 UserMgr 中查找完整的好友信息（包括头像路径）
    auto contact = UserMgr::GetInstance()->findUserByUid(friendUid);
    QString friendAvatar = "";
    QString friendEmail = "";

    if (contact)
    {
        friendAvatar = contact->_avatarpath;
        friendEmail = contact->_email;
        qDebug() << "Found contact, avatar:" << friendAvatar << "email:" << friendEmail;
    }
    else
    {
        qDebug() << "Cannot find contact with uid:" << friendUid << ", using default values";
        friendAvatar = "";  // 使用默认空头像
        friendEmail = "";
    }

    // 在 ChatListModel 中添加或获取聊天项
    int chatIndex = _chat_model->getOrAddChatItem(friendUid, friendName, friendAvatar, friendEmail);
    qDebug() << "Chat index:" << chatIndex;

    // 使用 ChatSessionMgr 切换会话
    ChatSessionMgr::GetInstance()->switchSession(friendUid, friendName, friendAvatar, _msg_model);

    ui->label_username->setText(friendName);

    qDebug() << "Switched to chat session, uid:" << friendUid << "name:" << friendName;

    // 跳转到聊天界面
    ui->third_stackWidget->setCurrentWidget(ui->chat_widget);
}

// 测试函数：添加假消息数据
void ChatWidget::testAddMessages()
{
    // 使用 global.h 中的假数据
    for (int i = 0; i < 5; ++i) {
        // 添加对方的消息
        auto otherMsg = std::make_shared<MsgModel::MsgItem>();
        otherMsg->type = MsgModel::MsgItem::TextMessage;
        otherMsg->content = strs[i % strs.size()];
        otherMsg->sender = names[i % names.size()];
        otherMsg->avatar = heads[i % heads.size()];
        otherMsg->senderUid = 1000 + i;
        otherMsg->time = times[i % times.size()];
        otherMsg->isSelf = false;
        _msg_model->addMessage(otherMsg);

        // 添加自己的消息（测试长文本换行）
        auto selfMsg = std::make_shared<MsgModel::MsgItem>();
        selfMsg->type = MsgModel::MsgItem::TextMessage;
        // 添加一条很长的消息来测试自动换行
        if (i == 2) {
            selfMsg->content = "这是一条非常长的消息，用来测试文本自动换行功能。当文本长度超过消息宽度的一半时，应该自动换行显示。这样可以确保所有内容都能正确显示，而不会被截断。";
        } else {
            selfMsg->content = "收到！这是一条回复消息 " + QString::number(i + 1);
        }
        selfMsg->sender = UserMgr::GetInstance()->GetName();
        selfMsg->avatar = UserMgr::GetInstance()->GetAvatarPath();
        selfMsg->senderUid = UserMgr::GetInstance()->GetUid();
        selfMsg->time = times[(i + 1) % times.size()];
        selfMsg->isSelf = true;
        _msg_model->addMessage(selfMsg);
    }

    // 滚动到底部
    ui->msg_listView->scrollToBottom();
}

void ChatWidget::on_btn_send_clicked()
{
    auto user_info = UserMgr::GetInstance()->GetRootUser();
    int currentFriendUid = ChatSessionMgr::GetInstance()->currentFriendUid();

    qDebug() << "=== Send button clicked ===";
    qDebug() << "Current friend uid:" << currentFriendUid;

    // 检查是否有选中的聊天会话
    if (currentFriendUid == 0)
    {
        qDebug() << "No chat session selected";
        return;
    }

    auto pTextEdit = ui->edit_input;
    const QVector<MsgInfo>& msgList = pTextEdit->getMsgList();

    qDebug() << "MsgList size:" << msgList.size();
    if (msgList.isEmpty())
    {
        qDebug() << "MsgList is empty!";
        return;
    }

    // 准备 TCP 发送数据
    QJsonObject textObj;
    QJsonArray textArray;
    int txt_size = 0;

    // 获取当前时间
    QString currentTime = QDateTime::currentDateTime().toString("hh:mm:ss");

    // 辅助 lambda: 创建并发送消息
    auto addAndSendMsg = [&](MsgModel::MsgItem::MsgType type, const QString& content)
    {
        // 1. 创建消息对象并保存到 ChatSessionMgr
        auto msgItem = std::make_shared<MsgModel::MsgItem>();
        msgItem->type = type;
        msgItem->content = content;
        msgItem->sender = user_info->_name;
        msgItem->avatar = user_info->_avatarpath;
        msgItem->senderUid = user_info->_uid;
        msgItem->time = currentTime;
        msgItem->isSelf = true;
        ChatSessionMgr::GetInstance()->addSentMessage(currentFriendUid, msgItem);
    };

    for (const auto& msgInfo : msgList)
    {
        // 消息内容长度不合规就跳过
        if (msgInfo.content.length() > 1024)
        {
            continue;
        }

        QString type = msgInfo.msgFlag;

        if (type == "text")
        {
            // 累积到 TCP 发送数组
            if (txt_size + msgInfo.content.length() > 1024 && !textArray.isEmpty())
            {
                textObj["from_uid"] = user_info->_uid;
                textObj["to_uid"] = currentFriendUid;
                textObj["text_array"] = textArray;
                QJsonDocument doc(textObj);
                QString jsonString = doc.toJson(QJsonDocument::Indented);
                emit TcpMgr::GetInstance()->sig_send_data(ReqId::ID_TEXT_CHAT_MSG_REQ, jsonString.toUtf8());
                // 重置
                txt_size = 0;
                textArray = QJsonArray();
                textObj = QJsonObject();
            }

            txt_size += msgInfo.content.length();
            QJsonObject obj;
            obj["content"] = msgInfo.content;
            obj["msgid"] = QUuid::createUuid().toString();
            textArray.append(obj);

            // 添加到会话管理器
            addAndSendMsg(MsgModel::MsgItem::TextMessage, msgInfo.content);
        }
        else if (type == "image")
        {
            addAndSendMsg(MsgModel::MsgItem::ImageMessage, msgInfo.content);
        }
        else if (type == "file")
        {
            // TODO: 文件消息处理
        }
    }

    // 发送剩余的文本消息给服务器
    if (!textArray.isEmpty())
    {
        textObj["from_uid"] = user_info->_uid;
        textObj["to_uid"] = currentFriendUid;
        textObj["text_array"] = textArray;
        QJsonDocument doc(textObj);
        QString jsonString = doc.toJson(QJsonDocument::Indented);
        emit TcpMgr::GetInstance()->sig_send_data(ReqId::ID_TEXT_CHAT_MSG_REQ, jsonString.toUtf8());
    }
}

// 收到新消息时的槽函数
void ChatWidget::slot_messageReceived(int friendUid, std::shared_ptr<MsgModel::MsgItem> msg)
{
    // 如果是当前正在聊天的会话，实时显示消息
    if (friendUid == ChatSessionMgr::GetInstance()->currentFriendUid()) {
        _msg_model->addMessage(msg);
        // 滚动到底部
        ui->msg_listView->scrollToBottom();
    }
    // 否则消息已经保存在 ChatSessionMgr 的缓存中，下次切换会话时会自动加载
}

// 发送消息后的槽函数
void ChatWidget::slot_messageSent(int friendUid, std::shared_ptr<MsgModel::MsgItem> msg)
{
    qDebug() << "=== slot_messageSent ===";
    qDebug() << "friendUid:" << friendUid << "current:" << ChatSessionMgr::GetInstance()->currentFriendUid();

    // 如果是当前正在聊天的会话，实时显示消息
    if (friendUid == ChatSessionMgr::GetInstance()->currentFriendUid())
    {
        qDebug() << "Adding message to model, content:" << msg->content;
        _msg_model->addMessage(msg);
        qDebug() << "Model row count after add:" << _msg_model->rowCount();
        // 滚动到底部
        ui->msg_listView->scrollToBottom();
    }
    else
    {
        qDebug() << "Not current session, message cached";
    }
}


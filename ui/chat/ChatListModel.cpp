#include "ChatListModel.h"
#include "net/tcpmgr.h"

using namespace ChatModel;

ChatListModel::ChatListModel(QObject *parent)
    : QAbstractListModel(parent)
{
    connect(TcpMgr::GetInstance().get(), &TcpMgr::sig_chatlistview_addItem, this, [this](std::shared_ptr<ChatModel::ChatItem> item){
        this->addChatItem(item);
    });
}

int ChatListModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_chatItems.count();
}

QVariant ChatListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_chatItems.count())
        return QVariant();

    const auto &item = m_chatItems.at(index.row());

    switch (role) {
    case ChatRole::AvatarRole:
        return item->contactInfo->_avatarpath;

    case ChatRole::NameRole:
        return item->name;

    case ChatRole::MessageRole:
        return item->lastMessage;

    case ChatRole::TimeRole:
        return formatTime(item->time);

    case ChatRole::UnreadCountRole:
        return item->unreadCount;

    case ChatRole::IsMutedRole:
        return item->isMuted;

    case ChatRole::UidRole:
        return item->contactInfo->_uid;

    case ChatRole::EmailRole:
        return item->contactInfo->_email;

    default:
        return QVariant();
    }
}

void ChatListModel::addChatItem(std::shared_ptr<ChatItem> item)
{
    int row = m_chatItems.count();

    beginInsertRows(QModelIndex(), row, row);
    this->m_chatItems.append(item);
    endInsertRows();
}

// 添加聊天项（便捷方法）
void ChatListModel::addChatItem(const QString &name, const QString &message, const QString &time)
{
    ChatItem item;
    item.name = name;
    item.lastMessage = message;

    // 解析时间字符串
    if (time.contains(":")) {
        // 今天的时间，格式如 "10:30"
        QTime t = QTime::fromString(time, "hh:mm");
        item.time = QDateTime(QDate::currentDate(), t);
    } else if (time == "昨天") {
        item.time = QDateTime::currentDateTime().addDays(-1);
    } else if (time.startsWith("星期")) {
        item.time = QDateTime::currentDateTime().addDays(-3);
    } else {
        // 使用日期格式 "MM/dd"
        QDate d = QDate::fromString(time, "MM/dd");
        if (d.isValid()) {
            item.time = QDateTime(d, QTime(0, 0));
        } else {
            item.time = QDateTime::currentDateTime();
        }
    }

    addChatItem(std::make_shared<ChatItem>(item));
}

// 按时间排序
void ChatListModel::sortByTime()
{
    beginResetModel();

    std::sort(m_chatItems.begin(), m_chatItems.end(),
              [](const std::shared_ptr<ChatItem>& a, const std::shared_ptr<ChatItem>& b) {
                  return a->time > b->time;  // 降序，最新的在前面
              });

    endResetModel();
}

// 格式化时间显示
QString ChatListModel::formatTime(const QDateTime &time) const
{
    QDateTime now = QDateTime::currentDateTime();
    QDate today = now.date();
    QDate messageDate = time.date();

    // 今天的消息，显示时间
    if (messageDate == today) {
        return time.toString("hh:mm");
    }

    // 昨天的消息
    if (messageDate == today.addDays(-1)) {
        return "昨天";
    }

    // 本周的消息，显示星期
    int daysAgo = messageDate.daysTo(today);
    if (daysAgo < 7) {
        QStringList weekDays = {"星期日", "星期一", "星期二", "星期三",
                                "星期四", "星期五", "星期六"};
        return weekDays[messageDate.dayOfWeek() % 7];
    }

    // 今年的消息，显示月日
    if (messageDate.year() == today.year()) {
        return time.toString("MM/dd");
    }

    // 更早的消息，显示年月日
    return time.toString("yyyy/MM/dd");
}

// 查找指定 uid 的聊天项索引
int ChatListModel::findChatItemByUid(int uid) const
{
    for (int i = 0; i < m_chatItems.size(); ++i) {
        if (m_chatItems[i]->contactInfo && m_chatItems[i]->contactInfo->_uid == uid)
        {
            return i;
        }
    }
    return -1;
}

// 添加或获取聊天项（如果已存在则不添加），返回索引
int ChatListModel::getOrAddChatItem(int uid, const QString &name, const QString &avatar, const QString &email)
{
    // 先查找是否已存在
    int existingIndex = findChatItemByUid(uid);
    if (existingIndex >= 0)
    {
        return existingIndex;
    }

    // 不存在则添加新项
    ChatItem item;
    item.name = name;
    item.lastMessage = "";  // 新会话没有最后消息
    item.time = QDateTime::currentDateTime();
    item.unreadCount = 0;
    item.isMuted = false;
    item.contactInfo = std::make_shared<ContactInfo>(uid, avatar, name, email);

    addChatItem(std::make_shared<ChatItem>(item));

    // 返回新添加项的索引（最后一项）
    return m_chatItems.size() - 1;
}

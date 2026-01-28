#ifndef MSGITEMDELEGATE_H
#define MSGITEMDELEGATE_H

#include <QStyledItemDelegate>

class MsgItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit MsgItemDelegate(QObject *parent = nullptr);
};

#endif // MSGITEMDELEGATE_H

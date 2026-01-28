#ifndef SEARCHPOPUP_H
#define SEARCHPOPUP_H

#include <QWidget>
#include <QListWidget>
#include <QVBoxLayout>
#include "ui/chat/SearchListModel.h"
#include "ui/chat/SearchItemDelegate.h"

class SearchPopup : public QWidget
{
    Q_OBJECT

public:
    explicit SearchPopup(QWidget *parent = nullptr);
    ~SearchPopup();

    void showPopup(QWidget* anchorWidget);  // 在指定控件下方显示
    void hidePopup();

    void updateList(std::shared_ptr<ContactInfo> info);

    bool isEmpty();

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    QListView* _listview;
    QVBoxLayout* _layout;

    SearchListModel* _model = nullptr;
    SearchItemDelegate* _delegate = nullptr;
};

#endif // SEARCHPOPUP_H

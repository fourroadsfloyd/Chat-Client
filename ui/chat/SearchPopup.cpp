#include "SearchPopup.h"
#include <QApplication>
#include <QEvent>
#include <QMouseEvent>
#include <QDebug>

SearchPopup::SearchPopup(QWidget *parent)
    : QWidget(parent), _model(new SearchListModel(this)), _delegate(new SearchItemDelegate(this))
{
    // 设置窗口标志：工具窗口、无边框、不抢夺焦点
    setWindowFlags(Qt::Tool | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::WindowDoesNotAcceptFocus);
    setAttribute(Qt::WA_TranslucentBackground, false);
    setAttribute(Qt::WA_ShowWithoutActivating);  // 显示时不激活窗口，不抢夺焦点
    setFocusPolicy(Qt::NoFocus);  // 窗口本身不接受焦点

    // 创建布局
    _layout = new QVBoxLayout(this);
    _layout->setContentsMargins(0, 0, 0, 0);
    _layout->setSpacing(0);

    // 创建列表控件
    _listview = new QListView(this);
    _listview->setMaximumHeight(200);
    _listview->setMinimumWidth(190);
    _listview->setFocusPolicy(Qt::NoFocus);  // 列表也不接受焦点

    _layout->addWidget(_listview);
    
    // 设置样式
    setStyleSheet(
        "QListView {"
        "   border: 1px solid #ccc;"
        "   background-color: white;"
        "   border-radius: 4px;"
        "}"
        "QListView::item {"
        "   padding: 5px;"
        "}"
        "QListView::item:hover {"
        "   background-color: #e0e0e0;"
        "}"
        "QListView::item:selected {"
        "   background-color: #0078d4;"
        "   color: white;"
        "}"
    );

    // 安装全局事件过滤器，监听鼠标点击
    qApp->installEventFilter(this);

    _listview->setModel(_model);
    _listview->setItemDelegate(_delegate);
}

SearchPopup::~SearchPopup()
{
    qApp->removeEventFilter(this);  //还需要卸载过滤器？
}

void SearchPopup::showPopup(QWidget* anchorWidget)
{
    if (!anchorWidget) {
        return;
    }

    // 计算弹出位置：在 anchorWidget 下方
    QPoint globalPos = anchorWidget->mapToGlobal(QPoint(0, anchorWidget->height()));
    move(globalPos);

    // 设置宽度与 anchorWidget 一致
    setFixedWidth(anchorWidget->width() + 50);

    show();
    raise();
    // 不调用 activateWindow()，避免抢夺焦点
}

void SearchPopup::hidePopup()
{
    _model->clear();
    hide();
}

void SearchPopup::updateList(std::shared_ptr<ContactInfo> info)
{
    _model->addSearch(info);
}

bool SearchPopup::isEmpty()
{
    if(_model->getCount())
    {
        return false;
    }

    return true;
}

bool SearchPopup::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        
        // 检查点击是否在弹出窗口之外
        if (isVisible()) {
            // 获取全局坐标
            QPoint globalPos = mouseEvent->globalPosition().toPoint();
            
            // 检查点击是否在弹出窗口内
            QRect popupRect = QRect(mapToGlobal(QPoint(0, 0)), size());
            
            if (!popupRect.contains(globalPos)) {
                // 点击在弹出窗口外，隐藏窗口
                hidePopup();
            }
        }
    }
    
    return QWidget::eventFilter(watched, event);
}


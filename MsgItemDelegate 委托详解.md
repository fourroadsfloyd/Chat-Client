# MsgItemDelegate 委托详解

## 一、什么是委托？

委托（Delegate）是 Qt Model/View 架构中的关键组件，负责**自定义显示和编辑**数据。

```
┌─────────────────────────────────────────────────┐
│                    架构图                        │
├─────────────────────────────────────────────────┤
│  Model (数据层)      →  存储消息数据              │
│       ↓                                        │
│  View (视图层)       →  QListView 显示消息列表    │
│       ↓                                        │
│  Delegate (委托层)   →  自定义绘制每个消息样式    │  ← 我们关注的
└─────────────────────────────────────────────────┘
```

## 二、类的整体结构



```cpp
class MsgItemDelegate : public QStyledItemDelegate
{
public:
    explicit MsgItemDelegate(QObject *parent = nullptr);
    
    // 核心虚函数 - 必须实现
    void paint(...) override;           // 绘制 item
    QSize sizeHint(...) override;       // 返回 item 大小
    
protected:
    // 辅助绘制方法
    void paintSelfMessage(...);         // 绘制自己的消息
    void paintOtherMessage(...);        // 绘制对方的消息
    void paintAvatar(...);              // 绘制头像
    
    // 成员变量
    QFont m_contentFont;                // 内容字体
    QFont m_timeFont;                   // 时间字体
    QFont m_senderFont;                 // 发送者字体
    QFontMetricsF m_contentFontMetrics; // 字体度量（计算尺寸）
    // ...
};
```

## 三、核心工作流程

### 3.1 构造函数 - 初始化



```cpp
MsgItemDelegate::MsgItemDelegate(QObject *parent)
    : QStyledItemDelegate(parent),
      m_contentFontMetrics(m_contentFont),  // 初始化 FontMetrics
      // ...
{
    // 设置字体属性
    m_contentFont.setPointSize(10);       // 内容字号 10
    m_senderFont.setPointSize(9);         // 发送者字号 9
    m_senderFont.setBold(true);           // 发送者加粗
    m_timeFont.setPointSize(8);           // 时间字号 8
    
    // 更新 FontMetrics（基于设置后的字体）
    m_contentFontMetrics = QFontMetricsF(m_contentFont);
    // ...
}
```

**FontMetrics 的作用**：计算文本的宽度和高度



```
QFontMetrics::horizontalAdvance("你好")  →  返回文本宽度（像素）
QFontMetrics::height()                   →  返回字体高度
```

### 3.2 `sizeHint()` - 计算 Item 大小

Qt 在布局时会调用这个方法询问每个 item 需要多大空间：



```cpp
QSize MsgItemDelegate::sizeHint(...) const
{
    // 1. 获取消息内容
    QString content = index.data(MsgRole::ContentRole).toString();
    
    // 2. 计算文本宽度
    int textWidth = m_contentFontMetrics.horizontalAdvance(content);
    int actualBubbleWidth = qMin(option.rect.width() / 2, textWidth) + PADDING * 2;
    //         限制最大宽度为视图一半         ↑        ↑
    //                                      文本宽度  左右内边距
    
    // 3. 创建 QTextDocument 计算换行后的高度
    QTextDocument doc;
    doc.setDefaultFont(m_contentFont);
    doc.setPlainText(content);
    doc.setTextWidth(actualBubbleWidth - PADDING * 2);  // 设置宽度限制，触发换行
    int contentHeight = doc.documentLayout()->documentSize().height();
    
    // 4. 计算总高度
    int senderHeight = m_senderFontMetrics.height() + SPACING;
    int timeHeight = m_timeFontMetrics.height() + SPACING;
    int totalHeight = senderHeight + contentHeight + timeHeight;
    
    // 5. 返回 item 大小
    return QSize(option.rect.width(), totalHeight);
    //      整个视图宽度               动态计算的高度
}
```

**图解**：



```
┌──────────────────────────────────────────┐ option.rect.width()
│ senderHeight: 发送者名称                  │ ← 固定高度
├──────────────────────────────────────────┤
│ contentHeight:                           │ ← 根据文本动态计算
│ 消息内容...                               │   短消息 → 小高度
│ (可能换行)                               │   长消息 → 大高度
├──────────────────────────────────────────┤
│ timeHeight: 12:30                        │ ← 固定高度
└──────────────────────────────────────────┘
        ↑                    ↑
    totalHeight 计算得出
```

### 3.3 `paint()` - 绘制入口

每个 item 需要绘制时，Qt 会调用这个方法：



```cpp
void MsgItemDelegate::paint(...) const
{
    painter->save();  // 保存绘制状态
    
    // 1. 设置抗锯齿
    painter->setRenderHint(QPainter::Antialiasing);
    
    // 2. 绘制背景
    painter->fillRect(option.rect, QColor(240, 240, 240));
    
    // 3. 获取数据
    QString content = index.data(MsgRole::ContentRole).toString();
    QString sender = index.data(MsgRole::SenderRole).toString();
    QString avatar = index.data(MsgRole::AvatarRole).toString();
    QString time = index.data(MsgRole::TimeRole).toString();
    bool isSelf = index.data(MsgRole::IsSelfRole).toBool();
    
    // 4. 根据消息类型选择绘制方式
    if (isSelf)
        paintSelfMessage(painter, option.rect, avatar, sender, content, time);
    else
        paintOtherMessage(painter, option.rect, avatar, sender, content, time);
    
    painter->restore();  // 恢复绘制状态
}
```

### 3.4 `paintOtherMessage()` - 绘制对方消息



```cpp
void MsgItemDelegate::paintOtherMessage(...) const
{
    int left = rect.left() + PADDING;
    int top = rect.top() + PADDING;
    
    // ┌─────────────────────────────────────────────┐
    // │  步骤1: 绘制头像（左侧）                       │
    // └─────────────────────────────────────────────┘
    QRect avatarRect(left, top, AVATAR_SIZE, AVATAR_SIZE);
    paintAvatar(painter, avatarRect, avatar);
    
    // ┌─────────────────────────────────────────────┐
    // │  步骤2: 计算气泡宽度（动态）                   │
    // └─────────────────────────────────────────────┘
    int textWidth = m_contentFontMetrics.horizontalAdvance(content);
    int actualBubbleWidth = qMin(rect.width()/2, textWidth) + PADDING * 2;
    //                     最大宽度限制    文本实际宽度
    
    // ┌─────────────────────────────────────────────┐
    // │  步骤3: 绘制发送者名称（头像右侧）             │
    // └─────────────────────────────────────────────┘
    QRect senderRect(left + AVATAR_SIZE + SPACING, top, ...);
    painter->drawText(senderRect, Qt::AlignLeft | Qt::AlignVCenter, sender);
    
    // ┌─────────────────────────────────────────────┐
    // │  步骤4: 准备文本内容（用于绘制）               │
    // └─────────────────────────────────────────────┘
    QTextDocument doc;
    doc.setDefaultFont(m_contentFont);
    doc.setPlainText(content);
    doc.setTextWidth(actualBubbleWidth);  // 设置换行宽度
    int bubbleHeight = doc.documentLayout()->documentSize().height();
    
    // ┌─────────────────────────────────────────────┐
    // │  步骤5: 绘制气泡（白色）                       │
    // └─────────────────────────────────────────────┘
    int bubbleLeft = left + AVATAR_SIZE + SPACING;
    int bubbleTop = senderRect.bottom() + SPACING;
    QRect bubbleRect(bubbleLeft, bubbleTop, actualBubbleWidth, bubbleHeight);
    
    QPainterPath path;
    path.addRoundedRect(bubbleRect, BUBBLE_RADIUS, BUBBLE_RADIUS);
    painter->fillPath(path, Qt::white);
    
    // ┌─────────────────────────────────────────────┐
    // │  步骤6: 绘制文本内容                          │
    // └─────────────────────────────────────────────┘
    painter->translate(bubbleRect.left() + SPACING, bubbleRect.top() + PADDING);
    doc.drawContents(painter);
    painter->translate(-bubbleRect.left() - SPACING, -bubbleRect.top() - PADDING);
    
    // ┌─────────────────────────────────────────────┐
    // │  步骤7: 绘制时间（气泡下方）                   │
    // └─────────────────────────────────────────────┘
    QRect timeRect(bubbleLeft, bubbleRect.bottom() + SPACING, ...);
    painter->drawText(timeRect, Qt::AlignLeft | Qt::AlignTop, time);
}
```

**视觉效果**：



```
┌───────────────────────────────────────────────┐
│ [头像] 张三                                    │
│        ┌─────────────────────┐                │
│        │ 消息内容...         │                │
│        │ (可能换行)         │                │
│        └─────────────────────┘                │
│        12:30                                  │
└───────────────────────────────────────────────┘
```

### 3.5 `paintSelfMessage()` - 绘制自己的消息

与对方消息类似，但方向相反（右侧对齐）：



```cpp
void MsgItemDelegate::paintSelfMessage(...) const
{
    int right = rect.right() - PADDING;  // 从右侧开始
    
    // 1. 绘制头像（右侧）
    QRect avatarRect(right - AVATAR_SIZE, top, AVATAR_SIZE, AVATAR_SIZE);
    
    // 2. 计算位置（从右向左）
    int bubbleRight = avatarRect.left() - SPACING;
    QRect bubbleRect(bubbleRight - actualBubbleWidth, bubbleTop, ...);
    
    // 3. 绘制气泡（蓝色）
    painter->fillPath(path, QColor(135, 206, 250));
    
    // 4. 文本和时间都是右对齐
}
```

**视觉效果**：



```
┌───────────────────────────────────────────────┐
│                                    李四 [头像] │
│                        ┌─────────────────────┐│
│                        │ 消息内容...         ││
│                        └─────────────────────┘│
│                                    12:31      │
└───────────────────────────────────────────────┘
```

## 四、关键技术点

### 4.1 `QTextDocument` 的作用



```
QTextDocument = 富文本文档引擎

功能：
1. 自动换行：setTextWidth() 触发
2. 计算高度：documentSize().height()
3. 绘制文本：drawContents()

示例：
doc.setTextWidth(100);  // 设置宽度 100
doc.setPlainText("这是一段很长的文本...");
// 文本会在 100px 处自动换行

qreal height = doc.documentLayout()->documentSize().height();
// 获取换行后的总高度
```

### 4.2 坐标变换（translate）



```cpp
// 为什么需要 translate？

// 原始坐标（气泡左上角在 0, 0）
painter->translate(bubbleRect.left() + PADDING, bubbleRect.top() + PADDING);
doc.drawContents(painter);  // 现在从气泡内 PADDING 位置开始绘制
painter->translate(...);    // 恢复原坐标系统
```

### 4.3 头像缓存



```cpp
mutable QHash<QString, QIcon> m_iconCache;  // 缓存头像

// 避免重复加载图片文件
QIcon avatarIcon = m_iconCache.value(avatar);
if (avatarIcon.isNull()) {
    avatarIcon = QIcon(avatar);  // 首次加载
    m_iconCache[avatar] = avatarIcon;  // 缓存
}
```

## 五、常量说明



```cpp
static constexpr int PADDING = 15;       // 内边距
static constexpr int MAX_WIDTH = 250;    // 气泡最大宽度
static constexpr int BUBBLE_RADIUS = 8;  // 气泡圆角半径
static constexpr int SPACING = 5;        // 元素间距
static constexpr int AVATAR_SIZE = 40;   // 头像尺寸
```

## 六、总结

| 方法                  | 作用           | 调用时机             |
| --------------------- | -------------- | -------------------- |
| `sizeHint()`          | 返回 item 大小 | View 布局时          |
| `paint()`             | 绘制 item      | 每个 item 需要重绘时 |
| `paintSelfMessage()`  | 绘制自己的消息 | `paint()` 内部调用   |
| `paintOtherMessage()` | 绘制对方消息   | `paint()` 内部调用   |
| `paintAvatar()`       | 绘制头像       | 消息绘制方法内调用   |

委托的核心思想：**将数据和显示分离**，Model 只管存储数据，Delegate 负责如何展示。
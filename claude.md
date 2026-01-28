# 项目说明

## 项目概述
这是一个基于 Qt C++ 开发的聊天客户端应用程序，支持用户注册、登录、好友管理和实时聊天功能。

## 技术栈
- Qt 5/6 (C++17)
- QNetworkAccessManager (HTTP 通信)
- QTcpSocket (TCP 聊天通信)
- QSettings (配置管理)
- Model/View 架构 (聊天列表和消息展示)

## 项目结构

```
client/
├── data/           # 数据管理层
│   ├── UserStructInfo.h
│   └── usermgr.h/cpp          # 用户管理单例
├── net/            # 网络通信层
│   ├── httpmgr.h/cpp          # HTTP 管理器
│   └── tcpmgr.h/cpp           # TCP 管理器
├── ui/             # 用户界面层
│   ├── login/                  # 登录相关界面
│   │   ├── logindialog
│   │   ├── registerdialog
│   │   └── resetdialog
│   ├── chat/                   # 聊天相关界面
│   │   ├── ChatWidget
│   │   ├── MsgWidget
│   │   ├── AddFriendDialog
│   │   └── ...
│   ├── ClickedBtn              # 可点击按钮
│   ├── clickedlabel            # 可点击标签
│   └── timerbtn                # 计时按钮
├── tool/           # 工具类
│   ├── singleton.h             # 单例模板
│   ├── CircleQueue.h           # 环形队列
│   └── AsyncLog.h              # 异步日志
├── style/          # 样式文件 (qss)
├── res/            # 资源文件
├── global.h/cpp    # 全局定义和头文件
├── mainwindow.h/cpp # 主窗口
└── main.cpp        # 程序入口
```

## 核心组件

### 1. 网络通信
- **HttpMgr**: 单例类，处理 REST API 请求（登录、注册、获取验证码等）
- **TcpMgr**: 单例类，处理 TCP 长连接，用于实时聊天消息传输

### 2. 用户管理
- **UserMgr**: 单例类，管理当前登录用户信息和好友列表

### 3. 协议定义
在 `global.h` 中定义了所有请求/响应 ID：
- `ID_GET_VERIFY_CODE`: 获取验证码
- `ID_REG_USER`: 用户注册
- `ID_LOGIN_USER`: 用户登录
- `ID_CHAT_LOGIN`: 聊天服务器登录
- `ID_TEXT_CHAT_MSG_REQ`: 发送聊天消息
- `ID_ADD_FRIEND_REQ`: 添加好友申请
- 等...

### 4. 数据结构
- **ChatList::ChatItem**: 聊天列表项数据
- **MsgList::MessageData**: 聊天消息数据

## 编译说明

### 环境要求
- Qt 5.15+ 或 Qt 6.x
- C++17 编译器
- CMake 或 qmake

### 构建步骤
```bash
qmake Client.pro
make
```

或使用 Qt Creator 直接打开 `Client.pro` 进行构建。

## 开发约定

1. **单例模式**: 网络管理器和用户管理器使用单例模式，通过 `Instance()` 访问
2. **信号槽**: 使用 Qt 信号槽机制进行组件间通信
3. **样式管理**: UI 样式通过 QSS 文件集中管理
4. **编码规范**:
   - 类名使用大驼峰命名 (PascalCase)
   - 变量名使用小驼峰命名 (camelCase)
   - 成员变量以 `m_` 开头

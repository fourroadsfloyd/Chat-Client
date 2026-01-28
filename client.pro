QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

DESTDIR = ./bin

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ClickedBtn.cpp \
    MsgInput.cpp \
    clickedlabel.cpp \
    data/usermgr.cpp \
    global.cpp \
    main.cpp \
    mainwindow.cpp \
    net/httpmgr.cpp \
    net/tcpmgr.cpp \
    timerbtn.cpp \
    ui/chat/AddFriendDialog.cpp \
    ui/chat/AddFriendErrorDialog.cpp \
    ui/chat/ApplyFriendItemDelegate.cpp \
    ui/chat/ApplyFriendListModel.cpp \
    ui/chat/ChatItemDelegate.cpp \
    ui/chat/ChatListModel.cpp \
    ui/chat/ChatSessionMgr.cpp \
    ui/chat/ContactItemDelegate.cpp \
    ui/chat/ContactListModel.cpp \
    ui/chat/MsgItemDelegate.cpp \
    ui/chat/MsgListModel.cpp \
    ui/chat/SearchItemDelegate.cpp \
    ui/chat/SearchListModel.cpp \
    ui/chat/SearchPopup.cpp \
    ui/chat/chatwidget.cpp \
    ui/login/logindialog.cpp \
    ui/login/registerdialog.cpp \
    ui/login/resetdialog.cpp

HEADERS += \
    ClickedBtn.h \
    MsgInput.h \
    clickedlabel.h \
    data/UserStructInfo.h \
    data/usermgr.h \
    global.h \
    mainwindow.h \
    net/httpmgr.h \
    net/tcpmgr.h \
    timerbtn.h \
    tool/AsyncLog.h \
    tool/CircleQueue.h \
    tool/singleton.h \
    ui/chat/AddFriendDialog.h \
    ui/chat/AddFriendErrorDialog.h \
    ui/chat/ApplyFriendItemDelegate.h \
    ui/chat/ApplyFriendListModel.h \
    ui/chat/ChatItemDelegate.h \
    ui/chat/ChatListModel.h \
    ui/chat/ChatSessionMgr.h \
    ui/chat/ChatWidget.h \
    ui/chat/ContactItemDelegate.h \
    ui/chat/ContactListModel.h \
    ui/chat/MsgItemDelegate.h \
    ui/chat/MsgListModel.h \
    ui/chat/SearchItemDelegate.h \
    ui/chat/SearchListModel.h \
    ui/chat/SearchPopup.h \
    ui/login/logindialog.h \
    ui/login/registerdialog.h \
    ui/login/resetdialog.h


FORMS += \
    mainwindow.ui \
    ui/chat/AddFriendDialog.ui \
    ui/chat/AddFriendErrorDialog.ui \
    ui/chat/ChatWidget.ui \
    ui/login/logindialog.ui \
    ui/login/registerdialog.ui \
    ui/login/resetdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

DISTFILES += \
    config.ini

win32:CONFIG(release, debug | release)
{
    #指定要拷贝的文件目录为工程目录下release目录下的所有dll、lib文件，例如工程目录在D:\QT\Test
    #PWD就为D:/QT/Test，DllFile = D:/QT/Test/release/*.dll
    TargetConfig = $${PWD}/config.ini
    #将输入目录中的"/"替换为"\"
    TargetConfig = $$replace(TargetConfig, /, \\)
    #将输出目录中的"/"替换为"\"
    OutputDir =  $${OUT_PWD}/$${DESTDIR}
    OutputDir = $$replace(OutputDir, /, \\)
    #执行copy命令
    QMAKE_POST_LINK += $$QMAKE_COPY \"$$TargetConfig\" \"$$OutputDir\"
}

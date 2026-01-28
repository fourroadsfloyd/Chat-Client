/****************************************************************************
** Meta object code from reading C++ file 'tcpmgr.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../net/tcpmgr.h"
#include <QtNetwork/QSslError>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tcpmgr.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN6TcpMgrE_t {};
} // unnamed namespace

template <> constexpr inline auto TcpMgr::qt_create_metaobjectdata<qt_meta_tag_ZN6TcpMgrE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "TcpMgr",
        "sig_con_success",
        "",
        "bsuccess",
        "sig_send_data",
        "ReqId",
        "reqId",
        "dataBytes",
        "sig_swich_chatdlg",
        "sig_login_failed",
        "sig_user_search",
        "std::shared_ptr<SearchInfo>",
        "sig_user_search_no_user",
        "sig_id_notify_add_friend_req",
        "std::shared_ptr<AddFriendInfo>",
        "info",
        "sig_id_auth_friend_rsp",
        "std::shared_ptr<ContactInfo>",
        "sig_notify_auth_friend_req",
        "sig_chatlistview_addItem",
        "std::shared_ptr<ChatModel::ChatItem>",
        "item",
        "sig_text_chat_msg",
        "std::shared_ptr<MsgModel::MsgItem>",
        "msg",
        "fromUid",
        "slot_tcp_connect",
        "ServerInfo",
        "slot_send_data"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'sig_con_success'
        QtMocHelpers::SignalData<void(bool)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 3 },
        }}),
        // Signal 'sig_send_data'
        QtMocHelpers::SignalData<void(ReqId, QByteArray)>(4, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 5, 6 }, { QMetaType::QByteArray, 7 },
        }}),
        // Signal 'sig_swich_chatdlg'
        QtMocHelpers::SignalData<void()>(8, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'sig_login_failed'
        QtMocHelpers::SignalData<void(int)>(9, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 2 },
        }}),
        // Signal 'sig_user_search'
        QtMocHelpers::SignalData<void(std::shared_ptr<SearchInfo>)>(10, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 11, 2 },
        }}),
        // Signal 'sig_user_search_no_user'
        QtMocHelpers::SignalData<void()>(12, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'sig_id_notify_add_friend_req'
        QtMocHelpers::SignalData<void(std::shared_ptr<AddFriendInfo>)>(13, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 14, 15 },
        }}),
        // Signal 'sig_id_auth_friend_rsp'
        QtMocHelpers::SignalData<void(std::shared_ptr<ContactInfo>)>(16, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 17, 15 },
        }}),
        // Signal 'sig_notify_auth_friend_req'
        QtMocHelpers::SignalData<void(std::shared_ptr<ContactInfo>)>(18, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 17, 15 },
        }}),
        // Signal 'sig_chatlistview_addItem'
        QtMocHelpers::SignalData<void(std::shared_ptr<ChatModel::ChatItem>)>(19, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 20, 21 },
        }}),
        // Signal 'sig_text_chat_msg'
        QtMocHelpers::SignalData<void(std::shared_ptr<MsgModel::MsgItem>, int)>(22, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 23, 24 }, { QMetaType::Int, 25 },
        }}),
        // Slot 'slot_tcp_connect'
        QtMocHelpers::SlotData<void(ServerInfo)>(26, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 27, 2 },
        }}),
        // Slot 'slot_send_data'
        QtMocHelpers::SlotData<void(ReqId, QByteArray)>(28, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 5, 6 }, { QMetaType::QByteArray, 7 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<TcpMgr, qt_meta_tag_ZN6TcpMgrE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject TcpMgr::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN6TcpMgrE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN6TcpMgrE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN6TcpMgrE_t>.metaTypes,
    nullptr
} };

void TcpMgr::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<TcpMgr *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->sig_con_success((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 1: _t->sig_send_data((*reinterpret_cast< std::add_pointer_t<ReqId>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QByteArray>>(_a[2]))); break;
        case 2: _t->sig_swich_chatdlg(); break;
        case 3: _t->sig_login_failed((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 4: _t->sig_user_search((*reinterpret_cast< std::add_pointer_t<std::shared_ptr<SearchInfo>>>(_a[1]))); break;
        case 5: _t->sig_user_search_no_user(); break;
        case 6: _t->sig_id_notify_add_friend_req((*reinterpret_cast< std::add_pointer_t<std::shared_ptr<AddFriendInfo>>>(_a[1]))); break;
        case 7: _t->sig_id_auth_friend_rsp((*reinterpret_cast< std::add_pointer_t<std::shared_ptr<ContactInfo>>>(_a[1]))); break;
        case 8: _t->sig_notify_auth_friend_req((*reinterpret_cast< std::add_pointer_t<std::shared_ptr<ContactInfo>>>(_a[1]))); break;
        case 9: _t->sig_chatlistview_addItem((*reinterpret_cast< std::add_pointer_t<std::shared_ptr<ChatModel::ChatItem>>>(_a[1]))); break;
        case 10: _t->sig_text_chat_msg((*reinterpret_cast< std::add_pointer_t<std::shared_ptr<MsgModel::MsgItem>>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 11: _t->slot_tcp_connect((*reinterpret_cast< std::add_pointer_t<ServerInfo>>(_a[1]))); break;
        case 12: _t->slot_send_data((*reinterpret_cast< std::add_pointer_t<ReqId>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QByteArray>>(_a[2]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (TcpMgr::*)(bool )>(_a, &TcpMgr::sig_con_success, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (TcpMgr::*)(ReqId , QByteArray )>(_a, &TcpMgr::sig_send_data, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (TcpMgr::*)()>(_a, &TcpMgr::sig_swich_chatdlg, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (TcpMgr::*)(int )>(_a, &TcpMgr::sig_login_failed, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (TcpMgr::*)(std::shared_ptr<SearchInfo> )>(_a, &TcpMgr::sig_user_search, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (TcpMgr::*)()>(_a, &TcpMgr::sig_user_search_no_user, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (TcpMgr::*)(std::shared_ptr<AddFriendInfo> )>(_a, &TcpMgr::sig_id_notify_add_friend_req, 6))
            return;
        if (QtMocHelpers::indexOfMethod<void (TcpMgr::*)(std::shared_ptr<ContactInfo> )>(_a, &TcpMgr::sig_id_auth_friend_rsp, 7))
            return;
        if (QtMocHelpers::indexOfMethod<void (TcpMgr::*)(std::shared_ptr<ContactInfo> )>(_a, &TcpMgr::sig_notify_auth_friend_req, 8))
            return;
        if (QtMocHelpers::indexOfMethod<void (TcpMgr::*)(std::shared_ptr<ChatModel::ChatItem> )>(_a, &TcpMgr::sig_chatlistview_addItem, 9))
            return;
        if (QtMocHelpers::indexOfMethod<void (TcpMgr::*)(std::shared_ptr<MsgModel::MsgItem> , int )>(_a, &TcpMgr::sig_text_chat_msg, 10))
            return;
    }
}

const QMetaObject *TcpMgr::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TcpMgr::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN6TcpMgrE_t>.strings))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "Singleton<TcpMgr>"))
        return static_cast< Singleton<TcpMgr>*>(this);
    if (!strcmp(_clname, "std::enable_shared_from_this<TcpMgr>"))
        return static_cast< std::enable_shared_from_this<TcpMgr>*>(this);
    return QObject::qt_metacast(_clname);
}

int TcpMgr::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void TcpMgr::sig_con_success(bool _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void TcpMgr::sig_send_data(ReqId _t1, QByteArray _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1, _t2);
}

// SIGNAL 2
void TcpMgr::sig_swich_chatdlg()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void TcpMgr::sig_login_failed(int _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1);
}

// SIGNAL 4
void TcpMgr::sig_user_search(std::shared_ptr<SearchInfo> _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 4, nullptr, _t1);
}

// SIGNAL 5
void TcpMgr::sig_user_search_no_user()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void TcpMgr::sig_id_notify_add_friend_req(std::shared_ptr<AddFriendInfo> _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 6, nullptr, _t1);
}

// SIGNAL 7
void TcpMgr::sig_id_auth_friend_rsp(std::shared_ptr<ContactInfo> _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 7, nullptr, _t1);
}

// SIGNAL 8
void TcpMgr::sig_notify_auth_friend_req(std::shared_ptr<ContactInfo> _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 8, nullptr, _t1);
}

// SIGNAL 9
void TcpMgr::sig_chatlistview_addItem(std::shared_ptr<ChatModel::ChatItem> _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 9, nullptr, _t1);
}

// SIGNAL 10
void TcpMgr::sig_text_chat_msg(std::shared_ptr<MsgModel::MsgItem> _t1, int _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 10, nullptr, _t1, _t2);
}
QT_WARNING_POP

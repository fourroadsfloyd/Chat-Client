/****************************************************************************
** Meta object code from reading C++ file 'ChatSessionMgr.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../ui/chat/ChatSessionMgr.h"
#include <QtNetwork/QSslError>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ChatSessionMgr.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN14ChatSessionMgrE_t {};
} // unnamed namespace

template <> constexpr inline auto ChatSessionMgr::qt_create_metaobjectdata<qt_meta_tag_ZN14ChatSessionMgrE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "ChatSessionMgr",
        "sig_messageReceived",
        "",
        "friendUid",
        "std::shared_ptr<MsgModel::MsgItem>",
        "msg",
        "sig_messageSent",
        "sig_sessionChanged",
        "oldFriendUid",
        "newFriendUid"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'sig_messageReceived'
        QtMocHelpers::SignalData<void(int, std::shared_ptr<MsgModel::MsgItem>)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 3 }, { 0x80000000 | 4, 5 },
        }}),
        // Signal 'sig_messageSent'
        QtMocHelpers::SignalData<void(int, std::shared_ptr<MsgModel::MsgItem>)>(6, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 3 }, { 0x80000000 | 4, 5 },
        }}),
        // Signal 'sig_sessionChanged'
        QtMocHelpers::SignalData<void(int, int)>(7, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 8 }, { QMetaType::Int, 9 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<ChatSessionMgr, qt_meta_tag_ZN14ChatSessionMgrE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject ChatSessionMgr::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN14ChatSessionMgrE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN14ChatSessionMgrE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN14ChatSessionMgrE_t>.metaTypes,
    nullptr
} };

void ChatSessionMgr::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<ChatSessionMgr *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->sig_messageReceived((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<std::shared_ptr<MsgModel::MsgItem>>>(_a[2]))); break;
        case 1: _t->sig_messageSent((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<std::shared_ptr<MsgModel::MsgItem>>>(_a[2]))); break;
        case 2: _t->sig_sessionChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (ChatSessionMgr::*)(int , std::shared_ptr<MsgModel::MsgItem> )>(_a, &ChatSessionMgr::sig_messageReceived, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (ChatSessionMgr::*)(int , std::shared_ptr<MsgModel::MsgItem> )>(_a, &ChatSessionMgr::sig_messageSent, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (ChatSessionMgr::*)(int , int )>(_a, &ChatSessionMgr::sig_sessionChanged, 2))
            return;
    }
}

const QMetaObject *ChatSessionMgr::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ChatSessionMgr::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN14ChatSessionMgrE_t>.strings))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "Singleton<ChatSessionMgr>"))
        return static_cast< Singleton<ChatSessionMgr>*>(this);
    return QObject::qt_metacast(_clname);
}

int ChatSessionMgr::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void ChatSessionMgr::sig_messageReceived(int _t1, std::shared_ptr<MsgModel::MsgItem> _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1, _t2);
}

// SIGNAL 1
void ChatSessionMgr::sig_messageSent(int _t1, std::shared_ptr<MsgModel::MsgItem> _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1, _t2);
}

// SIGNAL 2
void ChatSessionMgr::sig_sessionChanged(int _t1, int _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1, _t2);
}
QT_WARNING_POP

/****************************************************************************
** Meta object code from reading C++ file 'QMLRoom.h'
**
** Created: Wed Sep 26 18:43:51 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "QMLRoom.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QMLRoom.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QMLRoom[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       3,   14, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // properties: name, type, flags
      20,    8, 0x0b095001,
      40,   28, 0x08095001,
      98,   50, 0x00095009,

       0        // eod
};

static const char qt_meta_stringdata_QMLRoom[] = {
    "QMLRoom\0QStringList\0clients\0QVariantMap\0"
    "variables\0QDeclarativeListProperty<QMLFunctionDefinition>\0"
    "functions\0"
};

void QMLRoom::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData QMLRoom::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QMLRoom::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QMLRoom,
      qt_meta_data_QMLRoom, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QMLRoom::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QMLRoom::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QMLRoom::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QMLRoom))
        return static_cast<void*>(const_cast< QMLRoom*>(this));
    return QObject::qt_metacast(_clname);
}

int QMLRoom::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    
#ifndef QT_NO_PROPERTIES
     if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QStringList*>(_v) = clients(); break;
        case 1: *reinterpret_cast< QVariantMap*>(_v) = variables(); break;
        case 2: *reinterpret_cast< QDeclarativeListProperty<QMLFunctionDefinition>*>(_v) = functions(); break;
        }
        _id -= 3;
    } else if (_c == QMetaObject::WriteProperty) {
        _id -= 3;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 3;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
QT_END_MOC_NAMESPACE

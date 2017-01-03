/****************************************************************************
** Meta object code from reading C++ file 'intaction.h'
**
** Created: Sat Jan 12 10:08:01 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "intaction.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'intaction.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_intAction[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      16,   11,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
      29,   10,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_intAction[] = {
    "intAction\0\0code\0sigCode(int)\0codeSignal()\0"
};

const QMetaObject intAction::staticMetaObject = {
    { &QAction::staticMetaObject, qt_meta_stringdata_intAction,
      qt_meta_data_intAction, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &intAction::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *intAction::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *intAction::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_intAction))
        return static_cast<void*>(const_cast< intAction*>(this));
    return QAction::qt_metacast(_clname);
}

int intAction::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAction::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: sigCode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: codeSignal(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void intAction::sigCode(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE

/****************************************************************************
** Meta object code from reading C++ file 'macefctnbar.h'
**
** Created: Sat Jan 12 10:08:02 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "macefctnbar.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'macefctnbar.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MaceFctnBar[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      18,   13,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
      50,   45,   12,   12, 0x08,
      83,   78,   12,   12, 0x0a,
      97,   95,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MaceFctnBar[] = {
    "MaceFctnBar\0\0item\0sendItem(QListWidgetItem*)\0"
    "pair\0setItem(QPair<QString,int>)\0code\0"
    "setNew(int)\0f\0set_field(bool)\0"
};

const QMetaObject MaceFctnBar::staticMetaObject = {
    { &QHBoxLayout::staticMetaObject, qt_meta_stringdata_MaceFctnBar,
      qt_meta_data_MaceFctnBar, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MaceFctnBar::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MaceFctnBar::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MaceFctnBar::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MaceFctnBar))
        return static_cast<void*>(const_cast< MaceFctnBar*>(this));
    return QHBoxLayout::qt_metacast(_clname);
}

int MaceFctnBar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QHBoxLayout::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: sendItem((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 1: setItem((*reinterpret_cast< QPair<QString,int>(*)>(_a[1]))); break;
        case 2: setNew((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: set_field((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void MaceFctnBar::sendItem(QListWidgetItem * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE

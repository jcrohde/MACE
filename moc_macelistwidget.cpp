/****************************************************************************
** Meta object code from reading C++ file 'macelistwidget.h'
**
** Created: Sat Jan 12 10:08:05 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "macelistwidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'macelistwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MaceListWidget[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      21,   16,   15,   15, 0x05,

 // slots: signature, parameters, type, tag, flags
      46,   44,   15,   15, 0x0a,
      67,   62,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MaceListWidget[] = {
    "MaceListWidget\0\0fctn\0call_function(QString)\0"
    "f\0set_field(bool)\0code\0setNew(int)\0"
};

const QMetaObject MaceListWidget::staticMetaObject = {
    { &QListWidget::staticMetaObject, qt_meta_stringdata_MaceListWidget,
      qt_meta_data_MaceListWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MaceListWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MaceListWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MaceListWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MaceListWidget))
        return static_cast<void*>(const_cast< MaceListWidget*>(this));
    return QListWidget::qt_metacast(_clname);
}

int MaceListWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QListWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: call_function((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: set_field((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: setNew((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void MaceListWidget::call_function(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE

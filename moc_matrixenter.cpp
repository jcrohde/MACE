/****************************************************************************
** Meta object code from reading C++ file 'matrixenter.h'
**
** Created: Sat Jan 12 10:08:10 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "matrixenter.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'matrixenter.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_matrixEnter[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      18,   13,   12,   12, 0x05,
      49,   12,   12,   12, 0x05,
      60,   12,   12,   12, 0x05,
      66,   12,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
      74,   12,   12,   12, 0x0a,
     106,   83,   12,   12, 0x0a,
     153,   12,   12,   12, 0x08,
     166,   12,   12,   12, 0x08,
     174,   12,   12,   12, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_matrixEnter[] = {
    "matrixEnter\0\0item\0changeMatrix(QListWidgetItem*)\0"
    "inserted()\0bye()\0hello()\0accept()\0"
    "li,co,characteristic,i\0"
    "make_visible(int,int,MaceInt,QListWidgetItem*)\0"
    "changeWish()\0clean()\0show_info()\0"
};

const QMetaObject matrixEnter::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_matrixEnter,
      qt_meta_data_matrixEnter, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &matrixEnter::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *matrixEnter::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *matrixEnter::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_matrixEnter))
        return static_cast<void*>(const_cast< matrixEnter*>(this));
    return QDialog::qt_metacast(_clname);
}

int matrixEnter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: changeMatrix((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 1: inserted(); break;
        case 2: bye(); break;
        case 3: hello(); break;
        case 4: accept(); break;
        case 5: make_visible((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< MaceInt(*)>(_a[3])),(*reinterpret_cast< QListWidgetItem*(*)>(_a[4]))); break;
        case 6: changeWish(); break;
        case 7: clean(); break;
        case 8: show_info(); break;
        default: ;
        }
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void matrixEnter::changeMatrix(QListWidgetItem * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void matrixEnter::inserted()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void matrixEnter::bye()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void matrixEnter::hello()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}
QT_END_MOC_NAMESPACE

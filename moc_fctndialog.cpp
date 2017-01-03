/****************************************************************************
** Meta object code from reading C++ file 'fctndialog.h'
**
** Created: Sat Jan 12 10:07:59 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "fctndialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fctndialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FctnDialog[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,
      25,   23,   11,   11, 0x05,
      42,   11,   11,   11, 0x05,
      53,   11,   11,   11, 0x05,
      61,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      67,   11,   11,   11, 0x08,
      75,   11,   11,   11, 0x08,
      87,   23,   11,   11, 0x08,
     103,   11,   11,   11, 0x08,
     114,   23,   11,   11, 0x0a,
     169,  152,   11,   11, 0x0a,
     212,  208,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_FctnDialog[] = {
    "FctnDialog\0\0inserted()\0i\0newFctnCode(int)\0"
    "rejected()\0hello()\0bye()\0agree()\0"
    "show_info()\0statSwitch(int)\0nextLine()\0"
    "change_linesColumns(QListWidgetItem*)\0"
    "characteristic,i\0"
    "make_visible(MaceInt,QListWidgetItem*)\0"
    "str\0make_settings(QString)\0"
};

const QMetaObject FctnDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_FctnDialog,
      qt_meta_data_FctnDialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FctnDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FctnDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FctnDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FctnDialog))
        return static_cast<void*>(const_cast< FctnDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int FctnDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: inserted(); break;
        case 1: newFctnCode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: rejected(); break;
        case 3: hello(); break;
        case 4: bye(); break;
        case 5: agree(); break;
        case 6: show_info(); break;
        case 7: statSwitch((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: nextLine(); break;
        case 9: change_linesColumns((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 10: make_visible((*reinterpret_cast< MaceInt(*)>(_a[1])),(*reinterpret_cast< QListWidgetItem*(*)>(_a[2]))); break;
        case 11: make_settings((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void FctnDialog::inserted()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void FctnDialog::newFctnCode(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void FctnDialog::rejected()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void FctnDialog::hello()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void FctnDialog::bye()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}
QT_END_MOC_NAMESPACE

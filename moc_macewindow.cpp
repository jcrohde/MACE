/****************************************************************************
** Meta object code from reading C++ file 'macewindow.h'
**
** Created: Sat Jan 12 10:08:08 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "macewindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'macewindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MaceWindow[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      16,   12,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      34,   12,   11,   11, 0x08,
      53,   11,   11,   11, 0x08,
      63,   11,   11,   11, 0x08,
      70,   11,   11,   11, 0x08,
      77,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MaceWindow[] = {
    "MaceWindow\0\0str\0emission(QString)\0"
    "give_info(QString)\0newFile()\0load()\0"
    "save()\0saveFileAs()\0"
};

const QMetaObject MaceWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MaceWindow,
      qt_meta_data_MaceWindow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MaceWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MaceWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MaceWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MaceWindow))
        return static_cast<void*>(const_cast< MaceWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MaceWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: emission((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: give_info((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: newFile(); break;
        case 3: load(); break;
        case 4: save(); break;
        case 5: saveFileAs(); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void MaceWindow::emission(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE

/****************************************************************************
** Meta object code from reading C++ file 'maceform.h'
**
** Created: Sat Jan 12 10:08:02 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "maceform.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'maceform.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MaceForm[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      14,   10,    9,    9, 0x0a,
      33,    9,    9,    9, 0x0a,
      47,   45,    9,    9, 0x0a,
      78,    9,    9,    9, 0x0a,
      94,    9,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MaceForm[] = {
    "MaceForm\0\0str\0calculate(QString)\0"
    "getSignal()\0i\0make_visible(QListWidgetItem*)\0"
    "linearAlgebra()\0plotten()\0"
};

const QMetaObject MaceForm::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_MaceForm,
      qt_meta_data_MaceForm, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MaceForm::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MaceForm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MaceForm::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MaceForm))
        return static_cast<void*>(const_cast< MaceForm*>(this));
    return QDialog::qt_metacast(_clname);
}

int MaceForm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: calculate((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: getSignal(); break;
        case 2: make_visible((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 3: linearAlgebra(); break;
        case 4: plotten(); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

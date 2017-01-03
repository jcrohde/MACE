/****************************************************************************
** Meta object code from reading C++ file 'macetextedit.h'
**
** Created: Sat Jan 12 10:08:06 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "macetextedit.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'macetextedit.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MaceTextEdit[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      18,   14,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
      43,   14,   13,   13, 0x0a,
      76,   66,   13,   13, 0x0a,
     109,   14,   13,   13, 0x0a,
     135,   14,   13,   13, 0x0a,
     158,   14,   13,   13, 0x0a,
     180,   13,   13,   13, 0x0a,
     184,   13,   13,   13, 0x0a,
     192,   13,   13,   13, 0x0a,
     203,  197,   13,   13, 0x0a,
     231,  229,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MaceTextEdit[] = {
    "MaceTextEdit\0\0str\0pleaseCalculate(QString)\0"
    "displayResult(QString)\0str,lines\0"
    "displayMatrixResult(QString,int)\0"
    "displaySLEResult(QString)\0"
    "standardWrite(QString)\0singleMatrix(QString)\0"
    "C()\0reset()\0eq()\0event\0keyPressEvent(QKeyEvent*)\0"
    "e\0mousePressEvent(QMouseEvent*)\0"
};

const QMetaObject MaceTextEdit::staticMetaObject = {
    { &QTextEdit::staticMetaObject, qt_meta_stringdata_MaceTextEdit,
      qt_meta_data_MaceTextEdit, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MaceTextEdit::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MaceTextEdit::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MaceTextEdit::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MaceTextEdit))
        return static_cast<void*>(const_cast< MaceTextEdit*>(this));
    return QTextEdit::qt_metacast(_clname);
}

int MaceTextEdit::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTextEdit::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: pleaseCalculate((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: displayResult((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: displayMatrixResult((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: displaySLEResult((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: standardWrite((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: singleMatrix((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: C(); break;
        case 7: reset(); break;
        case 8: eq(); break;
        case 9: keyPressEvent((*reinterpret_cast< QKeyEvent*(*)>(_a[1]))); break;
        case 10: mousePressEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void MaceTextEdit::pleaseCalculate(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE

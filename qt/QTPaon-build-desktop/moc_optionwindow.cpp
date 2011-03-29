/****************************************************************************
** Meta object code from reading C++ file 'optionwindow.h'
**
** Created: Sun Mar 20 20:39:02 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../QTNibbler/optionwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'optionwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_OptionWindow[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      20,   14,   13,   13, 0x08,
      37,   13,   13,   13, 0x08,
      51,   13,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_OptionWindow[] = {
    "OptionWindow\0\0level\0updateLevel(int)\0"
    "changeMulti()\0changeWall()\0"
};

const QMetaObject OptionWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_OptionWindow,
      qt_meta_data_OptionWindow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &OptionWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *OptionWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *OptionWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_OptionWindow))
        return static_cast<void*>(const_cast< OptionWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int OptionWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: updateLevel((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: changeMulti(); break;
        case 2: changeWall(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

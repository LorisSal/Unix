/****************************************************************************
** Meta object code from reading C++ file 'mainwindowex4.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindowex4.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindowex4.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindowEx4_t {
    QByteArrayData data[9];
    char stringdata0[235];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindowEx4_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindowEx4_t qt_meta_stringdata_MainWindowEx4 = {
    {
QT_MOC_LITERAL(0, 0, 13), // "MainWindowEx4"
QT_MOC_LITERAL(1, 14, 40), // "on_pushButtonDemarrerTraiteme..."
QT_MOC_LITERAL(2, 55, 0), // ""
QT_MOC_LITERAL(3, 56, 26), // "on_pushButtonVider_clicked"
QT_MOC_LITERAL(4, 83, 28), // "on_pushButtonQuitter_clicked"
QT_MOC_LITERAL(5, 112, 29), // "on_pushButtonAnnuler1_clicked"
QT_MOC_LITERAL(6, 142, 29), // "on_pushButtonAnnuler2_clicked"
QT_MOC_LITERAL(7, 172, 29), // "on_pushButtonAnnuler3_clicked"
QT_MOC_LITERAL(8, 202, 32) // "on_pushButtonAnnulerTous_clicked"

    },
    "MainWindowEx4\0on_pushButtonDemarrerTraitements_clicked\0"
    "\0on_pushButtonVider_clicked\0"
    "on_pushButtonQuitter_clicked\0"
    "on_pushButtonAnnuler1_clicked\0"
    "on_pushButtonAnnuler2_clicked\0"
    "on_pushButtonAnnuler3_clicked\0"
    "on_pushButtonAnnulerTous_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindowEx4[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x08 /* Private */,
       3,    0,   50,    2, 0x08 /* Private */,
       4,    0,   51,    2, 0x08 /* Private */,
       5,    0,   52,    2, 0x08 /* Private */,
       6,    0,   53,    2, 0x08 /* Private */,
       7,    0,   54,    2, 0x08 /* Private */,
       8,    0,   55,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindowEx4::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindowEx4 *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_pushButtonDemarrerTraitements_clicked(); break;
        case 1: _t->on_pushButtonVider_clicked(); break;
        case 2: _t->on_pushButtonQuitter_clicked(); break;
        case 3: _t->on_pushButtonAnnuler1_clicked(); break;
        case 4: _t->on_pushButtonAnnuler2_clicked(); break;
        case 5: _t->on_pushButtonAnnuler3_clicked(); break;
        case 6: _t->on_pushButtonAnnulerTous_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject MainWindowEx4::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_MainWindowEx4.data,
    qt_meta_data_MainWindowEx4,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindowEx4::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindowEx4::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindowEx4.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindowEx4::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

/****************************************************************************
** Meta object code from reading C++ file 'InitWindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../Windows/InitWindow/InitWindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'InitWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_InitWindow_t {
    QByteArrayData data[9];
    char stringdata0[161];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_InitWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_InitWindow_t qt_meta_stringdata_InitWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "InitWindow"
QT_MOC_LITERAL(1, 11, 11), // "DataIsReady"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 28), // "on_StartSensorButton_clicked"
QT_MOC_LITERAL(4, 53, 24), // "on_GetDataButton_clicked"
QT_MOC_LITERAL(5, 78, 21), // "CallbackSerialReceive"
QT_MOC_LITERAL(6, 100, 18), // "TimeoutResponseStm"
QT_MOC_LITERAL(7, 119, 28), // "on_SetNameSerialPort_clicked"
QT_MOC_LITERAL(8, 148, 12) // "PaintGraphic"

    },
    "InitWindow\0DataIsReady\0\0"
    "on_StartSensorButton_clicked\0"
    "on_GetDataButton_clicked\0CallbackSerialReceive\0"
    "TimeoutResponseStm\0on_SetNameSerialPort_clicked\0"
    "PaintGraphic"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_InitWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   50,    2, 0x08 /* Private */,
       4,    0,   51,    2, 0x08 /* Private */,
       5,    0,   52,    2, 0x08 /* Private */,
       6,    0,   53,    2, 0x08 /* Private */,
       7,    0,   54,    2, 0x08 /* Private */,
       8,    0,   55,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void InitWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<InitWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->DataIsReady(); break;
        case 1: _t->on_StartSensorButton_clicked(); break;
        case 2: _t->on_GetDataButton_clicked(); break;
        case 3: _t->CallbackSerialReceive(); break;
        case 4: _t->TimeoutResponseStm(); break;
        case 5: _t->on_SetNameSerialPort_clicked(); break;
        case 6: _t->PaintGraphic(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (InitWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&InitWindow::DataIsReady)) {
                *result = 0;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject InitWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_InitWindow.data,
    qt_meta_data_InitWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *InitWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *InitWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_InitWindow.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int InitWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void InitWindow::DataIsReady()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

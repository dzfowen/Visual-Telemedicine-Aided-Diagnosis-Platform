/****************************************************************************
** Meta object code from reading C++ file 'mhdReader.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mhdReader.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mhdReader.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_mhdReader_t {
    QByteArrayData data[15];
    char stringdata[167];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_mhdReader_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_mhdReader_t qt_meta_stringdata_mhdReader = {
    {
QT_MOC_LITERAL(0, 0, 9),
QT_MOC_LITERAL(1, 10, 14),
QT_MOC_LITERAL(2, 25, 0),
QT_MOC_LITERAL(3, 26, 14),
QT_MOC_LITERAL(4, 41, 14),
QT_MOC_LITERAL(5, 56, 7),
QT_MOC_LITERAL(6, 64, 19),
QT_MOC_LITERAL(7, 84, 4),
QT_MOC_LITERAL(8, 89, 4),
QT_MOC_LITERAL(9, 94, 17),
QT_MOC_LITERAL(10, 112, 14),
QT_MOC_LITERAL(11, 127, 7),
QT_MOC_LITERAL(12, 135, 8),
QT_MOC_LITERAL(13, 144, 13),
QT_MOC_LITERAL(14, 158, 8)
    },
    "mhdReader\0slider_x_moved\0\0slider_y_moved\0"
    "slider_z_moved\0Saveimg\0openVolumeRendering\0"
    "test\0Edit\0changeBrighteness\0changeContrast\0"
    "overlap\0editMask\0origianlPoint\0newPoint"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_mhdReader[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x08 /* Private */,
       3,    1,   82,    2, 0x08 /* Private */,
       4,    1,   85,    2, 0x08 /* Private */,
       5,    0,   88,    2, 0x08 /* Private */,
       6,    0,   89,    2, 0x08 /* Private */,
       7,    0,   90,    2, 0x08 /* Private */,
       8,    0,   91,    2, 0x08 /* Private */,
       9,    1,   92,    2, 0x08 /* Private */,
      10,    1,   95,    2, 0x08 /* Private */,
      11,    0,   98,    2, 0x08 /* Private */,
      12,    0,   99,    2, 0x08 /* Private */,
      13,    0,  100,    2, 0x08 /* Private */,
      14,    0,  101,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void mhdReader::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        mhdReader *_t = static_cast<mhdReader *>(_o);
        switch (_id) {
        case 0: _t->slider_x_moved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->slider_y_moved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->slider_z_moved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->Saveimg(); break;
        case 4: _t->openVolumeRendering(); break;
        case 5: _t->test(); break;
        case 6: _t->Edit(); break;
        case 7: _t->changeBrighteness((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->changeContrast((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->overlap(); break;
        case 10: _t->editMask(); break;
        case 11: _t->origianlPoint(); break;
        case 12: _t->newPoint(); break;
        default: ;
        }
    }
}

const QMetaObject mhdReader::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_mhdReader.data,
      qt_meta_data_mhdReader,  qt_static_metacall, 0, 0}
};


const QMetaObject *mhdReader::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *mhdReader::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_mhdReader.stringdata))
        return static_cast<void*>(const_cast< mhdReader*>(this));
    return QObject::qt_metacast(_clname);
}

int mhdReader::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

/****************************************************************************
** Meta object code from reading C++ file 'audioConnThread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../audioConnThread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'audioConnThread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_audioConnThread_t {
    QByteArrayData data[8];
    char stringdata[108];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_audioConnThread_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_audioConnThread_t qt_meta_stringdata_audioConnThread = {
    {
QT_MOC_LITERAL(0, 0, 15),
QT_MOC_LITERAL(1, 16, 32),
QT_MOC_LITERAL(2, 49, 0),
QT_MOC_LITERAL(3, 50, 5),
QT_MOC_LITERAL(4, 56, 10),
QT_MOC_LITERAL(5, 67, 6),
QT_MOC_LITERAL(6, 74, 10),
QT_MOC_LITERAL(7, 85, 22)
    },
    "audioConnThread\0audioSingle_ForwardAudioToOthers\0"
    "\0char*\0clientUser\0Buffer\0BufferSize\0"
    "audioSingle_Disconnect"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_audioConnThread[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   24,    2, 0x06 /* Public */,
       7,    1,   31,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3, QMetaType::Int,    4,    5,    6,
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void audioConnThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        audioConnThread *_t = static_cast<audioConnThread *>(_o);
        switch (_id) {
        case 0: _t->audioSingle_ForwardAudioToOthers((*reinterpret_cast< char*(*)>(_a[1])),(*reinterpret_cast< char*(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 1: _t->audioSingle_Disconnect((*reinterpret_cast< char*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (audioConnThread::*_t)(char * , char * , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&audioConnThread::audioSingle_ForwardAudioToOthers)) {
                *result = 0;
            }
        }
        {
            typedef void (audioConnThread::*_t)(char * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&audioConnThread::audioSingle_Disconnect)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject audioConnThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_audioConnThread.data,
      qt_meta_data_audioConnThread,  qt_static_metacall, 0, 0}
};


const QMetaObject *audioConnThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *audioConnThread::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_audioConnThread.stringdata))
        return static_cast<void*>(const_cast< audioConnThread*>(this));
    return QThread::qt_metacast(_clname);
}

int audioConnThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void audioConnThread::audioSingle_ForwardAudioToOthers(char * _t1, char * _t2, int _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void audioConnThread::audioSingle_Disconnect(char * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
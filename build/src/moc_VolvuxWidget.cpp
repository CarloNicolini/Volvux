/****************************************************************************
** Meta object code from reading C++ file 'VolvuxWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/VolvuxWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'VolvuxWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_VolvuxWidget_t {
    QByteArrayData data[17];
    char stringdata0[261];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VolvuxWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VolvuxWidget_t qt_meta_stringdata_VolvuxWidget = {
    {
QT_MOC_LITERAL(0, 0, 12), // "VolvuxWidget"
QT_MOC_LITERAL(1, 13, 24), // "framePercentageGenerated"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 24), // "memoryAllocatedMegaBytes"
QT_MOC_LITERAL(4, 64, 11), // "eyeZChanged"
QT_MOC_LITERAL(5, 76, 10), // "fovChanged"
QT_MOC_LITERAL(6, 87, 12), // "zNearChanged"
QT_MOC_LITERAL(7, 100, 11), // "zFarChanged"
QT_MOC_LITERAL(8, 112, 12), // "binVoxLoaded"
QT_MOC_LITERAL(9, 125, 14), // "generateFrames"
QT_MOC_LITERAL(10, 140, 21), // "setOffscreenRendering"
QT_MOC_LITERAL(11, 162, 3), // "val"
QT_MOC_LITERAL(12, 166, 13), // "onEyeZChanged"
QT_MOC_LITERAL(13, 180, 14), // "onZNearChanged"
QT_MOC_LITERAL(14, 195, 13), // "onZFarChanged"
QT_MOC_LITERAL(15, 209, 25), // "onSurfaceThicknessChanged"
QT_MOC_LITERAL(16, 235, 25) // "onSurfaceCurvatureChanged"

    },
    "VolvuxWidget\0framePercentageGenerated\0"
    "\0memoryAllocatedMegaBytes\0eyeZChanged\0"
    "fovChanged\0zNearChanged\0zFarChanged\0"
    "binVoxLoaded\0generateFrames\0"
    "setOffscreenRendering\0val\0onEyeZChanged\0"
    "onZNearChanged\0onZFarChanged\0"
    "onSurfaceThicknessChanged\0"
    "onSurfaceCurvatureChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VolvuxWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   84,    2, 0x06 /* Public */,
       3,    1,   87,    2, 0x06 /* Public */,
       4,    1,   90,    2, 0x06 /* Public */,
       5,    1,   93,    2, 0x06 /* Public */,
       6,    1,   96,    2, 0x06 /* Public */,
       7,    1,   99,    2, 0x06 /* Public */,
       8,    1,  102,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    0,  105,    2, 0x0a /* Public */,
      10,    1,  106,    2, 0x0a /* Public */,
      12,    1,  109,    2, 0x0a /* Public */,
      13,    1,  112,    2, 0x0a /* Public */,
      14,    1,  115,    2, 0x0a /* Public */,
      15,    1,  118,    2, 0x0a /* Public */,
      16,    1,  121,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   11,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,

       0        // eod
};

void VolvuxWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        VolvuxWidget *_t = static_cast<VolvuxWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->framePercentageGenerated((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 1: _t->memoryAllocatedMegaBytes((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->eyeZChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 3: _t->fovChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 4: _t->zNearChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 5: _t->zFarChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 6: _t->binVoxLoaded((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->generateFrames(); break;
        case 8: _t->setOffscreenRendering((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->onEyeZChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 10: _t->onZNearChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 11: _t->onZFarChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 12: _t->onSurfaceThicknessChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 13: _t->onSurfaceCurvatureChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (VolvuxWidget::*_t)(double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VolvuxWidget::framePercentageGenerated)) {
                *result = 0;
            }
        }
        {
            typedef void (VolvuxWidget::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VolvuxWidget::memoryAllocatedMegaBytes)) {
                *result = 1;
            }
        }
        {
            typedef void (VolvuxWidget::*_t)(double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VolvuxWidget::eyeZChanged)) {
                *result = 2;
            }
        }
        {
            typedef void (VolvuxWidget::*_t)(double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VolvuxWidget::fovChanged)) {
                *result = 3;
            }
        }
        {
            typedef void (VolvuxWidget::*_t)(double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VolvuxWidget::zNearChanged)) {
                *result = 4;
            }
        }
        {
            typedef void (VolvuxWidget::*_t)(double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VolvuxWidget::zFarChanged)) {
                *result = 5;
            }
        }
        {
            typedef void (VolvuxWidget::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VolvuxWidget::binVoxLoaded)) {
                *result = 6;
            }
        }
    }
}

const QMetaObject VolvuxWidget::staticMetaObject = {
    { &QGLWidget::staticMetaObject, qt_meta_stringdata_VolvuxWidget.data,
      qt_meta_data_VolvuxWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *VolvuxWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VolvuxWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_VolvuxWidget.stringdata0))
        return static_cast<void*>(const_cast< VolvuxWidget*>(this));
    return QGLWidget::qt_metacast(_clname);
}

int VolvuxWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void VolvuxWidget::framePercentageGenerated(double _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void VolvuxWidget::memoryAllocatedMegaBytes(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void VolvuxWidget::eyeZChanged(double _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void VolvuxWidget::fovChanged(double _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void VolvuxWidget::zNearChanged(double _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void VolvuxWidget::zFarChanged(double _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void VolvuxWidget::binVoxLoaded(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_END_MOC_NAMESPACE

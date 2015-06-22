/****************************************************************************
** Meta object code from reading C++ file 'openglwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "src/openglwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'openglwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_OpenGLWidget_t {
    QByteArrayData data[65];
    char stringdata[1014];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_OpenGLWidget_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_OpenGLWidget_t qt_meta_stringdata_OpenGLWidget = {
    {
QT_MOC_LITERAL(0, 0, 12), // "OpenGLWidget"
QT_MOC_LITERAL(1, 13, 12), // "modelChanged"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 10), // "fpsChanged"
QT_MOC_LITERAL(4, 38, 9), // "printHelp"
QT_MOC_LITERAL(5, 48, 5), // "reset"
QT_MOC_LITERAL(6, 54, 11), // "saveAsImage"
QT_MOC_LITERAL(7, 66, 15), // "selectNextModel"
QT_MOC_LITERAL(8, 82, 15), // "selectPrevModel"
QT_MOC_LITERAL(9, 98, 15), // "toggleWireframe"
QT_MOC_LITERAL(10, 114, 17), // "switchToWireframe"
QT_MOC_LITERAL(11, 132, 19), // "toggleNormalDisplay"
QT_MOC_LITERAL(12, 152, 16), // "addNormalDisplay"
QT_MOC_LITERAL(13, 169, 15), // "toggleSolidView"
QT_MOC_LITERAL(14, 185, 13), // "switchToSolid"
QT_MOC_LITERAL(15, 199, 16), // "toggleProjection"
QT_MOC_LITERAL(16, 216, 18), // "switchToOrthogonal"
QT_MOC_LITERAL(17, 235, 19), // "switchToPerspective"
QT_MOC_LITERAL(18, 255, 13), // "toggleCulling"
QT_MOC_LITERAL(19, 269, 12), // "toggleShadow"
QT_MOC_LITERAL(20, 282, 14), // "toggleShowAxes"
QT_MOC_LITERAL(21, 297, 16), // "toggleBackground"
QT_MOC_LITERAL(22, 314, 13), // "changeShading"
QT_MOC_LITERAL(23, 328, 17), // "toggleToonShading"
QT_MOC_LITERAL(24, 346, 16), // "switchToZShading"
QT_MOC_LITERAL(25, 363, 19), // "switchToFlatShading"
QT_MOC_LITERAL(26, 383, 20), // "switchToPhongShading"
QT_MOC_LITERAL(27, 404, 19), // "switchToCellShading"
QT_MOC_LITERAL(28, 424, 21), // "switchToNormalShading"
QT_MOC_LITERAL(29, 446, 16), // "tuneAmbientLight"
QT_MOC_LITERAL(30, 463, 16), // "tuneDiffuseLight"
QT_MOC_LITERAL(31, 480, 17), // "tuneSpecularLight"
QT_MOC_LITERAL(32, 498, 20), // "switchKaKdKsLighting"
QT_MOC_LITERAL(33, 519, 24), // "switchToDirectionalLight"
QT_MOC_LITERAL(34, 544, 16), // "togglePointLight"
QT_MOC_LITERAL(35, 561, 18), // "switchToPointLight"
QT_MOC_LITERAL(36, 580, 15), // "turnOnSpotlight"
QT_MOC_LITERAL(37, 596, 20), // "changeSpotlightAngle"
QT_MOC_LITERAL(38, 617, 8), // "rotateUp"
QT_MOC_LITERAL(39, 626, 10), // "rotateDown"
QT_MOC_LITERAL(40, 637, 10), // "rotateLeft"
QT_MOC_LITERAL(41, 648, 11), // "rotateRight"
QT_MOC_LITERAL(42, 660, 3), // "pan"
QT_MOC_LITERAL(43, 664, 5), // "panUp"
QT_MOC_LITERAL(44, 670, 7), // "panDown"
QT_MOC_LITERAL(45, 678, 7), // "panLeft"
QT_MOC_LITERAL(46, 686, 8), // "panRight"
QT_MOC_LITERAL(47, 695, 6), // "zoomIn"
QT_MOC_LITERAL(48, 702, 7), // "zoomOut"
QT_MOC_LITERAL(49, 710, 11), // "moveForward"
QT_MOC_LITERAL(50, 722, 12), // "moveBackward"
QT_MOC_LITERAL(51, 735, 22), // "setLightSourcePosition"
QT_MOC_LITERAL(52, 758, 13), // "toggleTexture"
QT_MOC_LITERAL(53, 772, 18), // "switchTextureModes"
QT_MOC_LITERAL(54, 791, 22), // "switchToTextureNearest"
QT_MOC_LITERAL(55, 814, 21), // "switchToTextureLinear"
QT_MOC_LITERAL(56, 836, 18), // "switchToTextureNMN"
QT_MOC_LITERAL(57, 855, 18), // "switchToTextureLMN"
QT_MOC_LITERAL(58, 874, 18), // "switchToTextureNML"
QT_MOC_LITERAL(59, 893, 18), // "switchToTextureLML"
QT_MOC_LITERAL(60, 912, 14), // "turnOffTexture"
QT_MOC_LITERAL(61, 927, 23), // "switchToTextureWrapping"
QT_MOC_LITERAL(62, 951, 24), // "switchToTextureMirroring"
QT_MOC_LITERAL(63, 976, 23), // "switchToTextureClamping"
QT_MOC_LITERAL(64, 1000, 13) // "enterDemoMode"

    },
    "OpenGLWidget\0modelChanged\0\0fpsChanged\0"
    "printHelp\0reset\0saveAsImage\0selectNextModel\0"
    "selectPrevModel\0toggleWireframe\0"
    "switchToWireframe\0toggleNormalDisplay\0"
    "addNormalDisplay\0toggleSolidView\0"
    "switchToSolid\0toggleProjection\0"
    "switchToOrthogonal\0switchToPerspective\0"
    "toggleCulling\0toggleShadow\0toggleShowAxes\0"
    "toggleBackground\0changeShading\0"
    "toggleToonShading\0switchToZShading\0"
    "switchToFlatShading\0switchToPhongShading\0"
    "switchToCellShading\0switchToNormalShading\0"
    "tuneAmbientLight\0tuneDiffuseLight\0"
    "tuneSpecularLight\0switchKaKdKsLighting\0"
    "switchToDirectionalLight\0togglePointLight\0"
    "switchToPointLight\0turnOnSpotlight\0"
    "changeSpotlightAngle\0rotateUp\0rotateDown\0"
    "rotateLeft\0rotateRight\0pan\0panUp\0"
    "panDown\0panLeft\0panRight\0zoomIn\0zoomOut\0"
    "moveForward\0moveBackward\0"
    "setLightSourcePosition\0toggleTexture\0"
    "switchTextureModes\0switchToTextureNearest\0"
    "switchToTextureLinear\0switchToTextureNMN\0"
    "switchToTextureLMN\0switchToTextureNML\0"
    "switchToTextureLML\0turnOffTexture\0"
    "switchToTextureWrapping\0"
    "switchToTextureMirroring\0"
    "switchToTextureClamping\0enterDemoMode"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_OpenGLWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      66,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  344,    2, 0x06 /* Public */,
       3,    1,  347,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,  350,    2, 0x0a /* Public */,
       5,    0,  351,    2, 0x0a /* Public */,
       6,    0,  352,    2, 0x0a /* Public */,
       7,    0,  353,    2, 0x0a /* Public */,
       8,    0,  354,    2, 0x0a /* Public */,
       9,    0,  355,    2, 0x0a /* Public */,
      10,    1,  356,    2, 0x0a /* Public */,
      11,    0,  359,    2, 0x0a /* Public */,
      12,    1,  360,    2, 0x0a /* Public */,
      13,    0,  363,    2, 0x0a /* Public */,
      14,    1,  364,    2, 0x0a /* Public */,
      15,    0,  367,    2, 0x0a /* Public */,
      16,    0,  368,    2, 0x0a /* Public */,
      17,    0,  369,    2, 0x0a /* Public */,
      18,    0,  370,    2, 0x0a /* Public */,
      18,    1,  371,    2, 0x0a /* Public */,
      19,    0,  374,    2, 0x0a /* Public */,
      19,    1,  375,    2, 0x0a /* Public */,
      20,    0,  378,    2, 0x0a /* Public */,
      20,    1,  379,    2, 0x0a /* Public */,
      21,    0,  382,    2, 0x0a /* Public */,
      22,    0,  383,    2, 0x0a /* Public */,
      23,    0,  384,    2, 0x0a /* Public */,
      24,    1,  385,    2, 0x0a /* Public */,
      25,    1,  388,    2, 0x0a /* Public */,
      26,    1,  391,    2, 0x0a /* Public */,
      27,    1,  394,    2, 0x0a /* Public */,
      28,    1,  397,    2, 0x0a /* Public */,
      29,    1,  400,    2, 0x0a /* Public */,
      30,    1,  403,    2, 0x0a /* Public */,
      31,    1,  406,    2, 0x0a /* Public */,
      32,    0,  409,    2, 0x0a /* Public */,
      33,    1,  410,    2, 0x0a /* Public */,
      34,    0,  413,    2, 0x0a /* Public */,
      35,    1,  414,    2, 0x0a /* Public */,
      36,    1,  417,    2, 0x0a /* Public */,
      37,    1,  420,    2, 0x0a /* Public */,
      38,    0,  423,    2, 0x0a /* Public */,
      39,    0,  424,    2, 0x0a /* Public */,
      40,    0,  425,    2, 0x0a /* Public */,
      41,    0,  426,    2, 0x0a /* Public */,
      42,    2,  427,    2, 0x0a /* Public */,
      43,    1,  432,    2, 0x0a /* Public */,
      44,    1,  435,    2, 0x0a /* Public */,
      45,    1,  438,    2, 0x0a /* Public */,
      46,    1,  441,    2, 0x0a /* Public */,
      47,    0,  444,    2, 0x0a /* Public */,
      48,    0,  445,    2, 0x0a /* Public */,
      49,    0,  446,    2, 0x0a /* Public */,
      50,    0,  447,    2, 0x0a /* Public */,
      51,    2,  448,    2, 0x0a /* Public */,
      52,    0,  453,    2, 0x0a /* Public */,
      53,    0,  454,    2, 0x0a /* Public */,
      54,    1,  455,    2, 0x0a /* Public */,
      55,    1,  458,    2, 0x0a /* Public */,
      56,    1,  461,    2, 0x0a /* Public */,
      57,    1,  464,    2, 0x0a /* Public */,
      58,    1,  467,    2, 0x0a /* Public */,
      59,    1,  470,    2, 0x0a /* Public */,
      60,    1,  473,    2, 0x0a /* Public */,
      61,    1,  476,    2, 0x0a /* Public */,
      62,    1,  479,    2, 0x0a /* Public */,
      63,    1,  482,    2, 0x0a /* Public */,
      64,    0,  485,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Float, QMetaType::Float,    2,    2,
    QMetaType::Void, QMetaType::Float,    2,
    QMetaType::Void, QMetaType::Float,    2,
    QMetaType::Void, QMetaType::Float,    2,
    QMetaType::Void, QMetaType::Float,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,

       0        // eod
};

void OpenGLWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        OpenGLWidget *_t = static_cast<OpenGLWidget *>(_o);
        switch (_id) {
        case 0: _t->modelChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->fpsChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->printHelp(); break;
        case 3: _t->reset(); break;
        case 4: _t->saveAsImage(); break;
        case 5: _t->selectNextModel(); break;
        case 6: _t->selectPrevModel(); break;
        case 7: _t->toggleWireframe(); break;
        case 8: _t->switchToWireframe((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->toggleNormalDisplay(); break;
        case 10: _t->addNormalDisplay((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: _t->toggleSolidView(); break;
        case 12: _t->switchToSolid((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 13: _t->toggleProjection(); break;
        case 14: _t->switchToOrthogonal(); break;
        case 15: _t->switchToPerspective(); break;
        case 16: _t->toggleCulling(); break;
        case 17: _t->toggleCulling((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 18: _t->toggleShadow(); break;
        case 19: _t->toggleShadow((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 20: _t->toggleShowAxes(); break;
        case 21: _t->toggleShowAxes((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 22: _t->toggleBackground(); break;
        case 23: _t->changeShading(); break;
        case 24: _t->toggleToonShading(); break;
        case 25: _t->switchToZShading((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 26: _t->switchToFlatShading((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 27: _t->switchToPhongShading((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 28: _t->switchToCellShading((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 29: _t->switchToNormalShading((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 30: _t->tuneAmbientLight((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 31: _t->tuneDiffuseLight((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 32: _t->tuneSpecularLight((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 33: _t->switchKaKdKsLighting(); break;
        case 34: _t->switchToDirectionalLight((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 35: _t->togglePointLight(); break;
        case 36: _t->switchToPointLight((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 37: _t->turnOnSpotlight((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 38: _t->changeSpotlightAngle((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 39: _t->rotateUp(); break;
        case 40: _t->rotateDown(); break;
        case 41: _t->rotateLeft(); break;
        case 42: _t->rotateRight(); break;
        case 43: _t->pan((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 44: _t->panUp((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 45: _t->panDown((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 46: _t->panLeft((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 47: _t->panRight((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 48: _t->zoomIn(); break;
        case 49: _t->zoomOut(); break;
        case 50: _t->moveForward(); break;
        case 51: _t->moveBackward(); break;
        case 52: _t->setLightSourcePosition((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 53: _t->toggleTexture(); break;
        case 54: _t->switchTextureModes(); break;
        case 55: _t->switchToTextureNearest((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 56: _t->switchToTextureLinear((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 57: _t->switchToTextureNMN((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 58: _t->switchToTextureLMN((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 59: _t->switchToTextureNML((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 60: _t->switchToTextureLML((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 61: _t->turnOffTexture((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 62: _t->switchToTextureWrapping((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 63: _t->switchToTextureMirroring((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 64: _t->switchToTextureClamping((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 65: _t->enterDemoMode(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (OpenGLWidget::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&OpenGLWidget::modelChanged)) {
                *result = 0;
            }
        }
        {
            typedef void (OpenGLWidget::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&OpenGLWidget::fpsChanged)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject OpenGLWidget::staticMetaObject = {
    { &QOpenGLWidget::staticMetaObject, qt_meta_stringdata_OpenGLWidget.data,
      qt_meta_data_OpenGLWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *OpenGLWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *OpenGLWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_OpenGLWidget.stringdata))
        return static_cast<void*>(const_cast< OpenGLWidget*>(this));
    if (!strcmp(_clname, "QOpenGLFunctions"))
        return static_cast< QOpenGLFunctions*>(const_cast< OpenGLWidget*>(this));
    return QOpenGLWidget::qt_metacast(_clname);
}

int OpenGLWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QOpenGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 66)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 66;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 66)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 66;
    }
    return _id;
}

// SIGNAL 0
void OpenGLWidget::modelChanged(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void OpenGLWidget::fpsChanged(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE

#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLContext>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QInputEvent>
#include <cstring>

class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    OpenGLWidget(QWidget *parent = 0) : QOpenGLWidget(parent) {
        setFocusPolicy(Qt::StrongFocus);
    }

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void updateModelInfo();
    void fpsCounter();

    void keyPressEvent(QKeyEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

signals:
    void modelChanged(QString);
    void fpsChanged(QString);    

public slots:
    void printHelp();
    void reset();
    void saveAsImage();
    void selectNextModel();
    void selectPrevModel();
    void toggleWireframe();
    void switchToWireframe(bool);
    void toggleNormalDisplay();
    void addNormalDisplay(bool);
    void toggleSolidView();
    void switchToSolid(bool);
    void toggleProjection();
    void switchToOrthogonal();
    void switchToPerspective();
    void toggleCulling();
    void toggleCulling(bool);
    void toggleShadow();
    void toggleShadow(bool);
    void toggleShowAxes();
    void toggleShowAxes(bool);
    void toggleBackground();
    void changeShading();
    void toggleToonShading();
    void switchToZShading(bool);
    void switchToFlatShading(bool);
    void switchToPhongShading(bool);
    void switchToCellShading(bool);
    void switchToNormalShading(bool);
    void tuneAmbientLight(int);
    void tuneDiffuseLight(int);
    void tuneSpecularLight(int);
    void switchKaKdKsLighting();
    void switchToDirectionalLight(bool);
    void togglePointLight();
    void switchToPointLight(bool);
    void turnOnSpotlight(bool);
    void changeSpotlightAngle(int);
    void rotateUp();
    void rotateDown();
    void rotateLeft();
    void rotateRight();
    void pan(float, float);
    void panUp(float);
    void panDown(float);
    void panLeft(float);
    void panRight(float);
    void zoomIn();
    void zoomOut();
    void moveForward();
    void moveBackward();
    void setLightSourcePosition(int,int);
    void toggleTexture();
    void switchTextureModes();
    void switchToTextureNearest(bool);
    void switchToTextureLinear(bool);
    void switchToTextureNMN(bool);
    void switchToTextureLMN(bool);
    void switchToTextureNML(bool);
    void switchToTextureLML(bool);
    void turnOffTexture(bool);
    void switchToTextureWrapping(bool);
    void switchToTextureMirroring(bool);
    void switchToTextureClamping(bool);
    void enterDemoMode();
    void toggleNaturalRotation();
};

#endif // OPENGLWIDGET_H

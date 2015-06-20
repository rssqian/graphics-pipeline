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
    void fpsCounter();

    void keyPressEvent(QKeyEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

signals:
    void fpsChanged(QString);

public slots:
    void printHelp();
    void reset();
    void saveAsImage();
    void selectNextModel();
    void selectPrevModel();
    void toggleWireframe();
    void switchToWireframe(bool);
    void toggleSolidView();
    void switchToSolid(bool);
    void toggleProjection();
    void switchToOrthogonal();
    void switchToPerspective();
    void toggleCulling();
    void toggleTexture();
    void toggleBackground();
    void changeShading();
    void switchToNoShading();
    void switchToFlatShading();
    void switchToPhongShading();
    void tuneAmbientLight(int);
    void tuneDiffuseLight(int);
    void tuneSpecularLight(int);
    void switchKaKdKsLighting();
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
};

#endif // OPENGLWIDGET_H

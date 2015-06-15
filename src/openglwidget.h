#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLContext>
#include <QKeyEvent>

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

    void keyPressEvent(QKeyEvent *event);

public slots:
    void printHelp();
    void reset();
    void saveAsImage();
    void selectNextModel();
    void selectPrevModel();
    void toggleWireframe();
    void switchToWireframe();
    void switchToSolid();
    void toggleProjection();
    void toggleCulling();
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
    void panUp(int);
    void panDown(int);
    void panLeft(int);
    void panRight(int);
    void zoomIn();
    void zoomOut();
    void moveForward();
    void moveBackward();
    void setLightSourcePosition(int,int);
};

#endif // OPENGLWIDGET_H

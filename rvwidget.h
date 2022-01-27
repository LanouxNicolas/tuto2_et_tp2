#ifndef RVWIDGET_H
#define RVWIDGET_H

#include <QWidget>
#include <QMessageBox>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QVector3D>
#include <QTimer>
#include <QMouseEvent>
#include <QKeyEvent>
#include "rvbody.h"
#include "rvcamera.h"
#include "rvpyramid.h"
#include "rvcube.h"
#include "rvplane.h"

class RVWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT


public:
    RVWidget(QWidget *parent = nullptr);
    ~RVWidget();



private:
    float angleY;
    float angleX;
    QTimer* timer;
    QPointF oldpos;
    bool isSpinning;
    int fov;
    RVBody* body;
    RVBody* plane;
    RVCamera* camera;

private slots:
    void update();

public slots:
    void startAnimation();
    void changeFov(int);
    void changeOpacity(int);
    void toggleWireframe(bool);
    void toggleCulling(bool);
    void changeScale(int);
    void changeSaturation(int);

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;

    // QOpenGLWidget interface
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
};
#endif // RVWIDGET_H

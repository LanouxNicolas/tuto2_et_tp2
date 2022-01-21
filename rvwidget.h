#ifndef RVWIDGET_H
#define RVWIDGET_H

#include <QWidget>
#include <QMessageBox>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QTimer>
#include "rvbody.h"
#include "rvcamera.h"
#include "rvpyramid.h"

class RVWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT


public:
    RVWidget(QWidget *parent = nullptr);
    ~RVWidget();

    // Attributs pour le rendu
private:
    RVBody* body;
    RVCamera* camera;
    QTimer* timer;
    float angleY;

protected slots:
    void update();
    void changeFov(float fov);

    // QOpenGLWidget interface
protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
};
#endif // RVWIDGET_H

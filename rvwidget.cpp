#include "rvwidget.h"

RVWidget::RVWidget(QWidget *parent)
    : QOpenGLWidget(parent), QOpenGLFunctions()
{
    timer = new QTimer();
    angleY = 5;
}

RVWidget::~RVWidget()
{
}

void RVWidget::update()
{
    body->rotate(angleY, QVector3D(0, 1, 0));
    QOpenGLWidget::update();
}

void RVWidget::changeFov(float fov)
{
    camera->setFov(fov);
    this->update();
}



void RVWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0.0f, 0.566f, 0.867f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    //glDisable(GL_CULL_FACE);

    camera = new RVCamera();
    body = new RVPyramid();
    body->setCamera(camera);
    body->setPosition(QVector3D(0, -0.5, -80));
    body->initialize();
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(10);
}

void RVWidget::resizeGL(int w, int h)
{
    float fov = ((float)w)/h;
    camera->setFov(fov);
    glViewport(0, 0, w, h);
}

void RVWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    body->draw();
}


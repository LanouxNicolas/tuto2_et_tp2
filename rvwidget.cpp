#include "rvwidget.h"

RVWidget::RVWidget(QWidget *parent)
    : QOpenGLWidget(parent), QOpenGLFunctions()
{
    angleY=0;
    angleX=0;
    timer = new QTimer(this);
    isSpinning=false;
    fov = 45;
    opacity=100;
}

RVWidget::~RVWidget()
{
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
    body->setPosition(QVector3D(0, -0.5f, -80));
    body->initialize();
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(10); // ou (*timer).
}

void RVWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    camera->setAspect((float)w/h);
}

void RVWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    body->draw();
}

void RVWidget::update(){
    angleY+=5;
    QOpenGLWidget::update();
}

void RVWidget::mousePressEvent(QMouseEvent* event){
    oldpos = QPointF(event->position());
}

void RVWidget::mouseMoveEvent(QMouseEvent* event){
    QPointF pos = QPointF(event->position());
    float dx = (-oldpos.x()+pos.x())/width();
    float dy = (-oldpos.y()+pos.y())/height();
    angleX+=dy*180;
    angleY+=dx*180;
    oldpos = QPointF(event->position());
    QOpenGLWidget::update();
}

void RVWidget::startAnimation(){
    if (isSpinning){
        timer->stop();
    }
    else{
        timer->start(30);
    }
    isSpinning=!isSpinning;
}

void RVWidget::changeFov(int newFov)
{
    camera->setFov(newFov);
    this->update();
}

void RVWidget::changeOpacity(int newOpacity)
{
    opacity = newOpacity;
    QOpenGLWidget::update();
}

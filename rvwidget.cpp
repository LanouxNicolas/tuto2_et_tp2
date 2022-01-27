#include "rvwidget.h"

RVWidget::RVWidget(QWidget *parent)
    : QOpenGLWidget(parent), QOpenGLFunctions()
{
    angleY=0;
    angleX=0;
    timer = new QTimer(this);
    isSpinning=false;
    fov = 45;
    grabKeyboard();
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
    camera->setPosition(QVector3D(0, 7, 4));
    body = new RVCube();
    body->setCamera(camera);
    body->setPosition(QVector3D(0, 0, 0));//0,0,-4
    body->initialize();
    plane = new RVPlane();
    plane->setCamera(camera);
    plane->setPosition(QVector3D(0, 0, 0));
    plane->setScale(5);
    plane->initialize();


    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    //timer->start(10); // ou (*timer).
}

void RVWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    camera->setAspect((float)w/h);
}

void RVWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for (int i=-15;i<15;i=i+3){
        for (int j =-15; j<15;j=j+3){
            body->setPosition(QVector3D(i,0,j));
            body->draw();
        }
    }
    plane->draw();
}

void RVWidget::update(){
    //angleY+=5;
    body->rotate(5,QVector3D(0,1,0));
    //body->setOrientation(angleY,angleX,0.0);
    QOpenGLWidget::update();
}

void RVWidget::mousePressEvent(QMouseEvent* event){
    oldpos = QPointF(event->position());
}

void RVWidget::mouseMoveEvent(QMouseEvent* event){
    QPointF pos = QPointF(event->position());
    float dx = (-oldpos.x()+pos.x())/width();
    float dy = (-oldpos.y()+pos.y())/height();
    angleX=dy*180;
    angleY=dx*180;
    oldpos = QPointF(event->position());
    body->rotate(angleX,QVector3D(1,0,0));
    body->rotate(angleY,QVector3D(0,1,0));
    QOpenGLWidget::update();
}

void RVWidget::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Left){
        camera->setPosition(camera->getPosition().operator+=(QVector3D(-1,0,0)));
    }
    else if(event->key()==Qt::Key_Right){
        camera->setPosition(camera->getPosition().operator+=(QVector3D(1,0,0)));
    }
    else if(event->key()==Qt::Key_Up){
        camera->setPosition(camera->getPosition().operator+=(QVector3D(0,0,-1)));
    }
    else if(event->key()==Qt::Key_Down){
        camera->setPosition(camera->getPosition().operator+=(QVector3D(0,0,1)));
    }
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
    body->setOpacity((float)newOpacity/100);
    QOpenGLWidget::update();
}

void RVWidget::toggleWireframe(bool val)
{
    body->setWireframe(val);
    QOpenGLWidget::update();
}

void RVWidget::toggleCulling(bool val)
{
    body->setCulling(val);
    QOpenGLWidget::update();
}

void RVWidget::changeScale(int val)
{
    body->setScale(val);
    QOpenGLWidget::update();
}

void RVWidget::changeSaturation(int g)
{
    body->setGlobalColor(QVector3D((float)g/255,(float)g/255,(float)g/255));
    QOpenGLWidget::update();
}

#include "rvcamera.h"

RVCamera::RVCamera()
{
    position = QVector3D(0, 0, 0);
    target = QVector3D(0, 0, -1);
    up = QVector3D(0, 1, 0);
    fov  = 45;
    aspect = 1.33f;
    zMax = 100;
    zMin  = 0.1f;
}

RVCamera::~RVCamera()
{
}

QMatrix4x4 RVCamera::viewMatrix()
{
    QMatrix4x4 view;
    view.lookAt(position, target, up);
    return view;
}

QMatrix4x4 RVCamera::projectionMatrix()
{
    QMatrix4x4 proj;
    proj.perspective(fov, aspect, zMin, zMax);
    return proj;
}

QVector3D RVCamera::getPosition() const
{
    return position;
}

void RVCamera::setPosition(const QVector3D &position)
{
    this->position = position;
}

QVector3D RVCamera::getTarget() const
{
    return target;
}

void RVCamera::setTarget(const QVector3D &target)
{
    this->target = target;
}

QVector3D RVCamera::getUp() const
{
    return up;
}

void RVCamera::setUp(const QVector3D &up)
{
    this->up = up;
}

float RVCamera::getFov() const
{
    return fov;
}

void RVCamera::setFov(float fov)
{
    this->fov = fov;
}

float RVCamera::getAspect() const
{
    return aspect;
}

void RVCamera::setAspect(float aspect)
{
    this->aspect = aspect;
}

float RVCamera::getZMin() const
{
    return zMin;
}

void RVCamera::setZMin(float zMin)
{
    this->zMin = zMin;
}

float RVCamera::getZMax() const
{
    return zMax;
}

void RVCamera::setZMax(float zMax)
{
    this->zMax = zMax;
}

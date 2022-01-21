#include "rvbody.h"

RVBody::RVBody()
    :QOpenGLFunctions(),
      vao(), program(),
      position(), orientation()
{
    vbo = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    ibo = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    vbo.create();
    ibo.create();
    vao.create();
    program.create();

    numVertices = 0;
    numTriangles = 0;
    numIndices = 0;

    VSFileName = "NO VS FILE";
    FSFileName = "NO FS FILE";
}

RVBody::~RVBody()
{
    if (program.hasOpenGLShaderPrograms())
        program.removeAllShaders();
    vao.destroy();
    ibo.destroy();
    vbo.destroy();
}


void RVBody::initialize()
{
    initializeShader();
    initializeBuffer();		//à écrire dans la classe fille
    initializeVAO();    	//à écrire dans la classe fille
}

void RVBody::initializeShader()
{
    initializeOpenGLFunctions();

    if (program.hasOpenGLShaderPrograms())
        program.removeAllShaders();
    bool resultat;

    program.bind();
    //Vertex Shader
    resultat = program.addShaderFromSourceFile(QOpenGLShader::Vertex, VSFileName);
    if (!resultat)     {
        QMessageBox msg;
        msg.setWindowTitle("Vertex shader");
        msg.setText(program.log());
        msg.exec();
        exit(EXIT_FAILURE);
    }

    //Fragment Shader
    resultat = program.addShaderFromSourceFile(QOpenGLShader::Fragment, FSFileName);
    if (!resultat)     {
        QMessageBox msg;
        msg.setWindowTitle("Fragment shader");
        msg.setText(program.log());
        msg.exec();
        exit(EXIT_FAILURE);
    }

    //Link
    resultat = program.link();
    if (!resultat)     {
        QMessageBox msg;
        msg.setWindowTitle("Link du shader program");
        msg.setText(program.log());
        msg.exec();
        exit(EXIT_FAILURE);
    }

    //Libération
    program.release();
}

QMatrix4x4 RVBody::modelMatrix()
{
    QMatrix4x4 model;
    model.translate(position);
    model.rotate(orientation);
    return model;
}

void RVBody::translate(QVector3D position)
{
    this->position += position;
}

void RVBody::rotate(float angle, QVector3D axis)
{
    orientation =  QQuaternion::fromAxisAndAngle(axis, angle) * orientation ;
}

void RVBody::setOrientation(float yaw, float pitch, float roll)
{
    orientation = QQuaternion::fromEulerAngles(pitch, yaw, roll);
}

void RVBody::setCamera(RVCamera *newCamera)
{
    camera = newCamera;
}

void RVBody::setPosition(const QVector3D &newPosition)
{
    position = newPosition;
}

const QVector3D &RVBody::getPosition() const
{
    return position;
}

const QQuaternion &RVBody::getOrientation() const
{
    return orientation;
}

const QString &RVBody::getVSFileName() const
{
    return VSFileName;
}

const QString &RVBody::getFSFileName() const
{
    return FSFileName;
}

void RVBody::setVSFileName(const QString &newVSFileName)
{
    VSFileName = newVSFileName;
}

void RVBody::setFSFileName(const QString &newFSFileName)
{
    FSFileName = newFSFileName;
}

int RVBody::getNumVertices() const
{
    return numVertices;
}

int RVBody::getNumTriangles() const
{
    return numTriangles;
}

int RVBody::getNumIndices() const
{
    return numIndices;
}

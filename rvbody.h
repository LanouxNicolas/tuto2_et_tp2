#ifndef RVBODY_H
#define RVBODY_H

#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include <QMessageBox>

#include "rvcamera.h"

class RVBody : public QOpenGLFunctions
{
public:
    RVBody();
    virtual ~RVBody();

    virtual void draw() = 0;
    virtual QMatrix4x4 modelMatrix();

    void initialize();
    void initializeShader();
    virtual void initializeBuffer() = 0;
    virtual void initializeVAO() = 0;

    // pour bouger l'objet
    void rotate(float angle, QVector3D axis);
    void translate(QVector3D position);
    void setOrientation(float yaw, float pitch, float roll);

    // accesseurs et mutateurs .....
    RVCamera *getCamera() const;
    void setCamera(RVCamera *newCamera);

    const QVector3D &getPosition() const;
    void setPosition(const QVector3D &newPosition);

    const QQuaternion &getOrientation() const;
    void setOrientation(const QQuaternion &newOrientation);

    int getNumVertices() const;

    int getNumTriangles() const;

    int getNumIndices() const;

    const QString &getVSFileName() const;
    void setVSFileName(const QString &newVSFileName);

    const QString &getFSFileName() const;
    void setFSFileName(const QString &newFSFileName);

protected:
    QString VSFileName;               //! : nom du fichier qui contient le vertex shader
    QString FSFileName;               //! : nom du fichier qui contient le fragment shader
    QOpenGLBuffer vbo;                //! : vertex buffer qui stocke les sommets du maillage
    QOpenGLBuffer ibo;                //! : index buffer (optionnel) qui stocke les index à utiliser pour le rendu
    QOpenGLVertexArrayObject vao;     //! : vertex array object (obligatoire)
    QOpenGLShaderProgram program;     //! : shader program (obligatoire)

    QVector3D position;               //! : position de l'objet dans la scène
    QQuaternion orientation;          //! : attitude de l'objet dans la scène

    int numVertices;                  //! : nombre de sommets de l'objet (lecture seule)
    int numTriangles;                 //! : nombre de triangles de l'objet (lecture seule)
    int numIndices;                   //! : nombre d'index (0 si on n'utilise pas l'ibo)

    RVCamera *camera;                 //! : pointeur sur la caméra utilisée pour le rendu.
};

#endif // RVBODY_H

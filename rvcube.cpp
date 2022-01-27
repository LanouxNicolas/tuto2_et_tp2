#include "rvcube.h"

RVCube::RVCube()
    :RVBody()
{
    //Je définis ici les shaders à utiliser dans RVPyramid
    VSFileName = ":/shaders/VS_simple.vsh";
    FSFileName = ":/shaders/FS_simple.fsh";
}

void RVCube::draw()
{
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    if (wireframe){
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else{
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    if(culling){
        glEnable(GL_CULL_FACE);
    }
    else{
        glDisable(GL_CULL_FACE);
    }
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    program.bind();
    vao.bind();

    //Définition de la variable uniforme
    QMatrix4x4 matrix;

    matrix = camera->projectionMatrix() * camera->viewMatrix() * this->modelMatrix();
    //program.setUniformValue("u_ModelViewProjectionMatrix", matrix);

   // camera->projectionMatrix().perspective(camera->getFov(), camera->getAspect(), 0.1f, 100.0f);
    //matrix = camera->projectionMatrix() * camera->viewMatrix() * this->modelMatrix();
    program.setUniformValue("u_ModelViewProjectionMatrix", matrix);
    program.setUniformValue("u_Opacity", opacity);
    program.setUniformValue("u_color", globalColor);
    //Commande de rendu (indexé)
    for(int i =0;i<6;i++){
        glDrawArrays(GL_TRIANGLE_FAN, i*4, 4);
        //glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    }

    vao.release();
    program.release();
}

void RVCube::initializeBuffer()
{
    //Définition de 4 points
    QVector3D A(0, 0, 1);
    QVector3D B(1, 0, 1);
    QVector3D C(1, 1, 1);
    QVector3D D(0, 1, 1);
    QVector3D E(0, 0, 0);
    QVector3D F(1, 0, 0);
    QVector3D G(1, 1, 0);
    QVector3D H(0, 1, 0);

    //Définition de 4 couleurs
    QVector3D rouge(1, 0, 0);
    QVector3D vert(0, 1, 0);
    QVector3D bleu(0, 0, 1);
    QVector3D magenta(1, 0, 1);
    QVector3D cyan(0, 1, 1);
    QVector3D jaune(1, 1, 0);

    //On prépare le tableau des données
    QVector3D vertexData[] = {
        A, B, C, D,
        F, E, H, G,
        D, C, G, H,
        B, F, G, C,
        E, A, D, H,
        E, F, B, A,
        rouge, rouge, rouge, rouge,
        cyan, cyan, cyan, cyan,
        bleu, bleu, bleu, bleu,
        magenta, magenta, magenta, magenta,
        vert, vert, vert, vert,
        jaune, jaune, jaune, jaune
    };

    //Initialisation du Vertex Buffer Object
    vbo = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    //Création du VBO
    vbo.create();
    //Lien du VBO avec le contexte de rendu OpenGL
    vbo.bind();
    //Allocation des données dans le VBO
    vbo.allocate(vertexData, sizeof (vertexData));
    vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    //Libération du VBO
    vbo.release();

    numVertices = 24;
    numTriangles=12;                 //! : nombre de triangles de l'objet (lecture seule)
    numIndices=4;
}

void RVCube::initializeVAO()
{
    //Initialisation du Vertex Array Object
    program.bind();
    vao.bind();
    vbo.bind();

    //Définition des attributs
    program.setAttributeBuffer("rv_Position", GL_FLOAT, 0, 3);
    program.enableAttributeArray("rv_Position");

    program.setAttributeBuffer("rv_Color", GL_FLOAT, sizeof(QVector3D)*numVertices, 3);
    program.enableAttributeArray("rv_Color");

    //Libération
    vao.release();
    program.release();
}

QMatrix4x4 RVCube::modelMatrix()
{
    QMatrix4x4 model;
    model.translate(-0.5f, -0.5f, -0.5f);
    return RVBody::modelMatrix() * model;
}

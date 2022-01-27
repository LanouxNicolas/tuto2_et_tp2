#include "rvplane.h"

RVPlane::RVPlane()
{
    x=10;
    z=10;
    FSFileName = ":/shaders/FS_plan.fsh";
}

void RVPlane::initializeBuffer(){
    globalColor=QVector3D(0,11,0);
    //Définition de 4 points
    QVector3D A(-x/2.0, 0, -z/2.0);
    QVector3D B(-x/2.0, 0, z/2.0);
    QVector3D C(x/2.0, 0, z/2.0);
    QVector3D D(x/2.0, 0, -z/2.0);

    //Initialisation du Vertex Buffer Object
    //On prépare le tableau des données
    QVector3D vertexData[] = {
        A, B, C, D
    };
    //Lien du VBO avec le contexte de rendu OpenG
    vbo.bind();
    //Allocation des données dans le VBO
    vbo.allocate(vertexData, sizeof (vertexData));
    vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    //Libération du VBO
    vbo.release();
}

void RVPlane::draw()
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
    //for(int i =0;i<6;i++){
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
        //glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    //}

    vao.release();
    program.release();
}

QMatrix4x4 RVPlane::modelMatrix()
{
    QMatrix4x4 model;
    model.translate(-0.5f, -0.5f, -0.5f);
    return RVBody::modelMatrix() * model;
}


#include "prism.h"

Prism::Prism()
{
    motion = Vec4();
    enable_texture = false;
    enable_bumping = false;
    //valores default do prisma de base triangular reto
    double cathetus = 1.0;
    double height   = 1.0;

    vertexs[0].setVec4(0.0,0.0,0.0);
    vertexs[1].setVec4(0.0,0.0,cathetus);
    vertexs[2].setVec4(cathetus,0.0,0.0);
    vertexs[3].setVec4(0.0,height,0.0);
    vertexs[4].setVec4(0.0,height,cathetus);
    vertexs[5].setVec4(cathetus,height,0.0);
    initvertexs[0].setVec4(0.0,0.0,0.0);
    initvertexs[1].setVec4(0.0,0.0,cathetus);
    initvertexs[2].setVec4(cathetus,0.0,0.0);
    initvertexs[3].setVec4(0.0,height,0.0);
    initvertexs[4].setVec4(0.0,height,cathetus);
    initvertexs[5].setVec4(cathetus,height,0.0);
transform.setIdentity();
    refreshNormals();
    mesh = new Mesh();

    Face face[5];

    face[0].vertexs.push_back(&vertexs[0]);
    face[0].vertexs.push_back(&vertexs[2]);
    face[0].vertexs.push_back(&vertexs[1]);
    face[0].normals.push_back(&normals[0]);
//    face[0].normals.push_back(&normals[0]);
//    face[0].normals.push_back(&normals[0]);
    mesh->faces.push_back(face[0]);

    face[1].vertexs.push_back(&vertexs[3]);
    face[1].vertexs.push_back(&vertexs[4]);
    face[1].vertexs.push_back(&vertexs[5]);
    face[1].normals.push_back(&normals[1]);
//    face[1].normals.push_back(&normals[1]);
//    face[1].normals.push_back(&normals[1]);
    mesh->faces.push_back(face[1]);

    face[2].vertexs.push_back(&vertexs[2]);
    face[2].vertexs.push_back(&vertexs[5]);
    face[2].vertexs.push_back(&vertexs[4]);
    face[2].vertexs.push_back(&vertexs[1]);
    face[2].normals.push_back(&normals[2]);
//    face[2].normals.push_back(&normals[2]);
//    face[2].normals.push_back(&normals[2]);
//    face[2].normals.push_back(&normals[2]);
    mesh->faces.push_back(face[2]);

    face[3].vertexs.push_back(&vertexs[0]);
    face[3].vertexs.push_back(&vertexs[3]);
    face[3].vertexs.push_back(&vertexs[5]);
    face[3].vertexs.push_back(&vertexs[2]);
    face[3].normals.push_back(&normals[3]);
//    face[3].normals.push_back(&normals[3]);
//    face[3].normals.push_back(&normals[3]);
//    face[3].normals.push_back(&normals[3]);
    mesh->faces.push_back(face[3]);

    face[4].vertexs.push_back(&vertexs[0]);
    face[4].vertexs.push_back(&vertexs[1]);
    face[4].vertexs.push_back(&vertexs[4]);
    face[4].vertexs.push_back(&vertexs[3]);
    face[4].normals.push_back(&normals[4]);
//    face[4].normals.push_back(&normals[4]);
//    face[4].normals.push_back(&normals[4]);
//    face[4].normals.push_back(&normals[4]);
    mesh->faces.push_back(face[4]);
    enabled = true;
    selected = false;


}

void Prism::refreshNormals()
{
    //normais a face
    normals[0] = Vec4::crossProduct(vertexs[2]-vertexs[0],vertexs[1]-vertexs[2]).unitary(); //vertices:0,1,2
    normals[1] = Vec4::crossProduct(vertexs[4]-vertexs[3],vertexs[5]-vertexs[4]).unitary(); //vertices:3,4,5
    normals[2] = Vec4::crossProduct(vertexs[5]-vertexs[2],vertexs[4]-vertexs[5]).unitary(); //vertices:1,2,4,5
    normals[3] = Vec4::crossProduct(vertexs[3]-vertexs[0],vertexs[5]-vertexs[3]).unitary(); //vertices:0,2,3,5
    normals[4] = Vec4::crossProduct(vertexs[0]-vertexs[3],vertexs[1]-vertexs[0]).unitary(); //vertices:0,1,3,4

    //normal do vertice é a média das normais as faces que o vertice pertence
//    normals[0] = ((normal[0]+normal[3]+normal[4])/3.0).unitary();
//    normals[1] = ((normal[0]+normal[2]+normal[4])/3.0).unitary();
//    normals[2] = ((normal[0]+normal[2]+normal[3])/3.0).unitary();
//    normals[3] = ((normal[1]+normal[3]+normal[4])/3.0).unitary();
//    normals[4] = ((normal[1]+normal[2]+normal[4])/3.0).unitary();
//    normals[5] = ((normal[1]+normal[2]+normal[3])/3.0).unitary();
}

void Prism::draw()
{
    if(isEnabled()){

    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    glColor3f(0,0,1);
    for(int i=0;i<6;i++){
        vertexs[i] = transform.transpose().vector(initvertexs[i]);

    }
    glPointSize(1);
    refreshNormals();

    mesh->draw();
    //this->//boundingBox().wireframe();
    }
    if (selected){
        Draw::drawSelection(getMax(),getMin());

//        glColor3f(1,1,1);
//        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
//        mesh->draw();

    }
}

void Prism::wireframe()
{

    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    for(int i=0;i<6;i++){
        vertexs[i] = transform.transpose().vector(initvertexs[i]);
    }
    refreshNormals();
    mesh->draw();
}

void Prism::aplyTransform(Matrix4x4 t)
{
    transform = transform.multMatrix(transform,t);
    transform = t;

}

void Prism::setIdentityTransform()
{
    transform.setIdentity();
}


void Prism::setMaterial(int material)
{
    mesh->setMaterial(material);
}

void Prism::changeCoords(Matrix4x4 matrix)
{
    transform = transform.multMatrix(transform,matrix);
    for(int i=0;i<6;i++){
        vertexs[i] = transform.transpose().vector(initvertexs[i]);
    }
    refreshNormals();
}

Mesh * Prism::getMesh()
{
    return mesh;
}

void Prism::setName(QString nm)
{
    name = nm;
}

QString Prism::getName()
{
    return name;
}

int Prism::getIdMaterial()
{
    return mesh->getMaterial();
}

void Prism::tryIntersection(RayIntersection *intersect, Ray ray)
{
    if(motion==Vec4())
    intersect->rayBoxIntersection(mesh,ray,transform,getMaxInit(),getMinInit(),this);
    else{
        Matrix4x4 mat = Matrix4x4();
        mat.setIdentity();
        Vec4 position = this->getMatrixTransformation().getTranslateSeted();
        Vec4 rotate = this->getMatrixTransformation().getRotationSeted();
        Vec4 scale = this->getMatrixTransformation().getScaleSeted();

        Vec4 nextposition = position+this->motion;
        nextposition = position + (nextposition - position)*myrand;
        mat.scale(scale.x(),scale.y(),scale.z());
        mat.setRotationX(rotate.x());
        mat.setRotationY(rotate.y());
        mat.setRotationZ(rotate.z());
        mat.setTranslate(nextposition);
        intersect->rayBoxIntersection(mesh,ray,mat,getMaxInit(),getMinInit(),this);
    }
}

void Prism::setSelected(bool b)
{
    selected = b;
}

bool Prism::isSelected()
{
    return selected;
}

void Prism::setEnabled(bool b)
{
    enabled = b;
}

bool Prism::isEnabled()
{
    return enabled;
}

Matrix4x4 Prism::getMatrixTransformation()
{
    return transform;
}

int Prism::getNumFaces()
{
    return mesh->faces.size();
}

int Prism::getNumVertexs()
{
    return 6;
}

void Prism::setTransform(Matrix4x4 m)
{
    transform = m;
}



QString Prism::saveObject()
{
    QString obj;
    QString aux;
    obj += "p ";
    Vec4 parameters;
    //translacao
    parameters = transform.getTranslateSeted();
    obj += aux.sprintf("%.3f %.3f %.3f ",parameters.x(),parameters.y(),parameters.z());
    //escala
    parameters = transform.getScaleSeted();
    obj += aux.sprintf("%.3f %.3f %.3f ",parameters.x(),parameters.y(),parameters.z());
    //rotação
    parameters = transform.getRotationSeted();
    obj += aux.sprintf("%.3f %.3f %.3f ",parameters.x(),parameters.y(),parameters.z());
    obj += aux.sprintf("%d ",this->getIdMaterial());
    parameters = this->getMesh()->getMaterialM()->getAmbiente();
    obj += aux.sprintf("%.3f %.3f %.3f ",parameters.x(),parameters.y(),parameters.z());
    parameters = this->getMesh()->getMaterialM()->getDiffuse();
    obj += aux.sprintf("%.3f %.3f %.3f ",parameters.x(),parameters.y(),parameters.z());
    parameters = this->getMesh()->getMaterialM()->getSpecular();
    obj += aux.sprintf("%.3f %.3f %.3f ",parameters.x(),parameters.y(),parameters.z());
    obj += aux.sprintf("%.3f ",this->getMesh()->getMaterialM()->getShininess());
    obj += aux.sprintf("%.3f ",this->getMesh()->getMaterialM()->getReflection());
    obj += aux.sprintf("%.3f ",this->getMesh()->getMaterialM()->getRefraction());
    obj += aux.sprintf("%.3f %.3f ",this->getMesh()->getMaterialM()->getGlossyReflection(),this->getMesh()->getMaterialM()->getGlossyRefraction());
    obj += aux.sprintf("%.3f %.3f %.3f ",motion.x(),motion.y(),motion.z());
    if (this->enabled)
        obj += "t ";
    else
        obj += "f ";
    if (this->selected)
        obj += "t ";
    else
        obj += "f ";
    obj +=this->name+"\n";
    return obj;
}


Vec4 Prism::getMin()
{
    refreshVertexs();
    float pmin[3] = {vertexs[0].x(),vertexs[0].y(),vertexs[0].z()};
    for (int i=0;i<6;i++){
        if(pmin[0]>=vertexs[i].x1) pmin[0] = vertexs[i].x1;
        if(pmin[1]>=vertexs[i].x2) pmin[1] = vertexs[i].x2;
        if(pmin[2]>=vertexs[i].x3) pmin[2] = vertexs[i].x3;
    }
    return Vec4(pmin[0],pmin[1],pmin[2]);

}

Vec4 Prism::getMax()
{
    refreshVertexs();
    float pmax[3] = {vertexs[0].x(),vertexs[0].y(),vertexs[0].z()};
    for (int i=1;i<6;i++){

        if(pmax[0]<=vertexs[i].x1) pmax[0] = vertexs[i].x1;
        if(pmax[1]<=vertexs[i].x2) pmax[1] = vertexs[i].x2;
        if(pmax[2]<=vertexs[i].x3) pmax[2] = vertexs[i].x3;

    }
    return Vec4(pmax[0],pmax[1],pmax[2]);

}

Cube Prism::boundingBox()
{
    return Cube(this->getMin(),this->getMax(),this->getCenter());
}

Vec4 Prism::getCenter()
{
    Vec4 center;
    for (int i=0;i<6;i++){
        center = center + transform.transpose().vector(initvertexs[i]);

    }

    return center/6;
}

void Prism::refreshVertexs()
{
    for (int i=0;i<6;i++){
        vertexs[i] = transform.transpose().vector(initvertexs[i]);

    }
}

Vec4 Prism::getMinInit()
{
    //refreshVertexs();
    float pmin[3] = {initvertexs[0].x(),initvertexs[0].y(),initvertexs[0].z()};
 //   Vec4 min;
    for (int i=1;i<6;i++){
        //vertexs[i] = transform.transpose().vector(initvertexs[i]);
        if (pmin[0]>initvertexs[i].x1) pmin[0] = initvertexs[i].x1;
        if (pmin[1]>initvertexs[i].x2) pmin[1] = initvertexs[i].x2;
        if (pmin[2]>initvertexs[i].x3) pmin[2] = initvertexs[i].x3;

        }



    return Vec4(pmin[0],pmin[1],pmin[2]);

}

Vec4 Prism::getMaxInit()
{
    //refreshVertexs();
    float pmax[3] = {initvertexs[0].x(),initvertexs[0].y(),initvertexs[0].z()};

    //Vec4 max;
    for (int i=1;i<6;i++){

        if (pmax[0]<=initvertexs[i].x1) pmax[0] = initvertexs[i].x1;
        if (pmax[1]<=initvertexs[i].x2) pmax[1] = initvertexs[i].x2;
        if (pmax[2]<=initvertexs[i].x3) pmax[2] = initvertexs[i].x3;
    }
    return Vec4(pmax[0],pmax[1],pmax[2]);

}

void Prism::setMotion(Vec4 m)
{
    motion = m;
}

Vec4 Prism::getMotion()
{
    return motion;
}

bool Prism::getEnabledTexture()
{
    return this->enable_texture;
}

void Prism::setEnabledTexture(bool b)
{
    this->enable_texture = b;
}

void Prism::setTexture(Texture *tex)
{
    this->textures.clear();
    this->textures.push_back(tex);
}

void Prism::addTexture(Texture *tex)
{
    this->textures.push_back(tex);
}

void Prism::removeTexture(Texture *tex)
{
    std::vector<Texture*>::iterator iter;
    iter = this->textures.begin();
    for(unsigned int i=0;i<textures.size();i++){

        if(textures.at(i) == tex){
            textures.erase(iter);
            break;
        }
        iter++;
    }
}

int Prism::getLenTexture()
{
    return textures.size();
}

Texture *Prism::getTexture(int i)
{
    return textures.at(i);
}

bool Prism::getEnabledBump()
{
    return enable_bumping;
}

void Prism::setEnabledBump(bool b)
{
    this->enable_bumping = b;
}

void Prism::setBump(Bump *bump)
{
    bumps.clear();
    bumps.push_back(bump);
}

void Prism::addBump(Bump *bump)
{
    bumps.push_back(bump);
}

void Prism::removeBump(Bump *bump)
{
    std::vector<Bump*>::iterator iter;
    iter = this->bumps.begin();
    for(unsigned int i=0;i<bumps.size();i++){

        if(bumps.at(i) == bump){
            bumps.erase(iter);
            break;
        }
        iter++;
    }

}

int Prism::getLenBump()
{
    return bumps.size();
}

Bump *Prism::getBump(int i)
{
    return bumps.at(i);
}

QString Prism::getType()
{
    return "OBJPRISM";
}

int Prism::getTypeInt()
{
    return OBJPRISM;
}


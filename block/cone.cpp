#include "cone.h"



Cone::Cone()
{
    motion = Vec4();
    enable_texture = false;
    enable_bumping = false;
    motion = Vec4();
    double height = 1.0;
    double radius = 1.0;
    double alpha = 2*M_PI / SEGMENTS;
    transform.setIdentity();
    for (int i = 0;i<SEGMENTS;i++){
        vertexs[i].setVec4(cos(alpha*i)*radius,0,sin(alpha*i)*radius);
        initvertexs[i] = vertexs[i];
        normals[i] = Vec4(cos(alpha*i)*radius,0,sin(alpha*i)*radius).unitary();
        initnormals[i] = normals[i];

    }
    vertexs[SEGMENTS] = Vec4(0,height,0);
    initvertexs[SEGMENTS] = Vec4(0,height,0);
    normals[SEGMENTS] = Vec4(0,1,0);
    initnormals[SEGMENTS] = Vec4(0,1,0);
    normals[SEGMENTS+1] = Vec4(0,-1,0);
    initnormals[SEGMENTS+1] = Vec4(0,-1,0);
//    vertexs[SEGMENTS+1] = Vec4(0,1,0);
//    initvertexs[SEGMENTS+1] = Vec4(0,1,0);

    //calculo das normais
//    for (int i = 0;i<SEGMENTS;i++){
//        normals[i].setVec4(cos(alpha*i)*radius,0.0,sin(alpha*i)*radius);
//        normals[i] = normals[i].unitary();
//        initnormals[i] = normals[i];
//    }


//    if (SEGMENTS>3){
//       normals[SEGMENTS]   = Vec4::crossProduct(vertexs[1]-vertexs[2],vertexs[0]-vertexs[1]).unitary();// //face inferior
//       initnormals[SEGMENTS] = normals[SEGMENTS];
//       normals[SEGMENTS+1] = Vec4::crossProduct(vertexs[SEGMENTS+1]-vertexs[SEGMENTS],vertexs[SEGMENTS+2]-vertexs[SEGMENTS+1]).unitary();
//       initnormals[SEGMENTS+1] = normals[SEGMENTS+1];
//    }
    mesh = new Mesh();
    Face face[SEGMENTS+1];
    for(int i=0;i<SEGMENTS;i++){
        if(i<SEGMENTS-1){
            face[i].vertexs.push_back(&vertexs[SEGMENTS]);
            face[i].vertexs.push_back(&vertexs[i]);
            face[i].vertexs.push_back(&vertexs[i+1]);
            face[i].normals.push_back(&normals[SEGMENTS]);
            face[i].normals.push_back(&normals[i]);
            face[i].normals.push_back(&normals[i+1]);
        }else{
            face[i].vertexs.push_back(&vertexs[SEGMENTS]);
            face[i].vertexs.push_back(&vertexs[i]);
            face[i].vertexs.push_back(&vertexs[0]);

            face[i].normals.push_back(&normals[SEGMENTS]);
            face[i].normals.push_back(&normals[i]);
            face[i].normals.push_back(&normals[0]);
        }
        mesh->faces.push_back(face[i]);
    }
    for (int i=SEGMENTS-1;i>=0;i--){
        face[SEGMENTS].vertexs.push_back(&vertexs[i]);
    }
    face[SEGMENTS].normals.push_back(&normals[SEGMENTS+1]);
    mesh->faces.push_back(face[SEGMENTS]);
    enabled = true;
    selected = false;
}

void Cone::draw()
{
    if(isEnabled()){
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
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

void Cone::wireframe()
{
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    refreshNormals();
    mesh->draw();
}

void Cone::refreshNormals()
{
    for (int i = 0;i<SEGMENTS+1;i++){
        vertexs[i] = transform.transpose().vector(initvertexs[i]);
        normals[i] = transform.transform_normal_ray(transform,initnormals[i])*(-1);

    }
    normals[SEGMENTS+1] = transform.transform_normal_ray(transform,initnormals[SEGMENTS+1]);

}

void Cone::aplyTransform(Matrix4x4 t)
{
    transform = transform.multMatrix(transform,t);
    transform = t;
    //transform.scale(2,2,2);
    //mesh->transform = transform;

//    for (int i=0;i>8;i++){
//        transform.transpose();
//        vertexs[i] = transform.vector(vertexs[i]);
    //    }
}

void Cone::setIdentityTransform()
{
    transform.setIdentity();
}

void Cone::setMaterial(int material)
{
    mesh->setMaterial(material);
}

void Cone::changeCoords(Matrix4x4 matrix)
{
    transform = transform.multMatrix(transform,matrix);
    refreshNormals();

}

Mesh * Cone::getMesh()
{
    return mesh;
}

void Cone::setName(QString nm)
{
    name = nm;
}

QString Cone::getName()
{
    return name;
}

int Cone::getIdMaterial()
{
    return mesh->getMaterial();
}

void Cone::tryIntersection(RayIntersection *intersect, Ray ray)
{


    if (motion==Vec4())
       intersect->rayConeIntersection(mesh,this->transform,ray,this);
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
        intersect->rayConeIntersection(mesh,mat,ray,this);
    }
}

void Cone::setSelected(bool b)
{
    selected = b;
}

bool Cone::isSelected()
{
    return selected;
}

void Cone::setEnabled(bool b)
{
    enabled = b;
}

bool Cone::isEnabled()
{
    return enabled;
}

Matrix4x4 Cone::getMatrixTransformation()
{
    return transform;
}

int Cone::getNumFaces()
{
    return mesh->faces.size();
}

int Cone::getNumVertexs()
{
    return 2*SEGMENTS;
}

void Cone::setTransform(Matrix4x4 m)
{
    transform = m;
}

QString Cone::saveObject()
{
    QString obj;
    QString aux;
    obj += "e ";
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


Vec4 Cone::getMin()
{


    refreshVertexs();
    float pmin[3] = {vertexs[0].x(),vertexs[0].y(),vertexs[0].z()};

    //Vec4 min;
    for (int i=1;i<SEGMENTS+1;i++){
        if (pmin[0]>=vertexs[i].x1) pmin[0] = vertexs[i].x1;
        if (pmin[1]>=vertexs[i].x2) pmin[1] = vertexs[i].x2;
        if (pmin[2]>=vertexs[i].x3) pmin[2] = vertexs[i].x3;


    }
    return Vec4(pmin[0],pmin[1],pmin[2]);

}

Vec4 Cone::getMax()
{
    refreshVertexs();
    float pmax[3] = {vertexs[0].x(),vertexs[0].y(),vertexs[0].z()};
    //Vec4 max;
    for (int i=1;i<SEGMENTS+1;i++){

        if(pmax[0]<=vertexs[i].x1) pmax[0] = vertexs[i].x1;
        if(pmax[1]<=vertexs[i].x2) pmax[1] = vertexs[i].x2;
        if(pmax[2]<=vertexs[i].x3) pmax[2] = vertexs[i].x3;

    }
    return Vec4(pmax[0],pmax[1],pmax[2]);

}

Cube Cone::boundingBox()
{
    return Cube(this->getMin(),this->getMax(),this->getCenter());
}

Vec4 Cone::getCenter()
{
    return (getMax()+getMin())/2;
}

void Cone::refreshVertexs()
{
    for (int i = 0;i<SEGMENTS;i++){
        vertexs[i] = transform.transpose().vector(initvertexs[i]);
    }
    vertexs[SEGMENTS] = transform.transpose().vector(initvertexs[SEGMENTS]);

}

void Cone::setMotion(Vec4 m)
{
    motion = m;
}

Vec4 Cone::getMotion()
{
    return motion;
}

bool Cone::getEnabledTexture()
{
    return this->enable_texture;
}

void Cone::setEnabledTexture(bool b)
{
    this->enable_texture = b;
}

void Cone::setTexture(Texture *tex)
{
    this->textures.clear();
    this->textures.push_back(tex);
}

void Cone::addTexture(Texture *tex)
{
    this->textures.push_back(tex);
}

void Cone::removeTexture(Texture *tex)
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

int Cone::getLenTexture()
{
    return textures.size();
}

Texture *Cone::getTexture(int i)
{
    return textures.at(i);
}

bool Cone::getEnabledBump()
{
    return enable_bumping;
}

void Cone::setEnabledBump(bool b)
{
    this->enable_bumping = b;
}

void Cone::setBump(Bump *bump)
{
    bumps.clear();
    bumps.push_back(bump);
}

void Cone::addBump(Bump *bump)
{
    bumps.push_back(bump);
}

void Cone::removeBump(Bump *bump)
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

int Cone::getLenBump()
{
    return bumps.size();
}

Bump *Cone::getBump(int i)
{
    return bumps.at(i);
}

QString Cone::getType()
{
    return "OBJCONE";
}

int Cone::getTypeInt()
{
    return OBJCONE;
}



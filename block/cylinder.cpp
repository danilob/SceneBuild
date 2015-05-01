#include "cylinder.h"
double height = 1.0;
double radius = 1.0;
double alpha = 2*M_PI / SEGMENTS;

Cylinder::Cylinder()
{
    enable_texture = false;
    enable_bumping = false;
    motion = Vec4();
    transform.setIdentity();
    for (int i = 0;i<SEGMENTS;i++){
        vertexs[i].setVec4(cos(alpha*i)*radius,0,sin(alpha*i)*radius);
        initvertexs[i] = vertexs[i];

    }
    for (int i = 0;i<SEGMENTS;i++){
        vertexs[i+SEGMENTS].setVec4(cos(alpha*i)*radius,1,sin(alpha*i)*radius);
        initvertexs[i+SEGMENTS] = vertexs[i+SEGMENTS];
    }
    //calculo das normais
    for (int i = 0;i<SEGMENTS;i++){
        normals[i].setVec4(cos(alpha*i)*radius,0.0,sin(alpha*i)*radius);
        normals[i] = normals[i].unitary();
        initnormals[i] = normals[i];
    }


    if (SEGMENTS>3){
       normals[SEGMENTS]   = Vec4::crossProduct(vertexs[1]-vertexs[2],vertexs[0]-vertexs[1]).unitary();// //face inferior
       initnormals[SEGMENTS] = normals[SEGMENTS];
       normals[SEGMENTS+1] = Vec4::crossProduct(vertexs[SEGMENTS+1]-vertexs[SEGMENTS],vertexs[SEGMENTS+2]-vertexs[SEGMENTS+1]).unitary();
       initnormals[SEGMENTS+1] = normals[SEGMENTS+1];
    }
    mesh = new Mesh();
    Face face[SEGMENTS+2];
    for(int i=0;i<SEGMENTS;i++){
        if(i<SEGMENTS-1){
            face[i].vertexs.push_back(&vertexs[i]);
            face[i].vertexs.push_back(&vertexs[i+1]);
            face[i].vertexs.push_back(&vertexs[SEGMENTS+(i+1)]);
            face[i].vertexs.push_back(&vertexs[SEGMENTS+i]);
            face[i].normals.push_back(&normals[i]);
            face[i].normals.push_back(&normals[i+1]);
            face[i].normals.push_back(&normals[i+1]);
            face[i].normals.push_back(&normals[i]);
        }else{
            face[i].vertexs.push_back(&vertexs[i]);
            face[i].vertexs.push_back(&vertexs[0]);
            face[i].vertexs.push_back(&vertexs[SEGMENTS]);
            face[i].vertexs.push_back(&vertexs[SEGMENTS+i]);
            face[i].normals.push_back(&normals[i]);
            face[i].normals.push_back(&normals[0]);
            face[i].normals.push_back(&normals[0]);
            face[i].normals.push_back(&normals[i]);
        }
        mesh->faces.push_back(face[i]);
    }
    for (int i=SEGMENTS-1;i>0;i--){
        face[SEGMENTS].vertexs.push_back(&vertexs[i]);
        //if (i==0)
            face[SEGMENTS].normals.push_back(&normals[SEGMENTS]);
    }
    mesh->faces.push_back(face[SEGMENTS]);
    for (int i=0;i<SEGMENTS;i++){
        face[SEGMENTS+1].vertexs.push_back(&vertexs[SEGMENTS+i]);
        //if (i==0)
            face[SEGMENTS+1].normals.push_back(&normals[SEGMENTS+1]);
    }
    mesh->faces.push_back(face[SEGMENTS+1]);
    enabled = true;
    selected = false;
}

void Cylinder::draw()
{
    if(isEnabled()){
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    refreshNormals();
    mesh->draw();
    }
    if (selected){
         Draw::drawSelection(getMax(),getMin());
    }
}

void Cylinder::wireframe()
{
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    refreshNormals();
    mesh->draw();
}

void Cylinder::refreshNormals()
{
    for (int i = 0;i<SEGMENTS;i++){
        vertexs[i] = transform.transpose().vector(initvertexs[i]);
    }
    for (int i = 0;i<SEGMENTS;i++){
        vertexs[i+SEGMENTS] = transform.transpose().vector(initvertexs[i+SEGMENTS]);

    }
    //calculo das normais
    for (int i = 0;i<SEGMENTS;i++){
        normals[i] = transform.transform_normal_ray(transform,initnormals[i])*(-1);
    }


    if (SEGMENTS>3){
       normals[SEGMENTS] = Vec4::crossProduct(vertexs[1]-vertexs[2],vertexs[0]-vertexs[1]).unitary();
       normals[SEGMENTS+1] = Vec4::crossProduct(vertexs[SEGMENTS+1]-vertexs[SEGMENTS],vertexs[SEGMENTS+2]-vertexs[SEGMENTS+1]).unitary();
    }

}

void Cylinder::aplyTransform(Matrix4x4 t)
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

void Cylinder::setIdentityTransform()
{
    transform.setIdentity();
}

void Cylinder::setMaterial(int material)
{
    mesh->setMaterial(material);
}

void Cylinder::changeCoords(Matrix4x4 matrix)
{
    transform = transform.multMatrix(transform,matrix);
    refreshNormals();

}

Mesh * Cylinder::getMesh()
{
    return mesh;
}

void Cylinder::setName(QString nm)
{
    name = nm;
}

QString Cylinder::getName()
{
    return name;
}

int Cylinder::getIdMaterial()
{
    return mesh->getMaterial();
}

void Cylinder::tryIntersection(RayIntersection *intersect, Ray ray)
{
    if(motion==Vec4())
    intersect->rayCylinderIntersection(mesh,this->transform,ray,this);
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
        intersect->rayCylinderIntersection(mesh,mat,ray,this);
    }
}

void Cylinder::setSelected(bool b)
{
    selected = b;
}

bool Cylinder::isSelected()
{
    return selected;
}

void Cylinder::setEnabled(bool b)
{
    enabled = b;
}

bool Cylinder::isEnabled()
{
    return enabled;
}

Matrix4x4 Cylinder::getMatrixTransformation()
{
    return transform;
}

int Cylinder::getNumFaces()
{
    return mesh->faces.size();
}

int Cylinder::getNumVertexs()
{
    return 2*SEGMENTS;
}

void Cylinder::setTransform(Matrix4x4 m)
{
    transform = m;
}

QString Cylinder::saveObject()
{
    QString obj;
    QString aux;
    obj += "y ";
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


Vec4 Cylinder::getMin()
{


    refreshVertexs();
    float pmin[3] = {vertexs[0].x(),vertexs[0].y(),vertexs[0].z()};

    //Vec4 min;
    for (int i=1;i<2*SEGMENTS;i++){
        if (pmin[0]>=vertexs[i].x1) pmin[0] = vertexs[i].x1;
        if (pmin[1]>=vertexs[i].x2) pmin[1] = vertexs[i].x2;
        if (pmin[2]>=vertexs[i].x3) pmin[2] = vertexs[i].x3;


    }
    return Vec4(pmin[0],pmin[1],pmin[2]);

}

Vec4 Cylinder::getMax()
{
    refreshVertexs();
    float pmax[3] = {vertexs[0].x(),vertexs[0].y(),vertexs[0].z()};
    //Vec4 max;
    for (int i=1;i<2*SEGMENTS;i++){

        if(pmax[0]<=vertexs[i].x1) pmax[0] = vertexs[i].x1;
        if(pmax[1]<=vertexs[i].x2) pmax[1] = vertexs[i].x2;
        if(pmax[2]<=vertexs[i].x3) pmax[2] = vertexs[i].x3;

    }
    return Vec4(pmax[0],pmax[1],pmax[2]);

}

Cube Cylinder::boundingBox()
{
    return Cube(this->getMin(),this->getMax(),this->getCenter());
}

Vec4 Cylinder::getCenter()
{
    Vec4 center;
    for (int i = 0;i<SEGMENTS;i++){
        center = center+ transform.transpose().vector(initvertexs[i]);


    }
    for (int i = 0;i<SEGMENTS;i++){
        center = center + transform.transpose().vector(initvertexs[i+SEGMENTS]);

    }
    return center/(2*SEGMENTS);
}

void Cylinder::refreshVertexs()
{
    for (int i = 0;i<SEGMENTS;i++){
        vertexs[i] = transform.transpose().vector(initvertexs[i]);


    }
    for (int i = 0;i<SEGMENTS;i++){
        vertexs[i+SEGMENTS] = transform.transpose().vector(initvertexs[i+SEGMENTS]);

    }
}

void Cylinder::setMotion(Vec4 m)
{
    motion = m;
}

Vec4 Cylinder::getMotion()
{
    return motion;
}

bool Cylinder::getEnabledTexture()
{
    return this->enable_texture;
}

void Cylinder::setEnabledTexture(bool b)
{
    this->enable_texture = b;
}

void Cylinder::setTexture(Texture *tex)
{
    this->textures.clear();
    this->textures.push_back(tex);
}

void Cylinder::addTexture(Texture *tex)
{
    this->textures.push_back(tex);
}

void Cylinder::removeTexture(Texture *tex)
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

int Cylinder::getLenTexture()
{
    return textures.size();
}

Texture *Cylinder::getTexture(int i)
{
    return textures.at(i);
}


bool Cylinder::getEnabledBump()
{
    return enable_bumping;
}

void Cylinder::setEnabledBump(bool b)
{
    this->enable_bumping = b;
}

void Cylinder::setBump(Bump *bump)
{
    bumps.clear();
    bumps.push_back(bump);
}

void Cylinder::addBump(Bump *bump)
{
    bumps.push_back(bump);
}

void Cylinder::removeBump(Bump *bump)
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

int Cylinder::getLenBump()
{
    return bumps.size();
}

Bump *Cylinder::getBump(int i)
{
    return bumps.at(i);
}

QString Cylinder::getType()
{
    return "OBJCYLINDER";
}

int Cylinder::getTypeInt()
{
    return OBJCYLINDER;
}

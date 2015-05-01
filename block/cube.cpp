#include "cube.h"

#define ERRORN 0.0001

Cube::Cube()
{
    motion = Vec4();
    enable_texture = false;
    enable_bumping = false;
    //default: side = 1.0
    //configurar o cubo no quadrante positivo do eixo global no canto
    double side = 1.0;
    //lista das normais da face
    vertexs[0].setVec4((-0.5)*side  ,(-0.5)*side  ,(-0.5)*side );
    vertexs[1].setVec4((-0.5)*side  ,(-0.5)*side  ,(0.5)*side);
    vertexs[2].setVec4((0.5)*side ,(-0.5)*side  ,(0.5)*side);
    vertexs[3].setVec4((0.5)*side ,(-0.5)*side  ,(-0.5)*side );
    vertexs[4].setVec4((-0.5)*side  ,(0.5)*side  ,(-0.5)*side );
    vertexs[5].setVec4((-0.5)*side  ,(0.5)*side ,(0.5)*side);
    vertexs[6].setVec4((0.5)*side ,(0.5)*side ,(0.5)*side);
    vertexs[7].setVec4((0.5)*side ,(0.5)*side ,(-0.5)*side );
    initvertexs[0].setVec4((-0.5)*side  ,(-0.5)*side  ,(-0.5)*side );
    initvertexs[1].setVec4((-0.5)*side  ,(-0.5)*side  ,(0.5)*side);
    initvertexs[2].setVec4((0.5)*side ,(-0.5)*side  ,(0.5)*side);
    initvertexs[3].setVec4((0.5)*side ,(-0.5)*side  ,(-0.5)*side );
    initvertexs[4].setVec4((-0.5)*side  ,(0.5)*side  ,(-0.5)*side );
    initvertexs[5].setVec4((-0.5)*side  ,(0.5)*side ,(0.5)*side);
    initvertexs[6].setVec4((0.5)*side ,(0.5)*side ,(0.5)*side);
    initvertexs[7].setVec4((0.5)*side ,(0.5)*side ,(-0.5)*side );
    transform.setIdentity();
    refreshNormals();
    mesh = new Mesh();

    Face face[6];
    face[0].vertexs.push_back(&vertexs[0]);
    face[0].vertexs.push_back(&vertexs[3]);
    face[0].vertexs.push_back(&vertexs[2]);
    face[0].vertexs.push_back(&vertexs[1]);
    face[0].normals.push_back(&normals[0]);
//    face[0].normals.push_back(&normals[0]);
//    face[0].normals.push_back(&normals[0]);
//    face[0].normals.push_back(&normals[0]);
    mesh->faces.push_back(face[0]);
    face[1].vertexs.push_back(&vertexs[4]);
    face[1].vertexs.push_back(&vertexs[5]);
    face[1].vertexs.push_back(&vertexs[6]);
    face[1].vertexs.push_back(&vertexs[7]);
    face[1].normals.push_back(&normals[1]);
//    face[1].normals.push_back(&normals[1]);
//    face[1].normals.push_back(&normals[1]);
//    face[1].normals.push_back(&normals[1]);
    mesh->faces.push_back(face[1]);
    face[2].vertexs.push_back(&vertexs[2]);
    face[2].vertexs.push_back(&vertexs[6]);
    face[2].vertexs.push_back(&vertexs[5]);
    face[2].vertexs.push_back(&vertexs[1]);
    face[2].normals.push_back(&normals[2]);
//    face[2].normals.push_back(&normals[2]);
//    face[2].normals.push_back(&normals[2]);
//    face[2].normals.push_back(&normals[2]);
    mesh->faces.push_back(face[2]);
    face[3].vertexs.push_back(&vertexs[3]);
    face[3].vertexs.push_back(&vertexs[7]);
    face[3].vertexs.push_back(&vertexs[6]);
    face[3].vertexs.push_back(&vertexs[2]);
    face[3].normals.push_back(&normals[3]);
//    face[3].normals.push_back(&normals[3]);
//    face[3].normals.push_back(&normals[3]);
//    face[3].normals.push_back(&normals[3]);
    mesh->faces.push_back(face[3]);
    face[4].vertexs.push_back(&vertexs[0]);
    face[4].vertexs.push_back(&vertexs[4]);
    face[4].vertexs.push_back(&vertexs[7]);
    face[4].vertexs.push_back(&vertexs[3]);
    face[4].normals.push_back(&normals[5]);
//    face[4].normals.push_back(&normals[5]);
//    face[4].normals.push_back(&normals[5]);
//    face[4].normals.push_back(&normals[5]);
    mesh->faces.push_back(face[4]);
    face[5].vertexs.push_back(&vertexs[4]);
    face[5].vertexs.push_back(&vertexs[0]);
    face[5].vertexs.push_back(&vertexs[1]);
    face[5].vertexs.push_back(&vertexs[5]);
    face[5].normals.push_back(&normals[4]);
//    face[5].normals.push_back(&normals[4]);
//    face[5].normals.push_back(&normals[4]);
//    face[5].normals.push_back(&normals[4]);
    mesh->faces.push_back(face[5]);
    enabled = true;
    selected = false;

}

Cube::Cube(Vec4 min, Vec4 max,Vec4 center)
{
    motion = Vec4();
    //Cube c = Cube();
    double side = 1.0;
    //lista das normais da face
    vertexs[0].setVec4((-0.5)*side  ,(-0.5)*side  ,(-0.5)*side );
    vertexs[1].setVec4((-0.5)*side  ,(-0.5)*side  ,(0.5)*side);
    vertexs[2].setVec4((0.5)*side ,(-0.5)*side  ,(0.5)*side);
    vertexs[3].setVec4((0.5)*side ,(-0.5)*side  ,(-0.5)*side );
    vertexs[4].setVec4((-0.5)*side  ,(0.5)*side  ,(-0.5)*side );
    vertexs[5].setVec4((-0.5)*side  ,(0.5)*side ,(0.5)*side);
    vertexs[6].setVec4((0.5)*side ,(0.5)*side ,(0.5)*side);
    vertexs[7].setVec4((0.5)*side ,(0.5)*side ,(-0.5)*side );
    initvertexs[0].setVec4((-0.5)*side  ,(-0.5)*side  ,(-0.5)*side );
    initvertexs[1].setVec4((-0.5)*side  ,(-0.5)*side  ,(0.5)*side);
    initvertexs[2].setVec4((0.5)*side ,(-0.5)*side  ,(0.5)*side);
    initvertexs[3].setVec4((0.5)*side ,(-0.5)*side  ,(-0.5)*side );
    initvertexs[4].setVec4((-0.5)*side  ,(0.5)*side  ,(-0.5)*side );
    initvertexs[5].setVec4((-0.5)*side  ,(0.5)*side ,(0.5)*side);
    initvertexs[6].setVec4((0.5)*side ,(0.5)*side ,(0.5)*side);
    initvertexs[7].setVec4((0.5)*side ,(0.5)*side ,(-0.5)*side );
    transform.setIdentity();
    refreshNormals();
    mesh = new Mesh();

    Face face[6];
    face[0].vertexs.push_back(&vertexs[0]);
    face[0].vertexs.push_back(&vertexs[3]);
    face[0].vertexs.push_back(&vertexs[2]);
    face[0].vertexs.push_back(&vertexs[1]);
    face[0].normals.push_back(&normals[0]);
//    face[0].normals.push_back(&normals[0]);
//    face[0].normals.push_back(&normals[0]);
//    face[0].normals.push_back(&normals[0]);
    mesh->faces.push_back(face[0]);
    face[1].vertexs.push_back(&vertexs[4]);
    face[1].vertexs.push_back(&vertexs[5]);
    face[1].vertexs.push_back(&vertexs[6]);
    face[1].vertexs.push_back(&vertexs[7]);
    face[1].normals.push_back(&normals[1]);
//    face[1].normals.push_back(&normals[1]);
//    face[1].normals.push_back(&normals[1]);
//    face[1].normals.push_back(&normals[1]);
    mesh->faces.push_back(face[1]);
    face[2].vertexs.push_back(&vertexs[2]);
    face[2].vertexs.push_back(&vertexs[6]);
    face[2].vertexs.push_back(&vertexs[5]);
    face[2].vertexs.push_back(&vertexs[1]);
    face[2].normals.push_back(&normals[2]);
//    face[2].normals.push_back(&normals[2]);
//    face[2].normals.push_back(&normals[2]);
//    face[2].normals.push_back(&normals[2]);
    mesh->faces.push_back(face[2]);
    face[3].vertexs.push_back(&vertexs[3]);
    face[3].vertexs.push_back(&vertexs[7]);
    face[3].vertexs.push_back(&vertexs[6]);
    face[3].vertexs.push_back(&vertexs[2]);
    face[3].normals.push_back(&normals[3]);
//    face[3].normals.push_back(&normals[3]);
//    face[3].normals.push_back(&normals[3]);
//    face[3].normals.push_back(&normals[3]);
    mesh->faces.push_back(face[3]);
    face[4].vertexs.push_back(&vertexs[0]);
    face[4].vertexs.push_back(&vertexs[4]);
    face[4].vertexs.push_back(&vertexs[7]);
    face[4].vertexs.push_back(&vertexs[3]);
    face[4].normals.push_back(&normals[5]);
//    face[4].normals.push_back(&normals[5]);
//    face[4].normals.push_back(&normals[5]);
//    face[4].normals.push_back(&normals[5]);
    mesh->faces.push_back(face[4]);
    face[5].vertexs.push_back(&vertexs[4]);
    face[5].vertexs.push_back(&vertexs[0]);
    face[5].vertexs.push_back(&vertexs[1]);
    face[5].vertexs.push_back(&vertexs[5]);
    face[5].normals.push_back(&normals[4]);
//    face[5].normals.push_back(&normals[4]);
//    face[5].normals.push_back(&normals[4]);
//    face[5].normals.push_back(&normals[4]);
    mesh->faces.push_back(face[5]);
    Matrix4x4 t;
    t.setIdentity();
    //Vec4 med = (max-min)/2.0;
    //float s = (min-max).module()*sqrt(3.0)/3.0; //escala

    //center = center/2.0;
    //min = min - center;
    //max = max - center;
    //t.set
    transform.setIdentity();
    center = (max+min)/2.0;
    //float diag = (max - center).module();
    float h    = (max - Vec4(max.x(),center.y(),max.z())).module(); //eixo y
    float c    = (Vec4(max.x(),center.y(),center.z())-Vec4(max.x(),center.y(),max.z())).module(); //eixo z
    float l    = (center - Vec4(max.x(),center.y(),center.z())).module();

    t.scale(2*l,2*h,2*c);
    t.translate(center);
    transform = t;
    //this->refreshVertexs();
    //this->draw();
}

Cube Cube::setCube(Vec4 min, Vec4 max)
{
    Cube cube = Cube();
    cube.transform.setIdentity();
    Matrix4x4 t;
    t.setIdentity();
    Vec4 center = (max+min)/2.0;

    //float s = (min-max).module()*sqrt(3.0)/3.0; //escala
    //this->transform.setIdentity();
    float diag = (max - center).module();
    float h    = (max - Vec4(max.x(),center.y(),max.z())).module(); //eixo y
    float c    = (Vec4(max.x(),center.y(),center.z())-Vec4(max.x(),center.y(),max.z())).module(); //eixo z
    float l    = (center - Vec4(max.x(),center.y(),center.z())).module();

    t.scale(2*l,2*h,2*c);
    t.translate(center);
    cube.setTransform(t);
    return cube;

}

Cube Cube::combineCube(Cube a, Cube b)
{
   Vec4 min,max;
   Vec4 aux1,aux2;
   aux1 = a.getMin();
   aux2 = b.getMin();
   if(aux1.x()<aux2.x()) min.x1 = aux1.x();
   else min.x1 = aux2.x();
   if(aux1.y()<aux2.y()) min.x2 = aux1.y();
   else min.x2 = aux2.y();
   if(aux1.z()<aux2.z()) min.x3 = aux1.z();
   else min.x3 = aux2.z();

   aux1 = a.getMax();
   aux2 = b.getMax();
   if(aux1.x()>aux2.x()) max.x1 = aux1.x();
   else max.x1 = aux2.x();
   if(aux1.y()>aux2.y()) max.x2 = aux1.y();
   else max.x2 = aux2.y();
   if(aux1.z()>aux2.z()) max.x3 = aux1.z();
   else max.x3 = aux2.z();

   Cube c = Cube(min,max);
//   c = c.setCube(min,max);
   return c;

}

Vec4 Cube::getMin()
{
    refreshVertexs();
    float pmin[3] = {vertexs[0].x(),vertexs[0].y(),vertexs[0].z()};
 //   Vec4 min;
    for (int i=1;i<8;i++){
        vertexs[i] = transform.transpose().vector(initvertexs[i]);
        if (pmin[0]>vertexs[i].x1) pmin[0] = vertexs[i].x1;
        if (pmin[1]>vertexs[i].x2) pmin[1] = vertexs[i].x2;
        if (pmin[2]>vertexs[i].x3) pmin[2] = vertexs[i].x3;

        }



    return Vec4(pmin[0],pmin[1],pmin[2]);

}

Vec4 Cube::getMax()
{
    refreshVertexs();
    float pmax[3] = {vertexs[0].x(),vertexs[0].y(),vertexs[0].z()};

    //Vec4 max;
    for (int i=1;i<8;i++){

        if (pmax[0]<=vertexs[i].x1) pmax[0] = vertexs[i].x1;
        if (pmax[1]<=vertexs[i].x2) pmax[1] = vertexs[i].x2;
        if (pmax[2]<=vertexs[i].x3) pmax[2] = vertexs[i].x3;
    }
    return Vec4(pmax[0],pmax[1],pmax[2]);

}

//calculo das normais dos vertices
void Cube::refreshNormals()
{
    //normais a face

    normals[0] = Vec4::crossProduct(vertexs[3]-vertexs[0],vertexs[2]-vertexs[3]).unitary(); //vertices:0,1,2,3
    normals[1] = Vec4::crossProduct(vertexs[4]-vertexs[7],vertexs[5]-vertexs[4]).unitary(); //vertices:4,5,6,7
    normals[2] = Vec4::crossProduct(vertexs[6]-vertexs[2],vertexs[5]-vertexs[6]).unitary(); //vertices:1,2,5,6
    normals[3] = Vec4::crossProduct(vertexs[7]-vertexs[3],vertexs[6]-vertexs[7]).unitary(); //vertices:2,3,6,7
    normals[4] = Vec4::crossProduct(vertexs[4]-vertexs[5],vertexs[0]-vertexs[4]).unitary(); //vertices:0,1,4,5
    normals[5] = Vec4::crossProduct(vertexs[4]-vertexs[0],vertexs[7]-vertexs[4]).unitary(); //vertices:0,3,4,7

//    //normal do vertice é a média das normais as faces que o vertice pertence
//    normals[0] = ((normal[0]+normal[4]+normal[5])).unitary();
//    normals[1] = ((normal[0]+normal[2]+normal[4])).unitary();
//    normals[2] = ((normal[0]+normal[2]+normal[3])).unitary();
//    normals[3] = ((normal[0]+normal[3]+normal[5])).unitary();
//    normals[4] = ((normal[1]+normal[4]+normal[5])).unitary();
//    normals[5] = ((normal[1]+normal[2]+normal[4])).unitary();
//    normals[6] = ((normal[1]+normal[2]+normal[3])).unitary();
//    normals[7] = ((normal[1]+normal[3]+normal[5])).unitary();
}

void Cube::draw()
{

    if(isEnabled()){
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    //refreshNormals();
    for (int i=0;i<8;i++){
        //transform.transpose();
        vertexs[i] = transform.transpose().vector(initvertexs[i]);
    }

    //Draw::drawPoint(getMax(),4);
    //Draw::drawPoint(getMin(),4);
    refreshNormals();
    mesh->draw();
    //boundingBox().wireframe();
    }
    if (selected){
        //glDisable(GL_Li);
        Draw::drawSelection(getMax(),getMin());
//        glColor3f(1,1,1);
//        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
//        mesh->draw();
        //this->//boundingBox().wireframe();

    }

}

void Cube::wireframe()
{
    glDisable(GL_LIGHTING);
    glLineWidth(0.5);
    glColor3f(1,1,1);
    for (int i=0;i<8;i++){
        //transform.transpose();
        vertexs[i] = transform.transpose().vector(initvertexs[i]);


    }
    glLineWidth(0.5);
    refreshNormals();
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    mesh->draw();

    glEnable(GL_LIGHTING);

}



void Cube::aplyTransform(Matrix4x4 t)
{
    transform = transform.multMatrix(transform,t);
    transform = t;
    //mesh->transform = transform;
    //refreshNormals();
}

void Cube::setIdentityTransform()
{
        transform.setIdentity();
}



void Cube::setMaterial(int material)
{
    mesh->setMaterial(material);
}

void Cube::changeCoords(Matrix4x4 matrix)
{
    //transform.showMatrix4x4();
    transform = transform.multMatrix(transform,matrix);
    //transform.showMatrix4x4();
    for (int i=0;i<8;i++){
        //transform.transpose();
        vertexs[i] = transform.transpose().vector(initvertexs[i]);
        //vertexs[i].showVec4();
    }

    refreshNormals();
}

Mesh * Cube::getMesh()
{
    return mesh;
}

void Cube::setName(QString nm)
{
    name = nm;
}

QString Cube::getName()
{
    return name;
}

int Cube::getIdMaterial()
{
   return mesh->getMaterial();
}



void Cube::tryIntersection(RayIntersection *intersect,Ray ray)
{
    if(motion==Vec4())
    intersect->rayBoxIntersection(mesh,ray,transform,this->getMaxInit(),this->getMinInit(),this);
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
        intersect->rayBoxIntersection(mesh,ray,mat,this->getMaxInit(),this->getMinInit(),this);
    }

}

void Cube::setSelected(bool b)
{
    selected = b;
}

bool Cube::isSelected()
{
    return selected;
}

void Cube::setEnabled(bool b)
{
    enabled = b;
}

bool Cube::isEnabled()
{
    return enabled;
}

Matrix4x4 Cube::getMatrixTransformation()
{
    return transform;
}



int Cube::getNumFaces()
{
    return mesh->faces.size();
}

int Cube::getNumVertexs()
{
    return 8;
}

void Cube::setTransform(Matrix4x4 m)
{
    transform = m;
}

QString Cube::saveObject()
{
    QString obj;
    QString aux;
    obj += "c ";
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

Cube Cube::boundingBox()
{

    return Cube(getMin(),getMax(),getCenter());
}

Vec4 Cube::getCenter()
{
    Vec4 center;
    for (int i=0;i<8;i++){
        //transform.transpose();
        center = center + transform.transpose().vector(initvertexs[i]);
        //vertexs[i].showVec4();
    }
    return center/8.0;
}

void Cube::refreshVertexs()
{
    for (int i=0;i<8;i++){
        //transform.transpose();
        vertexs[i] = transform.transpose().vector(initvertexs[i]);
        //vertexs[i].showVec4();
    }
}

Vec4 Cube::getMinInit()
{
    //refreshVertexs();
    float pmin[3] = {initvertexs[0].x(),initvertexs[0].y(),initvertexs[0].z()};
 //   Vec4 min;
    for (int i=1;i<8;i++){
        //vertexs[i] = transform.transpose().vector(initvertexs[i]);
        if (pmin[0]>initvertexs[i].x1) pmin[0] = initvertexs[i].x1;
        if (pmin[1]>initvertexs[i].x2) pmin[1] = initvertexs[i].x2;
        if (pmin[2]>initvertexs[i].x3) pmin[2] = initvertexs[i].x3;

        }



    return Vec4(pmin[0],pmin[1],pmin[2]);

}

Vec4 Cube::getMaxInit()
{
    //refreshVertexs();
    float pmax[3] = {initvertexs[0].x(),initvertexs[0].y(),initvertexs[0].z()};

    //Vec4 max;
    for (int i=1;i<8;i++){

        if (pmax[0]<=initvertexs[i].x1) pmax[0] = initvertexs[i].x1;
        if (pmax[1]<=initvertexs[i].x2) pmax[1] = initvertexs[i].x2;
        if (pmax[2]<=initvertexs[i].x3) pmax[2] = initvertexs[i].x3;
    }
    return Vec4(pmax[0],pmax[1],pmax[2]);

}

void Cube::setMotion(Vec4 m)
{
    motion = m;
}

Vec4 Cube::getMotion()
{
    return motion;
}

bool Cube::getEnabledTexture()
{
    return this->enable_texture;
}

void Cube::setEnabledTexture(bool b)
{
    this->enable_texture = b;
}

void Cube::setTexture(Texture *tex)
{
    this->textures.clear();
    this->textures.push_back(tex);
}

void Cube::addTexture(Texture *tex)
{
    this->textures.push_back(tex);
}

void Cube::removeTexture(Texture *tex)
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

int Cube::getLenTexture()
{
    return textures.size();
}

Texture *Cube::getTexture(int i)
{
    return textures.at(i);
}


bool Cube::getEnabledBump()
{
    return enable_bumping;
}

void Cube::setEnabledBump(bool b)
{
    this->enable_bumping = b;
}

void Cube::setBump(Bump *bump)
{
    bumps.clear();
    bumps.push_back(bump);
}

void Cube::addBump(Bump *bump)
{
    bumps.push_back(bump);
}

void Cube::removeBump(Bump *bump)
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

int Cube::getLenBump()
{
    return bumps.size();
}

Bump *Cube::getBump(int i)
{
    return bumps.at(i);
}

QString Cube::getType()
{
    return "OBJCUBE";
}

int Cube::getTypeInt()
{
    return OBJCUBE;
}

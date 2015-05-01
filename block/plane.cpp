#include "plane.h"

#define ERRORN 0.0001

Plane::Plane()
{
    motion = Vec4();
    enable_texture = false;
    enable_bumping = false;
    //default: side = 1.0
    //configurar o cubo no quadrante positivo do eixo global no canto
    double side = 1.0;
    //lista das normais da face
    vertexs[0].setVec4(-side ,0.0 , side);
    vertexs[1].setVec4( side ,0.0 , side);
    vertexs[2].setVec4( side ,0.0 ,-side);
    vertexs[3].setVec4(-side ,0.0 ,-side);

    initvertexs[0].setVec4(-side ,0.0 , side);
    initvertexs[1].setVec4( side ,0.0 , side);
    initvertexs[2].setVec4( side ,0.0 ,-side);
    initvertexs[3].setVec4(-side ,0.0 ,-side);

    transform.setIdentity();
    refreshNormals();
    mesh = new Mesh();

    Face face;
    face.vertexs.push_back(&vertexs[0]);
    face.vertexs.push_back(&vertexs[1]);
    face.vertexs.push_back(&vertexs[2]);
    face.vertexs.push_back(&vertexs[3]);
    face.normals.push_back(&normals[0]);
//    face[0].normals.push_back(&normals[0]);
//    face[0].normals.push_back(&normals[0]);
//    face[0].normals.push_back(&normals[0]);
    mesh->faces.push_back(face);

    enabled = true;
    selected = false;

}

//calculo das normais dos vertices
void Plane::refreshNormals()
{
    //normais a face

    normals[0] = Vec4::crossProduct(vertexs[1]-vertexs[0],vertexs[3]-vertexs[0]).unitary(); //vertices:0,1,2,3


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

void Plane::draw()
{

    if(isEnabled()){
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    //refreshNormals();
    for (int i=0;i<4;i++){
        //transform.transpose();
        vertexs[i] = transform.transpose().vector(initvertexs[i]);
    }
    refreshNormals();
    mesh->draw();
    }
    if (selected){

        glColor3f(1,1,1);
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
        mesh->draw();

    }

}

void Plane::wireframe()
{
    for (int i=0;i<4;i++){
        //transform.transpose();
        vertexs[i] = transform.transpose().vector(initvertexs[i]);
    }
    refreshNormals();
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    mesh->draw();

}



void Plane::aplyTransform(Matrix4x4 t)
{
    transform = transform.multMatrix(transform,t);
    transform = t;
    //mesh->transform = transform;
    //refreshNormals();
}

void Plane::setIdentityTransform()
{
        transform.setIdentity();
}



void Plane::setMaterial(int material)
{
    mesh->setMaterial(material);
}

void Plane::changeCoords(Matrix4x4 matrix)
{
    //transform.showMatrix4x4();
    transform = transform.multMatrix(transform,matrix);
    //transform.showMatrix4x4();
    for (int i=0;i<4;i++){
        //transform.transpose();
        vertexs[i] = transform.transpose().vector(initvertexs[i]);
        //vertexs[i].showVec4();
    }

    refreshNormals();
}

Mesh * Plane::getMesh()
{
    return mesh;
}

void Plane::setName(QString nm)
{
    name = nm;
}

QString Plane::getName()
{
    return name;
}

int Plane::getIdMaterial()
{
   return mesh->getMaterial();
}



void Plane::tryIntersection(RayIntersection *intersect,Ray ray)
{

    intersect->rayPlanIntersection(mesh,ray,this);

}

void Plane::setSelected(bool b)
{
    selected = b;
}

bool Plane::isSelected()
{
    return selected;
}

void Plane::setEnabled(bool b)
{
    enabled = b;
}

bool Plane::isEnabled()
{
    return enabled;
}

Matrix4x4 Plane::getMatrixTransformation()
{
    return transform;
}

int Plane::getNumFaces()
{
    return 1;
}

int Plane::getNumVertexs()
{
    return 4;
}

void Plane::setTransform(Matrix4x4 m)
{
    transform = m;
}

QString Plane::saveObject()
{
    QString obj;
    QString aux;
    obj += "t ";
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

Plane::~Plane()
{
    delete []mesh;
}



Vec4 Plane::getMin()
{

    float pmin[3] = {INFINITY};
    Vec4 min;
    for (int i=0;i<4;i++){
        if(pmin[0]>=vertexs[i].x1 && pmin[1]>=vertexs[i].x2 && pmin[2]>=vertexs[i].x3){
            pmin[0] = vertexs[i].x1;
            pmin[1] = vertexs[i].x2;
            pmin[2] = vertexs[i].x3;
            min = vertexs[i];
        }

    }
    return min;

}

Vec4 Plane::getMax()
{
    float pmax[3] = {-INFINITY};

    Vec4 max;
    for (int i=0;i<4;i++){

        if(pmax[0]<=vertexs[i].x1 && pmax[1]<=vertexs[i].x2 && pmax[2]<=vertexs[i].x3){
            pmax[0] = vertexs[i].x1;
            pmax[1] = vertexs[i].x2;
            pmax[2] = vertexs[i].x3;
            max = vertexs[i];
        }
    }
    return max;

}

Cube Plane::boundingBox()
{
    return Cube(this->getMin(),this->getMax());
}

Vec4 Plane::getCenter()
{
    return (this->getMax()+this->getMin())/2.0;
}

void Plane::setMotion(Vec4 m)
{
    motion = m;
}

Vec4 Plane::getMotion()
{
    return motion;
}

bool Plane::getEnabledTexture()
{
    return this->enable_texture;
}

void Plane::setEnabledTexture(bool b)
{
    this->enable_texture = b;
}

void Plane::setTexture(Texture *tex)
{
    this->textures.clear();
    this->textures.push_back(tex);
}

void Plane::addTexture(Texture *tex)
{
    this->textures.push_back(tex);
}

void Plane::removeTexture(Texture *tex)
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

int Plane::getLenTexture()
{
    return textures.size();
}

Texture *Plane::getTexture(int i)
{
    return textures.at(i);
}


bool Plane::getEnabledBump()
{
    return enable_bumping;
}

void Plane::setEnabledBump(bool b)
{
    this->enable_bumping = b;
}

void Plane::setBump(Bump *bump)
{
    bumps.clear();
    bumps.push_back(bump);
}

void Plane::addBump(Bump *bump)
{
    bumps.push_back(bump);
}

void Plane::removeBump(Bump *bump)
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

int Plane::getLenBump()
{
    return bumps.size();
}

Bump *Plane::getBump(int i)
{
    return bumps.at(i);
}

QString Plane::getType()
{
    return "OBJPLANE";
}

int Plane::getTypeInt()
{
    return OBJPLANE;
}

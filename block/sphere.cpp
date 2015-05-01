#include "sphere.h"
#define ERRORN 0.0001

Sphere::Sphere()
{
    motion = Vec4();
    enable_texture = false;
    enable_bumping = false;
    double radius = 1.0;
    double alpha = 2*M_PI / STACKS;
    double beta = 2*M_PI / SLICES;

    //vertexs[0] = Vec4(0.0,radius,0.0);
    for (int i = 0;i<STACKS/2;i++){
        double  ratio_radius = sin(alpha*(i+1));
        for(int j=0;j<SLICES;j++){
            vertexs[i*SLICES+(j+1)].setVec4(cos(beta*j)*ratio_radius,cos(alpha*(i+1)),sin(beta*j)*ratio_radius);
            initvertexs[i*SLICES+(j+1)] = vertexs[i*SLICES+(j+1)];
            normals[i*SLICES+(j+1)] = Vec4(vertexs[i*SLICES+(j+1)]).unitary();
            initnormals[i*SLICES+(j+1)] = normals[i*SLICES+(j+1)];
        }
    }
    vertexs[0] = Vec4(0.0,radius,0.0);
    initvertexs[0] = Vec4(0.0,radius,0.0);
    normals[0] = Vec4(0,1,0);
    initnormals[0] = Vec4(0,1,0);
    vertexs[SLICES*(STACKS/2)+1] = Vec4(0.0,-radius,0.0);
    initvertexs[SLICES*(STACKS/2)+1] = Vec4(0.0,-radius,0.0);
    normals[SLICES*(STACKS/2)+1] = Vec4(0,-1,0);
    initnormals[SLICES*(STACKS/2)+1] = Vec4(0,-1,0);
    transform.setIdentity();
    mesh = new Mesh();
    //vertexs[SLICES*STACKS]
    Face face[((STACKS/2)*SLICES)+(2*SLICES)];
    //desenho da lateral do hemisferio
    for(int i=0;i<STACKS/2;i++){
        for(int j=0;j<SLICES;j++){
            if(i==0){
                if ((j+1)!=SLICES){
                    face[i*SLICES+j].vertexs.push_back(&vertexs[0]);
                    face[i*SLICES+j].vertexs.push_back(&vertexs[(j+1)]);
                    face[i*SLICES+j].vertexs.push_back(&vertexs[(j+2)]);
                    face[i*SLICES+j].normals.push_back(&normals[0]);
                    face[i*SLICES+j].normals.push_back(&normals[(j+1)]);
                    face[i*SLICES+j].normals.push_back(&normals[(j+2)]);
                }else{
                    face[i*SLICES+j].vertexs.push_back(&vertexs[0]);
                    face[i*SLICES+j].vertexs.push_back(&vertexs[(j+1)]);
                    face[i*SLICES+j].vertexs.push_back(&vertexs[(SLICES-j)]);
                    face[i*SLICES+j].normals.push_back(&normals[0]);
                    face[i*SLICES+j].normals.push_back(&normals[(j+1)]);
                    face[i*SLICES+j].normals.push_back(&normals[(SLICES-j)]);
                }

            }else if((i+1)==STACKS/2){
                    if ((j+1)!=SLICES){
                        face[i*SLICES+j].vertexs.push_back(&vertexs[SLICES*(STACKS/2)+1]);
                        face[i*SLICES+j].vertexs.push_back(&vertexs[(i-1)*SLICES+(j+2)]);
                        face[i*SLICES+j].vertexs.push_back(&vertexs[(i-1)*SLICES+(j+1)]);
                        face[i*SLICES+j].normals.push_back(&normals[SLICES*(STACKS/2)+1]);
                        face[i*SLICES+j].normals.push_back(&normals[(i-1)*SLICES+(j+2)]);
                        face[i*SLICES+j].normals.push_back(&normals[(i-1)*SLICES+(j+1)]);
                    }else{
                        face[i*SLICES+j].vertexs.push_back(&vertexs[SLICES*(STACKS/2)+1]);
                        face[i*SLICES+j].vertexs.push_back(&vertexs[(i-1)*STACKS+(1)]);
                        face[i*SLICES+j].vertexs.push_back(&vertexs[(i-1)*STACKS+(j+1)]);
                        face[i*SLICES+j].normals.push_back(&normals[SLICES*(STACKS/2)+1]);
                        face[i*SLICES+j].normals.push_back(&normals[(i-1)*STACKS+(1)]);
                        face[i*SLICES+j].normals.push_back(&normals[(i-1)*STACKS+(j+1)]);
                    }

            }else{
                if ((j+1)!=SLICES){
                    face[i*SLICES+j].vertexs.push_back(&vertexs[(i-1)*SLICES+(j+1)]);
                    face[i*SLICES+j].vertexs.push_back(&vertexs[i*SLICES+(j+1)]);
                    face[i*SLICES+j].vertexs.push_back(&vertexs[i*SLICES+(j+2)]);
                    face[i*SLICES+j].vertexs.push_back(&vertexs[(i-1)*SLICES+(j+2)]);

                    face[i*SLICES+j].normals.push_back(&normals[(i-1)*SLICES+(j+1)]);
                    face[i*SLICES+j].normals.push_back(&normals[i*SLICES+(j+1)]);
                    face[i*SLICES+j].normals.push_back(&normals[i*SLICES+(j+2)]);
                    face[i*SLICES+j].normals.push_back(&normals[(i-1)*SLICES+(j+2)]);
                }else{
                    face[i*SLICES+j].vertexs.push_back(&vertexs[(i-1)*SLICES+(j+1)]);
                    face[i*SLICES+j].vertexs.push_back(&vertexs[i*SLICES+(j+1)]);
                    face[i*SLICES+j].vertexs.push_back(&vertexs[i*SLICES+(1)]);
                    face[i*SLICES+j].vertexs.push_back(&vertexs[(i-1)*SLICES+(1)]);
                    face[i*SLICES+j].normals.push_back(&normals[(i-1)*SLICES+(j+1)]);
                    face[i*SLICES+j].normals.push_back(&normals[i*SLICES+(j+1)]);
                    face[i*SLICES+j].normals.push_back(&normals[i*SLICES+(1)]);
                    face[i*SLICES+j].normals.push_back(&normals[(i-1)*SLICES+(1)]);
                }

            }

            mesh->faces.push_back(face[i*SLICES+j]);

        }
    }
//    for(int i=(SLICES-1);i>0;i--){
//        for(int j=0;j<STACKS;j++){
//        if(j<STACKS-1){
//            face[j+(STACKS*(SLICES-i))].vertexs.push_back(&vertexs[j+(STACKS*(SLICES-i))]);
//            face[j+(STACKS*(SLICES-i))].vertexs.push_back(&vertexs[j+(STACKS*(SLICES-i-1))]);
//            face[j+(STACKS*(SLICES-i))].vertexs.push_back(&vertexs[j+(STACKS*(SLICES-i-1))+1]);
//            face[j+(STACKS*(SLICES-i))].vertexs.push_back(&vertexs[j+(STACKS*(SLICES-i))+1]);
//            face[j+(STACKS*(SLICES-i))].normals.push_back(&normals[j+(STACKS*(SLICES-i))]);
//            face[j+(STACKS*(SLICES-i))].normals.push_back(&normals[j+(STACKS*(SLICES-i-1))]);
//            face[j+(STACKS*(SLICES-i))].normals.push_back(&normals[j+(STACKS*(SLICES-i))+1]);
//            face[j+(STACKS*(SLICES-i))].normals.push_back(&normals[j+(STACKS*(SLICES-i-1)+1)]);
//        }else{
//            face[j+(STACKS*(SLICES-i))].vertexs.push_back(&vertexs[j+(STACKS*(SLICES-i))]);
//            face[j+(STACKS*(SLICES-i))].vertexs.push_back(&vertexs[j+(STACKS*(SLICES-i-1))]);
//            face[j+(STACKS*(SLICES-i))].vertexs.push_back(&vertexs[STACKS+((j+1)*(SLICES-i-2))]);
//            face[j+(STACKS*(SLICES-i))].vertexs.push_back(&vertexs[STACKS+((j+1)*(SLICES-i-1))]);
//            face[j+(STACKS*(SLICES-i))].normals.push_back(&normals[j+(STACKS*(SLICES-i))]);
//            face[j+(STACKS*(SLICES-i))].normals.push_back(&normals[j+(STACKS*(SLICES-i-1))]);
//            face[j+(STACKS*(SLICES-i))].normals.push_back(&normals[STACKS+((j+1)*(SLICES-i-2))]);
//            face[j+(STACKS*(SLICES-i))].normals.push_back(&normals[STACKS+((j+1)*(SLICES-i-1))]);
//        }
//        mesh->faces.push_back(face[j+(STACKS*(SLICES-i))]);
//        }
//    }
//    //desenho do fundo da esfera

////    for(int j=0;j<STACKS;j++){
////        if(j<STACKS-1){
////            face[j+(STACKS*(SLICES))].vertexs.push_back(&vertexs[STACKS*SLICES]);
////            face[j+(STACKS*(SLICES))].vertexs.push_back(&vertexs[j+1]);
////            face[j+(STACKS*(SLICES))].vertexs.push_back(&vertexs[j]);
////            face[j+(STACKS*(SLICES))].normals.push_back(&normals[STACKS*SLICES]);
////            face[j+(STACKS*(SLICES))].normals.push_back(&normals[j+1]);
////            face[j+(STACKS*(SLICES))].normals.push_back(&normals[j]);

////        }else{
////            face[j+(STACKS*(SLICES))].vertexs.push_back(&vertexs[j]);
////            face[j+(STACKS*(SLICES))].vertexs.push_back(&vertexs[STACKS*SLICES]);
////            face[j+(STACKS*(SLICES))].vertexs.push_back(&vertexs[0]);
////            face[j+(STACKS*(SLICES))].normals.push_back(&normals[j]);
////            face[j+(STACKS*(SLICES))].normals.push_back(&normals[STACKS*SLICES]);
////            face[j+(STACKS*(SLICES))].normals.push_back(&normals[0]);

////        }
////        mesh->faces.push_back(face[j+(STACKS*(SLICES))]);
////    }

////    for(int i=0;i<STACKS;i++){
////        face[(STACKS*SLICES)+STACKS].vertexs.push_back(&vertexs[i+STACKS*(SLICES-1)]);
////        if (i==0)
////            face[(STACKS*SLICES)+STACKS].normals.push_back(&normals[(STACKS*SLICES)+1]);
////    }
////    mesh->faces.push_back(face[(STACKS*SLICES)+STACKS]);

    enabled = true;
    selected = false;
}

void Sphere::draw()
{
    if(isEnabled()){
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    refreshNormals();
//    refreshVertexs();
//    glPointSize(1.0);
//    for (int i=0;i<SLICES*(STACKS/2);i++){
//        glBegin(GL_POINTS);
//        glVertex3f(vertexs[i].x(),vertexs[i].y(),vertexs[i].z());
//        glEnd();
//    }
//    glDisable(GL_LIGHTING);
//    glColor3f(1,1,1);
//    glBegin(GL_POINTS);
//    glVertex3f(getMax().x(),getMax().y(),getMax().z());
//    glVertex3f(getMin().x(),getMin().y(),getMin().z());

//    glEnd();
//    glEnable(GL_LIGHTING);


    mesh->draw();
    //boundingBox().wireframe();
    }
    if (selected){

        Draw::drawSelection(getMax(),getMin());
//        glColor3f(1,1,1);
//        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
//        mesh->draw();

    }


}

void Sphere::wireframe()
{
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    refreshNormals();

    mesh->draw();


}

void Sphere::aplyTransform(Matrix4x4 t)
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

void Sphere::setIdentityTransform()
{
    transform.setIdentity();
}


void Sphere::refreshNormals()
{
    for (int i = 0;i<(STACKS/2);i++){
        for(int j=0;j<SLICES;j++){
            vertexs[i*SLICES+(j+1)] = transform.transpose().vector(initvertexs[i*SLICES+(j+1)]);
            normals[i*SLICES+(j+1)] = transform.transform_normal_ray(transform,initnormals[i*SLICES+(j+1)]).unitary()*(-1);
        }
    }
    vertexs[0] = transform.transpose().vector(initvertexs[0]);
    vertexs[(STACKS/2)*SLICES+1] = transform.transpose().vector(initvertexs[(STACKS/2)*SLICES+1]);
    normals[0] = transform.transform_normal_ray(transform,initnormals[0]).unitary()*(-1);
    normals[(STACKS/2)*SLICES+1] = transform.transform_normal_ray(transform,initnormals[(STACKS/2)*SLICES+1]).unitary()*(-1);
}

void Sphere::setMaterial(int material)
{
    mesh->setMaterial(material);
}

void Sphere::changeCoords(Matrix4x4 matrix)
{
    transform = transform.multMatrix(transform,matrix);
    refreshNormals();
}

Mesh * Sphere::getMesh()
{
    return mesh;
}

void Sphere::setName(QString nm)
{
    name = nm;
}

QString Sphere::getName()
{
    return name;
}

int Sphere::getIdMaterial()
{
    return mesh->getMaterial();
}

void Sphere::tryIntersection(RayIntersection *intersect, Ray ray)
{

    if(motion==Vec4())
        intersect->raySphereIntersection(mesh,transform,ray,this);
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
        intersect->raySphereIntersection(mesh,mat,ray,this);
    }
}

void Sphere::setSelected(bool b)
{
    selected = b;
}

bool Sphere::isSelected()
{
    return selected;
}

void Sphere::setEnabled(bool b)
{
    enabled = b;
}

bool Sphere::isEnabled()
{
    return enabled;
}

Matrix4x4 Sphere::getMatrixTransformation()
{
    return transform;
}

int Sphere::getNumFaces()
{
    return mesh->faces.size();
}

int Sphere::getNumVertexs()
{
    return SLICES*STACKS + 2;
}

void Sphere::setTransform(Matrix4x4 m)
{
    transform = m;
}

QString Sphere::saveObject()
{
    QString obj;
    QString aux;
    obj += "s ";
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

Sphere::~Sphere()
{
    delete []mesh;
}

Cube Sphere::boundingBox()
{
    if (getMotion().module()>0){ //reescalar a dimensão da bouding box
        if (((getCenter()+getMotion())-this->getMax()).module() <= ((getCenter()+getMotion())-this->getMin()).module()){ // o movimento esta no sentido da posição máxima
            return Cube(this->getMin(),this->getMax()+getMotion());
        }else{
            return Cube(this->getMin()+getMotion(),this->getMax());

        }
    }

    return Cube(this->getMin(),this->getMax());
}



Vec4 Sphere::getMin()
{
    refreshVertexs();
    float pmin[3] = {vertexs[0].x(),vertexs[0].y(),vertexs[0].z()};
    for (int i=1;i<SLICES*(STACKS/2)+1;i++){
        if(pmin[0]>=vertexs[i].x1) pmin[0] = vertexs[i].x1;
        if(pmin[1]>=vertexs[i].x2) pmin[1] = vertexs[i].x2;
        if(pmin[2]>=vertexs[i].x3) pmin[2] = vertexs[i].x3;


    }
    return Vec4(pmin[0],pmin[1],pmin[2]);

}

Vec4 Sphere::getMax()
{
    refreshVertexs();
    float pmax[3] = {vertexs[0].x(),vertexs[0].y(),vertexs[0].z()};
    for (int i=1;i<SLICES*(STACKS/2)+1;i++){

        if(pmax[0]<=vertexs[i].x1) pmax[0] = vertexs[i].x1;
        if(pmax[1]<=vertexs[i].x2) pmax[1] = vertexs[i].x2;
        if(pmax[2]<=vertexs[i].x3) pmax[2] = vertexs[i].x3;

    }
    return Vec4(pmax[0],pmax[1],pmax[2]);

}

Vec4 Sphere::getCenter()
{
    return (this->getMax()-this->getMin())/2.0;
}

void Sphere::refreshVertexs()
{
    for (int i = SLICES;i>0;i--){
        for(int j=0;j<STACKS;j++){
            vertexs[j+(STACKS*(SLICES-i))] = transform.transpose().vector(initvertexs[j+(STACKS*(SLICES-i))]);
        }
    }
}

void Sphere::setMotion(Vec4 m)
{
    motion = m;
}

Vec4 Sphere::getMotion()
{
    return motion;
}

bool Sphere::getEnabledTexture()
{
    return this->enable_texture;
}

void Sphere::setEnabledTexture(bool b)
{
    this->enable_texture = b;
}

void Sphere::setTexture(Texture *tex)
{
    this->textures.clear();
    this->textures.push_back(tex);
}

void Sphere::addTexture(Texture *tex)
{
    this->textures.push_back(tex);
}

void Sphere::removeTexture(Texture *tex)
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

int Sphere::getLenTexture()
{
    return textures.size();
}

Texture *Sphere::getTexture(int i)
{
    return textures.at(i);
}


bool Sphere::getEnabledBump()
{
    return enable_bumping;
}

void Sphere::setEnabledBump(bool b)
{
    this->enable_bumping = b;
}

void Sphere::setBump(Bump *bump)
{
    bumps.clear();
    bumps.push_back(bump);
}

void Sphere::addBump(Bump *bump)
{
    bumps.push_back(bump);
}

void Sphere::removeBump(Bump *bump)
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

int Sphere::getLenBump()
{
    return bumps.size();
}

Bump *Sphere::getBump(int i)
{
    return bumps.at(i);
}

QString Sphere::getType()
{
    return "OBJSPHERE";
}

int Sphere::getTypeInt()
{
    return OBJSPHERE;
}

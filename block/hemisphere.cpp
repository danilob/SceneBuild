#include "hemisphere.h"

HemiSphere::HemiSphere()
{
    motion = Vec4();
    enable_texture = false;
    enable_bumping = false;
    float radius = 1.0;
    double alpha = M_PI / STACKS;
    double beta = 2*M_PI / SLICES;

    //vertexs[0] = Vec4(0.0,radius,0.0);
    for (int i = 0;i<=STACKS/2;i++){
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
    normals[SLICES*STACKS+1] = Vec4(0,-radius,0).unitary();
    initnormals[SLICES*STACKS+1] = Vec4(0,-radius,0).unitary();

    normals[SLICES*STACKS+2] = Vec4(0,-1,0);
    normals[SLICES*STACKS+2] = Vec4(0,-1,0);
//    vertexs[SLICES*(STACKS)+1] = Vec4(0.0,radius,0.0);
//    initvertexs[SLICES*(STACKS)+1] = Vec4(0.0,radius,0.0);
    //normals[SLICES*(STACKS/2)+1] = Vec4(0,-1,0);
    //initnormals[SLICES*(STACKS/2)+1] = Vec4(0,-1,0);
    transform.setIdentity();
    mesh = new Mesh();
    //vertexs[SLICES*STACKS]
    Face face[((STACKS/2)*SLICES)+1];
    //desenho da lateral do hemisferio
    for(int i=0;i<=STACKS/2;i++){
        for(int j=0;j<SLICES;j++){
            if(i==0){
                if ((j+1)!=SLICES){
                    face[i*SLICES+j].vertexs.push_back(&vertexs[0]);
                    face[i*SLICES+j].vertexs.push_back(&vertexs[(j+1)]);
                    face[i*SLICES+j].vertexs.push_back(&vertexs[(j+2)]);

                    face[i*SLICES+j].normals.push_back(&normals[SLICES*STACKS+1]);
                    face[i*SLICES+j].normals.push_back(&normals[(j+1)]);
                    face[i*SLICES+j].normals.push_back(&normals[(j+2)]);

                }else{
                    face[i*SLICES+j].vertexs.push_back(&vertexs[0]);
                    face[i*SLICES+j].vertexs.push_back(&vertexs[(j+1)]);
                    face[i*SLICES+j].vertexs.push_back(&vertexs[(SLICES-j)]);

                    face[i*SLICES+j].normals.push_back(&normals[SLICES*STACKS+1]);
                    face[i*SLICES+j].normals.push_back(&normals[(j+1)]);
                    face[i*SLICES+j].normals.push_back(&normals[(SLICES-j)]);

                }

            }else if((i+1)==1+STACKS/2){
                for(int k=0;k<SLICES;k++) face[i*SLICES+j].vertexs.push_back(&vertexs[(i-1)*SLICES+(k+1)]);
                face[i*SLICES+j].normals.push_back(&normals[SLICES*STACKS+2]);
                mesh->faces.push_back(face[i*SLICES+j]);
                break;

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

    enabled = true;
    selected = false;
}

void HemiSphere::draw()
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

void HemiSphere::wireframe()
{
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    refreshNormals();

    mesh->draw();


}

void HemiSphere::aplyTransform(Matrix4x4 t)
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

void HemiSphere::setIdentityTransform()
{
    transform.setIdentity();
}


void HemiSphere::refreshNormals()
{
    for (int i = 0;i<=(STACKS/2);i++){
        for(int j=0;j<SLICES;j++){
            vertexs[i*SLICES+(j+1)] = transform.transpose().vector(initvertexs[i*SLICES+(j+1)]);
            normals[i*SLICES+(j+1)] = transform.transform_normal_ray(transform,initnormals[i*SLICES+(j+1)]).unitary()*(-1);
        }
    }
    vertexs[0] = transform.transpose().vector(initvertexs[0]);
    //vertexs[(STACKS/2)*SLICES+1] = transform.transpose().vector(initvertexs[(STACKS/2)*SLICES+1]);
    normals[SLICES*STACKS+1] = transform.transform_normal_ray(transform,initnormals[SLICES*STACKS+1]).unitary();
    normals[(STACKS*SLICES)+2] = transform.transform_normal_ray(transform,initnormals[(STACKS*SLICES)+2]).unitary();
}

void HemiSphere::setMaterial(int material)
{
    mesh->setMaterial(material);
}

void HemiSphere::changeCoords(Matrix4x4 matrix)
{
    transform = transform.multMatrix(transform,matrix);
    refreshNormals();
}

Mesh * HemiSphere::getMesh()
{
    return mesh;
}

void HemiSphere::setName(QString nm)
{
    name = nm;
}

QString HemiSphere::getName()
{
    return name;
}

int HemiSphere::getIdMaterial()
{
    return mesh->getMaterial();
}

void HemiSphere::tryIntersection(RayIntersection *intersect, Ray ray)
{

    if(motion==Vec4())
        intersect->rayHemiSphereIntersection(mesh,transform,ray,this);
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
            intersect->rayHemiSphereIntersection(mesh,mat,ray,this);
        }
}

void HemiSphere::setSelected(bool b)
{
    selected = b;
}

bool HemiSphere::isSelected()
{
    return selected;
}

void HemiSphere::setEnabled(bool b)
{
    enabled = b;
}

bool HemiSphere::isEnabled()
{
    return enabled;
}

Matrix4x4 HemiSphere::getMatrixTransformation()
{
    return transform;
}

int HemiSphere::getNumFaces()
{
    return mesh->faces.size();
}

int HemiSphere::getNumVertexs()
{
    return SLICES*STACKS + 1;
}

void HemiSphere::setTransform(Matrix4x4 m)
{
    transform = m;
}

QString HemiSphere::saveObject()
{
    QString obj;
    QString aux;
    obj += "h ";
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


Vec4 HemiSphere::getMin()
{

    refreshVertexs();
    float pmin[3] = {vertexs[0].x(),vertexs[0].y(),vertexs[0].z()};
    for (int i=1;i<(SLICES*STACKS/2+1);i++){
        if(pmin[0]>=vertexs[i].x1) pmin[0] = vertexs[i].x1;
        if(pmin[1]>=vertexs[i].x2) pmin[1] = vertexs[i].x2;
        if(pmin[2]>=vertexs[i].x3) pmin[2] = vertexs[i].x3;


    }
    return Vec4(pmin[0],pmin[1],pmin[2]);

}

Vec4 HemiSphere::getMax()
{
    refreshVertexs();
    float pmax[3] = {vertexs[0].x(),vertexs[0].y(),vertexs[0].z()};

    for (int i=1;i<(SLICES*STACKS/2+1);i++){

        if(pmax[0]<=vertexs[i].x1) pmax[0] = vertexs[i].x1;
        if(pmax[1]<=vertexs[i].x2) pmax[1] = vertexs[i].x2;
        if(pmax[2]<=vertexs[i].x3) pmax[2] = vertexs[i].x3;

    }
    return Vec4(pmax[0],pmax[1],pmax[2]);

}

Cube HemiSphere::boundingBox()
{
    return Cube(this->getMin(),this->getMax(),this->getCenter());
}

Vec4 HemiSphere::getCenter()
{
    return (getMax()+getMin())/2;



}

void HemiSphere::refreshVertexs()
{
    refreshNormals();
}


void HemiSphere::setMotion(Vec4 m)
{
    motion = m;
}

Vec4 HemiSphere::getMotion()
{
    return motion;
}

bool HemiSphere::getEnabledTexture()
{
    return this->enable_texture;
}

void HemiSphere::setEnabledTexture(bool b)
{
    this->enable_texture = b;
}

void HemiSphere::setTexture(Texture *tex)
{
    this->textures.clear();
    this->textures.push_back(tex);
}

void HemiSphere::addTexture(Texture *tex)
{
    this->textures.push_back(tex);
}

void HemiSphere::removeTexture(Texture *tex)
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

int HemiSphere::getLenTexture()
{
    return textures.size();
}

Texture *HemiSphere::getTexture(int i)
{
    return textures.at(i);
}


bool HemiSphere::getEnabledBump()
{
    return enable_bumping;
}

void HemiSphere::setEnabledBump(bool b)
{
    this->enable_bumping = b;
}

void HemiSphere::setBump(Bump *bump)
{
    bumps.clear();
    bumps.push_back(bump);
}

void HemiSphere::addBump(Bump *bump)
{
    bumps.push_back(bump);
}

void HemiSphere::removeBump(Bump *bump)
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

int HemiSphere::getLenBump()
{
    return bumps.size();
}

Bump *HemiSphere::getBump(int i)
{
    return bumps.at(i);
}

QString HemiSphere::getType()
{
    return "OBJHEMISPHERE";
}

int HemiSphere::getTypeInt()
{
    return OBJHEMISPHERE;
}

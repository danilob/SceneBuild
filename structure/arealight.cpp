#include "arealight.h"
#include "photon.h"
#include <stdio.h>
#include <stdlib.h> // RAND_MAX é definido em stdlib.h

#define myrand ((float)rand() / float(RAND_MAX))

float AreaLight::attenuation(float distance){
    return 1.0/(factor_attenuation->x()+distance*factor_attenuation->y()+distance*distance*factor_attenuation->z());
}
/**********************************************************************************************/
/********************** Ínicio das Definições da Classe AreaLight **************************/
/**********************************************************************************************/

AreaLight::AreaLight(){
    position_light  = new Vec4(0.0,0.0,1.0,0.0);
    diffuse_light   = new Vec4(1.0,1.0,1.0,1.0);
    specular_light  = new Vec4(1.0,1.0,1.0,1.0);
    ambient_light   = new Vec4(1.0,1.0,1.0,1.0);
    factor_attenuation = new Vec4(1.0,0.0,0.0,0.0);; //constante, linear, quadratico
    vecA = new Vec4(1,0,0);
    vecB = new Vec4(0,0,-1);
    name.append("Area Light");
    selected = false;
    enabled  = true;
    visible  = false;
}

void AreaLight::drawLightOpenGL(int flag_light)
{
    glLightfv(flag_light, GL_POSITION, &position_light->x1);
    glLightfv(flag_light, GL_DIFFUSE , &diffuse_light->x1);
    glLightfv(flag_light, GL_SPECULAR, &specular_light->x1);
    glLightfv(flag_light, GL_AMBIENT, &ambient_light->x1);
    glLightf(flag_light, GL_CONSTANT_ATTENUATION , factor_attenuation->x());
    glLightf(flag_light, GL_LINEAR_ATTENUATION   , factor_attenuation->y());
    glLightf(flag_light, GL_QUADRATIC_ATTENUATION, factor_attenuation->z());



}

void AreaLight::setLight(Vec4 *pos, Vec4 *diff, Vec4 *spec, Vec4 *amb)
{
    position_light  = pos;
    diffuse_light   = diff;
    specular_light  = spec;
    ambient_light   = amb;
}

void AreaLight::drawLight()
{
    return;
}

void AreaLight::drawReferenceLight()
{
    if(isVisible()){
        glPushMatrix();
        glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,&diffuse_light->x1);
        glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,&specular_light->x1);
        glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,&ambient_light->x1);
        Vec4 pos = Vec4(position_light->x(),position_light->y(),position_light->z());
        Vec4 a = Vec4(vecA->x(),vecA->y(),vecA->z());
        Vec4 b = Vec4(vecB->x(),vecB->y(),vecB->z());
        glBegin(GL_QUADS);
            glVertex3f(pos.x(),pos.y(),pos.z());
            glVertex3f(pos.x()+a.x(),pos.y()+a.y(),pos.z()+a.z());
            glVertex3f(pos.x()+a.x()+b.x(),pos.y()+a.y()+b.y(),pos.z()+a.z()+b.z());
            glVertex3f(pos.x()+b.x(),pos.y()+b.y(),pos.z()+b.z());
        glEnd();
        glPopMatrix();
    }
}

Vec4 AreaLight::calculateColor(Vec4 pit, Vec4 n,Vec4 viewer, Material *m,Vec4 position,Vec4 texColor,int mode_texture)
{
    if(mode_texture==TYPE_ONLY_TEXTURE){
        Vec4 l = (position-pit)/(position-pit).module();
        float fator = fmax((n*l)/(n.module()*l.module()),0);
        Vec4 Diffuse;
        Diffuse.x1 = (texColor.x() * diffuse_light->x1)*fator;
        Diffuse.x2 = (texColor.y() * diffuse_light->x2)*fator;
        Diffuse.x3 = (texColor.z() * diffuse_light->x3)*fator;

        l = l.unitary();
        Vec4 r = (n*((l*n)*2) - l);
        Vec4 v = (viewer-pit)/(viewer-pit).module();
        r = (r+v)/(r+v).module();

        float fator2 = fmax(pow((r*v),m->shininess*128),0);
        if(r*n<0) fator2 = 0;
        Vec4 especular;
        especular.x1 = (texColor.x() * specular_light->x1)*fator2;
        especular.x2 = (texColor.y() * specular_light->x2)*fator2;
        especular.x3 = (texColor.z() * specular_light->x3)*fator2;

        Vec4 ambiente;
        ambiente.x1 = texColor.x() * ambient_light->x1;
        ambiente.x2 = texColor.y() * ambient_light->x2;
        ambiente.x3 = texColor.z() * ambient_light->x3;

        Vec4 color = (Diffuse)*attenuation((position-viewer).module());
        return color;

    }else if(mode_texture==TYPE_REPLACE_TEXTURE){
        Vec4 l = (position-pit)/(position-pit).module();
        float fator = fmax((n*l)/(n.module()*l.module()),0);
        Vec4 Diffuse;
        Diffuse.x1 = (m->diffuse[0] * diffuse_light->x1)*fator;
        Diffuse.x2 = (m->diffuse[1] * diffuse_light->x2)*fator;
        Diffuse.x3 = (m->diffuse[2] * diffuse_light->x3)*fator;

        //calculo da contribuicao especular
        l = l.unitary();
        Vec4 r = (n*((l*n)*2) - l);
        Vec4 v = (viewer-pit)/(viewer-pit).module();
        r = (r+v)/(r+v).module();

        float fator2 = fmax(pow((r*v),m->shininess*128),0);
        if(r*n<0) fator2 = 0;
        Vec4 especular;
        especular.x1 = (m->specular[0] * specular_light->x1)*fator2;
        especular.x2 = (m->specular[1] * specular_light->x2)*fator2;
        especular.x3 = (m->specular[2] * specular_light->x3)*fator2;
        //calculo da contribuição ambiente
        Vec4 ambiente;
        ambiente.x1 = m->ambient[0] * ambient_light->x1;
        ambiente.x2 = m->ambient[1] * ambient_light->x2;
        ambiente.x3 = m->ambient[2] * ambient_light->x3;

        Vec4 color = texColor.mult((Diffuse+especular)*attenuation((position-viewer).module()));
    return color;
    }else{
        Vec4 l = (position-pit)/(position-pit).module();
        float fator = fmax((n*l)/(n.module()*l.module()),0);
        Vec4 Diffuse;
        Diffuse.x1 = (m->diffuse[0] * diffuse_light->x1)*fator;
        Diffuse.x2 = (m->diffuse[1] * diffuse_light->x2)*fator;
        Diffuse.x3 = (m->diffuse[2] * diffuse_light->x3)*fator;

        //calculo da contribuicao especular
        l = l.unitary();
        Vec4 r = (n*((l*n)*2) - l);
        Vec4 v = (viewer-pit)/(viewer-pit).module();
        r = (r+v)/(r+v).module();

        float fator2 = fmax(pow((r*v),m->shininess*128),0);
        if(r*n<0) fator2 = 0;
        Vec4 especular;
        especular.x1 = (m->specular[0] * specular_light->x1)*fator2;
        especular.x2 = (m->specular[1] * specular_light->x2)*fator2;
        especular.x3 = (m->specular[2] * specular_light->x3)*fator2;
        //calculo da contribuição ambiente
        Vec4 ambiente;
        ambiente.x1 = m->ambient[0] * ambient_light->x1;
        ambiente.x2 = m->ambient[1] * ambient_light->x2;
        ambiente.x3 = m->ambient[2] * ambient_light->x3;

        Vec4 color = (Diffuse+especular)*attenuation((position-viewer).module());
    return color;
    }
}

QString AreaLight::getName()
{
    return this->name;
}

void AreaLight::setName(QString name)
{
    this->name = name;
}

bool AreaLight::isVisible()
{
    return visible;
}

void AreaLight::setVisible(bool b)
{
    this->visible = b;
}

int AreaLight::getTypeLight()
{
    return LIGHT_AREA;
}

bool AreaLight::isSelected()
{
    return selected;
}

void AreaLight::setSelected(bool b)
{
    this->selected = b;
}

bool AreaLight::isEnabled()
{
    return enabled;
}

void AreaLight::setEnabled(bool b)
{
    this->enabled = b;
}

void AreaLight::setAmbientColor(QColor color)
{
    ambient_light = new Vec4((float)color.red()/255.0,(float)color.green()/255.0,(float)color.blue()/255.0);
}

QColor AreaLight::getAmbientColor()
{
    QColor color;
    color.setRgb((int)(ambient_light->x()*255),(int)(ambient_light->y()*255),(int)(ambient_light->z()*255));
    return color;
}

void AreaLight::setSpecularColor(QColor color)
{
    specular_light = new Vec4((float)color.red()/255.0,(float)color.green()/255.0,(float)color.blue()/255.0);
}

QColor AreaLight::getSpecularColor()
{
    QColor color;
    color.setRgb((int)(specular_light->x()*255),(int)(specular_light->y()*255),(int)(specular_light->z()*255));
    return color;
}

void AreaLight::setDiffuseColor(QColor color)
{
    diffuse_light = new Vec4((float)color.red()/255.0,(float)color.green()/255.0,(float)color.blue()/255.0);
}

QColor AreaLight::getDiffuseColor()
{
    QColor color;
    color.setRgb((int)(diffuse_light->x()*255),(int)(diffuse_light->y()*255),(int)(diffuse_light->z()*255));
    return color;
}

void AreaLight::setPosition(Vec4 pos)
{
    position_light = new Vec4(pos.x(),pos.y(),pos.z());
}

Vec4 AreaLight::getPosition()
{
    Vec4 value(position_light->x(),position_light->y(),position_light->z());
    return value;
}

void AreaLight::setDirection(Vec4)
{
    return;
}

Vec4 AreaLight::getDirection()
{
    return Vec4();
}

void AreaLight::setAttenuation(Vec4 pos)
{
    factor_attenuation = new Vec4(pos.x(),pos.y(),pos.z());
}

Vec4 AreaLight::getAttenuation()
{
    Vec4 value(factor_attenuation->x(),factor_attenuation->y(),factor_attenuation->z());
    return value;
}

int AreaLight::getAngle()
{
    return -1;
}

void AreaLight::setAngle(int angle)
{
    return;
}

void AreaLight::setExponent(int exp)
{
    return;
}

int AreaLight::getExponent()
{
    return -1;
}

QString AreaLight::saveLight()
{
    QString lig;
    QString aux;
    lig += "r ";
    lig += aux.sprintf("%.3f %.3f %.3f ",ambient_light->x(),ambient_light->y(),ambient_light->z());
    lig += aux.sprintf("%.3f %.3f %.3f ",specular_light->x(),specular_light->y(),specular_light->z());
    lig += aux.sprintf("%.3f %.3f %.3f ",diffuse_light->x(),diffuse_light->y(),diffuse_light->z());
    lig += aux.sprintf("%.3f %.3f %.3f ",position_light->x(),position_light->y(),position_light->z());
    lig += aux.sprintf("%.3f %.3f %.3f ",factor_attenuation->x(),factor_attenuation->y(),factor_attenuation->z());
    lig += aux.sprintf("%.3f %.3f %.3f ",vecA->x(),vecA->y(),vecA->z());
    lig += aux.sprintf("%.3f %.3f %.3f ",vecB->x(),vecB->y(),vecB->z());

    if (this->enabled)
        lig += "t ";
    else
        lig += "f ";
    if (this->visible)
        lig += "t ";
    else
        lig += "f ";
    if (this->selected)
        lig += "t ";
    else
        lig += "f ";
    lig += this->name+"\n";
    return lig;
}


Vec4 AreaLight::randLight()
{

    Vec4 position(position_light->x1,position_light->x2,position_light->x3);
    Vec4 a = Vec4(vecA->x(),vecA->y(),vecA->z());
    Vec4 b = Vec4(vecB->x(),vecB->y(),vecB->z());
    return position + a*myrand + b*myrand;
}

AreaLight::~AreaLight()
{
    delete     [] position_light;
    delete     []diffuse_light;
    delete     []specular_light;
    delete     []ambient_light;
    delete     []factor_attenuation;
}

int AreaLight::getAngleInner()
{
    return -1;
}

void AreaLight::setAngleInner(int angle)
{
    return;
}

void AreaLight::setVecA(Vec4 a)
{
    vecA = new Vec4(a.x(),a.y(),a.z());
}

Vec4 AreaLight::getVecA()
{
    return Vec4(vecA->x(),vecA->y(),vecA->z());
}

void AreaLight::setVecB(Vec4 b)
{
    vecB = new Vec4(b.x(),b.y(),b.z());
}

Vec4 AreaLight::getVecB()
{
    return Vec4(vecB->x(),vecB->y(),vecB->z());
}

QString AreaLight::getTypeLightS()
{
    return "LIGHT_AREA";
}

std::vector<Photon*> AreaLight::emitPhotons(int ne, int pow, Object *obj)
{
    srand(time(0));
    std::vector<Photon*> photons;
    if (pow==0) return photons;
    //emite a quantidade inicial de photons
    int n = 1; //number of emitted photons
    if(obj==NULL){
        while (n<=ne){
            Vec4 normal;
            if(myrand<0.5)
               normal = (*vecA) ^ (*vecB);
            else
                normal = (*vecB) ^ (*vecA);
            normal.normalize();
            float du = -(1-myrand)/2.0 + myrand*(1-myrand);
            float dv = -(1-myrand)/2.0 + myrand*(1-myrand);
            Vec4 d = normal + (*vecA).unitary()*du + (*vecB).unitary()*dv;
            Vec4 p = randLight();
            Photon* photon =  new Photon(p,d.unitary());
            photon->setPower(Vec4((1.)/ne,(1.)/ne,(1./ne)));
            n++;
            photons.push_back(photon);
        }
    }
    else{
        Vec4 max = obj->getMax();
        Vec4 min = obj->getMin();
        Vec4 d,p;
        bool hit;
        while (n<=ne){
            float x,y,z;
            do{
                x = (max.x()-min.x())*myrand + min.x(); //ξ1 ∈ [0,1] is a random number
                y = (max.y()-min.y())*myrand + min.y(); //ξ2 ∈ [0,1] is a random number
                z = (max.z()-min.z())*myrand + min.z(); //ξ3 ∈ [0,1] is a random number
                p = randLight();
                d = (Vec4(x,y,z)-p).unitary();
                Ray ray(p,d);
                RayIntersection *inter = new RayIntersection();
                inter->t = 120000;
                inter->tmin = 0;
                obj->tryIntersection(inter,ray);
                if(inter->normal==Vec4()) hit = false;
                else hit = true;
                delete inter;
            } while (((x<min.x())||(x>max.x()))||((y<min.y())||(y>max.y()))||((z<min.z())||(z>max.z()))||(!hit));
            Photon* photon =  new Photon(p,d.unitary());
            photon->setPower(Vec4((1.)/ne,(1.)/ne,(1.)/ne));
            photon->setType(CAUSTIC);
            n++;
            photons.push_back(photon);
        }
    }
    return photons;
}

void AreaLight::setPower(int pow)
{
    this->power = pow;
}

int AreaLight::getPower()
{
    return this->power;
}

//std::vector<Photon*> AreaLight::emitPhotons(int ne)
//{
//    std::vector<Photon*> photons;
//    int n = 1; //number of emitted photons
//    while (n<=ne){
//        float x,y,z;
//        do{
//            x = 2*myrand - 1; //ξ1 ∈ [0,1] is a random number
//            y = 2*myrand - 1; //ξ2 ∈ [0,1] is a random number
//            z = 2*myrand - 1; //ξ3 ∈ [0,1] is a random number
//        } while (x*x + y*y + z*z > 1);
//        Vec4 d(x,y,z);
//        Vec4 p = randLight();
//        Photon* photon =  new Photon(p,d);
//        photon->setPower(Vec4(1.0/ne,1.0/ne,1.0/ne));
//        n++;
//        photons.push_back(photon);
//    }

//}

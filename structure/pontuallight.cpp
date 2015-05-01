#include "pontuallight.h"
#include "photon.h"
#include <stdio.h>
#include <stdlib.h> // RAND_MAX é definido em stdlib.h

#define myrand ((float)(rand())/(float)(RAND_MAX) )
float PontualLight::attenuation(float distance){
    return 1.0/(factor_attenuation->x()+distance*factor_attenuation->y()+distance*distance*factor_attenuation->z());
}
/**********************************************************************************************/
/********************** Ínicio das Definições da Classe PontualLight **************************/
/**********************************************************************************************/

PontualLight::PontualLight(){
    position_light  = new Vec4(0.0,0.0,1.0,0.0);
    diffuse_light   = new Vec4(1.0,1.0,1.0,1.0);
    specular_light  = new Vec4(1.0,1.0,1.0,1.0);
    ambient_light   = new Vec4(1.0,1.0,1.0,1.0);
    factor_attenuation = new Vec4(1.0,0.0,0.0,0.0);; //constante, linear, quadratico
    name.append("Pontual Light");
    selected = false;
    enabled  = true;
    visible  = false;
}

void PontualLight::drawLightOpenGL(int flag_light)
{
    glLightfv(flag_light, GL_POSITION, &position_light->x1);
    glLightfv(flag_light, GL_DIFFUSE , &diffuse_light->x1);
    glLightfv(flag_light, GL_SPECULAR, &specular_light->x1);
    glLightfv(flag_light, GL_AMBIENT, &ambient_light->x1);
    glLightf(flag_light, GL_CONSTANT_ATTENUATION , factor_attenuation->x());
    glLightf(flag_light, GL_LINEAR_ATTENUATION   , factor_attenuation->y());
    glLightf(flag_light, GL_QUADRATIC_ATTENUATION, factor_attenuation->z());



}

void PontualLight::setLight(Vec4 *pos, Vec4 *diff, Vec4 *spec, Vec4 *amb)
{
    position_light = pos;
    diffuse_light   = diff;
    specular_light  = spec;
    ambient_light   = amb;
}

void PontualLight::drawLight()
{
    return;
}

void PontualLight::drawReferenceLight()
{
    if(isVisible()){
        glPushMatrix();

        glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,&diffuse_light->x1);
        glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,&specular_light->x1);
        glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,&ambient_light->x1);
        //glPushMatrix();
        glTranslatef(position_light->x1,position_light->x2,position_light->x3);
        glutSolidSphere(0.5,20,20);
        //glPopMatrix();
        glPopMatrix();
    }
}

Vec4 PontualLight::calculateColor(Vec4 pit, Vec4 n,Vec4 viewer, Material *m,Vec4 position,Vec4 texColor,int mode_texture)
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

        float fator2 = fmax(pow((r*n),m->shininess*128),0);
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

        float fator2 = fmax(pow((r*n),m->shininess*128),0);
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

QString PontualLight::getName()
{
    return this->name;
}

void PontualLight::setName(QString name)
{
    this->name = name;
}

bool PontualLight::isVisible()
{
    return visible;
}

void PontualLight::setVisible(bool b)
{
    this->visible = b;
}

int PontualLight::getTypeLight()
{
    return LIGHT_PONTUAL;
}

bool PontualLight::isSelected()
{
    return selected;
}

void PontualLight::setSelected(bool b)
{
    this->selected = b;
}

bool PontualLight::isEnabled()
{
    return enabled;
}

void PontualLight::setEnabled(bool b)
{
    this->enabled = b;
}

void PontualLight::setAmbientColor(QColor color)
{
    ambient_light = new Vec4((float)color.red()/255.0,(float)color.green()/255.0,(float)color.blue()/255.0);
}

QColor PontualLight::getAmbientColor()
{
    QColor color;
    color.setRgb((int)(ambient_light->x()*255),(int)(ambient_light->y()*255),(int)(ambient_light->z()*255));
    return color;
}

void PontualLight::setSpecularColor(QColor color)
{
    specular_light = new Vec4((float)color.red()/255.0,(float)color.green()/255.0,(float)color.blue()/255.0);
}

QColor PontualLight::getSpecularColor()
{
    QColor color;
    color.setRgb((int)(specular_light->x()*255),(int)(specular_light->y()*255),(int)(specular_light->z()*255));
    return color;
}

void PontualLight::setDiffuseColor(QColor color)
{
    diffuse_light = new Vec4((float)color.red()/255.0,(float)color.green()/255.0,(float)color.blue()/255.0);
}

QColor PontualLight::getDiffuseColor()
{
    QColor color;
    color.setRgb((int)(diffuse_light->x()*255),(int)(diffuse_light->y()*255),(int)(diffuse_light->z()*255));
    return color;
}

void PontualLight::setPosition(Vec4 pos)
{
    position_light = new Vec4(pos.x(),pos.y(),pos.z());
}

Vec4 PontualLight::getPosition()
{
    Vec4 value(position_light->x(),position_light->y(),position_light->z());
    return value;
}

void PontualLight::setDirection(Vec4)
{
    return;
}

Vec4 PontualLight::getDirection()
{
    return Vec4();
}

void PontualLight::setAttenuation(Vec4 pos)
{
    factor_attenuation = new Vec4(pos.x(),pos.y(),pos.z());
}

Vec4 PontualLight::getAttenuation()
{
    Vec4 value(factor_attenuation->x(),factor_attenuation->y(),factor_attenuation->z());
    return value;
}

int PontualLight::getAngle()
{
    return -1;
}

void PontualLight::setAngle(int angle)
{
    return;
}

void PontualLight::setExponent(int exp)
{
    return;
}

int PontualLight::getExponent()
{
    return -1;
}

QString PontualLight::saveLight()
{
    QString lig;
    QString aux;
    lig += "o ";
    lig += aux.sprintf("%.3f %.3f %.3f ",ambient_light->x(),ambient_light->y(),ambient_light->z());
    lig += aux.sprintf("%.3f %.3f %.3f ",specular_light->x(),specular_light->y(),specular_light->z());
    lig += aux.sprintf("%.3f %.3f %.3f ",diffuse_light->x(),diffuse_light->y(),diffuse_light->z());
    lig += aux.sprintf("%.3f %.3f %.3f ",position_light->x(),position_light->y(),position_light->z());
    lig += aux.sprintf("%.3f %.3f %.3f ",factor_attenuation->x(),factor_attenuation->y(),factor_attenuation->z());

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


Vec4 PontualLight::randLight()
{

    Vec4 position(position_light->x1,position_light->x2,position_light->x3);
    return position;
}

PontualLight::~PontualLight()
{
    delete     [] position_light;
    delete     []diffuse_light;
    delete     []specular_light;
    delete     []ambient_light;
    delete     []factor_attenuation;
}

int PontualLight::getAngleInner()
{
    return -1;
}

void PontualLight::setAngleInner(int angle)
{
    return;
}

void PontualLight::setVecA(Vec4 a)
{
    return;
}

Vec4 PontualLight::getVecA()
{
    return Vec4();
}

void PontualLight::setVecB(Vec4 b)
{
    return;
}

Vec4 PontualLight::getVecB()
{
    return Vec4();
}

QString PontualLight::getTypeLightS()
{
    return "LIGHT_PONTUAL";
}

std::vector<Photon*> PontualLight::emitPhotons(int ne,int pow,Object* obj)
{
    std::vector<Photon*> photons;
    if (pow==0) return photons;
    //emite a quantidade inicial de photons
    int n = 1; //number of emitted photons
    if(obj==NULL){
        while (n<=ne){
            float x,y,z;
            float theta,phi;
            float signal = 1;
            if (myrand>0.5) signal = -1;
            theta = acos(myrand*signal);
            phi = 2*M_PI*myrand;
            x = sin(theta)*cos(phi);
            y = sin(theta)*sin(phi);
            z = cos(theta);
//            do{
//                x = 2*myrand - 1; //ξ1 ∈ [0,1] is a random number
//                y = 2*myrand - 1; //ξ2 ∈ [0,1] is a random number
//                z = 2*myrand - 1; //ξ3 ∈ [0,1] is a random number
//            } while (x*x + y*y + z*z > 1);
            Vec4 d(x,y,z);
            Vec4 p = getPosition();
            Photon* photon =  new Photon(p,d);
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
                p = getPosition();
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

void PontualLight::setPower(int pow)
{
    this->power = pow;
}

int PontualLight::getPower()
{
    return power;
}


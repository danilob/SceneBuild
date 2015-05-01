#include "directionallight.h"
#include "photon.h"
DirectionalLight::DirectionalLight(){

    direction_light = new Vec4(1.0,1.0,1.0,0.0);
    diffuse_light   = new Vec4(1.0,1.0,1.0,1.0);
    specular_light  = new Vec4(1.0,1.0,1.0,1.0);
    ambient_light   = new Vec4(1.0,1.0,1.0,1.0);
    name.append("Directional Light");
    selected = false;
    enabled  = true;
    visible  = false;


}

void DirectionalLight::drawLightOpenGL(int flag_light)
{
    direction_light->x4 = 0;
    glLightfv(flag_light, GL_POSITION, &direction_light->x1);
    glLightfv(flag_light, GL_DIFFUSE , &diffuse_light->x1);
    glLightfv(flag_light, GL_SPECULAR, &specular_light->x1);
    glLightfv(flag_light, GL_AMBIENT, &ambient_light->x1);

}

void DirectionalLight::setLight(Vec4 *pos, Vec4 *diff, Vec4 *spec, Vec4 *amb)
{
    direction_light = pos;
    diffuse_light   = diff;
    specular_light  = spec;
    ambient_light   = amb;

}

void DirectionalLight::drawLight()
{
    return;
}

void DirectionalLight::drawReferenceLight()
{
    if(isVisible()){
        glPushMatrix();
        glLineWidth(1.5);
        glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,&diffuse_light->x1);
        glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,&specular_light->x1);
        glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,&ambient_light->x1);

        Draw::drawArrow(direction_light,20);
        glBegin(GL_LINES);
        glVertex3f(20*direction_light->x1,20*direction_light->x2,20*direction_light->x3);
        glVertex3f(25*direction_light->x1,25*direction_light->x2,25*direction_light->x3);

        glEnd();
        glLineWidth(1.0);
        glPopMatrix();
    }

}

Vec4 DirectionalLight::calculateColor(Vec4 pit, Vec4 n,Vec4 viewer, Material *m,Vec4,Vec4 texColor,int mode_texture)
{
    Vec4 position(direction_light->x1,direction_light->x2,direction_light->x3);
    Vec4 l = (position);
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

    Vec4 color = ambiente+(Diffuse+especular);
    return color;
}

QString DirectionalLight::getName()
{
    return this->name;
}

void DirectionalLight::setName(QString name)
{
    this->name = name;
}

bool DirectionalLight::isVisible()
{
    return visible;
}

void DirectionalLight::setVisible(bool b)
{
    this->visible = b;
}

int DirectionalLight::getTypeLight()
{
    return LIGHT_DIRECTIONAL;
}

bool DirectionalLight::isSelected()
{
    return selected;
}

void DirectionalLight::setPosition(Vec4)
{
    return;
}

Vec4 DirectionalLight::getPosition()
{
    return Vec4();
}

void DirectionalLight::setSelected(bool b)
{
    this->selected = b;
}

bool DirectionalLight::isEnabled()
{
    return enabled;
}

void DirectionalLight::setEnabled(bool b)
{
    this->enabled = b;
}

void DirectionalLight::setAmbientColor(QColor color)
{
    ambient_light = new Vec4((float)color.red()/255.0,(float)color.green()/255.0,(float)color.blue()/255.0);
}

QColor DirectionalLight::getAmbientColor()
{
    QColor color;
    color.setRgb((int)(ambient_light->x()*255),(int)(ambient_light->y()*255),(int)(ambient_light->z()*255));
    return color;
}

void DirectionalLight::setSpecularColor(QColor color)
{
    specular_light = new Vec4((float)color.red()/255.0,(float)color.green()/255.0,(float)color.blue()/255.0);
}

QColor DirectionalLight::getSpecularColor()
{
    QColor color;
    color.setRgb((int)(specular_light->x()*255),(int)(specular_light->y()*255),(int)(specular_light->z()*255));
    return color;
}

void DirectionalLight::setDiffuseColor(QColor color)
{
    diffuse_light = new Vec4((float)color.red()/255.0,(float)color.green()/255.0,(float)color.blue()/255.0);
}

QColor DirectionalLight::getDiffuseColor()
{
    QColor color;
    color.setRgb((int)(diffuse_light->x()*255),(int)(diffuse_light->y()*255),(int)(diffuse_light->z()*255));
    return color;
}


void DirectionalLight::setDirection(Vec4 pos)
{
    direction_light = new Vec4(pos.x(),pos.y(),pos.z());
}

Vec4 DirectionalLight::getDirection()
{
    Vec4 value(direction_light->x(),direction_light->y(),direction_light->z());
    return value;
}

void DirectionalLight::setAttenuation(Vec4)
{
    return;
}

Vec4 DirectionalLight::getAttenuation()
{
    return Vec4();
}

QString DirectionalLight::saveLight()
{
    QString lig;
    QString aux;
    lig += "d ";
    lig += aux.sprintf("%.3f %.3f %.3f ",ambient_light->x(),ambient_light->y(),ambient_light->z());
    lig += aux.sprintf("%.3f %.3f %.3f ",specular_light->x(),specular_light->y(),specular_light->z());
    lig += aux.sprintf("%.3f %.3f %.3f ",diffuse_light->x(),diffuse_light->y(),diffuse_light->z());
    lig += aux.sprintf("%.3f %.3f %.3f ",direction_light->x(),direction_light->y(),direction_light->z());

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

Vec4 DirectionalLight::randLight()
{
    return Vec4(direction_light->x(),direction_light->y(),direction_light->z())*10000;;
}

int DirectionalLight::getAngle()
{
    return -1;
}

void DirectionalLight::setAngle(int angle)
{
    return;
}

void DirectionalLight::setExponent(int exp)
{
    return;
}

int DirectionalLight::getExponent()
{
    return -1;
}

int DirectionalLight::getAngleInner()
{
    return -1;
}

void DirectionalLight::setAngleInner(int angle)
{
    return;
}

void DirectionalLight::setVecA(Vec4 a)
{
    return;
}

Vec4 DirectionalLight::getVecA()
{
    return Vec4();
}

void DirectionalLight::setVecB(Vec4 b)
{
    return;
}

Vec4 DirectionalLight::getVecB()
{
    return Vec4();
}

QString DirectionalLight::getTypeLightS()
{
    return "LIGHT_DIRECTIONAL";
}

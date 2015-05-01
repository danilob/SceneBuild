#include "spotlight.h"
#include "photon.h"
float SpotLight::attenuation(float distance){
    return 1.0/(factor_attenuation->x()+distance*factor_attenuation->y()+distance*distance*factor_attenuation->z());
}

float smoothstep(float min,float max, float x){
    if(x<min) return 0;
    if(x>max) return 1;
    return -2*pow(((x-min)/(max-min)),3)+3*pow(((x-min)/(max-min)),2);
}

int SpotLight::isInConeSpot(Vec4 pit)
{
    Vec4 d(direction_light->x(),direction_light->y(),direction_light->z());
    Vec4 p(position_light->x(),position_light->y(),position_light->z());
    Vec4 v = (pit-p).unitary();
    float cosDirection = v*d;
    if (cos(angle_light*M_PI/180.0)<=cosDirection) return 1;
    else return 0;

}

float SpotLight::isInDualConeSpot(Vec4 pit)
{
    if(angle_inner_light == 0) return isInConeSpot(pit);
    Vec4 p(position_light->x(),position_light->y(),position_light->z());
    Vec4 d(direction_light->x(),direction_light->y(),direction_light->z());
    Vec4 v = (pit-p).unitary();
    float cosOuter = cos((float)angle_light*M_PI/180.0);
    float cosInner = cos((float)angle_inner_light*M_PI/180.0);
    float cosDirection = v*d;
    return smoothstep(cosOuter,cosInner,cosDirection);
}


SpotLight::SpotLight()
{
    direction_light  = new Vec4(0.0,1.0,1.0,0.0);
    position_light  = new Vec4(1.0,1.0,1.0,1.0);
    diffuse_light   = new Vec4(1.0,1.0,1.0,1.0);
    specular_light  = new Vec4(1.0,1.0,1.0,1.0);
    ambient_light   = new Vec4(0.0,0.0,0.0,1.0);
    factor_attenuation = new Vec4(1.0,0.0,0.0,0.0); //constante, linear, quadratico
    angle_light = 45;           //para luz do tipo spot
    expoent_light = 1.0;          //fator de atenuação
    angle_inner_light = 0;
    name.append("Spot Light");
    selected = false;
    enabled  = true;
    visible  = false;
}

void SpotLight::setLight(int angle, int expoent, Vec4 *pos, Vec4 *dir, Vec4 *diff, Vec4 *spec, Vec4 *amb)
{
    if(angle>180){
        angle_light = 180;
    }else{
        angle_light = angle;
    }
    expoent_light = expoent;
    position_light = pos;
    direction_light = dir;
    diffuse_light = diff;
    specular_light = spec;
    ambient_light = amb;
}

void SpotLight::drawLight()
{
    return;
}

void SpotLight::drawLightOpenGL(int flag_light)
{
    direction_light->x4 = 0;
    glLightfv(flag_light, GL_POSITION, &position_light->x1);
    glLightfv(flag_light, GL_DIFFUSE , &diffuse_light->x1);
    glLightfv(flag_light, GL_SPECULAR, &specular_light->x1);
    glLightfv(flag_light, GL_AMBIENT, &ambient_light->x1);
    glLightf(flag_light, GL_CONSTANT_ATTENUATION , factor_attenuation->x1);
    glLightf(flag_light, GL_LINEAR_ATTENUATION   , factor_attenuation->x2);
    glLightf(flag_light, GL_QUADRATIC_ATTENUATION, factor_attenuation->x3);
    glLightf(flag_light, GL_SPOT_CUTOFF, angle_light);
    glLightfv(flag_light, GL_SPOT_DIRECTION, &direction_light->x1);
    glLightf(flag_light, GL_SPOT_EXPONENT, expoent_light);
}

void SpotLight::drawReferenceLight()
{
    if (isVisible()){
        glPushMatrix();

        glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,&diffuse_light->x1);
        glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,&specular_light->x1);
        glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,&ambient_light->x1);
        //glPushMatrix();

        Draw::drawSpot(position_light,direction_light,angle_light);

        //glPopMatrix();
        glPopMatrix();
    }

}

Vec4 SpotLight::calculateColor(Vec4 pit, Vec4 n,Vec4 viewer, Material *m,Vec4 pos,Vec4 texColor,int mode_texture)
{
    if(mode_texture==TYPE_ONLY_TEXTURE){
        Vec4 direction(direction_light->x1,direction_light->x2,direction_light->x3);
        Vec4 position(position_light->x1,position_light->x2,position_light->x3);
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

        Vec4 color = ((Diffuse+especular))*isInDualConeSpot(pit)*pow(direction*(l*-1),expoent_light)*attenuation((position-viewer).module());
        return color;

    }else if(mode_texture==TYPE_REPLACE_TEXTURE){

    Vec4 direction(direction_light->x1,direction_light->x2,direction_light->x3);

    //calculo da contribuição difusa

    Vec4 position(position_light->x1,position_light->x2,position_light->x3);
    if ((position-pit).unitary()*n<=0) return Vec4();
    //direction = (direction)/(direction).module();
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

    Vec4 color = texColor.mult(((Diffuse+especular))*isInDualConeSpot(pit)*pow(direction*(l*-1),expoent_light)*attenuation((position-viewer).module()));
    return color;
    }else{
        Vec4 direction(direction_light->x1,direction_light->x2,direction_light->x3);

        //calculo da contribuição difusa

        Vec4 position(position_light->x1,position_light->x2,position_light->x3);
        if ((position-pit).unitary()*n<=0) return Vec4();
        //direction = (direction)/(direction).module();
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

        Vec4 color = ((Diffuse+especular))*isInDualConeSpot(pit)*pow(direction*(l*-1),expoent_light)*attenuation((position-viewer).module());
        return color;
    }
}

QString SpotLight::getName()
{
    return this->name;
}

void SpotLight::setName(QString name)
{
    this->name = name;
}

bool SpotLight::isVisible()
{
    return visible;
}

void SpotLight::setVisible(bool b)
{
    this->visible = b;
}

int SpotLight::getTypeLight()
{
    return LIGHT_SPOT;
}

Vec4 SpotLight::randLight()
{
    Vec4 position = Vec4(position_light->x(),position_light->y(),position_light->z());
    return position;
}

bool SpotLight::isSelected()
{
    return selected;
}

void SpotLight::setSelected(bool b)
{
    this->selected = b;
}

bool SpotLight::isEnabled()
{
    return enabled;
}

void SpotLight::setEnabled(bool b)
{
    this->enabled = b;
}

void SpotLight::setAmbientColor(QColor color)
{
    ambient_light =new Vec4((float)color.red()/255.0,(float)color.green()/255.0,(float)color.blue()/255.0);
}

QColor SpotLight::getAmbientColor()
{
    QColor color;
    color.setRgb((int)(ambient_light->x()*255),(int)(ambient_light->y()*255),(int)(ambient_light->z()*255));
    return color;
}

void SpotLight::setSpecularColor(QColor color)
{
    specular_light = new Vec4((float)color.red()/255.0,(float)color.green()/255.0,(float)color.blue()/255.0);
}

QColor SpotLight::getSpecularColor()
{
    QColor color;
    color.setRgb((int)(specular_light->x()*255),(int)(specular_light->y()*255),(int)(specular_light->z()*255));
    return color;
}

void SpotLight::setDiffuseColor(QColor color)
{
    diffuse_light = new Vec4((float)color.red()/255.0,(float)color.green()/255.0,(float)color.blue()/255.0);
}

QColor SpotLight::getDiffuseColor()
{
    QColor color;
    color.setRgb((int)(diffuse_light->x()*255),(int)(diffuse_light->y()*255),(int)(diffuse_light->z()*255));
    return color;
}

void SpotLight::setPosition(Vec4 pos)
{
    position_light = new Vec4(pos.x(),pos.y(),pos.z());
}

Vec4 SpotLight::getPosition()
{
    Vec4 value(position_light->x(),position_light->y(),position_light->z());
    return value;
}

void SpotLight::setDirection(Vec4 pos)
{
    direction_light = new Vec4(pos.x(),pos.y(),pos.z());
}

Vec4 SpotLight::getDirection()
{
    Vec4 value(direction_light->x(),direction_light->y(),direction_light->z());
    return value;
}

void SpotLight::setAttenuation(Vec4 pos)
{
    factor_attenuation = new Vec4(pos.x(),pos.y(),pos.z());
}

Vec4 SpotLight::getAttenuation()
{
    Vec4 value(factor_attenuation->x(),factor_attenuation->y(),factor_attenuation->z());
    return value;
}

int SpotLight::getAngle()
{
    return angle_light;
}

void SpotLight::setAngle(int angle)
{
    this->angle_light = angle;
}

int SpotLight::getAngleInner()
{
    return angle_inner_light;
}

void SpotLight::setAngleInner(int angle)
{
    this->angle_inner_light = angle;
}

void SpotLight::setExponent(int exp)
{
    this->expoent_light = exp;
}

int SpotLight::getExponent()
{
    return expoent_light;
}

QString SpotLight::saveLight()
{
    QString lig;
    QString aux;
    lig += "s ";
    lig += aux.sprintf("%.3f %.3f %.3f ",ambient_light->x(),ambient_light->y(),ambient_light->z());
    lig += aux.sprintf("%.3f %.3f %.3f ",specular_light->x(),specular_light->y(),specular_light->z());
    lig += aux.sprintf("%.3f %.3f %.3f ",diffuse_light->x(),diffuse_light->y(),diffuse_light->z());
    lig += aux.sprintf("%.3f %.3f %.3f ",position_light->x(),position_light->y(),position_light->z());
    lig += aux.sprintf("%.3f %.3f %.3f ",direction_light->x(),direction_light->y(),direction_light->z());
    lig += aux.sprintf("%.3f %.3f %.3f ",factor_attenuation->x(),factor_attenuation->y(),factor_attenuation->z());
    lig += aux.sprintf("%d %d ",angle_light,expoent_light);
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

QString SpotLight::getTypeLightS()
{
    return "LIGHT_SPOT";
}

void SpotLight::setVecA(Vec4 a)
{
    return;
}

Vec4 SpotLight::getVecA()
{
    return Vec4();
}

void SpotLight::setVecB(Vec4 b)
{
    return;
}

Vec4 SpotLight::getVecB()
{
    return Vec4();
}

#include "ambientlight.h"
#include "light.h"

/**********************************************************************************************/
/********************** Ínicio das Definições da Classe AmbientLight **************************/
/**********************************************************************************************/

AmbientLight::AmbientLight()
{
    ambient_light  =  new Vec4(0.3,0.3,0.3,1.0);
    name.append("Ambient Light");
    selected = false;
}

void AmbientLight::drawLightOpenGL(int flag_light)
{
    if(flag_light==-1)
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT,&ambient_light->x1);
}

Vec4 AmbientLight::calculateColor(Vec4 pit, Vec4 n,Vec4 viewer, Material *m,Vec4 pos,Vec4 texColor,int mode_texture)
{
    Vec4 ambiente;
    if(texColor!= Vec4()){
        ambiente.x1 = texColor.x() * ambient_light->x1*0.5;
        ambiente.x2 = texColor.y() * ambient_light->x2*0.5;
        ambiente.x3 = texColor.z() * ambient_light->x3*0.5;
        return ambiente;
    }
    ambiente.x1 = m->ambient[0] * ambient_light->x1;
    ambiente.x2 = m->ambient[1] * ambient_light->x2;
    ambiente.x3 = m->ambient[2] * ambient_light->x3;
    return ambiente;
}

QString AmbientLight::getName()
{
    return this->name;
}

void AmbientLight::setName(QString name)
{
    this->name = name;
}

bool AmbientLight::isEnabled()
{
    return true;
}

void AmbientLight::setEnabled(bool)
{
    return;
}

bool AmbientLight::isVisible()
{
    return visible;
}

void AmbientLight::setVisible(bool b)
{
    this->visible = b;
}

int AmbientLight::getTypeLight()
{
    return LIGHT_AMBIENT;
}

bool AmbientLight::isSelected()
{
    return selected;
}

void AmbientLight::setPosition(Vec4)
{
    return;
}

Vec4 AmbientLight::getPosition()
{
    return Vec4();
}

void AmbientLight::setDirection(Vec4)
{
    return;
}

Vec4 AmbientLight::getDirection()
{
    return Vec4();
}

void AmbientLight::setAttenuation(Vec4)
{
    return;
}

Vec4 AmbientLight::getAttenuation()
{
    return Vec4();
}

int AmbientLight::getAngle()
{
    return -1;
}

void AmbientLight::setAngle(int angle)
{
    return;
}

void AmbientLight::setExponent(int exp)
{
    return;
}

int AmbientLight::getExponent()
{
    return -1;
}

void AmbientLight::setSelected(bool b)
{
    this->selected = b;
}


void AmbientLight::setAmbientColor(QColor color)
{
    ambient_light = new Vec4((float)color.red()/255.0,(float)color.green()/255.0,(float)color.blue()/255.0);
}

QColor AmbientLight::getAmbientColor()
{
    QColor color;
    color.setRgb((int)(ambient_light->x()*255),(int)(ambient_light->y()*255),(int)(ambient_light->z()*255));
    return color;
}

void AmbientLight::setSpecularColor(QColor)
{
    return;
}

QColor AmbientLight::getSpecularColor()
{
    return QColor();
}

void AmbientLight::setDiffuseColor(QColor)
{
    return;
}


QColor AmbientLight::getDiffuseColor()
{
    return QColor();
}

QString AmbientLight::saveLight()
{
    QString lig;
    QString aux;
    lig += "a ";
    lig += aux.sprintf("%.3f %.3f %.3f ",ambient_light->x(),ambient_light->y(),ambient_light->z());
    if (this->selected)
        lig += "t ";
    else
        lig += "f ";
    lig += this->name+"\n";
    return lig;
}

Vec4 AmbientLight::randLight()
{
    return Vec4();
}

void AmbientLight::drawLight()
{
    return;
}

void AmbientLight::drawReferenceLight()
{
    return;
}

int AmbientLight::getAngleInner()
{
    return -1;
}

void AmbientLight::setAngleInner(int angle)
{
    return;
}

void AmbientLight::setVecA(Vec4 a)
{
    return;
}

Vec4 AmbientLight::getVecA()
{
    return Vec4();
}

void AmbientLight::setVecB(Vec4 b)
{
    return;
}

Vec4 AmbientLight::getVecB()
{
    return Vec4();
}

QString AmbientLight::getTypeLightS()
{
    return "LIGHT_AMBIENT";
}

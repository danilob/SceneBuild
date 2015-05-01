#include "effects.h"

Effects::Effects()
{
}

GlossyRefraction::GlossyRefraction()
{
    indice = 0;
    obj = NULL;
}

GlossyRefraction::GlossyRefraction(Object *obj)
{
    indice = 0;
    this->obj = obj;
}

int GlossyRefraction::getEffect()
{
    return GLOSSY_REFRACTION;
}

void GlossyRefraction::setParameters(float indice, float indice2, Vec4 v)
{
    this->indice = indice;
}

void GlossyRefraction::setParametersP1(float i)
{
    this->indice = i;
}

void GlossyRefraction::setParametersP2(float)
{
}

Vec4 GlossyRefraction::setParametersP3(float)
{
}

float GlossyRefraction::getParametersP1()
{
    return this->indice;
}

float GlossyRefraction::getParametersP2()
{
    return 0.0;
}

Vec4 GlossyRefraction::getParametersP3()
{
    return Vec4();
}

void GlossyRefraction::drawEffect()
{
    //a se pensar
}

void GlossyRefraction::setEnable(bool b)
{
    this->enabled = b;
}

bool GlossyRefraction::getEnable()
{
    return this->enabled;
}

void GlossyRefraction::setVisible(bool b)
{
    this->visible = b;
}

bool GlossyRefraction::getVisible()
{
    return this->visible;
}

Object *GlossyRefraction::getObject()
{
    return this->obj;
}

void GlossyRefraction::setObject(Object *obj)
{
    this->obj = obj;
}


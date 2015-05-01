#ifndef LIGHT_H
#define LIGHT_H
#include "math/vec4.h"
#include "extra/material.h"
#include "draw/draw.h"
#include "extra/texture.h"
#include "block/object.h"
#include <vector>

#define LIGHT_AMBIENT     0
#define LIGHT_DIRECTIONAL 1
#define LIGHT_PONTUAL     2
#define LIGHT_SPOT        3
#define LIGHT_AREA        4
class Photon;

class Light
{
public:
    virtual void       drawLight() = 0;
    virtual void       drawLightOpenGL(int flag_light = -1) = 0;
    virtual void       drawReferenceLight() = 0;
    virtual Vec4       calculateColor(Vec4,Vec4,Vec4, Material *,Vec4 l= Vec4(),Vec4 tex= Vec4(),int mode =-1) = 0;
    virtual QString    getName() = 0;
    virtual void       setName(QString name) = 0;
    virtual bool       isEnabled() = 0;
    virtual void       setEnabled(bool b) = 0;
    virtual bool       isSelected() = 0;
    virtual void       setSelected(bool b) = 0;
    virtual bool       isVisible() = 0;
    virtual void       setVisible(bool b) = 0;
    virtual void       setAmbientColor(QColor color) = 0;
    virtual QColor     getAmbientColor() = 0;
    virtual void       setSpecularColor(QColor color) = 0;
    virtual QColor     getSpecularColor() = 0;
    virtual void       setDiffuseColor(QColor color) = 0;
    virtual QColor     getDiffuseColor() = 0;
    virtual int        getTypeLight() = 0;
    virtual QString    getTypeLightS() = 0;
    virtual void       setPosition(Vec4 pos) = 0;
    virtual Vec4       getPosition() = 0;
    virtual void       setDirection(Vec4 pos) = 0;
    virtual Vec4       getDirection() = 0;
    virtual void       setAttenuation(Vec4 pos) = 0;
    virtual Vec4       getAttenuation() = 0;
    virtual int        getAngle() = 0;
    virtual void       setAngle(int angle) = 0;
    virtual void       setExponent(int exp) = 0;
    virtual int        getExponent() = 0;
    virtual QString    saveLight() = 0;
    virtual Vec4       randLight() = 0;
    virtual int        getAngleInner() = 0;
    virtual void       setAngleInner(int) = 0;
    virtual void       setVecA(Vec4) = 0;
    virtual Vec4       getVecA() = 0;
    virtual void       setVecB(Vec4) = 0;
    virtual Vec4       getVecB() = 0;
    virtual std::vector<Photon*> emitPhotons(int,int,Object* obj=NULL) = 0;
    virtual void       setPower(int pow) = 0;
    virtual int        getPower() = 0;



};






#endif // LIGHT_H

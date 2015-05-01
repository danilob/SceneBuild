#ifndef AMBIENTLIGHT_H
#define AMBIENTLIGHT_H

#include "light.h"

class AmbientLight: public Light
{
public:
    AmbientLight();
    void       setLight(Vec4 amb);
    void       drawLight();
    void       drawReferenceLight();
    Vec4       calculateColor(Vec4 pit,Vec4 n,Vec4 viewer, Material *m,Vec4 pos=Vec4(0,0,0),Vec4 texColor=Vec4(),int mode_texture=-1);
    void       drawLightOpenGL(int flag_light = -1);
    QString    getName();
    void       setName(QString name);
    bool       isEnabled();
    void       setEnabled(bool);
    bool       isVisible();
    void       setVisible(bool);
    void       setAmbientColor(QColor);
    QColor     getAmbientColor();
    void       setSpecularColor(QColor);
    QColor     getSpecularColor();
    void       setDiffuseColor(QColor);
    QColor     getDiffuseColor();
    int        getTypeLight();
    void       setSelected(bool);
    bool       isSelected();
    void       setPosition(Vec4);
    Vec4       getPosition();
    void       setDirection(Vec4);
    Vec4       getDirection();
    void       setAttenuation(Vec4);
    Vec4       getAttenuation();
    int        getAngle();
    void       setAngle(int angle);
    void       setExponent(int exp);
    int        getExponent();
    QString    saveLight();
    Vec4       randLight();
    int        getAngleInner();
    void       setAngleInner(int angle);
    void       setVecA(Vec4);
    Vec4       getVecA();
    void       setVecB(Vec4);
    Vec4       getVecB();
    QString    getTypeLightS();
    std::vector<Photon*>       emitPhotons(int,int,Object*){};
    void       setPower(int pow){};
    int        getPower(){};

private:
    Vec4*      ambient_light;
    QString    name;
    bool       visible;
    bool       selected;

};


#endif // AMBIENTLIGHT_H

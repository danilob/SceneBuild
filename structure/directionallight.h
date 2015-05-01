#ifndef DIRECTIONALLIGHT_H
#define DIRECTIONALLIGHT_H
#include "light.h"

class DirectionalLight: public Light
{
public:
    DirectionalLight();
    void setLight(Vec4* pos, Vec4* diff, Vec4* spec, Vec4* amb= new Vec4(1,1,1,1.0));                           //tipo de luz que tem o vetor de direção
    void drawLight();
    void drawReferenceLight();
    void drawLightOpenGL(int flag_light);
    Vec4 calculateColor(Vec4 pit,Vec4 n,Vec4 viewer, Material *m,Vec4 =Vec4(0,0,0),Vec4 texColor=Vec4(),int mode_texture=-1);
    QString    getName();
    void       setName(QString name);
    bool       isEnabled();
    void       setEnabled(bool b);
    bool       isVisible();
    void       setVisible(bool b);
    void       setAmbientColor(QColor color);
    QColor     getAmbientColor();
    void       setSpecularColor(QColor color);
    QColor     getSpecularColor();
    void       setDiffuseColor(QColor color);
    QColor     getDiffuseColor();
    int        getTypeLight();
    void       setSelected(bool b);
    bool       isSelected();
    void       setPosition(Vec4);
    Vec4       getPosition();
    void       setDirection(Vec4 pos);
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
    Vec4*      diffuse_light;
    Vec4*      specular_light;
    Vec4*      ambient_light;
    Vec4*      direction_light;
    bool       enabled;
    bool       visible;
    bool       selected;
    QString    name;
};


#endif // DIRECTIONALLIGHT_H

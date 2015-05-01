#ifndef SPOTLIGHT_H
#define SPOTLIGHT_H
#include "light.h"

class SpotLight: public Light
{
public:
    SpotLight();
    void setLight(int angle, int expoent,Vec4* pos,Vec4 *dir, Vec4* diff, Vec4* spec,Vec4* amb= new Vec4(1,1,1,1.0));  //tipo de luz que tem um ângulo de direção
    void drawLight();
    void drawReferenceLight();
    void drawLightOpenGL(int flag_light);
    Vec4 calculateColor(Vec4 pit,Vec4 n,Vec4 viewer, Material *m,Vec4 pos=Vec4(0,0,0),Vec4 texColor=Vec4(),int mode_texture=-1);
    QString    getName();
    void       setName(QString name);
    bool       isEnabled();
    void       setEnabled(bool b);
    bool       isVisible();
    void       setVisible(bool b);
    bool       isSelected();
    void       setSelected(bool b);
    void       setAmbientColor(QColor color);
    QColor     getAmbientColor();
    void       setSpecularColor(QColor color);
    QColor     getSpecularColor();
    void       setDiffuseColor(QColor color);
    QColor     getDiffuseColor();
    float      attenuation(float distance);
    int        getTypeLight();
    Vec4       randLight();

    void       setPosition(Vec4 pos);
    Vec4       getPosition();
    void       setDirection(Vec4 pos);
    Vec4       getDirection();
    void       setAttenuation(Vec4 pos);
    Vec4       getAttenuation();
    int        getAngle();
    void       setAngle(int angle);
    int        getAngleInner();
    void       setAngleInner(int angle);
    void       setExponent(int exp);
    int        getExponent();

    int        isInConeSpot(Vec4 pit);
    float      isInDualConeSpot(Vec4 pit);

    void       setVecA(Vec4);
    Vec4       getVecA();
    void       setVecB(Vec4);
    Vec4       getVecB();


    QString    saveLight();
    QString    getTypeLightS();
    std::vector<Photon*>       emitPhotons(int,int,Object*){};
    void       setPower(int pow){};
    int        getPower(){};


private:
    Vec4*     position_light;
    Vec4*     diffuse_light;
    Vec4*     specular_light;
    Vec4*     ambient_light;
    Vec4*     factor_attenuation;   //constante, linear, quadratico
    Vec4*     direction_light;
    int       angle_light;
    int       expoent_light;         //fator de atenuação da luz spot
    int       angle_inner_light;
    bool      enabled;
    bool      visible;
    bool      selected;
    QString   name;
};


#endif // SPOTLIGHT_H

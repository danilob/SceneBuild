#ifndef QUATERNION_H
#define QUATERNION_H
#include "vec4.h"
#include "matrix4x4.h"
class Quaternion
{
private:
    float s,x,y,z;
public:
    Quaternion();
    Quaternion(float r,float x, float y, float z);
    Quaternion(float x, float y, float z);
    Quaternion(float r, Vec4 v);
    //sets
    void setQuaternion(float r,float x, float y, float z);
    void setQuaternion(Vec4 AxisAngle);
    void setQuaternion(float r, Vec4 v);
    void setScalar(float s);
    void setPosX(float x);
    void setPosY(float y);
    void setPosZ(float z);
    //gets
    float getScalar(); //escalar
    float getPosX(); //coordenada x
    float getPosY(); //coordenada y
    float getPosZ(); //coordenada z
    Vec4 getVector();
    Quaternion getQuaternion();
    //fuctions
    Quaternion conjugate(); //conjugado do quaternion
    float normal(); //módulo
    Quaternion normalize(); // normalizacao
    Quaternion inverse();
    Vec4 toAxis();
    float toAngle();
    void toAxisAngle(Vec4 *axis, float *angle); //converter um quaternion para eixo e angulo
    void toEulerAngle(Vec4 *axis); //converter um quaternion para eixo e angulo
    void printQuaternion();
    Matrix4x4 getMatrix();
    static Quaternion toRotation(Quaternion q);
    static Quaternion fromRotation(Quaternion q);
    static Vec4 getVecRotation(Quaternion q,Vec4 v);
    //operadores
//    Quaternion operator +(Quaternion q);
//    Quaternion operator -(Quaternion q);
    Quaternion operator *(float k);
    Quaternion operator /(float k);
    //Quaternion operator *(Quaternion q);
    friend bool operator==(Quaternion p,Quaternion q);
    friend Quaternion operator+(Quaternion p,Quaternion q);
    friend Quaternion operator-(Quaternion p,Quaternion q);
    friend Quaternion operator*(Quaternion p,Quaternion q);
    friend Quaternion operator/(Quaternion p,Quaternion q);
    static float dot(Quaternion p, Quaternion q);

    static Quaternion Exp(Quaternion q);
    static Quaternion Exp(Quaternion q,float t);
    static Quaternion Log(Quaternion q);







}
;

#endif // QUATERNION_H

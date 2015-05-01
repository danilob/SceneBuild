#ifndef VEC4_H
#define VEC4_H
#include <stdio.h>
#include <math.h>
#include <QtOpenGL>
class Vec4
{
public:
    float x1,x2,x3,x4;
public:
    Vec4(float x=0.0,float y=0.0,float z=0.0,float w=1.0);
    void setVec4(Vec4 p);
    void setVec4(float x1=0.0,float x2=0.0,float x3=0.0,float x4=1.0);
    float x();
    float y();
    float z();
    float w();
    bool operator == (Vec4 v);
    bool operator != (Vec4 v);
    Vec4 operator + (Vec4 v);                    //soma de dois vetores
    void operator += (Vec4 v);                    //soma de dois vetores
    void operator /= (float k);                    //soma de dois vetores
    Vec4 operator ^ (Vec4 v);                    //produto vetorial entre dois vetores
    Vec4 operator - (Vec4 v);                    //subtração de dois vetores
    Vec4 operator / (float k);                   //divisão das componentes do vetor por um numero real
    Vec4 operator * (float k);                   //produto das componentes do vetor por um numero real
    float operator * (Vec4 v);                   //produto escalar entre dois vetores (dot)
    void normalize();
    Vec4 mult(Vec4 v);
    float dot(Vec4 v);
    float module();                              //retorna o modulo do vetor
    static float distSquared(Vec4 p1,Vec4 p2);   //retorna a distância entre dois pontos ao quadrado
    static float dist(Vec4 p1,Vec4 p2);   //retorna a distância entre dois pontos ao quadrado
    static float distPlane(Vec4 p,Vec4 plane,Vec4 ponto,float s);   //retorna a distância entre dois pontos ao quadrado
    Vec4 unitary();                              //verifica se o vetor é unitário
    void showVec4();                             //imprime os valores do vetor
    static Vec4 crossProduct(Vec4 a, Vec4 b);    //retorna o resultado do produto vetorial entre dois vetores


};


#endif // VEC4_H

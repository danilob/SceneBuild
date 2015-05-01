#ifndef RAY_H
#define RAY_H

#include "vec4.h"

class Ray
{
public:
    Ray();
    Ray(Vec4 ori,Vec4 dir);       //inicializa o raio com determinada origem e direção (vetor unitário)
    Vec4 positionRay(float t);    //retorna o vetor da posição do raio em determinado parâmetro t
    void setDirection(Vec4 dir);  //seta a direção do raio
    void setOrigin(Vec4 ori);     //seta a origem do raio
    static Ray rayReflect(Vec4 o,Vec4 v,Vec4 normal); //retorna o raio refletido pelo raio incidente com a normal
    static Ray rayRefract(Vec4 o, Vec4 v,Vec4 normal,float n1,float n2); // retorna o raio refratado
    static Ray rayReflectWitted(Vec4 o, Vec4 v,Vec4 normal);
    static Ray rayRefractWitted(Vec4 o, Vec4 v,Vec4 normal,float n); // retorna o raio refratado
    static Ray rayReflectGlossy(Vec4 o,Vec4 v,Vec4 normal,float factor); //glossy reflexão
    static Ray rayRefractGlossy(Vec4 o, Vec4 v,Vec4 normal,float n1,float n2,float factor); //glossy refraction
    static float reflectance(Vec4 v,Vec4 normal,float n1,float n2);

public:
    Vec4 origin;
    Vec4 direction;
    Vec4 inverse_direction;
    int sign[3];

};

#endif // RAY_H

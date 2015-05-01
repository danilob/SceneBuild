#include "ray.h"
//#define ERROR 0.001
#define myrand ((float)(random())/(float)(RAND_MAX) )

Ray::Ray()
{
    origin.setVec4(0,0,0,1);
    direction.setVec4(0,0,0,0);

    //t = 0;
}
Ray::Ray(Vec4 ori,Vec4 dir)
{
    origin    = ori;
    direction = dir;
    //if (dir.module()==0) dir = Vec4(1,1,1,0);
    inverse_direction = Vec4(1.0/dir.x1, 1.0/dir.x2, 1.0/dir.x3);
    sign[0] = (inverse_direction.x1 < 0);
    sign[1] = (inverse_direction.x2 < 0);
    sign[2] = (inverse_direction.x3 < 0);
}



Vec4 Ray::positionRay(float t)
{
    return origin + direction*t;

}

void Ray::setDirection(Vec4 dir)
{
    direction = dir;
    //if (dir.module()==0) dir = Vec4(1,1,1,0);
    inverse_direction = Vec4(1.0/dir.x1, 1.0/dir.x2, 1.0/dir.x3);
    sign[0] = (inverse_direction.x1 < 0);
    sign[1] = (inverse_direction.x2 < 0);
    sign[2] = (inverse_direction.x3 < 0);

}

void Ray::setOrigin(Vec4 ori)
{
    origin = ori;
}

Ray Ray::rayReflect(Vec4 o, Vec4 v, Vec4 normal)
{
    Vec4 ri = v - normal*(2*(v*normal));
    return Ray(o,ri.unitary());
}

Ray Ray::rayRefract(Vec4 o, Vec4 v, Vec4 normal, float n1, float n2)
{
    if(((normal*v)*(-1))<=0.0){
        float nl = n1;
        n1 = n2;
        n2 = nl;
    }
    float n = n1/n2;
    float cosi = -(normal*v);
    float sint2 = n*n*(1-cosi*cosi);
    if(sint2>1.0) return Ray();
    Vec4 dir = v*n +normal*(n*cosi-sqrt(1-sint2));
    return Ray(o,dir.unitary());
}

Ray Ray::rayReflectWitted(Vec4 o, Vec4 v, Vec4 normal)
{
    return Ray(o,(v+normal*2).unitary());
}

Ray Ray::rayRefractWitted(Vec4 o, Vec4 v, Vec4 normal, float n)
{

    v = v/fabs(v*normal);
    float kf = 1.0/sqrt(n*n*(v*v) - (v+normal)*(v+normal));
    Vec4 dir = (normal+v)*kf - normal;
    return Ray(o,dir.unitary());


}

Ray Ray::rayReflectGlossy(Vec4 o, Vec4 v, Vec4 normal, float factor)
{

    Vec4 ri  = v - normal*(2*(v*normal));
    ri = ri.unitary();
    float du = -(1-factor)/2.0 + myrand*(1-factor);
    float dv = -(1-factor)/2.0 + myrand*(1-factor);
    Vec4  ul = ri^normal;
    ul = ul.unitary();
    Vec4 vl = ri^ul;
    ri = ri + ul*du + vl*dv;
    return Ray(o,ri.unitary());
}

Ray Ray::rayRefractGlossy(Vec4 o, Vec4 v, Vec4 normal, float n1, float n2, float factor)
{

    if(((normal*v)*(-1))<=0.0){
        float nl = n1;
        n1 = n2;
        n2 = nl;
    }
    float n = n1/n2;
    float cosi = -(normal*v);
    float sint2 = n*n*(1-cosi*cosi);
    if(sint2>1.0) return Ray();
    Vec4 ri = v*n +normal*(n*cosi-sqrt(1-sint2));
    ri = ri.unitary();
    float du = -(1-factor)/2.0 + myrand*(1-factor);
    float dv = -(1-factor)/2.0 + myrand*(1-factor);
    Vec4  ul = ri^normal;
    ul = ul.unitary();
    Vec4 vl = ul^ri;
    ri = ri + ul*du + vl*dv;
    return Ray(o,ri.unitary());
}

float Ray::reflectance(Vec4 v, Vec4 normal, float n1, float n2)
{
    if(((normal*v)*(-1))<=0.0){
        float nl = n1;
        n1 = n2;
        n2 = nl;
    }
    float n = n1/n2;
    float cosi = -(normal*v);
    float sint2 = n*n*(1-cosi*cosi);
    if(sint2>1.0) return 1;
    float cost = sqrt(1-sint2);
    float rorth = (n1*cosi-n2*cost)/(n1*cosi+n2*cost);
    float rpar  = (n2*cosi-n1*cost)/(n2*cosi+n1*cost);
    return (rorth*rorth+rpar*rpar)/2.0;
}



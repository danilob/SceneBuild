#ifndef RAYINTERSECTION_H
#define RAYINTERSECTION_H
#include "math/vec4.h"
#include "extra/texture.h"
#include "structure/mesh.h"


class Ray;
class Object;
class Material;

class RayIntersection
{
public:
    RayIntersection();
    void rayBoxIntersection(Mesh *mesh, Ray ray,Matrix4x4 transform,Vec4 max,Vec4 min,Object *obj);
    void rayPlanIntersection(Mesh *mesh, Ray ray,Object *obj);
    void rayCylinderIntersection(Mesh *mesh,Matrix4x4 transform, Ray ray,Object *obj);
    void rayConeIntersection(Mesh *mesh,Matrix4x4 transform, Ray ray,Object *obj);
    void raySphereIntersection(Mesh *mesh, Matrix4x4 transform, Ray ray, Object *obj);
    void rayHemiSphereIntersection(Mesh *mesh, Matrix4x4 transform, Ray ray,Object *obj);
    void rayPlaneIntersection(Face face,Ray ray);
    Vec4 mappingCylinderLateral(Vec4 pos,Texture* text=NULL);
    Vec4 mappingCylinderCap(Vec4 pos,Texture* text=NULL);
    Vec4 mappingPlanar4(Face face,Vec4 pit, Texture* text=NULL);
    Vec4 mappingPlanar3(Face face,Vec4 pit, Texture* text=NULL);
    Vec4 mappingSpheric(Vec4 pos, Texture* text=NULL);
    ~RayIntersection();
public:
    float t,tmin;
    Vec4 mapping; //coordenada de textura parametro Vec4(u,v,0,0)
    Vec4 normal;
    Material *material;
    Object *obj;

};

#endif // RAYINTERSECTION_H

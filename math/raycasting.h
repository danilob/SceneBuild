#ifndef RAYCASTING_H
#define RAYCASTING_H
#include "vec4.h"
class Ray;
class Scene;
class Object;
class Light;
class Material;
struct Face;
class CastingWidget;

class RayCasting
{
public:
    RayCasting();
    RayCasting(Scene* scene,CastingWidget *rcast,Vec4 color,bool otimized=true);
    void   setScene(Scene* scene);
    void   rayCasting(GLubyte* pixels);                              //retorna a matrix de pixels
    Vec4   rayIntersection(Ray ray);                                 //retorna a cor do pixel final a partir do raio lançado de forma otimizada
    Vec4   rayIntersectionNotOtimized(Ray ray);                      //retorna a cor do pixel final a partir do raio lançado de forma não otimizada
    float  getRayInterceptionFace(Face f,Ray ray);                   //vefifica se existe interseção com o plano da face e retorna o parametro t do raio
    bool   tryInterceptionPointFace(Face f,Vec4 point);              //testa se o raio intercepta o plano limitado
    Vec4   calculatePixelColor(Vec4 normal,Material* material,Vec4 intercept); //calcula a iluminação na forma otimizada passando o ponto interseptado, seu vetor normal e o material do objeto
    Vec4   calculatePixelColorNotOtimized(Face face, Material* material, Vec4 intercept, std::vector<Light*> lights); //calcula a iluminação na forma não otimizada

public:
    Scene* scene;
    CastingWidget *raycast;
    Vec4 backgroundcolor;
    bool otimized;

};

#endif // RAYCASTING_H

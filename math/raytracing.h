#ifndef RAYTRACING_H
#define RAYTRACING_H

#include "vec4.h"
class Ray;
class Scene;
class Object;
class Light;
class Material;
struct Face;
class GLWidget;
class HBB;
class RayTracing
{
public:
    Scene*         scene;
    GLWidget*      widget;
    Vec4           backgroundcolor;
    bool           otimized;
    HBB*           hierachicalbb;
    bool           withhbb;
    //bool           withphotonmap;

public:
    RayTracing();
    RayTracing(Scene* scene,GLWidget *rcast,Vec4 color,bool otimized=true);
    ~RayTracing();
    void           rayTracing(QImage *pixels, int proportion, int samples);                               //retorna a imagem gerada pelo ray tracing
    void           setScene(Scene* scene);                                                                //adiciona o cenário para o calculo do ray tracing
    Vec4           rayIntersection(Ray ray,Object *obj=NULL);                                                              //retorna a cor do pixel final a partir do raio lançado de forma otimizada
    Vec4           calculatePixelColor(Object *obj,Vec4 normal,Material* material,Vec4 intercept, Ray v,Vec4 map = Vec4()); //calcula a cor do objeto com a iluminação na forma otimizada passando o ponto interseptado, seu vetor normal e o material do objeto
    Vec4           testObstruction(Ray ray,Object* obj=NULL);                                                              //lança um raio do objeto a fonte de luz e verifica se ocorre obstrução, gerando sombra ou não
    Ray            depthOfField(Vec4 pixel,float radius,float distancefocus);                             //efeito de depth of field ao cenário
    static Object* objectClicked(Scene* scn,int width,int height);                                        //retorna o objeto selecionado no clique da tela
    static Object* getObject(Ray ray, Scene *scene);                                                      //extrai o objeto selecionado com o lançamento do raio

};
#endif // RAYTRACING_H

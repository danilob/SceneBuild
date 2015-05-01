#ifndef OBJECT_H
#define OBJECT_H
#include <QString>
#include "math/vec4.h"
#include "math/matrix4x4.h"
#include "structure/mesh.h"
#include "math/ray.h"
#include "math/rayintersection.h"
#include "draw/draw.h"
#include <stdio.h>
#include <stdlib.h> // RAND_MAX é definido em stdlib.h
#include "extra/texture.h"
#include "extra/bump.h"

#define myrand ((float)(rand())/(float)(RAND_MAX) )

#define OBJCUBE 0;
#define OBJCONE 1;
#define OBJCYLINDER 2;
#define OBJHEMISPHERE 3;
#define OBJPLANE 4;
#define OBJPRISM 5;
#define OBJSPHERE 6;

class Cube;

class Object
{
public:
    virtual void        setSelected(bool) = 0;                      //seta o objeto como selecionado para possiveis alterações
    virtual bool        isSelected() = 0;                           //verifica se o objeto esta selecionado
    virtual void        setEnabled(bool) = 0;                       //seta o objeto como habilitado para o raycasting e para desenho
    virtual bool        isEnabled() = 0;                            //verifica se o objeto esta habilitado
    virtual void        setMaterial(int) = 0;                       //aplica um determinado material ao objeto
    virtual Mesh*       getMesh() = 0;                              //extrai a malha do objeto
    virtual Matrix4x4   getMatrixTransformation() = 0;              //extrai a matriz de transformação do objeto
    virtual void        setTransform(Matrix4x4) = 0;                //aplica uma determinada matriz de tranformação ao objeto
    virtual QString     getName() = 0;                              //extrai o nome do objeto
    virtual void        setName(QString) = 0;                       //seta um nome para o objeto
    virtual int         getNumFaces() = 0;                          //extrai a quantidade de faces do objeto
    virtual int         getNumVertexs() = 0;                        //extrai a quantidade de vertices do objeto
    virtual int         getIdMaterial() = 0;                        //extrai o identificador do material utilizado no objeto
    virtual void        tryIntersection(RayIntersection *,Ray) = 0; //testa a interseção do raio com o objeto
    virtual void        wireframe() = 0;                            //desenha o objeto como wireframe
    virtual void        draw() = 0;                                 //desenha o objeto
    virtual void        refreshNormals() = 0;                       //atualiza os vetores normais do objeto
    virtual QString     saveObject() = 0;                           //adiconar parametros do abjeto ao arquivo
    virtual QString     getType() = 0;                              //tipo do objeto em string
    virtual int         getTypeInt() = 0;                           //tipo do objeto em inteiro
    virtual Cube        boundingBox() = 0;                          //retorna a boudingbox do objeto
    virtual Vec4        getMax() = 0;                               //retorna o extremo máximo do objeto, não necessariamente este ponto esta no objeto
    virtual Vec4        getMin() = 0;                               //retorna o extremo mínimo do objeto, não necessariamente este ponto esta no objeto
    virtual Vec4        getCenter() = 0;                            //retorna o ponto médio do objeto, não necessariamente este ponto esta no objeto
    virtual void        setMotion(Vec4) = 0;                        //seta uma posição para o objeto
    virtual Vec4        getMotion() = 0;                            //extrai a posição do objeto
    virtual bool        getEnabledTexture() = 0;                    //habilita o uso da textura
    virtual void        setEnabledTexture(bool) = 0;                //seta se a textura esta habilitada ou não
    virtual void        setTexture(Texture*) = 0;                   //esta função deleta as texturas anteriores e adiciona a textura do parametro
    virtual void        addTexture(Texture*) = 0;                   //adiciona a testura ao objeto
    virtual void        removeTexture(Texture*) = 0;                //remove uma textura
    virtual int         getLenTexture() = 0;                        //retorna a quantidade de texturas do objeto
    virtual Texture*    getTexture(int) = 0;                        //retorna a textura de acordo com o indice

    virtual bool        getEnabledBump() = 0;                      //habilita o uso da textura
    virtual void        setEnabledBump(bool) = 0;                  //seta se a textura esta habilitada ou não
    virtual void        setBump(Bump*) = 0;                        //esta função deleta as texturas anteriores e adiciona a textura do parametro
    virtual void        addBump(Bump*) = 0;                        //adiciona a testura ao objeto
    virtual void        removeBump(Bump*) = 0;                     //remove uma textura
    virtual int         getLenBump() = 0;                          //retorna a quantidade de texturas do objeto
    virtual Bump*       getBump(int) = 0;                          //retorna a textura de acordo com o indice




};





#endif // OBJECT_H

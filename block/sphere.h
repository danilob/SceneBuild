#ifndef SPHERE_H
#define SPHERE_H

#include "object.h"
#include "structure/mesh.h"
#include "math/matrix4x4.h"
#include "cube.h"

#define SLICES 40 //linhas horizontais
#define STACKS 40 //linhas verticais

class Sphere: public Object
{
private:
    Vec4      vertexs[(SLICES*STACKS)+2];      //vertice corrente do objeto
    Vec4      initvertexs[(SLICES*STACKS)+2];  //vertices iniciais do objeto
    Vec4      normals[(SLICES*STACKS)+2];      //normal corrente do objeto
    Vec4      initnormals[(SLICES*STACKS)+1];  //normal inicial do objeto
    Mesh*     mesh;                            //estrutura de faces e vertices para o desenho
    Matrix4x4 transform;                       //matriz de transformação do objeto
    QString   name;                            //nome do objeto
    Vec4      motion;                          //efeito de translação motion blur do objeto
    bool      selected;                        //verifica se o objeto esta selecionado
    bool      enabled;                         //verifica se o objeto esta ativo
    //textura
    std::vector<Texture*> textures;
    std::vector<Bump*>    bumps;
    bool                  enable_bumping;
    bool                  enable_texture;

public:
    Sphere();
    ~Sphere();

    void      draw();
    void      refreshNormals();
    void      aplyTransform(Matrix4x4 t);
    void      setIdentityTransform();
    void      setMaterial(int material);
    void      wireframe();
    void      changeCoords(Matrix4x4 matrix);
    Mesh*     getMesh();
    void      setName(QString nm);
    QString   getName();
    int       getIdMaterial();
    void      tryIntersection(RayIntersection *intersect,Ray ray);
    void      setSelected(bool b);
    bool      isSelected();
    void      setEnabled(bool b);
    bool      isEnabled();
    Matrix4x4 getMatrixTransformation();
    int       getNumFaces();
    int       getNumVertexs();
    void      setTransform(Matrix4x4 m);
    QString   saveObject();
    Cube      boundingBox();
    Vec4      getMin();
    Vec4      getMax();
    Vec4      getCenter();
    void      refreshVertexs();
    void      setMotion(Vec4 m);
    Vec4      getMotion();
    bool      getEnabledTexture();
    void      setEnabledTexture(bool b);
    void      setTexture(Texture *tex);
    void      addTexture(Texture* tex);
    void      removeTexture(Texture* tex);
    int       getLenTexture();
    Texture*  getTexture(int i=0);
    bool      getEnabledBump();
    void      setEnabledBump(bool b);
    void      setBump(Bump* bump);
    void      addBump(Bump* bump);
    void      removeBump(Bump* bump);
    int       getLenBump();
    Bump*     getBump(int i);
    QString   getType();                              //tipo do objeto em string
    int       getTypeInt();                              //tipo do objeto em inteiro


};


#endif // SPHERE_H

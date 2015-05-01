#ifndef CUBE_H
#define CUBE_H
#include "object.h"
#include "math/matrix4x4.h"
#include "structure/mesh.h"
#include <vector>

class Cube: public Object
{
private:
    Vec4       vertexs[8];     //vertice corrente do objeto
    Vec4       initvertexs[8]; //vertices iniciais do objeto
    Vec4       normals[6];     //normal corrente do objeto
    Vec4       initnormals[6]; //normal inicial do objeto
    Mesh*      mesh;           //estrutura de faces e vertices para o desenho
    Matrix4x4  transform;      //matriz de transformação do objeto
    QString    name;           //nome do objeto
    Vec4       motion;         //efeito de translação motion blur do objeto
    bool       selected;       //verifica se o objeto esta selecionado
    bool       enabled;        //verifica se o objeto esta ativo

    //textura
    std::vector<Texture*> textures;
    std::vector<Bump*>    bumps;
    bool                  enable_bumping;
    bool                  enable_texture;

public:
    Cube();
    Cube(Vec4 min,Vec4 max, Vec4 center=Vec4());

    Cube       setCube(Vec4 min,Vec4 max);
    Cube       combineCube(Cube a,Cube b);
    Vec4       getMin();
    Vec4       getMax();
    void       draw();
    void       aplyTransform(Matrix4x4 t);
    void       refreshNormals();
    void       setIdentityTransform();
    void       setMaterial(int material);
    void       wireframe();
    void       changeCoords(Matrix4x4 matrix);
    Mesh*      getMesh();
    void       setName(QString nm);
    QString    getName();
    int        getIdMaterial();
    void       tryIntersection(RayIntersection *intersect,Ray ray);
    void       setSelected(bool b);
    bool       isSelected();
    void       setEnabled(bool b);
    bool       isEnabled();
    Matrix4x4  getMatrixTransformation();
    int        getNumFaces();
    int        getNumVertexs();
    void       setTransform(Matrix4x4 m);
    QString    saveObject();
    Cube       boundingBox();
    Vec4       getCenter();
    void       refreshVertexs();
    Vec4       getMinInit();
    Vec4       getMaxInit();
    void       setMotion(Vec4 m);
    Vec4       getMotion();
    bool       getEnabledTexture();
    void      setEnabledTexture(bool b);
    void      setTexture(Texture *tex);
    void      addTexture(Texture* tex);
    void      removeTexture(Texture* tex);
    int       getLenTexture();
    Texture*  getTexture(int i);
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


#endif // CUBE_H

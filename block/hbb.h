#ifndef HBB_H
#define HBB_H
#include "object.h"
#include "cube.h"
#include "math/rayintersection.h"
#include <vector>
class HBB: public Object
{
private:
    Object*               left;
    Object*               right;
    HBB*                  left_node;
    HBB*                  right_node;
    Cube                  box;

public:
     HBB();
     HBB(std::vector<Object*> objects,int axis); //constroi a estrutura
     ~HBB();
     bool                 hit(RayIntersection *intersect);                                      //verifica houve interseção do raio com a box
     std::vector<Object*> sortObjects(std::vector<Object*> objects,int axis);                   //ordena os objetos de acordo com seu ponto médio
     void                 drawStructure();                                                      //desenha a estrutura de HBB
     bool                 hitBox(Ray r,Matrix4x4 transform);                                    //verifica houve interseção do raio com a box
     bool                 HBBIntersection(RayIntersection *intersect,Ray ray,Object *obj=NULL); //verifica houve interseção do raio com a box na recursão
     Matrix4x4            getMatrixTransformation();


     //funções abaixo não tem significado para esta classe, mas devido a herança estamos a mantendo.
     void                 wireframe();
     void                 setSelected(bool);
     bool                 isSelected();
     void                 setEnabled(bool);
     bool                 isEnabled();
     void                 setMaterial(int);
     Mesh*                getMesh();
     void                 setTransform(Matrix4x4);
     QString              getName();
     void                 setName(QString);
     int                  getNumFaces();
     int                  getNumVertexs();
     int                  getIdMaterial();
     void                 tryIntersection(RayIntersection *,Ray);
     void                 draw();
     void                 refreshNormals();
     QString              saveObject();
     Cube                 boundingBox();
     Vec4                 getMax();
     Vec4                 getMin();
     Vec4                 getCenter();
     void                 setMotion(Vec4);
     Vec4                 getMotion();
     bool      getEnabledTexture();
     void      setEnabledTexture(bool b);
     void      setTexture(Texture *tex);
     void      addTexture(Texture* tex);
     void      removeTexture(Texture* tex);
     int       getLenTexture();
     Texture*  getTexture(int i);
     bool      getEnabledBump();
     void      setEnabledBump(bool);
     void      setBump(Bump*);
     void      addBump(Bump*);
     void      removeBump(Bump*);
     int       getLenBump();
     Bump*     getBump(int);
     QString   getType();                              //tipo do objeto em string
     int       getTypeInt();                              //tipo do objeto em inteiro
};

#endif // HBB_H

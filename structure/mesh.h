#ifndef STRUCTURE_H
#define STRUCTURE_H
#include "math/vec4.h"
#include "math/matrix4x4.h"
#include "extra/material.h"
#include <vector>


struct Face{
    std::vector<Vec4*> vertexs;
    std::vector<Vec4*> normals;
    //Vec4* textureCoord[3];

};


class Mesh
{
public:
    std::vector<Vec4> normals;
    std::vector<Face> faces;
    Material *material;
    int id_material;

public:
    Mesh();
    ~Mesh();
    void           draw();
    //void drawNormalFace(); //tentar fazer depois
    void           setMaterial(int type=0);          //setar a propriedade de material do mesh
    void           setMaterial(Vec4 amb,Vec4 diff,Vec4 spe,float shini, int val=0);
    void           setRefraction(float value);
    float          getRefraction();
    void           setReflection(float value);
    float          getReflection();

    void           setGlossyRefraction(float value);
    float          getGlossyRefraction();
    void           setGlossyReflection(float value);
    float          getGlossyReflection();

    void           setShininess(float shine);
    float          getShininess();
    void           drawNormalVertex();
    void           drawNormalFace(Face face);
    void           setMaterials();                   //desenhar o meterial
    static Vec4    getNormalFace(Face face);
    int            getMaterial();
    Material*      getMaterialM();




};


#endif // STRUCTURE_H

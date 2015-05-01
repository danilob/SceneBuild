#ifndef MATERIAL_H
#define MATERIAL_H
#include <GL/glut.h>
#include "math/vec4.h"
#include <QColor>
#define MATERIAL_NO_DEFINE      0
//tipos pedra
#define MATERIAL_EMERALD        1
#define MATERIAL_JADE           2
#define MATERIAL_OBSIDIAN       3
#define MATERIAL_PEARL          4
#define MATERIAL_RUBY           5
#define MATERIAL_TURQUOSIE      6
//tipos metal
#define MATERIAL_BRONZE         7
#define MATERIAL_BRONZE_POLIERT 8
#define MATERIAL_CHROME         9
#define MATERIAL_GOLD           10
#define MATERIAL_GOLD_POLIERT   11
#define MATERIAL_COPPER         12 //KUPFER
#define MATERIAL_COPPER_POLIERT 13 //KUPFER
#define MATERIAL_BRASS          14 //MESSING
#define MATERIAL_SILVER         15
#define MATERIAL_SILVER_POLIERT 16
#define MATERIAL_ZINN           17
//tipos kunstoff
#define MATERIAL_GUMMI          18
#define MATERIAL_PLASTIK        19

//cores
#define MATERIAL_BLACK_PLASTIC  20
#define MATERIAL_CYAN_PLASTIC   21
#define MATERIAL_GREEN_PLASTIC  22
#define MATERIAL_RED_PLASTIC    23
#define MATERIAL_WHITE_PLASTIC  24
#define MATERIAL_YELLOW_PLASTIC 25
#define MATERIAL_BLACK_RUBBER   26
#define MATERIAL_CYAN_RUBBER    27
#define MATERIAL_GREEN_RUBER    28
#define MATERIAL_RED_RUBBER     29
#define MATERIAL_WHITE_RUBBER   30
#define MATERIAL_YELLOW_RUBBER  31




class Material
{


public:
    float ambient[4];                   //constante ambiente do material
    float diffuse[4];                   //constante diffusa do material
    float specular[4];                  //constante especular do material
    float shininess;                    //brilho do material considerando de 0-1 padronizado para 128
    float refraction;
    float reflection;
    float glossyrefraction;
    float glossyreflection;
    //float refl;    /* reflection 0-1 */
    //float transp;  /* transparency 0-1 */

public:
    Material();
    Material(Vec4 amb,Vec4 diff,Vec4 spe,float shininess);


    Material*       getMaterial(int type);
    void static     setMaterial(Material *mat,Vec4 amb,Vec4 diff,Vec4 spe,float shini);
    void            setMaterial(Vec4 amb,Vec4 diff,Vec4 esp,float shini);
    void            setAmbienteMaterial(Vec4 amb);
    void            setDiffuseMaterial(Vec4 diff);
    void            setSpecularMaterial(Vec4 spe);
    void            setShininess(float shini);
    Vec4            getAmbiente();
    Vec4            getDiffuse();
    Vec4            getSpecular();
    float           getShininess();
    void            setRefraction(float value);
    float           getRefraction();
    void            setReflection(float value);
    float           getReflection();
    //efeito
    void            setGlossyRefraction(float value);
    float           getGlossyRefraction();
    void            setGlossyReflection(float value);
    float           getGlossyReflection();

    QColor          getColorAmbienteMaterial();
    QColor          getColorDiffuseMaterial();
    QColor          getColorSpecularMaterial();
    void            setMaterialOpenGL();


    void static     setMaterial(Material *mat,int type);
    void static     setMaterialOpenGL(int type);
    QColor static   getColorMaterial(int type);





};

#endif // MATERIAL_H

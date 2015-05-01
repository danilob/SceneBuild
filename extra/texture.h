#ifndef TEXTURE_H
#define TEXTURE_H
#include <GL/glut.h>
#include <string>
#include <QImage>
#include "math/vec4.h"

#define TYPE_ONLY_TEXTURE 0
#define TYPE_REPLACE_TEXTURE 1
#define TYPE_TEXTURE_BUMP 2
#define MAP_TILING 3
#define MAP_DEFAULT 4
#define PLANAR_MAPPING 5

class Texture
{
public:
    QImage *image;
    int  	type;	//tipo de uso da textura
    int     mapping; //informa o tipo de mapping se é tiling ou não
    QString path;
public:
    Texture();
    Texture(QImage* img,QString path);
    void setTypeMapping(int t_mapping);
    int  getTypeMapping();
    void setTypeTexture(int t_type);
    int  getTypeTexture();
    Vec4 getColorTexture(Vec4 map);
    Vec4 getColor(float x, float y);
    Vec4 sample(Vec4 val);
    QString getPath();
    void    setPath(QString path);


};

#endif // TEXTURE_H

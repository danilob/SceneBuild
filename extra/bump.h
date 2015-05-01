#ifndef BUMP_H
#define BUMP_H
/* Classe que define a textura do tipo bump mapping */
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

class Bump
{

public:
    QImage *image;
    QString path;
    int     mapping; //informa o tipo de mapping se é tiling ou não
public:
    Bump();
    Bump(QImage* img, QString path);
    void setTypeMapping(int t_mapping);
    int  getTypeMapping();
    Vec4 getColorBump(Vec4 map);
    Vec4 getColorNormalBump(Vec4 normal,Vec4 map);
    Vec4 getColorPointBump(Vec4 normal,Vec4 map,Vec4 pit);
    Vec4 getColor(float x, float y);
    Vec4 sample(Vec4 val);
    QString getPath();
    void    setPath(QString path);
};

#endif // BUMP_H

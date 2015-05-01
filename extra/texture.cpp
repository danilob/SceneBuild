#include "texture.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <QRgb>
#define DELTA 0.001
Texture::Texture()
{
    this->type = TYPE_ONLY_TEXTURE;
    this->mapping = MAP_DEFAULT;

}

Texture::Texture(QImage *img,QString path)
{
    image = img;
    this->path = path;
    this->type = TYPE_ONLY_TEXTURE;
    this->mapping = MAP_DEFAULT;

}

void Texture::setTypeMapping(int t_mapping)
{
    this->mapping = t_mapping;
}

int Texture::getTypeMapping()
{
    return this->mapping;
}

void Texture::setTypeTexture(int t_type)
{
    this->type = t_type;
}

int Texture::getTypeTexture()
{
    return this->type;
}

Vec4 Texture::getColorTexture(Vec4 map)
{
    QRgb color = image->pixel(map.x()*image->width(),map.y()*image->height());
    return Vec4(qRed(color)/255.0,qGreen(color)/255.0,qBlue(color)/255.0);
}


Vec4 Texture::getColor(float x, float y)
{
    QRgb color = image->pixel(x*image->width(),y*image->height());
    return  Vec4(qRed(color)/255.0,qGreen(color)/255.0,qBlue(color)/255.0);

}


Vec4 Texture::sample(Vec4 val)
{
    QRgb color = image->pixel(fmin(val.x()*image->width(),image->width()-1),fmin(val.y()*image->height(),image->height()-1));
    return  Vec4(qRed(color),qGreen(color),qBlue(color));
}

QString Texture::getPath()
{
    return this->path;
}

void Texture::setPath(QString path)
{
    this->path = path;
}



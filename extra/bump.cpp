#include "bump.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <QRgb>
#define DELTA 0.00001
Bump::Bump()
{
    this->mapping = MAP_DEFAULT;

}

Bump::Bump(QImage *img, QString path)
{
    image = img;
    this->path = path;
    this->mapping = MAP_DEFAULT;

}

void Bump::setTypeMapping(int t_mapping)
{
    this->mapping = t_mapping;
}

int Bump::getTypeMapping()
{
    return this->mapping;
}

Vec4 Bump::getColorBump(Vec4 map)
{
    QRgb color = image->pixel(map.x()*image->width(),map.y()*image->height());
    return Vec4(qRed(color)/255.0,qGreen(color)/255.0,qBlue(color)/255.0);
}

Vec4 Bump::getColorNormalBump(Vec4 n, Vec4 map)
{

    Vec4 normal = (Vec4(map.x(),0,0)^Vec4(0,map.y(),0));
    Vec4 A = (normal ^ Vec4(1,0,0));
    Vec4 B = (normal ^ A);

//    QRgb color = image->pixel(map.x()*image->width(),map.y()*image->height());
//    Vec4 bump1 =  Vec4(qRed(color)/255.0,qGreen(color)/255.0,qBlue(color)/255.0);
//    Vec4 map2 = Vec4(1-map.x(),1-map.y());
//    //map = Vec4(map.x(),0);

//    //QRgb color = image->pixel(map.x()*image->width(),map.y()*image->height());
//    //Vec4 bump2 =  Vec4(qRed(color)/255.0,qGreen(color)/255.0,qBlue(color)/255.0);
//    //Vec4 bu = Vec4(bump1.x());
//    //Vec4 bv = Vec4(0,bump1.y());
//    Vec4 bu = (getColor(map2.x(),map.y()) - getColor(map.x(),map.y())+getColor(map2.x(),map2.y())-getColor(map.x(),map2.y()))/(2*((Vec4(map2.x())+Vec4(map.x())).module()));
//    Vec4 bv = (getColor(map.x(),map2.y()) - getColor(map.x(),map.y())+getColor(map2.x(),map2.y())-getColor(map2.x(),map.y()))/(2*((Vec4(0,map2.y())+Vec4(0,map.y())).module()));
//    //Vec4 D = (bu.mult(A) - bv.mult(B));
//    Vec4 D = bv.mult((A^n)/n.module()) + bu.mult((n^B)/n.module());
//    return (n + D);
    float u = map.x(), v = map.y();
        //Normalized distance between texels.
    float tex_dist_u = 1.0/this->image->width();
    float tex_dist_v = 1.0/this->image->height();
    Vec4 du;
    //Checking the boundary conditions. The gradient on the borders
    //is the same point.
    if(u-tex_dist_u < DELTA)
      du = this->sample(Vec4(u,v)) -
        this->sample(Vec4(u + tex_dist_u, v));
    else if(u+tex_dist_u > 1+DELTA)
      du = this->sample(Vec4(u - tex_dist_u,v)) -
        this->sample(Vec4(u, v));
    //If we are at any central point, then compute the gradient as usual.
    else
      du = this->sample(Vec4(u - tex_dist_u,v)) -
        this->sample(Vec4(u + tex_dist_u, v));

    Vec4 dv;
    //Checking the boundary conditions.
    if(v-tex_dist_v < DELTA)
      dv = this->sample(Vec4(u,v + tex_dist_v)) -
        this->sample(Vec4(u, v));
    else if(v+tex_dist_v > 1+DELTA)
      dv = this->sample(Vec4(u,v)) -
        this->sample(Vec4(u, v - tex_dist_v));
    else
      dv = this->sample(Vec4(u,v + tex_dist_v)) -
        this->sample(Vec4(u, v - tex_dist_v));

    //Gray color of the gradient is normalized, i.e., average gray value.
    float u_val = (du.x() + du.y() + du.z())/3.0;
    float v_val = (dv.x() + dv.y() + dv.z())/3.0;

    //The bump intensity, as well as the average of the difference
    //(which was missing above).
    u_val *= 0.5;
    v_val *= 0.5;
    Vec4 D = ((A^normal)/normal.module())*v_val + ((normal^B)/normal.module())*u_val;
    //Vec4 D = ((A))*v_val*0.5 + ((B))*u_val*0.5;

    return (n + D).unitary();

}

Vec4 Bump::getColorPointBump(Vec4 normal, Vec4 map, Vec4 pit)
{

    normal = (Vec4(map.x(),0,0)^Vec4(0,map.y(),0));
    Vec4 A = (normal ^ Vec4(1,0,0));
    Vec4 B = (normal ^ A);
    float u = map.x(), v = map.y();
        //Normalized distance between texels.
    float tex_dist_u = 1.0/this->image->width();
    float tex_dist_v = 1.0/this->image->height();
    Vec4 du;
    //Checking the boundary conditions. The gradient on the borders
    //is the same point.
    if(u-tex_dist_u < DELTA)
      du = this->sample(Vec4(u,v)) -
        this->sample(Vec4(u + tex_dist_u, v));
    else if(u+tex_dist_u > 1)
      du = this->sample(Vec4(u - tex_dist_u,v)) -
        this->sample(Vec4(u, v));
    //If we are at any central point, then compute the gradient as usual.
    else
      du = this->sample(Vec4(u - tex_dist_u,v)) -
        this->sample(Vec4(u + tex_dist_u, v));

    Vec4 dv;
    //Checking the boundary conditions.
    if(v-tex_dist_v < DELTA)
      dv = this->sample(Vec4(u,v + tex_dist_v)) -
        this->sample(Vec4(u, v));
    else if(v+tex_dist_v > 1)
      dv = this->sample(Vec4(u,v)) -
        this->sample(Vec4(u, v - tex_dist_v));
    else
      dv = this->sample(Vec4(u,v + tex_dist_v)) -
        this->sample(Vec4(u, v - tex_dist_v));

    //Gray color of the gradient is normalized, i.e., average gray value.
    float u_val = (du.x() + du.y() + du.z())/3.0;
    float v_val = (dv.x() + dv.y() + dv.z())/3.0;

    //The bump intensity, as well as the average of the difference
    //(which was missing above).
    u_val *= 0.5;
    v_val *= 0.5;
    //QRgb color = image->pixel(map.x()*image->width(),map.y()*image->height());
    //Vec4 bump1 =  Vec4(qRed(color)/255.0,qGreen(color)/255.0,qBlue(color)/255.0);
    return pit + ((A^normal)/normal.module())*v_val + ((normal^B)/normal.module())*u_val;

}

Vec4 Bump::getColor(float x, float y)
{
    QRgb color = image->pixel(x*image->width(),y*image->height());
    return  Vec4(qRed(color)/255.0,qGreen(color)/255.0,qBlue(color)/255.0);

}


Vec4 Bump::sample(Vec4 val)
{
    QRgb color = image->pixel(fmin(val.x()*image->width(),image->width()),fmin(val.y()*image->height(),image->height()));
    return  Vec4(qRed(color),qGreen(color),qBlue(color));
}

QString Bump::getPath()
{
    return this->path;
}

void Bump::setPath(QString path)
{
    this->path = path;
}



#include "raycasting.h"
#include "interface/scene.h"
#include "math/ray.h"
#include "block/object.h"
#include "structure/light.h"
#include "rayintersection.h"

#define ERROR 0.001
#include "interface/castingwidget.h"
static int intersect =0;
static int notintersect =0;
#include <stdio.h>
#include <stdlib.h> // RAND_MAX é definido em stdlib.h

#define myrand ((float)(random())/(float)(RAND_MAX) )

RayCasting::RayCasting()
{
    this->scene = NULL;
    this->raycast = NULL;
}

RayCasting::RayCasting(Scene *sc,CastingWidget *rcast,Vec4 color,bool otimized)
{
    this->scene = sc;
    this->raycast = rcast;
    this->backgroundcolor = color;
    this->otimized = otimized;
}

void RayCasting::setScene(Scene *scene)
{
    this->scene = scene;
}

void RayCasting::rayCasting(GLubyte *pixels)
{
    //pixels = new GLubyte [(int)scene->viewport[0]*(int)scene->viewport[1]*3];
    srandom(time(NULL));
    Matrix4x4 changetoviewer;
    changetoviewer.setIdentity();
    Vec4 kv,iv,jv,kvl,ivl,jvl;
    kv = (scene->viewer[0] - scene->viewer[1])/((scene->viewer[0] - scene->viewer[1]).module());
    iv = (scene->viewer[2] ^ kv)/(scene->viewer[2] ^ kv).module();
    jv = (kv ^ iv)/(kv ^ iv).module();
    ivl.setVec4(iv.x1,jv.x1,kv.x1);
    jvl.setVec4(iv.x2,jv.x2,kv.x2);
    kvl.setVec4(iv.x3,jv.x3,kv.x3);
    Vec4 translate(-(iv*scene->viewer[0]),-(jv*scene->viewer[0]),-(kv*scene->viewer[0]));

    changetoviewer.setAxisX(iv);
    changetoviewer.setAxisY(jv);
    changetoviewer.setAxisZ(kv);
    changetoviewer.setTranslate(translate);

    //changetoviewer.showMatrix4x4();
    //changetoviewer.transpose().vector(Vec4(0,0,0)).showVec4();
    changetoviewer = changetoviewer.transpose();
    changetoviewer.setTranslate(scene->viewer[0]);


    Vec4 color[scene->viewport[0]*scene->viewport[1]];


    float h = 2.0*scene->projection.x3*(tan(M_PI*scene->projection.x1/360.0));
    float w = h*scene->projection.x2;
    float deltax = w/scene->viewport[0];
    float deltay = h/scene->viewport[1];
    notintersect = 0;
    intersect = 0;
    int count = 0;
    int soft = 20;
    for(int j=0;j<scene->viewport[1];j++)
        for (int i=0;i<scene->viewport[0];i++){
            Vec4 rays_color;
            for(int k=0;k<soft;k++){
                float alfa,beta;
                if(k==0){
                    alfa  = -w/2.0 + deltax/2.0  + i*deltax;
                    beta  = -h/2.0 + deltay/2.0 + j*deltay;
                }else{
                    alfa  = -w/2.0 + deltax*myrand  + i*deltax;
                    beta  = -h/2.0 + deltay*myrand + j*deltay;
                }

                Vec4 dir(alfa,beta,-scene->projection.x3);
                Ray ray(changetoviewer.transpose().vector(Vec4(0,0,0)),changetoviewer.transpose().vector(dir));
                ray.setDirection((ray.direction - ray.origin).unitary());
                rays_color = rays_color + rayIntersection(ray);
            }
            count++;
            raycast->setValueProgress(count);
            rays_color = rays_color / soft;
            color[(scene->viewport[0]*j)+(i)] = rays_color;
//            if (otimized) color[(scene->viewport[0]*j)+(i)] = rayIntersection(ray);
//            else color[(scene->viewport[0]*j)+(i)] = rayIntersectionNotOtimized(ray);
        }

    for(int i=0;i<scene->viewport[0]*scene->viewport[1];i++){
        pixels[3*i]   = ((int)(color[i].x1*255))%256;
        pixels[3*i+1] = ((int)(color[i].x2*255))%256;
        pixels[3*i+2] = ((int)(color[i].x3*255))%256;
    }
    //printf("hits: %d",hit);

}


Vec4 RayCasting::calculatePixelColorNotOtimized(Face face, Material* material, Vec4 intercept, std::vector<Light*> lights)
{
    Vec4 normal;
    if(face.normals.size()==1){
        normal = Mesh::getNormalFace(face); //normal a face
    }else{
        for(int i=0;i<face.normals.size();i++){
            Vec4 aux(face.normals[i]->x1,face.normals[i]->x2,face.normals[i]->x3);
            normal = normal + aux;

        }
        normal = normal / face.normals.size();
        normal = normal.unitary();
    }
    Vec4 color = Vec4(0,0,0);

    for (int i=1;i<scene->lights.size();i++){
        if (scene->lights.at(i)->isEnabled())
            color = color + scene->lights.at(i)->calculateColor(intercept,normal,scene->viewer[0],material,Vec4());
    }
    color = color + scene->lights.at(0)->calculateColor(intercept,normal,scene->viewer[0],material,Vec4());
    color.x1 = fmin(color.x1,1.0);
    color.x2 = fmin(color.x2,1.0);
    color.x3 = fmin(color.x3,1.0);
    return color;


}
Vec4 RayCasting::rayIntersection(Ray ray)
{

        RayIntersection *ray_intersection = new RayIntersection();
        ray_intersection->t = scene->projection.x4;
        ray_intersection->tmin = scene->projection.x3;
        for(int i=0;i<scene->objects.size();i++){

            if(scene->objects.at(i)->isEnabled())   scene->objects.at(i)->tryIntersection(ray_intersection,ray);

        }
        if (!(ray_intersection->t!=scene->projection.x4)){
            notintersect++;
            raycast->setValueNotIntersectRay(notintersect);
            return this->backgroundcolor;
        }else{
            intersect++;
            raycast->setValueIntersectRay(intersect);
            return calculatePixelColor(ray_intersection->normal,ray_intersection->material,ray.positionRay(ray_intersection->t));
        }
}

float RayCasting::getRayInterceptionFace(Face face,Ray ray)
{
    Vec4 p1(face.vertexs[0]->x1,face.vertexs[0]->x2,face.vertexs[0]->x3);
    Vec4 n = Mesh::getNormalFace(face);


    float t_ = (n*p1 - ray.origin*n)/(n*(ray.direction));

    if (t_>=0.01 && t_<1200000.0){
        if (tryInterceptionPointFace(face,ray.positionRay(t_))){
            return t_;
        }else{
            return -1;
        }
    }
    return t_;
}

bool RayCasting::tryInterceptionPointFace(Face face, Vec4 point)
{
    Vec4 a,b,c; //coordenadas do triangulo
    Vec4 n = Mesh::getNormalFace(face);
    for(int i=0;i<face.vertexs.size()-2;i++){
        a.setVec4(face.vertexs.at(0)->x1,face.vertexs.at(0)->x2,face.vertexs.at(0)->x3);
        b.setVec4(face.vertexs.at(i+1)->x1,face.vertexs.at(i+1)->x2,face.vertexs.at(i+1)->x3);
        c.setVec4(face.vertexs.at(i+2)->x1,face.vertexs.at(i+2)->x2,face.vertexs.at(i+2)->x3);
        if (Vec4::crossProduct((b-a),(point-a))*n > 0 && Vec4::crossProduct((c-b),(point-b))*n > 0 && Vec4::crossProduct((a-c),(point-c))*n > 0) return true;

    }
    return false;
}

Vec4 RayCasting::calculatePixelColor(Vec4 normal, Material *material, Vec4 intercept)
{

        Vec4 color = Vec4(0,0,0);
        //double fator =1.0;
        for (int i=1;i<scene->lights.size();i++){
            if (scene->lights.at(i)->isEnabled())
                color = color + scene->lights.at(i)->calculateColor(intercept,normal,scene->viewer[0],material,Vec4());
        }
        color = color + scene->lights.at(0)->calculateColor(intercept,normal,scene->viewer[0],material,Vec4());
        color.x1 = fmin(color.x1,1.0);
        color.x2 = fmin(color.x2,1.0);
        color.x3 = fmin(color.x3,1.0);
        return color;
}



Vec4 RayCasting::rayIntersectionNotOtimized(Ray ray)
{
    float t = INFINITY;
    Face face;
    Material *mat;
    Vec4 v(0,0,0,-1);
    for(int i=0;i<scene->objects.size();i++){
        if(scene->objects.at(i)->isEnabled())
            for(int j=0;j<scene->objects.at(i)->getMesh()->faces.size();j++){
                float tl = getRayInterceptionFace(scene->objects.at(i)->getMesh()->faces.at(j),ray);
                if(tl<t && tl>=0.01){
                    t = tl;
                    v.setVec4(ray.positionRay(t).x(),ray.positionRay(t).y(),ray.positionRay(t).z(),1);
                    face = (scene->objects.at(i)->getMesh()->faces.at(j));
                    mat = mat->getMaterial(scene->objects.at(i)->getIdMaterial());
                }
            }
    }
    if(v.x4==1){
        intersect++;
        raycast->setValueIntersectRay(intersect);
        return calculatePixelColorNotOtimized(face,mat,ray.positionRay(t),scene->lights);
    }else{
        notintersect++;
        raycast->setValueNotIntersectRay(notintersect);
        return this->backgroundcolor;
    }
}


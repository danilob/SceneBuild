#include "rayintersection.h"
#include "block/object.h"
#include "math/ray.h"
#define APROXIMATE 0.0001
bool teste = true;

//calculo para interseção ray-plane limitado
bool tryInterceptionPointFace(Face face, Vec4 point)
{
        Vec4 a,b,c,n; //coordenadas do triangulo
        for(int i=0;i<face.vertexs.size()-2;i++){
            n.setVec4(face.normals.at(0)->x1,face.normals.at(0)->x2,face.normals.at(0)->x3);
            a.setVec4(face.vertexs.at(0)->x1,face.vertexs.at(0)->x2,face.vertexs.at(0)->x3);
            b.setVec4(face.vertexs.at(i+1)->x1,face.vertexs.at(i+1)->x2,face.vertexs.at(i+1)->x3);
            c.setVec4(face.vertexs.at(i+2)->x1,face.vertexs.at(i+2)->x2,face.vertexs.at(i+2)->x3);
            if (Vec4::crossProduct((b-a),(point-a))*n >= 0 && Vec4::crossProduct((c-b),(point-b))*n >= 0 && Vec4::crossProduct((a-c),(point-c))*n >= 0) return true;

        }
        return false;
}





RayIntersection::RayIntersection()
{
    this->t=INFINITY;
    this->tmin=0;
    this->normal = Vec4(0,0,0);
    //this->obj = NULL;
    //this->material = NULL;
    //this->obj = NULL;


}

void RayIntersection::rayBoxIntersection(Mesh *mesh, Ray ray, Matrix4x4 transform,Vec4 max, Vec4 min,Object *obj)
{
    Vec4 bounds[2];
    bounds[0] = min;//Vec4(-0.5,-0.5,-0.5);
    bounds[1] = max;//Vec4(0.5,0.5,0.5);
    Ray copy;
    copy.setOrigin(transform.transform_origin_ray(transform,ray.origin));
    copy.setDirection(transform.transform_direction_ray(transform,ray.direction));
    float tmin, tmax, tymin, tymax, tzmin, tzmax;
    tmin = (bounds[copy.sign[0]].x() - copy.origin.x()) * copy.inverse_direction.x();
    tmax = (bounds[1-copy.sign[0]].x() - copy.origin.x()) * copy.inverse_direction.x();
    tymin = (bounds[copy.sign[1]].y() - copy.origin.y()) * copy.inverse_direction.y();
    tymax = (bounds[1-copy.sign[1]].y() - copy.origin.y()) * copy.inverse_direction.y();
    if ( (tmin > tymax) || (tymin > tmax) )
        return ;
    if (tymin > tmin)
        tmin = tymin;
    if (tymax < tmax)
        tmax = tymax;
    tzmin = (bounds[copy.sign[2]].z() - copy.origin.z()) * copy.inverse_direction.z();
    tzmax = (bounds[1-copy.sign[2]].z() - copy.origin.z()) * copy.inverse_direction.z();
    if ( (tmin > tzmax) || (tzmin > tmax) )
        return ;
    if (tzmin > tmin)
        tmin = tzmin;
    if (tzmax < tmax)
        tmax = tzmax;
    if (!( (tmin < t) && (tmax > tmin) )) return;

    for (int i=0;i<mesh->faces.size();i++){
        Vec4 p1,n;
        p1.setVec4(mesh->faces.at(i).vertexs[0]->x1,mesh->faces.at(i).vertexs[0]->x2,mesh->faces.at(i).vertexs[0]->x3);
        n.setVec4(mesh->faces.at(i).normals[0]->x(),mesh->faces.at(i).normals[0]->y(),mesh->faces.at(i).normals[0]->z());
        if ((!(fabs(n*(ray.direction))<APROXIMATE))){
            float t_ = (n*p1 - ray.origin*n)/(n*(ray.direction));
            if((t_<this->t) && t_>this->tmin){
                if (tryInterceptionPointFace(mesh->faces.at(i),ray.positionRay(t_))){
                    this->t = t_;
                    this->normal = n.unitary();
                    this->material = mesh->material;
                    if (obj->getLenTexture()>0||obj->getLenBump()>0 ){
                        if(obj->getLenTexture()>0){
                            if(mesh->faces.at(i).vertexs.size()==4)
                                this->mapping = mappingPlanar4(mesh->faces.at(i),ray.positionRay(t_),obj->getTexture(0));
                            if(mesh->faces.at(i).vertexs.size()==3)
                                this->mapping = mappingPlanar3(mesh->faces.at(i),ray.positionRay(t_),obj->getTexture(0));
                        }else{
                            if(mesh->faces.at(i).vertexs.size()==4)
                                this->mapping = mappingPlanar4(mesh->faces.at(i),ray.positionRay(t_),NULL);
                            if(mesh->faces.at(i).vertexs.size()==3)
                                this->mapping = mappingPlanar3(mesh->faces.at(i),ray.positionRay(t_),NULL);
                        }
                    }
                    this->obj = obj;
                }
            }
        }


    }
}

void RayIntersection::rayPlanIntersection(Mesh *mesh, Ray ray, Object *obj)
{
    Vec4 p1,n;
    p1.setVec4(mesh->faces.at(0).vertexs[0]->x1,mesh->faces.at(0).vertexs[0]->x2,mesh->faces.at(0).vertexs[0]->x3);
    n.setVec4(mesh->faces.at(0).normals[0]->x(),mesh->faces.at(0).normals[0]->y(),mesh->faces.at(0).normals[0]->z());
    if ((!(fabs(n*(ray.direction))<APROXIMATE))){
        float t_ = (n*p1 - ray.origin*n)/(n*(ray.direction));
        if((t_<this->t) && t_>this->tmin){
            if (tryInterceptionPointFace(mesh->faces.at(0),ray.positionRay(t_))){
                this->t = t_;
                this->normal = n.unitary();
                this->material = mesh->material;
                this->obj = obj;
            }
        }
    }
}

void RayIntersection::rayCylinderIntersection(Mesh *mesh,Matrix4x4 transform, Ray ray, Object *obj)
{

    Ray ray_copy;
    Ray line(Vec4(0,0.0,0),Vec4(0,1,0));

    ray_copy.setOrigin(transform.transform_origin_ray(transform,ray.origin));
    ray_copy.setDirection(transform.transform_direction_ray(transform,ray.direction));


    Vec4 cl = line.origin - line.direction*(line.origin*line.direction);
    Vec4 pl = ray_copy.origin - line.direction*(ray_copy.origin*line.direction);
    Vec4 dl = ray_copy.direction - line.direction*(ray_copy.direction*line.direction);

    float a,b,c,delta;

    a = dl*dl;
    b = (pl*dl - cl*pl)*2;
    c = pl*pl -2*(pl*cl) - cl*cl - 1.0;


        delta = b*b - 4*a*c;
        if (delta<0.0) return;
        float t0,t1;
        t0 = (-b-sqrt(delta))/(2*a);
        t1 = (-b+sqrt(delta))/(2*a);
        if (t1<t0){
            float aux;
            aux = t0;
            t0 = t1;
            t1 = aux;

        }
        if(t0<0.0) return;
        Vec4 auxp = Vec4();
        Vec4 pos = ray_copy.positionRay(t0);
        Vec4 lin = line.positionRay(sqrt(pow((pos-Vec4(0,0,0)).module(),2)-1));
        Vec4 n = (pos-Vec4(0,0,0)) - lin*(pos*lin);
        n = n.unitary();
        if(obj->getLenTexture()>0||obj->getLenBump()>0){
            auxp = mappingCylinderLateral(pos,NULL);
        }
        //

        if(pos.x2>1){
            n = Vec4(0,1,0);
            float est = (n*Vec4(0,1,0) - ray_copy.origin*n)/(n*(ray_copy.direction));
            if (est<0.0) return;
            Vec4 posi = ray_copy.positionRay(est);
            if (((posi.x()*posi.x() + posi.z()*posi.z())<=1)){
                t0 = est;
                pos = posi;
                if(obj->getLenTexture()>0||obj->getLenBump()>0){
                    auxp = mappingCylinderCap(pos,NULL);
                }
            }else{
                return;
            }
        }
        if(pos.x2<0){
            n = Vec4(0,-1,0);
            float est = (n*Vec4(0,0,0) - ray_copy.origin*n)/(n*(ray_copy.direction));
            if (est<0.0) return;
            Vec4 posi = ray_copy.positionRay(est);
            if (((posi.x()*posi.x() + posi.z()*posi.z())<=1)){
                t0 = est;
                pos = posi;
                if(obj->getLenTexture()>0){
                    auxp = mappingCylinderCap(pos,NULL);
                }
            }else{
                return;
            }
        }


        pos = transform.transform_position_ray(transform,pos);
        n =  transform.transform_normal_ray(transform,n);
        t0 = (pos - ray.origin).module();


        if (t0<t && t0>tmin){
            t = t0;
            this->normal = n.unitary();
            this->material = mesh->material;
            this->obj = obj;
            if(obj->getLenTexture()>0||obj->getLenBump()>0) this->mapping = auxp;
        }


}

void RayIntersection::rayConeIntersection(Mesh *mesh, Matrix4x4 transform, Ray ray, Object *obj)
{
    Ray copy;
    copy.setOrigin(transform.transform_origin_ray(transform,ray.origin));
    copy.setDirection(transform.transform_direction_ray(transform,ray.direction));
    float a,b,c,delta,t0,t1,t_;
    a = copy.direction.x()*copy.direction.x() + copy.direction.z()*copy.direction.z() - copy.direction.y()*copy.direction.y();
    b = 2*copy.origin.x()*copy.direction.x() + 2*copy.direction.y() - 2*copy.origin.y()*copy.direction.y() + 2*copy.origin.z()*copy.direction.z();
    c = copy.origin.x()*copy.origin.x() - copy.origin.y()*copy.origin.y() + 2*copy.origin.y() + copy.origin.z()*copy.origin.z() - 1.0;

//    a = copy.direction.x()*copy.direction.x() + copy.direction.z()*copy.direction.z() - copy.direction.y()*copy.direction.y()/4.0;
//    b = 2*copy.origin.x()*copy.direction.x() - copy.origin.y()*copy.direction.y()/2.0 + copy.direction.y()/4.0 + 2*copy.origin.z()*copy.direction.z();
//    c = copy.origin.x()*copy.origin.x() - copy.origin.y()*copy.origin.y()/4.0 + copy.origin.y()/4.0 + 1.0/16.0 + copy.origin.z()*copy.origin.z();

    delta = b*b - 4*a*c;
    Vec4 pos,n;
    if (delta<0.0){
       return;

    }else{
    t0 = (-b - sqrt(delta))/(2*a);
    t1 = (-b + sqrt(delta))/(2*a);
    t_ = fmin(t0,t1);
    pos = copy.positionRay(t_);
    n   = pos.unitary();
    }
    Vec4 auxp = Vec4();
    if(obj->getLenTexture()>0||obj->getLenBump()>0){
        auxp = mappingCylinderLateral(pos,NULL);
    }
    if(pos.y()<=0){
        n = Vec4(0,-1,0);
        float est = (n*Vec4(0,0,0) - copy.origin*n)/(n*(copy.direction));
        if (est<0.0) return;
        Vec4 posi = copy.positionRay(est);
        if (((posi.x()*posi.x() + posi.z()*posi.z())<=1)){
            t0 = est;
            pos = posi;

            if(obj->getLenTexture()>0||obj->getLenBump()>0){
                auxp = mappingCylinderCap(pos,NULL);
            }
        }else{
            return;
        }
    }
    if (pos.y()>1.0) return;
    pos = transform.transform_position_ray(transform,pos);
    n = transform.transform_normal_ray(transform,n);
    t_ = (pos - ray.origin).module();
    if (t_<t && t_>tmin) {
        this->t = t_;
        this->normal = n.unitary();
        this->material = mesh->material;
        this->obj = obj;
        if(obj->getLenTexture()>0 || obj->getLenBump()>0) this->mapping = auxp;
    }

}

void RayIntersection::raySphereIntersection(Mesh *mesh, Matrix4x4 transform, Ray ray,Object *obj)
{

    Ray copy;
    copy.setOrigin(transform.transform_origin_ray(transform,ray.origin));
    copy.setDirection(transform.transform_direction_ray(transform,ray.direction));
    float a,b,c,delta,t0,t1,t_;
    c = copy.origin.x()*copy.origin.x() + copy.origin.y()*copy.origin.y() + copy.origin.z()*copy.origin.z() -1;
    b = 2*copy.origin.x()*copy.direction.x() + 2*copy.origin.y()*copy.direction.y() + 2*copy.origin.z()*copy.direction.z();
    a = copy.direction.x()*copy.direction.x() + copy.direction.y()*copy.direction.y() + copy.direction.z()*copy.direction.z();

    delta = b*b - 4*a*c;
    Vec4 pos,auxp,n;
    if (delta<0.0){

       return;

    }else{
    t0 = (-b - sqrt(delta))/(2*a);
    t1 = (-b + sqrt(delta))/(2*a);
    t_ = fmin(t0,t1);
    pos = copy.positionRay(t_);
    auxp = pos;
    n   = pos;

    }/*
    if (pos.x2 <APROXIMATE){
        n = Vec4(0,-1,0);
        float est = (n*Vec4(0,0,0) - copy.origin*n)/(n*(copy.direction));
        if (est<APROXIMATE) return;
        Vec4 posi = copy.positionRay(est);
        if (((posi.x()*posi.x() + posi.z()*posi.z())<=1)){
            t_ = est;
            pos = posi;
        }else{
            return;
        }
    }
    }*/



    //qDebug() << "Here";
    pos.showVec4();
    pos = transform.transform_position_ray(transform,pos);
    n = transform.transform_normal_ray(transform,n);
    t_ = (pos - ray.origin).module();
    if (t_<t && t_>tmin) {
        this->t = t_;
        this->normal = n.unitary();
        this->material = mesh->material;
        this->obj = obj;
        if(obj->getLenTexture()>0||obj->getLenBump()>0) this->mapping = mappingSpheric(auxp,NULL);
    }



}

void RayIntersection::rayHemiSphereIntersection(Mesh *mesh, Matrix4x4 transform, Ray ray, Object *obj)
{
    Ray copy;
    copy.setOrigin(transform.transform_origin_ray(transform,ray.origin));
    copy.setDirection(transform.transform_direction_ray(transform,ray.direction));
    float a,b,c,delta,t0,t1,t_;
    c = copy.origin.x()*copy.origin.x() + copy.origin.y()*copy.origin.y() + copy.origin.z()*copy.origin.z() -1;
    b = 2*copy.origin.x()*copy.direction.x() + 2*copy.origin.y()*copy.direction.y() + 2*copy.origin.z()*copy.direction.z();
    a = copy.direction.x()*copy.direction.x() + copy.direction.y()*copy.direction.y() + copy.direction.z()*copy.direction.z();

    delta = b*b - 4*a*c;
    Vec4 pos,n;
    Vec4 auxp = Vec4();
    if (delta<0.0){
       return;

    }else{

    t0 = (-b - sqrt(delta))/(2*a);
    t1 = (-b + sqrt(delta))/(2*a);
    t_ = fmin(t0,t1);
    pos = copy.positionRay(t_);
    n   = pos;
    if(obj->getLenTexture()>0||obj->getLenBump()>0) auxp = mappingCylinderCap(pos,NULL);
    if (pos.x2 <APROXIMATE){
        n = Vec4(0,-1,0);
        float est = (n*Vec4(0,0,0) - copy.origin*n)/(n*(copy.direction));
        if (est<APROXIMATE) return;
        Vec4 posi = copy.positionRay(est);
        if (((posi.x()*posi.x() + posi.z()*posi.z())<=1)){
            t_ = est;
            pos = posi;
            if(obj->getLenTexture()>0||obj->getLenBump()>0) auxp = mappingCylinderCap(Vec4(pos.z(),pos.y(),pos.x()),NULL);
        }else{
            return;
        }
    }
    }

    pos = transform.transform_position_ray(transform,pos);
    n = transform.transform_normal_ray(transform,n);
    t_ = (pos - ray.origin).module();
    if (t_<t && t_>tmin) {
        this->t = t_;
        this->normal = n.unitary();
        this->material = mesh->material;
        this->obj = obj;
        if(obj->getLenTexture()>0||obj->getLenBump()>0) this->mapping = auxp;
    }



}

RayIntersection::~RayIntersection()
{
    //delete material;
    //delete obj;
}

Vec4 RayIntersection::mappingPlanar4(Face face, Vec4 pit,Texture* text)
{
    //considerando o seguinte esquema de face quadrada
    //        dv
    //  p0 --------- p3
    //  |             |
    //  | du          |
    //  |             |
    //  p1 --------- p2

    if (face.vertexs.size()!=4) return Vec4();
    Vec4 p0 = Vec4(face.vertexs[0]->x(),face.vertexs[0]->y(),face.vertexs[0]->z());
    Vec4 p1 = Vec4(face.vertexs[1]->x(),face.vertexs[1]->y(),face.vertexs[1]->z());
    Vec4 p3 = Vec4(face.vertexs[3]->x(),face.vertexs[3]->y(),face.vertexs[3]->z());
    float du = (p0 - p1).module();
    float dv = (p0 - p3).module();
    float d  = (p0 - pit).module();
    float cos = fabs(((pit - p0)*(p1 - p0))/(d*du));
    float sin = sqrt((1 - cos*cos));
    //float angle = (pit - p0)*(p1 - p0);
    float u,v;
    if(text!=NULL){
    if(text->getTypeMapping()==MAP_TILING){
    float x = ((d*cos)/(du/2) - floor((d*cos)/(du/2)))*(du/2);
    float y = ((d*sin)/(dv/2) - floor((d*sin)/(dv/2)))*(dv/2);
    u = (x)/(du/2);
    v = (y)/(dv/2);
    }else{
        u = ((d*cos))/(du);
        v = ((d*sin))/(dv);
    }
    }else{
        float x = ((d*cos)/(du/2) - floor((d*cos)/(du/2)))*(du/2);
        float y = ((d*sin)/(dv/2) - floor((d*sin)/(dv/2)))*(dv/2);
        u = (x)/(du/2);
        v = (y)/(dv/2);
    }
    return Vec4(u,v,0);

//    float u = (d*cos)/du;
//    float v = (d*sin)/dv;
//    return Vec4(u,v,0);



}

Vec4 RayIntersection::mappingPlanar3(Face face, Vec4 pit, Texture *text)
{
    if (face.vertexs.size()!=3) return Vec4();
    Vec4 p0 = Vec4(face.vertexs[0]->x(),face.vertexs[0]->y(),face.vertexs[0]->z());
    Vec4 p1 = Vec4(face.vertexs[1]->x(),face.vertexs[1]->y(),face.vertexs[1]->z());
    Vec4 p2 = Vec4(face.vertexs[2]->x(),face.vertexs[2]->y(),face.vertexs[2]->z());
    float du = (p1 - p2).module();
    float dv = (p0 - p1).module();
    float d  = (p1 - pit).module();
    float cos = fabs(((pit - p1)*(p2 - p1)))/(d*du);
    float sin = sqrt((1 - cos*cos));
    //float angle = (pit - p0)*(p1 - p0);
    float u,v;
    if(text->getTypeMapping()==MAP_TILING){
    float x = ((d*cos)/(du/2) - floor((d*cos)/(du/2)))*(du/2);
    float y = ((d*sin)/(dv/2) - floor((d*sin)/(dv/2)))*(dv/2);
    u = (x)/(du/2);
    v = (y)/(dv/2)*(0.5);
    }else{
        u = ((d*cos))/(du);
        v = ((d*sin))/(dv)*(0.5);
    }
    return Vec4(u,v,0);

}

Vec4 RayIntersection::mappingSpheric(Vec4 pos, Texture *text)
{
    float u = 0.5 + atan2(pos.x(),pos.z())/(2*M_PI);
    float v = 0.5 - (asin(pos.y())/(M_PI));
    return Vec4(u,v,0);
}

Vec4 RayIntersection::mappingCylinderLateral(Vec4 pos, Texture *text)
{
//    float angle = (Vec4(1,pos.y(),0)- Vec4(0,pos.y(),0))*(pos - Vec4(0,pos.y(),0));
//    float cos = ((Vec4(1,pos.y(),0)- Vec4(0,pos.y(),0))*(pos - Vec4(0,pos.y(),0)))/((Vec4(1,pos.y(),0)- Vec4(0,pos.y(),0)).module()*(pos - Vec4(0,pos.y(),0)).module());
//    if (angle<0){
//        angle = (Vec4(0,pos.y(),0)-pos)*(Vec4(1,pos.y(),0)- Vec4(0,pos.y(),0));
//    }
    //if (v.get_dimensao() != 2) return(-1);
        float resultado = 0;
        // Checar se o vetor "v" está mais perto da reta X:
        if (fabs(pos.z()) > fabs(pos.x()))// Se |v.x| > |v.y|...
        {
            resultado = pos.x()/pos.z();// (v.y/v.x)
            if (pos.z() > 0)// Se (v.x > 0)...
            {
                if (resultado < 0) resultado += 8;
            }
            else resultado += 4;
        }
        else// Caso o vetor "v" esteja mais perto da reta Y:
        {
            resultado = pos.z()/pos.x();// (v.x/v.y)
            // Se (v.y > 0)...
            if (pos.x() > 0) resultado = 2 - resultado;
            else resultado = 6 - resultado;
        }
        resultado/=8.0;

    float u = resultado;
    float v = 1-Vec4(0,pos.y(),0).module();
    return Vec4(u,v,0);


}

Vec4 RayIntersection::mappingCylinderCap(Vec4 pos, Texture *text)
{
    float angle = atan2(pos.z(),pos.x());//((Vec4(1,pos.y(),0)- Vec4(0,pos.y(),0))*(pos-Vec4(0,pos.y(),0)));
    float cos = ((Vec4(1,pos.y(),0)- Vec4(0,pos.y(),0))*(pos - Vec4(0,pos.y(),0)))/((Vec4(1,pos.y(),0)- Vec4(0,pos.y(),0)).module()*(pos - Vec4(0,pos.y(),0)).module());
    float sin = sqrt((1.0 - cos*cos));
    float d   = (Vec4(0,pos.y(),0) - pos).module();
    //float angle = atan2(pos.z(),pos.x());
    //float angle2 = atan2(pos.z(),pos.x());
    float u,v;
    if (angle<0){
        if(cos>=0){
            u = 0.5+(cos*d)*0.5;
            v = 0.5+(sin*d*0.5);
        }else{
            u = 0.5+(cos*d)*0.5;
            v = 0.5+(sin*d*0.5);
        }
    }else{
        if(cos>=0){
            u = 0.5+(cos*d)*0.5;
            v = 0.5 - (sin*d)*0.5;
        }else{
            u = 0.5+(cos*d)*0.5;
            v = 0.5 - (sin*d)*0.5;
        }
    }
   /* if((cos)<0) u = ((cos))*d;
    else            u = 0.5/((cos)*d) + 0.5;
    if(acos(sin)<0) v = 0.5/((sin)*d) + 0.5;
    else      v = ((sin))*d*/;
    //u = 1 - (acos(cos))/(2*M_PI);

//    if (angle<0) u = -angle/(2*M_PI);
//    else         u = 1 - angle/(2*M_PI);
    return Vec4(v,u,0);


}



#include "raytracing.h"
#include "interface/scene.h"
#include "math/ray.h"
#include "block/object.h"
#include "structure/light.h"
#include "rayintersection.h"
#include "block/hbb.h"
#define ERROR 0.001
#include "interface/glwidget.h"
#include <omp.h>
int max_depth = 5;
static float distLight = 0;
static int intersect =0;
static int notintersect =0;
#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h> // RAND_MAX é definido em stdlib.h
static int depth = 0;
static bool in = false;
float pshadow = 1;
inline float clamp(double x){ return x<0 ? 0 : x>1 ? 1 : x; }
inline int toInt(double x){ return int(pow(clamp(x),1/2.2)*255+.5); }

#define myrand ((float)(rand())/(float)(RAND_MAX) )

RayTracing::RayTracing()
{
    this->scene = NULL;
    this->widget = NULL;
}

RayTracing::RayTracing(Scene *sc,GLWidget *rcast,Vec4 color,bool otimized)
{
    this->scene = sc;//
    this->widget = rcast;
    //this->backgroundcolor = Vec4(100/255.0,189/255.0,176/255.0,1.0);//color whitted
    this->backgroundcolor = Vec4();
    this->otimized = otimized;
    withhbb = false;
}

void RayTracing::setScene(Scene *scene)
{
    this->scene = scene;
}

void setValue(Vec4* c,int i,Vec4 val){
    c[i] += val;
}

void RayTracing::rayTracing(QImage *pixels, int proportion,int samples)
{

    srand(time(0));
    double ti,tf,tempo; // ti = tempo inicial // tf = tempo final
      ti = tf = tempo = 0;
      timeval tempo_inicio,tempo_fim;
      gettimeofday(&tempo_inicio,NULL);


    if (scene->enablephoton) scene->generatePhotons();
    gettimeofday(&tempo_fim,NULL);
      tf = (double)tempo_fim.tv_usec + ((double)tempo_fim.tv_sec * (1000000.0));
      ti = (double)tempo_inicio.tv_usec + ((double)tempo_inicio.tv_sec * (1000000.0));
      tempo = (tf - ti)/1000000;
      printf("Tempo gasto em segundos gerar photons: %.3f\n",tempo);

      gettimeofday(&tempo_inicio,NULL);
      ti = tf = tempo = 0;

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


    changetoviewer = changetoviewer.transpose();
    changetoviewer.setTranslate(scene->viewer[0]);


    int height = (int)(scene->viewport[1]*(proportion/100.0));
    int width = (int)(scene->viewport[0]*(proportion/100.0));
    std::vector<Vec4> matriz;
    std::vector<int> withmotion;
    std::vector<Vec4> sum;
    sum.clear();
    matriz.clear();
    float h = 2.0*scene->projection.x3*(tan(M_PI*scene->projection.x1/360.0));
    float w = h*scene->projection.x2;
    float deltax = w/width;
    float deltay = h/height;
    notintersect = 0;
    intersect = 0;
    int count = 0;

    float alfa,beta;

    Vec4 dir;
    Ray ray;
    QRgb value;
    depth = 0;

    //Vec4 rays_color = Vec4();


    for(unsigned int j=0;j<height;j++)
        for(unsigned int i=0;i<width;i++){
            matriz.push_back( Vec4(0,0,0));
            withmotion.push_back(0);
        }

    int i,j,t;
    float znear = -scene->projection.x3;
    //se por acaso um objeto tiver o efeito motion blur sera desconsiderado o uso do hierarquical bounding boxes
    for (int i=0;i<scene->objects.size();i++)
        if(scene->objects.at(i)->getMotion()!=Vec4()) withhbb = false;
    //omp_set_num_threads(samples);
    //QImage image = QImage(scenewidth,sceneheight,QImage::Format_RGB32);
//#pragma omp parallel
//#pragma omp for  schedule(static,c) nowait private(i,j,alfa,beta,ray,dir,depth,in,val)  collapse(3)one) private(i,j,alfa,beta,ray,dir,depth,in,val) shared(count,znear,matriz,w,h,deltax,deltay,samples,changetoviewer,width,height) num_threads(samples)
    //{
    bool withreduction = false;
    float percent = 0.3;
    int backcount = 0;
    //omp_set_num_threads(8);
    Vec4 pixel;



    for (t=0;t<samples;t++){

    //#pragma omp barrier
//#pragma omp parallel for schedule(dynamic, omp_get_num_procs()) private(i,j,alfa,beta,dir,ray,backcount,pixel)
        for(j=0;j<height;j++){
            for (i=0;i<width;i++){
                backcount = matriz.at(i+(j*width)).x4;
                if (withreduction){
                    if (((((backcount/(float)samples)<=percent)||(withmotion.at(i+(j*width))!=0)))){
                        if(samples==1){
                            alfa  = -w/2.0 + deltax/2.0  + i*deltax;
                            beta  = -h/2.0 + deltay/2.0 + j*deltay;
                        }else{
                            alfa  = -w/2.0 + deltax*myrand  + i*deltax;
                            beta  = -h/2.0 + deltay*myrand + j*deltay;
                        }

                        dir.setVec4(alfa,beta,znear);
                        //teste para verificar se o cenário tem o efeito de depth of field
                        if (!(scene->radius>0 && scene->focal>0)){
                            ray.setOrigin(changetoviewer.transpose().vector(Vec4(0,0,0)));
                            ray.setDirection(changetoviewer.transpose().vector(dir));
                        }else{
                            Ray dof = depthOfField(dir,scene->radius,scene->focal);
                            ray.setOrigin(changetoviewer.transpose().vector(dof.origin));
                            ray.setDirection(changetoviewer.transpose().vector(dof.direction));
                        }
                        ray.setDirection((ray.direction - ray.origin).unitary());
                        depth = 0;
                        count++;
                        in = false;
                        pixel = rayIntersection(ray);
                        if (pixel.x4)
                            withmotion.at(i+(j*width)) = withmotion.at(i+(j*width)) + 1;
                        matriz.at(i+(j*width)) += pixel;
                        matriz.at(i+(j*width)).x4 = backcount+1;
                    }
                }
                else{
                    if(samples==1){
                        alfa  = -w/2.0 + deltax/2.0  + i*deltax;
                        beta  = -h/2.0 + deltay/2.0 + j*deltay;
                    }else{
                        alfa  = -w/2.0 + deltax*myrand  + i*deltax;
                        beta  = -h/2.0 + deltay*myrand + j*deltay;
                    }

                    dir.setVec4(alfa,beta,znear);
                    //teste para verificar se o cenário tem o efeito de depth of field
                    if (!(scene->radius>0 && scene->focal>0)){
                        ray.setOrigin(changetoviewer.transpose().vector(Vec4(0,0,0)));
                        ray.setDirection(changetoviewer.transpose().vector(dir));
                    }else{
                        Ray dof = depthOfField(dir,scene->radius,scene->focal);
                        ray.setOrigin(changetoviewer.transpose().vector(dof.origin));
                        ray.setDirection(changetoviewer.transpose().vector(dof.direction));
                    }
                    ray.setDirection((ray.direction - ray.origin).unitary());
                    depth = 0;
                    count++;
                    in = false;
                    Vec4 pixel = rayIntersection(ray);
                    matriz.at(i+(j*width)) += pixel;
                    matriz.at(i+(j*width)).x4 = backcount+1;

                }



                    //if(val==Vec4()) count++;



                //}
            }
        }


    }

    gettimeofday(&tempo_fim,NULL);
      tf = (double)tempo_fim.tv_usec + ((double)tempo_fim.tv_sec * (1000000.0));
      ti = (double)tempo_inicio.tv_usec + ((double)tempo_inicio.tv_sec * (1000000.0));
      tempo = (tf - ti)/1000000;
      printf("Tempo gasto em segundos %.3f\n",tempo);

    for(int j=0;j<height;j++)
        for(int i =0;i<width;i++){
            if(withreduction){
                matriz.at(i+(j*width)) /= matriz.at(i+(j*width)).x4;
            }else{
                matriz.at(i+(j*width)) /= samples;
            }
            value = qRgb((matriz.at(i+(j*width)).x()*255),(matriz.at(i+(j*width)).y()*255),(matriz.at(i+(j*width)).z()*255));
            pixels->setPixel(i,height-(j+1),value);
        }
    widget->showSampleRender(pixels);
    qDebug() << "Width: " << width;
    qDebug() << "Height: " << height;
    qDebug() << "Total de Raios: " << width*height*samples;
    qDebug() << "Total de Raios Intercepta: " << intersect;
    qDebug() << "Total de Raios Nao Intercepta: " << notintersect;
    qDebug() << "Tempo Gasto(s): " << tempo;

    /*Teste pessoal com a parelização
    omp_set_num_threads(8);

    //int c1 = samples*width*height/omp_get_num_threads();
    int c1 =  (height / (8) * width) + (samples * (height/8) * width);

    Vec4 *c = new Vec4[width*height];
    for (int i=0;i<scene->objects.size();i++)
        if(scene->objects.at(i)->getMotion()!=Vec4()) withhbb = false;

    #pragma omp parallel for schedule(dynamic, c1) private(i)// OpenMP
    for (int y=0; y<height; y++){ // Loop over image rows
        fprintf(stderr,"\rRendering (%d spp) %5.2f%%",samples*4,100.*y/(height-1));
        for (int x=0; x<width; x++) // Loop cols
            for (int s=0,i=((height-y-1)*width+x); s<samples; s++){
                float alfa  = -w/2.0 + deltax*myrand  + x*deltax;
                float beta  = -h/2.0 + deltay*myrand + y*deltay;
                Vec4 dir(alfa,beta,znear);
                    setValue(c,i,rayIntersection(Ray(changetoviewer.transpose().vector(Vec4(0,0,0)),(changetoviewer.transpose().vector(dir) - changetoviewer.transpose().vector(Vec4(0,0,0))).unitary())));
            }
    }
    for(int j=0;j<height;j++)
        for(int i =0;i<width;i++){
            int ind = ((height-j-1)*width+i);
            value = qRgb(toInt(c[ind].x()/(samples)),toInt(c[ind].y()/(samples)),toInt(c[ind].z()/(samples)));
            pixels->setPixel(i,height-(j+1),value);
        }
    widget->showSampleRender(pixels);
    FILE *f = fopen("image-teste2.ppm", "w"); // Write image to PPM file.
    fprintf(f, "P3\n%d %d\n%d\n", width, height, 255);
    for (int i=0; i<width*height; i++)
        fprintf(f,"%d %d %d ", toInt(c[i].x()/(samples)), toInt(c[i].y()/(samples)), toInt(c[i].z()/(samples)));
    */


}




Vec4 RayTracing::rayIntersection(Ray ray, Object *obj)
{

        RayIntersection *ray_intersection = new RayIntersection();
        ray_intersection->t = scene->projection.x4;
        Object* old = obj;
        ray_intersection->tmin = 0;
        if (withhbb){

        bool hit  = hierachicalbb->HBBIntersection(ray_intersection,ray,obj);

        old = ray_intersection->obj;

        if (!(hit) || old==obj){
            notintersect++;
            delete ray_intersection;
            return this->backgroundcolor;
        }else{
            intersect++;
            int withmotion = 0;
            if(obj->getMotion()!=Vec4()) withmotion++;
            Vec4 pixel = calculatePixelColor(old,ray_intersection->normal,ray_intersection->material,ray.positionRay(ray_intersection->t),ray,ray_intersection->mapping);
            if (pixel.x4!=0.0)
                pixel.x4 = withmotion;
            delete ray_intersection;
            return pixel;
        }
        }else{
            float aux = scene->projection.x4;

            for(int i=0;i<scene->objects.size();i++){

                if(scene->objects.at(i)->isEnabled() && scene->objects.at(i)!=obj){
                    scene->objects.at(i)->tryIntersection(ray_intersection,ray);
                }
                if (ray_intersection->t<aux){
                    obj = scene->objects.at(i);
                    aux = ray_intersection->t;
                }

            }

            if (ray_intersection->normal==Vec4()){
                notintersect++;
                delete ray_intersection;
                return this->backgroundcolor;
            }else{
                intersect++;
                int withmotion = 0;
                if(obj->getMotion()!=Vec4()) withmotion++;
                Vec4 pixel = calculatePixelColor(obj,ray_intersection->normal,ray_intersection->material,ray.positionRay(ray_intersection->t),ray,ray_intersection->mapping);
                if (pixel.x4!=0)
                    pixel.x4 = withmotion;
                delete ray_intersection;
                return pixel;
            }
        }

}



Vec4 RayTracing::calculatePixelColor(Object *obj,Vec4 normal, Material *material, Vec4 intercept,Ray r,Vec4 map)
{
        Vec4 color = Vec4(0,0,0);
        Vec4 aux = Vec4(0,0,0);
        int light_enable = 0;
        bool shadow = false;
        for (int i=1;i<scene->lights.size();i++){
                obj->setEnabled(false);
                aux = Vec4();
                Vec4 l = scene->lights.at(i)->randLight();
                Vec4 v = (r.direction);
                if((v*(normal*(-1)))<0.0) normal = normal*(-1);
                distLight = (l - intercept).module();
                Ray raio = Ray(intercept,(l - intercept).unitary());
                if (scene->lights.at(i)->isEnabled()){
                    light_enable++;
                    /* testar se a direção do ponto observado a luz está obstruido */
                    if ((testObstruction(raio,obj)==Vec4())){
                        //tratamentos no caso de textura no objeto no caso estamos tratando o objeto com uma única
                        //textura e um único bumping mapping
                        if(!scene->enablephoton){
                        if(obj->getLenTexture()>0 || obj->getLenBump()>0){
                            //o objeto tem textura e bump mapping
                            if ((obj->getLenTexture()>0 && obj->getEnabledTexture())&&(obj->getLenBump()>0 && obj->getEnabledBump()))
                                aux = aux + scene->lights.at(i)->calculateColor(intercept,obj->getBump(0)->getColorNormalBump(normal,map),scene->viewer[0],material,l,obj->getTexture(0)->getColorTexture(map),obj->getTexture(0)->getTypeTexture())*pshadow;
                            //objeto só possui textura
                            else if(obj->getLenTexture()>0 && obj->getEnabledTexture())
                                aux = aux + scene->lights.at(i)->calculateColor(intercept,normal,scene->viewer[0],material,l,obj->getTexture(0)->getColorTexture(map),obj->getTexture(0)->getTypeTexture())*pshadow;
                            //objeto só possui bump mapping
                            else if(obj->getLenBump()>0 && obj->getEnabledBump())
                                aux = aux + scene->lights.at(i)->calculateColor((intercept),obj->getBump(0)->getColorNormalBump(normal,map),scene->viewer[0],material,l)*pshadow;
                            //objeto não possui nem textura nem bump mapping habilitados
                            else
                                aux = aux + scene->lights.at(i)->calculateColor(intercept,normal,scene->viewer[0],material,l)*pshadow;
                        }else
                            aux = aux + scene->lights.at(i)->calculateColor(intercept,normal,scene->viewer[0],material,l)*pshadow;
                        }
                        else{ //utilizando o photonMapping
                            if(!scene->photonMap.renderCaustic && !scene->photonMap.renderGlobal)
                                aux = aux + scene->photonMap.radiance(intercept,r.direction,normal,material) + scene->lights.at(i)->calculateColor(intercept,normal,scene->viewer[0],material,l)*pshadow;
                            else
                                aux = aux + scene->photonMap.radiance(intercept,r.direction,normal,material);
                        }

                    }else{
                        shadow = true;
                        if(scene->enablephoton)
                            aux = aux + scene->photonMap.radiance(intercept,r.direction,normal,material);
                    }



                if((material->reflection>0 || material->glossyreflection>0) && depth<max_depth){
                    //qDebug() << "In!";
                    depth++;
                    if(material->glossyreflection>0)
                       aux = aux + (rayIntersection(Ray::rayReflectGlossy(intercept,r.direction,normal,1-material->getGlossyReflection()),obj))*material->getReflection();
                    else
                        aux = aux + (rayIntersection(Ray::rayReflect(intercept,r.direction,normal),obj))*material->getReflection();

                }
                if(material->refraction>0 && depth<max_depth){
                    //qDebug() << "In!";
                    depth++;
                    float reflectance = Ray::reflectance(v,normal,1.0,material->getRefraction());
                    if (material->glossyrefraction>0){
                        aux = aux  + (rayIntersection(Ray::rayReflectGlossy(intercept,r.direction,normal,1-material->getGlossyRefraction()),obj))*(reflectance);
                        aux = aux  + (rayIntersection(Ray::rayRefractGlossy(intercept,r.direction,normal,1.0,material->getRefraction(),1-material->getGlossyRefraction()),obj))*(1-reflectance);//*fabs(1-kr);
                    }else{
                        aux = aux  + (rayIntersection(Ray::rayReflect(intercept,r.direction,normal),obj))*(reflectance);
                        aux = aux  + (rayIntersection(Ray::rayRefract(intercept,r.direction,normal,1.0,material->getRefraction()),obj))*(1-reflectance);//*fabs(1-kr);
                    }
                }
                //modelo de transparencia proposto por whitted, 1980
//                else{
//                if(material->refraction>0 && depth<max_depth){
//                    depth++;
//                    aux = aux  + (rayIntersection(Ray::rayRefractWitted(intercept,r.direction,normal,material->refraction)))*(0.85)*material->getRefraction();//*fabs(1-kr);

//                }
//                }
                }
                obj->setEnabled(true);
                color = color + aux;


        }
        if(!scene->enablephoton)
            if (obj->getLenTexture()>0)
                if (obj->getTexture(0)>0 && obj->getEnabledTexture())
                    color = (color + scene->lights.at(0)->calculateColor(intercept,normal,scene->viewer[0],material,Vec4(),obj->getTexture(0)->getColorTexture(map),obj->getTexture(0)->getTypeTexture())*0.5)/light_enable;
                else
                    color = (color + scene->lights.at(0)->calculateColor(intercept,normal,scene->viewer[0],material,Vec4()))/light_enable;
            else{
                color = (color + scene->lights.at(0)->calculateColor(intercept,normal,scene->viewer[0],material,Vec4()))/light_enable;
            }
        else{
            if(!scene->photonMap.renderCaustic && !scene->photonMap.renderGlobal)
                color = (color + scene->lights.at(0)->calculateColor(intercept,normal,scene->viewer[0],material,Vec4()))*0.8/light_enable;
        }

        color.x1 = fmin(color.x1,1.0);
        color.x2 = fmin(color.x2,1.0);
        color.x3 = fmin(color.x3,1.0);
        if (shadow) color.x4 = 1.0;
        else color.x4 = 0.0;

        return color;
}

Vec4 RayTracing::testObstruction(Ray ray, Object *obj)
{
    RayIntersection *ray_intersection = new RayIntersection();
    ray_intersection->t = distLight;
    ray_intersection->tmin = 0.0;
    pshadow = 1;
    if (withhbb){
        bool hit  = hierachicalbb->HBBIntersection(ray_intersection,ray);

        if (hit && ray_intersection->t<distLight){
            if (ray_intersection->obj->getMesh()->getRefraction()>0){
                //delete ray_intersection;
                //pshadow = 0.85;
                //return Pintercept;
                //return Vec4();
                Vec4 Pintercept = ray.positionRay(ray_intersection->t);
                delete ray_intersection;
                return Pintercept;
            }
            Vec4 Pintercept = ray.positionRay(ray_intersection->t);
            delete ray_intersection;
            return Pintercept;
        }
    }else
    {
        for(int i=0;i<scene->objects.size();i++){

            if(scene->objects.at(i)->isEnabled() /*&& scene->objects.at(i)!=obj*/) scene->objects.at(i)->tryIntersection(ray_intersection,ray);

        }
        if (ray_intersection->t<distLight && ray_intersection->normal!=Vec4()){
            if (ray_intersection->obj->getMesh()->getRefraction()>0){
                //delete ray_intersection;
                //pshadow = 0.85;
                //return Vec4();
                Vec4 Pintercept = ray.positionRay(ray_intersection->t);
                delete ray_intersection;
                return Pintercept;
            }
            Vec4 Pintercept = ray.positionRay(ray_intersection->t);
            delete ray_intersection;
            return Pintercept;
        }

    }
    delete ray_intersection;
    return Vec4();
}

Ray RayTracing::depthOfField(Vec4 pixel,float radius, float distancefocus)
{
    float d = pixel.z();
    float f = -distancefocus;
    Vec4  p = Vec4(pixel.x()*(f/d),pixel.y()*(f/d),f);
    Vec4  o = Vec4(1,0,0)*(-radius/2)+Vec4(0,1,0)*(-radius/2)+Vec4(1,0,0)*radius*(myrand)+Vec4(0,1,0)*radius*(myrand);
    return Ray(o,p);


}

Object *RayTracing::objectClicked(Scene *scn, int width, int height)
{
    if(scn->objects.size()==0) return NULL;
    Matrix4x4 changetoviewer;
    changetoviewer.setIdentity();
    Vec4 kv,iv,jv,kvl,ivl,jvl;
    kv = (scn->viewer[0] - scn->viewer[1])/((scn->viewer[0] - scn->viewer[1]).module());
    iv = (scn->viewer[2] ^ kv)/(scn->viewer[2] ^ kv).module();
    jv = (kv ^ iv)/(kv ^ iv).module();
    ivl.setVec4(iv.x1,jv.x1,kv.x1);
    jvl.setVec4(iv.x2,jv.x2,kv.x2);
    kvl.setVec4(iv.x3,jv.x3,kv.x3);
    Vec4 translate(-(iv*scn->viewer[0]),-(jv*scn->viewer[0]),-(kv*scn->viewer[0]));

    changetoviewer.setAxisX(iv);
    changetoviewer.setAxisY(jv);
    changetoviewer.setAxisZ(kv);
    changetoviewer.setTranslate(translate);

    changetoviewer = changetoviewer.transpose();
    changetoviewer.setTranslate(scn->viewer[0]);

    float h = 2.0*scn->projection.x3*(tan(M_PI*scn->projection.x1/360.0));
    float w = h*scn->projection.x2;
    float deltax = w/scn->viewport[0];
    float deltay = h/scn->viewport[1];

    int j = height;
    int i = width;


    float alfa,beta;

    alfa  = -w/2.0 + deltax/2.0  + i*deltax;
    beta  = -h/2.0 + deltay/2.0 + j*deltay;


    Vec4 dir(alfa,beta,-scn->projection.x3);
    Ray ray(changetoviewer.transpose().vector(Vec4(0,0,0)),changetoviewer.transpose().vector(dir));
    ray.setDirection((ray.direction - ray.origin).unitary());

    return getObject(ray,scn);
}

Object* RayTracing::getObject(Ray ray,Scene* scene)
{
    RayIntersection *ray_intersection = new RayIntersection();
    Object *obj = NULL;
    HBB *hierachicalbb = new HBB(scene->objects,1);
    ray_intersection->t = scene->projection.x4;
    ray_intersection->tmin = 0;
    bool hit = hierachicalbb->HBBIntersection(ray_intersection,ray,obj);
    if (hit) return ray_intersection->obj;
    return NULL;

}

RayTracing::~RayTracing()
{
     delete[]scene;
     delete[]widget;
}






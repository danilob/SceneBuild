#include "photon.h"
#include "math/rayintersection.h"
#include "interface/scene.h"
#include <omp.h>
Photon::Photon()
{
}

Photon::Photon(Vec4 pos, Vec4 dir)
{
    position = pos;
    direction = dir;
    status = DIRECT;
    type = GLOBAL;
}

Photon::Photon(Vec4 pos, Vec4 dir, Vec4 pow, int flag)
{
    position = pos;
    direction = dir;
    power = pow;
    this->flag = flag;
    status = DIRECT;
    type = GLOBAL;
}

Photon::Photon(Vec4 pos, Vec4 dir, Vec4 pow)
{
    position = pos;
    direction = dir;
    power = pow;
    status = DIRECT;
    type = GLOBAL;
}

void Photon::setPosition(Vec4 pos)
{
    position = pos;
}

Vec4 Photon::getPosition()
{
    return position;
}

void Photon::setDirection(Vec4 dir)
{
    direction = dir;
}

Vec4 Photon::getDirection()
{
    return direction;
}

void Photon::setPower(Vec4 pow)
{
    power = pow;
}

Vec4 Photon::getPower()
{
    return power;
}

void Photon::setFlag(int flag)
{
    this->flag = flag;
}

int Photon::getFlag()
{
    return flag;
}

void Photon::setStatus(int status)
{
    this->status = status;
}

int Photon::getStatus()
{
    return this->status;
}

void Photon::setType(int type)
{
    this->type = type;
}

int Photon::getType()
{
    return type;
}

void Photon::setIndex(int id)
{
    this->index = id;
}

int Photon::getIndex()
{
    return this->index;
}

PhotonMap::PhotonMap()
{
    kdtree = new KdTree();
    caustic =  new KdTree();
    this->scene = NULL;
    radiusGlobal = 0.75;
    radiusCaustic = 0.15;
    depthMax = 4;
    fat = 1;
    renderCaustic = false;
    renderGlobal = false;
    nearsGlobal = 100;
    nearsCaustics = 60;
    filter = true;
}

int PhotonMap::getSizeGlobal()
{
    return kdtree->photons.size();
}


void PhotonMap::setScene(Scene *scn)
{
    this->scene = scn;
    hbb = new HBB(scene->objects,1);
}


void PhotonMap::constructPhotonMap(std::vector<Photon*> emitphotons)
{
    globalPhotons = 0;
    causticPhotons = 0;
    kdtree = new KdTree();
    srand(time(0));
    for( unsigned int i=0;i<emitphotons.size();i++){
        getHitPhoton(emitphotons.at(i),depthMax);
    }
    constructKdTree();
}

void PhotonMap::getHitPhoton(Photon *photon, int depth)
{
    if (!depth) return;
    Ray ray(photon->getPosition(),photon->getDirection());
    RayIntersection* intersect = new RayIntersection();
    Object* obj;
    bool hit  = hbb->HBBIntersection(intersect,ray,obj);
    if (!hit) return; //caso não tenha interceptado nenhum objeto
    obj = intersect->obj;
    Vec4 pHit = ray.positionRay(intersect->t); //ponto do hit
    //gerar novo photon caso o objeto tenha propriedades reflexivas ou refratarias, com a mesma profundidade
    if((photon->direction*(intersect->normal*(-1)))<0.0) intersect->normal = intersect->normal*(-1);
    if (intersect->material->getReflection()>0 || intersect->material->getRefraction()>0){
        if (intersect->material->getRefraction()>0){
            //iremos rolar a roleta para escolher entre a reflexão ou refração
            //float reflectance = Ray::reflectance(pHit,intersect->normal,1.0,intersect->material->getRefraction());
            float rolete = myrand;
            if (rolete>0.5){//reflexão
                Ray reflection = Ray::rayReflect(pHit,photon->direction,intersect->normal);
                Photon* p = new Photon(reflection.origin,reflection.direction,photon->getPower());
                if(photon->getType()==CAUSTIC) p->setType(CAUSTIC);
                p->setStatus(REFLECTED);
                getHitPhoton(p,depth-1);
            }else{//refração
                Ray refraction = Ray::rayRefract(pHit,photon->direction,intersect->normal,1.0,intersect->material->getRefraction());
                Photon* p = new Photon(refraction.origin,refraction.direction,photon->getPower());
                if(photon->getStatus()==DIRECT || photon->getStatus()==REFRACTED) p->setStatus(REFRACTED);
                else p->setStatus(REFLECTED);
                if(photon->getType()==CAUSTIC) p->setType(CAUSTIC);
                getHitPhoton(p,depth);
            }
        }else{//iremos gerar um ray de reflexão
            Ray reflection = Ray::rayReflect(pHit,photon->direction,intersect->normal);
            Photon* p = new Photon(reflection.origin,reflection.direction,photon->getPower());
            if(photon->getType()==CAUSTIC) p->setType(CAUSTIC);
            p->setStatus(REFLECTED);
            getHitPhoton(p,depth-1);
        }
        return;

    }
    //caso contrário houve um hit em um material difuso, primeiro passo será adicionar este hit no photon map
    //em seguida decidir se o raio continua ou para.
    //if(depth!=depthMax){
    Photon* p = new Photon(pHit,photon->getDirection()*(-1),photon->getPower()*fat);
    if(photon->getType()==CAUSTIC) p->setType(CAUSTIC);
    if(photon->getStatus()==REFRACTED){

        p->setStatus(DIFUSED);
        caustic->addPhoton(p); //kdtree de caustica
        causticPhotons++;
    }else{

        if(depth==0 && photon->getStatus()!=REFLECTED)
            p->setStatus(DIRECT);
        else{
            p->setStatus(REFLECTED);
        }
        if(!(p->getStatus()==DIRECT)){
            kdtree->addPhoton(p); //kdtree global
            globalPhotons++;
       }

    }
         //valor do ponto de hit, direção para origem do raio e power do photon
        //photons.push_back(p);

    //}

    //calculo da sobrevivencia do photon
    Vec4 diff = obj->getMesh()->getMaterialM()->getDiffuse().unitary();
    Vec4 spe = obj->getMesh()->getMaterialM()->getSpecular().unitary();
    Vec4 pow = photon->getPower();
    //energia máxima da diffusa e da especular
    float Pd = fmax(fmax(diff.x()*pow.x(),diff.y()*pow.y()),diff.z()*pow.z())/fmax(fmax(pow.x(),pow.y()),pow.z());
    float Ps = fmax(fmax(spe.x()*pow.x(),spe.y()*pow.y()),spe.z()*pow.z())/fmax(fmax(pow.x(),pow.y()),pow.z());

    float epsilon = myrand; //roleta russa
    float sob = 1;
    if (photon->getStatus()==REFRACTED) sob = 0.5;
    if(epsilon>=0 && epsilon<=Pd){//reflexão difusa
        Ray reflection = Ray::rayReflect(pHit,photon->getDirection(),intersect->normal);
        Vec4 ri = reflection.direction.unitary();
        float du = -(1-myrand)/2.0 + myrand*(1-myrand);
        float dv = -(1-myrand)/2.0 + myrand*(1-myrand);
        Vec4  ul = ri^intersect->normal;
        ul = ul.unitary();
        Vec4 vl = ri^ul;
        ri = ri + ul*du + vl*dv;
        pow = ((pow.mult(diff))/Pd);
        Photon* p = new Photon(reflection.origin,ri.unitary(),pow*sob);
        if(photon->getType()==CAUSTIC) p->setType(CAUSTIC);
        else  p->setStatus(REFLECTED);
        getHitPhoton(p,depth-1);
    }else if(epsilon>Pd && epsilon<=(Pd+Ps)){ //reflexão especular
        Ray reflection = Ray::rayReflect(pHit,photon->getDirection(),intersect->normal);
        Vec4 l = reflection.direction;
        Vec4 r = (intersect->normal*((l*intersect->normal)*2) - l);
        Vec4 v = (l-pHit)/(l-pHit).module();
        r = (r+v)/(r+v).module();
        Vec4 ri = r;
        float du = -(1-myrand)/2.0 + myrand*(1-myrand);
        float dv = -(1-myrand)/2.0 + myrand*(1-myrand);
        Vec4  ul = ri^intersect->normal;
        ul = ul.unitary();
        Vec4 vl = ri^ul;
        ri = ri + ul*du + vl*dv;
        pow = ((pow.mult(spe))/Ps);
        Photon* p = new Photon(reflection.origin,ri.unitary(),pow*sob);
        if(photon->getType()==CAUSTIC) p->setType(CAUSTIC);
        else  p->setStatus(REFLECTED);
        getHitPhoton(p,depth-1);
    }else{ //absorção
        return;
    }
}

void PhotonMap::constructKdTree()
{
    if(!kdtree->photons.empty())
        kdtree->createHeap();
    if(!caustic->photons.empty())
        caustic->createHeap();
}

bool first2 = true;
Vec4 PhotonMap::radiance(Vec4 position, Vec4 dir, Vec4 n,Material *mat)
{
    bool getRadiance = false;
    if(renderCaustic || renderGlobal) getRadiance = true; //significa que estamos interessados somente no desenho da radiancia


    if(getRadiance){
        if(renderGlobal){
            kdtree->clearHeap();
            if(!kdtree->photons.empty())
                kdtree->locatePhotons(0,position,nearsGlobal,radiusGlobal);
        }
        if(renderCaustic){
            caustic->clearHeap();
            if(!caustic->photons.empty())
                caustic->locatePhotons(0,position,nearsCaustics,radiusCaustic);
        }
    }
    else
    {
        if(!kdtree->photons.empty()){
            kdtree->clearHeap();
            kdtree->locatePhotons(0,position,nearsGlobal,radiusGlobal);
        }
        if(!caustic->photons.empty())
        {
            caustic->clearHeap();
            caustic->locatePhotons(0,position,nearsCaustics,radiusCaustic);
        }

    }

    float factor = 1;
    int nears = nearsGlobal;
    Vec4 flux = Vec4(0,0,0);
    Vec4 fluxcaustic = Vec4(0,0,0);
    int ni = 0;
    int i = 0;
    float distMax = 0;
    float k = 5.;
    if(kdtree->maxHeap.size()>0){
        distMax = Vec4::distSquared(kdtree->maxHeap.at(0)->getPosition(),position);
        i = kdtree->maxHeap.size();
        while (nears){
            float sob = 1;
            if (kdtree->maxHeap.at(i-1)->getType()==CAUSTIC) sob = 0.5;
            if(kdtree->maxHeap.at(i-1)->getStatus()!=DIFUSED && kdtree->maxHeap.at(i-1)->getStatus()!=DIRECT){
                Vec4 l = kdtree->maxHeap.at(i-1)->getDirection().unitary();
                if(Vec4::dist(kdtree->maxHeap.at(i-1)->position,position)<radiusGlobal){
                    if((n*l>0)){
                        if (!filter) k = 1;
                        float wpc = 1. - Vec4::dist(kdtree->maxHeap.at(i-1)->position,position)/(k*sqrt(distMax));
                        if(wpc<0) wpc = 0;
                        flux += (kdtree->maxHeap.at(i-1)->getPower()*factor)*wpc*sob;
                        nears--;
                        ni++;
                    }
                }
            }
            i--;
            if(i==0) break;
        }
    }
    if (filter)
        flux = (flux/((1.-2./(3*k))*M_PI*distMax)); //com filtro
    else
        flux = (flux/(M_PI*distMax));
    if(ni<4) flux = Vec4();
    if (caustic->maxHeap.size()==0) return flux;
    i = caustic->maxHeap.size();
    distMax = Vec4::distSquared(caustic->maxHeap.at(0)->getPosition(),position);
    ni = 0;
    nears = nearsCaustics;
    float alfa = 1.818;
    float beta = 1.953;

    while (nears){
        if(caustic->maxHeap.at(i-1)->getStatus()==DIFUSED){
            Vec4 l = caustic->maxHeap.at(i-1)->getDirection().unitary();
            if(Vec4::dist(caustic->maxHeap.at(i-1)->position,position)<radiusCaustic){
                if((n*l>0)){
                    float dp = Vec4::distSquared(caustic->maxHeap.at(i-1)->position,position);
                    float r2 = distMax;
                    float wpc;
                    if (filter)
                        wpc = alfa*(1. - (1. -(exp(-(beta*(dp/(2.*r2)))))/(1. -(exp(-beta)))));
                    else
                        wpc = 1;
                    fluxcaustic += (caustic->maxHeap.at(i-1)->getPower()*wpc);
                    nears--;
                    ni++;
                }
            }
        }
        i--;
        if(i==0) break;
    }
    fluxcaustic = (fluxcaustic/(M_PI*distMax)); //com filtro
    if(ni<4) fluxcaustic = Vec4();
    return flux+fluxcaustic;
}

void PhotonMap::drawPhotonMap()
{
    glDisable(GL_LIGHTING);
    glPointSize(1.5);
    glBegin(GL_POINTS);
        for(unsigned int i=0;i<kdtree->photons.size();i++){
            Vec4 p = kdtree->photons.at(i)->getPosition();
            Vec4 color = kdtree->photons.at(i)->getPower()*(1./fat);
            glColor3f(color.x(),color.y(),color.z());
            glVertex3f(p.x(),p.y(),p.z());
        }
    glEnd();
    glEnable(GL_LIGHTING);
}

void PhotonMap::drawPhotonMapCaustics()
{
    glDisable(GL_LIGHTING);
    glPointSize(1.5);
    glBegin(GL_POINTS);
        for(unsigned int i=0;i<caustic->photons.size();i++){
            Vec4 p = caustic->photons.at(i)->getPosition();
            Vec4 color = caustic->photons.at(i)->getPower()*(1./fat);
            glColor3f(color.x(),color.y(),color.z());
            glVertex3f(p.x(),p.y(),p.z());
        }
    glEnd();
    glEnable(GL_LIGHTING);
}

void PhotonMap::setNearsPhotonsGlobal(int val)
{
    this->nearsGlobal = val;
}

void PhotonMap::setNearsPhotonsCaustics(int val)
{
    this->nearsCaustics = val;
}

void PhotonMap::setDepth(int depthM)
{
    this->depthMax = depthM;
}

void PhotonMap::setRadiusGlogal(float rglobal)
{
    this->radiusGlobal = rglobal;
}

void PhotonMap::setRadiusCaustic(float rcaustic)
{
    this->radiusCaustic = rcaustic;
}

void PhotonMap::setFatorScalarPhoton(float factor)
{
    this->fat = factor;
}

void PhotonMap::setFilter(bool b)
{
    this->filter = b;
}


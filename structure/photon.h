#ifndef PHOTON_H
#define PHOTON_H
#include "math/vec4.h"
#include <vector>
#include "block/hbb.h"
#include "structure/kdtree.h"

#define REFRACTED 0//photon que sofreu refração
#define DIFUSED   1//photon que sofreu refração em alguma superficie especular e alcançou a difusa
#define DIRECT    2//photon que não bateu em nenhum superficie especular
#define REFLECTED 3
#define GLOBAL    4
#define CAUSTIC   5

class Scene;
class Photon
{
public:
    Vec4 position;
    Vec4 direction;
    Vec4 power;       //r,g,b
    //float phi,theta;  //direção de onde a luz incidiu
    int flag;         //valor utilizado na kd-tree
    int status; //tipo de photon
    int index;
    int type;

    Photon();
    Photon(Vec4 pos, Vec4 dir);
    Photon(Vec4 pos, Vec4 dir,Vec4 pow,int flag);
    Photon(Vec4 pos, Vec4 dir,Vec4 pow);

    void setPosition(Vec4 pos);
    Vec4 getPosition();
    void setDirection(Vec4 dir);
    Vec4 getDirection();
    void setPower(Vec4 pow);
    Vec4 getPower();
    void setFlag(int flag);
    int getFlag();
    void setStatus(int status);
    int getStatus();
    void setType(int type);
    int getType();
    void setIndex(int id);
    int getIndex();


};

class PhotonMap
{
public:
    Scene* scene;
    KdTree *kdtree;
    KdTree *caustic;
    int globalPhotons;
    int causticPhotons;
    HBB* hbb;
    int depthMax;
    int nearsGlobal;
    int nearsCaustics;
    float radiusGlobal;
    float radiusCaustic;
    float fat;
    bool renderCaustic;
    bool renderGlobal;
    bool filter;


public:
    PhotonMap();
    int getSizeGlobal();
    void setScene(Scene* scn);
    void constructPhotonMap(std::vector<Photon*> emitphotons); //constroí o photon map a partir dos photons emitidos inicialmente
    void getHitPhoton(Photon* photon,int depth); //adiciona onde os photons encontram uma superfície difusa até uma certa profundidade
    void constructKdTree();
    Vec4 radiance(Vec4 position,Vec4 dir,Vec4 n,Material *mat);
    void drawPhotonMap();
    void drawPhotonMapCaustics();

    void setNearsPhotonsGlobal(int val);
    void setNearsPhotonsCaustics(int val);
    void setDepth(int depthM);
    void setRadiusGlogal(float rglobal);
    void setRadiusCaustic(float rcaustic);
    void setFatorScalarPhoton(float factor);
    void setFilter(bool b);




};


#endif // PHOTON_H

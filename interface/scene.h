#ifndef SCENE_H
#define SCENE_H
#include <vector>
#include "block/object.h"
#include "structure/light.h"
#include "block/cube.h"
#include "block/prism.h"
#include "block/hemisphere.h"
#include "block/cylinder.h"
#include "block/plane.h"
#include "block/cone.h"
#include "block/sphere.h"
#include "structure/ambientlight.h"
#include "structure/pontuallight.h"
#include "structure/directionallight.h"
#include "structure/spotlight.h"
#include "structure/arealight.h"
#include "structure/photon.h"
#include "structure/kdtree.h"

#define BLOCK_CUBE        0
#define BLOCK_CONE        1
#define BLOCK_CYLINDER    2
#define BLOCK_HEMISPHERE  3
#define BLOCK_PRISM       5
#define BLOCK_PLANE       4
#define BLOCK_SPHERE      6
#define PLANALTO          7

class Scene
{
public:
    Scene();

    void pushObjects(Object *obj); //adiciona um objeto na cena
    void pushObjects(int define,int material=0); //carrega objetos para cena de acordo com os defines
    Object* addObject(int type);
    Light* addLight(int type);
    void pushViewer(Vec4 eye,Vec4 at, Vec4 up);
    void pushLights(Light *light);
    //void calculatePixels(GLubyte* pixels,int width,int height);
    void drawObjectsOpenGL(bool wireframe=false);
    void renderLightsOpenGL();
    void pushViewport(int width,int height);
    void pushProjection(float angle,float aspect,float near,float far);
    void pushBackgroundColor(Vec4 background);
    void setMaterialAllObjects(int id);
    void setDOF(float radius,float focal);
    float getRadiusDOF();
    float getFocalDOF();
    void drawPhotons(bool flag=true); //desenha os photons globais
    void drawPhotonsCaustic(bool flag=true); //desenha os photons de caustica
    void generatePhotons();
    void setSizePhotons(int value);
    void setSizePhotonsCaustic(int value);
    void renderGlobalRadiance(bool b);
    void renderCausticRadiance(bool b);
    void setPhotonsNearsCaustics(int val);
    void setPhotonsNearsGlobal(int val);
    void setEnablePhotonMap(bool b);
    void setRadiusGlobal(float val);
    void setRadiusCaustic(float val);
    void setDepthPhotons(int val);
    void setFilterPhoton(bool b);
    Object* getObjecSelected();
    void makeClone(Object* obj);
    ~Scene();

public:
    std::vector<Object*> objects; //objetos da cena
    std::vector<Object*>::iterator iter;
    std::vector<Light*> lights;   //luzes da cena
    std::vector<Light*>::iterator iterl;
    PhotonMap photonMap;
    //KdTree *kdtree;
    bool enablephoton;
    int sizePhotons;
    int sizePhotonsCaustic;
    Vec4 background_color;              //cor de fundo
    Vec4 viewer[3];               //posicão do observador
    Vec4 projection;              //valores de projeção: angle, aspect, near,far
    int viewport[2];              //dimensões da janela de visualização
    bool push_obj;                //flag que indica se eh possivel adicionar objetos
    //parametros do efeito dof do cenário
    float radius; //raio
    float focal;  //distância focal

};

#endif // SCENE_H

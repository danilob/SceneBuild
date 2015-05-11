#ifndef GLWIDGET_H
#define GLWIDGET_H
#include <QTimer>
#include <QGLWidget>
#include "math/vec4.h"
#include <QWheelEvent>
#include <QMouseEvent>
#include <QKeyEvent>
#include "scene.h"
#include "block/hbb.h"
#include <QGraphicsView>
#include <QImage>
class GLWidget : public QGLWidget
{
    Q_OBJECT
signals:
    void listingObjects(std::vector<Object*> objects);
    void listingLights(std::vector<Light*> lights);
    void getCamEye(Vec4);
    void getCam(Vec4 eye,Vec4 at,Vec4 up);
    void updateProjection(Vec4 projection);
    void widgetWidth(int);
    void widgetHeight(int);
    void showObjectSelected(Object *obj);
    void showLightSelected(Light *light);
    void stateSelected(int state);
    void setProgressRay(int value);
    void showSample(QImage*);
    void radiusDOF(double);
    void focalDOF(double);

public slots:
    void showGrid(bool b);
    void sizeGrid(int i);
    void solidGrid(bool b);
    void showViewports(bool b);
    void showHBB(bool s);

    void updateCamera(Vec4 eye,Vec4 at,Vec4 up);
    void updateProjectionOut(Vec4 projection);
    void setObject(int id);
    void addObject(int type);
    void removeObjectSelected();
    void setMaterialAllObjects(int id);
    void setDefaultWorld();
    void setSelectedObject(int i);
    void setMotionObjectSelected(Vec4 motion);
    void setSelectedLight(int i);
    void setTransformMatrixToObjectSelected(Matrix4x4 m);
    void setIdMaterialToObjectSelected(int i);

    //add objeto
    void addCube();
    void addCone();
    void addCylinder();
    void addSphere();
    void addPlane();
    void addHemisphere();
    void addPrism();

    //add light
    void addArea();
    void addDirectional();
    void addSpot();
    void addPontual();


    void setLightSelected(bool b);
    void setLightSelectedDiffuse(QColor color);
    void setLightSelectedAmbient(QColor color);
    void setLightSelectedSpecular(QColor color);

    void setLightSelectedDirection(Vec4 dir);
    void setLightSelectedPosition(Vec4 pos);
    void setLightSelectedAttenuation(Vec4 att);
    void setLightSelectedAngle(int angle);
    void setLightSelectedAngleInner(int angle);
    void setLightSelectedExponent(int angle);
    void setLightSelectedName(QString s);
    void setLightSelectedVecA(Vec4 a);
    void setLightSelectedVecB(Vec4 b);
    void setEnergyLight(int energy);

    void setEnabledLightSelected(bool b);
    void setVisibleLightSelected(bool b);
    void setDOF(float radius,float focal);

    void setEnabledObjectSelected(bool b);
    void setNameObjectSelected(QString s);
    void removeLightSelected();
    void addLight(int val);
    void setSelectedObject(Object* obj);
    int  getItemSelected();

    Scene* getScene();
    std::vector<Object*> getObjectsScene();
    std::vector<Light*> getLightsScene();
    //render functions
    void renderScene(QGraphicsView *qw, int percent,int samples);
    int numberRays();
    void setValueProgressRay(int value);
    void showSampleRender(QImage*);
    //photon map
    void setPhotonsNearsCaustics(int val);
    void setPhotonsNearsGlobal(int val);

    void setFilterPhotonMap(bool b);
    void setRenderGlobal(bool b);
    void setRenderCaustic(bool b);
    void setVisiblePhotonCaustic(bool flag);

    void setSizePhotons(int size);
    void setSizePhotonsCaustic(int size);

    void setRadiusGlobal(double val);
    void setRadiusCaustic(double val);
    void setDepthPhotons(int val);

    void setVisiblePhoton(bool flag);

    void setEnabledPhotonMap(bool b);


public:
    explicit GLWidget(QWidget *parent = 0);
    QTimer             timer;
    Scene*             scene;
    int                width,height;
    Vec4               cam_eye,cam_at,cam_up;
    Vec4               projection;
    Vec4               last_pos; //controle de movimentação da câmera
    double             angle; //angulo da perspectiva
    bool               move;
    int                sizegrid;
    bool               showgrid;
    bool               solidgrid;
    bool               showviewports;
    bool               showhbb;
    bool               showphotons;
    bool               showphotonscaustic;
    HBB*               boundingboxes;


    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);
    void updateCameraGL();
    void updateLightingGL();
    void wheelEvent(QWheelEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void saveImagem(QString file);
    void saveScene(QString file, bool b=true);
    void loadScene(QString file);
    void drawInformation();
    void updateObjectInterface();



    Vec4 mappingViewVertex(int x, int y);
};

#endif // GLWIDGET_H

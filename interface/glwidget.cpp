#include "glwidget.h"
#include <GL/glut.h>
#include "block/object.h"
#include "block/cube.h"
#include "block/prism.h"
#include "block/cylinder.h"
#include "block/hemisphere.h"
#include "extra/functions.h"
#include "draw/draw.h"
#include "math/quaternion.h"
#include "extra/functions.h"
#include "math/raytracing.h"
#include "camera.h"
#include <QPainter>

/* definições do modo de visualização */

#define MODE_DEFAULT    0 // modo de visualização normal o mouse é usado para rotacionar o cenário
#define MODE_OBJECT     1 // neste modo o mouse é utilizado para selecionar o objeto
#define MODE_TRANSLATE  2 //se um objeto está selecionado é possível transladar via teclado
#define MODE_ROTATE     3 //se um objeto está selecionado é possível rotacionar via teclado
#define MODE_SCALE      4 //se um objeto está selecionado é possível escalar via teclado

int modeview = 0;


static int scr_capture_count = 0;
static bool lbpressed = false;
//static bool mbpressed = false;
static bool rbpressed = false;

static float last_x = 0.0;
static float last_y = 0.0;
#define SET_CAM 0
#define SET_OBJECT 1
Camera* cam = new Camera();
static float savedCamera[9];
//variáveis estáticas

int last_pox_x,last_pox_y;
Quaternion q;
int id_material;
int state_key;


//variáveis trackball

int 	winWidth, winHeight;

float 	angletrack = 0.0, axis[3], trans[3];
bool 	trackingMouse  = false;
bool 	redrawContinue = false;
bool    trackballMove  = false;

/**************************************************************************************/
/******************************** Controle Track Ball *********************************/
/**************************************************************************************/

/*----------------------------------------------------------------------*/
/*
** These functions implement a simple trackball-like motion control.
*/

float lastPos[3] = {0.0, 0.0, 0.0};
int curx, cury;
int startX, startY;

void trackball_ptov(int x, int y, int width, int height, float v[3])
{
    float d, a;

    /* project x, y onto a hemi-sphere centered within width, height */
    //
    //	+-----------------------+	+
    //	|			|			|	|
    //	|			|	+		|	|
    //	|			|			|	|
    //	|-----------------------|	|	height
    //	|			|			|	|
    //	|			|			|	|
    //	|			|			|	|
    //	|			|			|	|
    //	+-----------------------+	+
    //
    //	+------width------------+
    //
    //  v[0] = (x - w/2)/(w/2)			in the range [-1, 1]
    //  v[1] = ((h -y) - h/2)/(h/2)		in the range [-1, 1]

    v[0] = (2.0*x  - width) / width;
    v[1] = (height - 2.0*y) / height;

    d = (float) sqrt(v[0]*v[0] + v[1]*v[1]);

    if (d < sqrt(2.0))
    {
        v[2] = sqrt(2.0 - d*d);
    }
    else
    {
        v[2] = 0.0;
    }

    //v[2] = (float) cos((M_PI/2.0) * ((d < 1.0) ? d : 1.0));

    a = 1.0 / (float) sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
    v[0] *= a;
    v[1] *= a;
    v[2] *= a;
}


void mouseMotion(int x, int y,int winWidth,int winHeight)
{
    float curPos[3], dx, dy, dz;

    trackball_ptov(x, y, winWidth, winHeight, curPos);
    if(trackingMouse)
    {
        dx = curPos[0] - lastPos[0];
        dy = curPos[1] - lastPos[1];
        dz = curPos[2] - lastPos[2];

        if (dx || dy || dz)
        {
            angletrack = 90.0 * sqrt(dx*dx + dy*dy + dz*dz);

            axis[0] = lastPos[1]*curPos[2] - lastPos[2]*curPos[1];
            axis[1] = lastPos[2]*curPos[0] - lastPos[0]*curPos[2];
            axis[2] = lastPos[0]*curPos[1] - lastPos[1]*curPos[0];

            lastPos[0] = curPos[0];
            lastPos[1] = curPos[1];
            lastPos[2] = curPos[2];
        }
    }
}

void startMotion(int x, int y,int winHeight,int winWidth)
{

    trackingMouse  = true;
    redrawContinue = false;
    startX	= x; startY = y;
    curx	= x; cury	= y;
    trackball_ptov(x, y, winWidth, winHeight, lastPos);
    trackballMove  = true;
}

void stopMotion(int x, int y)
{

    trackingMouse = false;

    if (startX != x || startY != y)
    {
        redrawContinue	= true;
    }
    else
    {
        angletrack		= 0.0;
        redrawContinue	= false;
        trackballMove	= false;
    }
}



//****************


GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(QGLFormat(QGL::SampleBuffers),parent)
{
    setFocusPolicy(Qt::StrongFocus);
    glEnable(GL_MULTISAMPLE);
    scene = new Scene();
    id_material = 0;
    //scene->pushObjects(BLOCK_CONE,MATERIAL_CHROME);
    updateLightingGL();
    listingObjects(scene->objects);
    listingLights(scene->lights);
    angle = 45.0;
    move = false;
    sizegrid = 20;
    showgrid = true;
    solidgrid = false;
    state_key = 0;
    q.setQuaternion(1,0,0,0);
    projection.setVec4(angle,45,0.01,120000.0);
    updateProjection(projection);
    showviewports = false;
    showhbb = false;
    showphotons = false;
    showphotonscaustic = false;
    //boundingboxes = new HBB();


}

Vec4 GLWidget::mappingViewVertex(int x, int y){
    Vec4 pos;
    float x1,x2;
    float max = qMax(height/2,width/2);
    x1 = x-(width/2);
    x2 = y-(height/2);
    x1 = (x1/max);
    x2 = (-x2/max);
    pos.setVec4(x1,x2);
    return pos;
}

void GLWidget::initializeGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_FUNC);
    glEnable(GL_POINT_SMOOTH);
    //glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);
    glEnable(GL_RESCALE_NORMAL);
    glLineWidth(1.0);
    glDepthFunc(1.0);
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);




        if (showgrid) Draw::drawPlane(sizegrid,solidgrid);
        scene->renderLightsOpenGL();
        scene->drawObjectsOpenGL();
        if (showhbb) boundingboxes->drawStructure();
            //boundingboxes->box.wireframe();
        scene->drawPhotons(showphotons);
        scene->drawPhotonsCaustic(showphotonscaustic);

        glPushMatrix();
        drawInformation();
        glPopMatrix();

    //updateGL();
    //glPopMatrix();

    //updateCameraGL();




}

void GLWidget::resizeGL(int w, int h)
{
    width  = w;
    height = h;

    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    scene->pushProjection(angle,(float)width/(float)height,projection.z(),projection.w());
    gluPerspective(angle,(float)width/(float)height,projection.z(),projection.w());
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(cam->eye.x(),cam->eye.y(),cam->eye.z(),cam->at.x(),cam->at.y(),cam->at.z(),cam->up.x(),cam->up.y(),cam->up.z());
    //gluLookAt(cam_eye.x1,cam_eye.x2,cam_eye.x3,cam_at.x1,cam_at.x2,cam_at.x3,cam_up.x1,cam_up.x2,cam_up.x3);
    projection.setVec4(angle,(float)width/(float)height,projection.z(),projection.w());
    updateProjection(projection);
    scene->pushViewport(width,height);
    scene->pushViewer(cam->eye,cam->at,cam->up);
    //scene->pushViewer(cam_eye,cam_at,cam_up);

    widgetWidth(width);
    widgetHeight(height);





}

void GLWidget::updateCamera(Vec4 eye, Vec4 at, Vec4 up)
{

    cam->eye = eye;
    cam->at  = at;
    cam->up  = up;
//    last_pos = at;
    updateCameraGL();
    //getCam(scene->viewer[0],scene->viewer[1],scene->viewer[2]);

}

void GLWidget::updateCameraGL()
{
    glViewport(0,0,width,height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    scene->pushProjection(angle,(float)width/(float)height,projection.z(),projection.w());
    gluPerspective(angle,(float)width/(float)height,projection.z(),projection.w());
    projection.setVec4(angle,(float)width/(float)height,projection.z(),projection.w());
    updateProjection(projection);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(cam->eye.x(),cam->eye.y(),cam->eye.z(),cam->at.x(),cam->at.y(),cam->at.z(),cam->up.x(),cam->up.y(),cam->up.z());
    scene->pushViewport(width,height);
    scene->pushViewer(cam->eye,cam->at,cam->up);
    //qDebug() << "Update Cam!" << scene->viewer[0].debug();
    //scene->viewer[0].showVec4();
    getCam(scene->viewer[0],scene->viewer[1],scene->viewer[2]);
    updateGL();

}

void GLWidget::wheelEvent(QWheelEvent *event)
{
    int numDegrees = event->delta() / 8;
    int numSteps = numDegrees / 15;
    if (numSteps>0 && angle<180.0){
        angle += 1;
    }
    else{
        if (!(angle<=5)){
            angle -= 1;
        }
    }
    updateCameraGL();
    //updateGL();

}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{

    int y = event->pos().y();
    int x = event->pos().x();
    if (lbpressed && !rbpressed) {
        cam->rotatex(y,last_y);
        cam->rotatey(x,last_x);
    }
    if (!lbpressed && rbpressed) {
        cam->translatex(x,last_x);
        cam->translatey(y,last_y);

    }
    if (lbpressed && rbpressed) {
        cam->zoom(y,last_y);

    }

    last_x = x;
    last_y = y;
    updateCameraGL();


//    if(event->buttons() & Qt::LeftButton){
//        //rever função de rotação da câmera
//        //        move = true;
//        //        int pos_x = event->x();
//        //        int pos_y = event->y();
//        //        if(pos_x>height|| pos_y>width) return;
//        //        int raio = 1;
//        //        Vec4 pnow = mappingViewVertex(pos_x,pos_y);
//        //        pnow.x3 = sqrt(raio-pnow.x1*pnow.x1-pnow.x2*pnow.x2);
//        //        if(isnan(pnow.x3)) return;

//        //        Vec4 v = Vec4::crossProduct(last_pos,pnow);

//        //        double angle = acos((last_pos*pnow)/(last_pos.module()*pnow.module()));

//        //        Quaternion qnew;
//        //        qnew.setQuaternion(cos(raio*angle/(2.0)),v*sin(raio*angle/(2.0)));
//        //        qnew = qnew.normalize();
//        //        q = q*qnew;
//        //        Vec4 teste;
//        //        cam_eye = q.getMatrix().vector(cam_eye);


//        //        if (isnan(-cam_eye.x1)||isnan(-cam_eye.x2)) cam_eye = teste;
//        //        if (cam_eye == Vec4()) cam_eye = teste;
//        //        getCamEye(cam_eye);
//        //        last_pos = pnow;
//        int y = height-event->pos().y();
//        mouseMotion(event->pos().x(),y,height,width);
//        if (trackingMouse) {
//            //glRotatef(angletrack, axis[0], axis[1], axis[2]);

//            Quaternion qnew;
//            //qnew.setQuaternion(Vec4(axis[0],axis[1],axis[2],angletrack));
//            qnew.setQuaternion(cos(angletrack*M_PI/(180.0)),Vec4(axis[0],axis[1],axis[2]).unitary()*sin(angletrack*M_PI/(180.0)));
//            //qnew = qnew.normalize();
//            //q = q.normalize();
//            q = qnew*q;
//            //q = q.normalize();
//            q = qnew.normalize();

//            cam_eye = q.getMatrix().vector(cam_eye);



//        }
//        //        if (trackingMouse) {
//        //                //glRotatef(angletrack, axis[0], axis[1], axis[2]);
//        //                Quaternion qnew;
//        //                qnew.setQuaternion(cos(angletrack*0.5),Vec4(axis[0],axis[1],axis[2])*sin(angletrack*0.5));
//        //                qnew = qnew.normalize();
//        //                q = q.normalize();
//        //                q = q-qnew;
//        //                q = q.normalize();
//        //                //Vec4 teste;
//        //                cam_eye = q.getMatrix().vector(cam_eye);

//        //                getCamEye(cam_eye);
//        //                //updateCameraGL();
//        //                //updateGL();

//        //        }
//        getCamEye(cam_eye);
//        //updateGL();


//    }



    //getCamEye(cam_eye);



}

void GLWidget::mouseReleaseEvent(QMouseEvent *event)
{
    int y = event->pos().y();
    int x = event->pos().x();
    if (event->button() & Qt::LeftButton) {
        // when the button is pressed
        lbpressed = false;
    }
    // if the left button is pressed
    if (event->button() & Qt::RightButton) {
        // when the button is pressed
        rbpressed = false;
    }
    last_x = x;
    last_y = y;
    updateCameraGL();
    //getCamEye(cam->eye);
//    move = false;
//    trackingMouse = false;
//    int y = height-event->pos().y();
//    stopMotion(event->pos().x(),y);
    //getCamEye(cam_eye);
    //q.setQuaternion(1,0,0,0);
    //printf("nao move");
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    if((modeview==MODE_OBJECT) & (event->button() == Qt::LeftButton)){
        updateCameraGL();
        Object *obj_sel = RayTracing::objectClicked(scene,event->pos().x(),height-event->pos().y());
        setSelectedObject(obj_sel);
    }else if((modeview==MODE_OBJECT) & (event->button() == Qt::RightButton)){
        updateCameraGL();
        QMenu menu;
        QMenu *openAct = new QMenu("Add Object");
        QMenu *openAct2 = new QMenu("Add Light");
        QAction *obj_cube= new QAction("Cube", this);
        QAction *obj_cone= new QAction("Cone", this);
        QAction *obj_sphere= new QAction("Sphere", this);
        QAction *obj_cylinder= new QAction("Cylinder", this);
        QAction *obj_hemisphere= new QAction("Hemisphere", this);
        QAction *obj_plane= new QAction("Plane", this);
        QAction *obj_prism= new QAction("Prism", this);
        connect(obj_cube,SIGNAL(triggered()),this,SLOT(addCube()));
        connect(obj_cone,SIGNAL(triggered()),this,SLOT(addCone()));
        connect(obj_sphere,SIGNAL(triggered()),this,SLOT(addSphere()));
        connect(obj_cylinder,SIGNAL(triggered()),this,SLOT(addCylinder()));
        connect(obj_hemisphere,SIGNAL(triggered()),this,SLOT(addHemisphere()));
        connect(obj_plane,SIGNAL(triggered()),this,SLOT(addPlane()));
        connect(obj_prism,SIGNAL(triggered()),this,SLOT(addPrism()));
        openAct->addAction(obj_cube);
        openAct->addAction(obj_cone);
        openAct->addAction(obj_sphere);
        openAct->addAction(obj_cylinder);
        openAct->addAction(obj_hemisphere);
        openAct->addAction(obj_plane);
        openAct->addAction(obj_prism);
        menu.addMenu(openAct);
        QAction *lig_area= new QAction("Area", this);
        QAction *lig_direct= new QAction("Directional", this);
        QAction *lig_pontual= new QAction("Pontual", this);
        QAction *lig_spot= new QAction("Spot", this);
        connect(lig_area,SIGNAL(triggered()),this,SLOT(addArea()));
        connect(lig_direct,SIGNAL(triggered()),this,SLOT(addDirectional()));
        connect(lig_pontual,SIGNAL(triggered()),this,SLOT(addPontual()));
        connect(lig_spot,SIGNAL(triggered()),this,SLOT(addSpot()));
        openAct2->addAction(lig_area);
        openAct2->addAction(lig_direct);
        openAct2->addAction(lig_pontual);
        openAct2->addAction(lig_spot);
        menu.addSeparator();
        menu.addMenu(openAct2);
        menu.exec(mapToGlobal(event->pos()));
        //QGLWidget::mouseReleaseEvent(event);
        updateCameraGL();
        return;
    }

    int y = event->pos().y();
    int x = event->pos().x();
    // if the left button isessed
    if (event->button() & Qt::LeftButton) {
        // when the button is pressed
        lbpressed = true;
    }
    // if the left button is pressed
    if (event->button() & Qt::RightButton) {
        // when the button is pressed
        rbpressed = true;
    }

    last_x = x;
    last_y = y;
    //GLWidget::mouseReleaseEvent(event);
    updateCameraGL();
}

void GLWidget::setDefaultWorld()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    move = false;
}

void GLWidget::updateLightingGL()
{

    Vec4 *light1pos           =    new Vec4(-10, 10, 10, 1.0 );
    Vec4 *light1diffuse       = new Vec4( 0.8f, 0.8f, 0.8, 1.0);
    Vec4 *light1specular      = new Vec4( 0.5f, 0.5f, 0.5f, 1.0 );
    PontualLight* direct1     = new PontualLight();
    direct1->setLight(light1pos,light1diffuse,light1specular);
    //direct1->factor_attenuation->setVec4(1.0,0.002,0);
    scene->pushLights(direct1);


    Vec4 *light2dir           = new Vec4( -0.588, -0.80, -0.248, 0.0);
    Vec4 *light2pos           = new Vec4( 6.0, 7.0, 3.0, 1.0);
    Vec4 *light2diffuse       = new Vec4(1.0f, 1.0f, 1.0, 1.0);
    Vec4 *light2specular      = new Vec4( 1.0, 1.0f, 1.0f, 1.0 );
    Vec4 *light2ambient       = new Vec4( 0.2, 0.2f, 0.2f, 1.0 );

    SpotLight* direct2        = new SpotLight();
    direct2->setLight(70,0,light2pos,light2dir,light2diffuse,light2specular,light2ambient);
    //scene->pushLights(direct2);

    Vec4* light3pos           = new Vec4( -0.5, 0.5, -0.5, 0.0 );
    Vec4* light3diffuse       = new Vec4( 0.798f, 0.838f, 1.0, 1.0 );
    Vec4* light3specular      = new Vec4( 0.06f, 0.0f, 0.0f, 1.0 );
    DirectionalLight* direct3 = new DirectionalLight();
    direct3->setLight(light3pos,light3diffuse,light3specular,new Vec4());
    //scene->pushLights(direct3);


    //    listingLights(scene->lights);
    //    updateGL();

}

void GLWidget::keyPressEvent(QKeyEvent *event)
{


    if(event->modifiers()==Qt::CTRL && event->key() == Qt::Key_C ){
        if (scene->getObjecSelected()){
            scene->makeClone(scene->getObjecSelected());
            listingObjects(scene->objects);
            showObjectSelected(scene->getObjecSelected());
        }
    }

    if(event->key() == Qt::Key_O){
        modeview = MODE_OBJECT;
        if(state_key == event->key()){
            state_key = 0;
        }else{
            state_key = event->key();
        }
    }

    if(event->key() == Qt::Key_C){
        modeview = MODE_DEFAULT;
    }

    if(event->key() == Qt::Key_S ){
        modeview = MODE_SCALE;
        if(state_key == event->key()){
            state_key = 0;
        }else{
            state_key = event->key();
        }
    }

    if(event->key() == Qt::Key_T ){
        modeview = MODE_TRANSLATE;
        if(state_key == event->key()){
            state_key = 0;
        }else{
            state_key = event->key();
        }
    }

    if(event->key() == Qt::Key_R ){
        modeview = MODE_ROTATE;
        if(state_key == event->key()){
            state_key = 0;
        }else{
            state_key = event->key();
        }
    }

    if(event->key() == Qt::Key_Delete ){
        if (modeview!=MODE_DEFAULT && scene->getObjecSelected())
            removeObjectSelected();
    }





    if(modeview == MODE_ROTATE){
        if(event->key() == Qt::Key_Right && event->modifiers()==Qt::ShiftModifier){ //scale +z
            for(int i=0;i<scene->objects.size();i++){
                if(scene->objects.at(i)->isSelected()){

                    Matrix4x4 mat = scene->objects.at(i)->getMatrixTransformation();
                    Matrix4x4 new_mat;
                    new_mat.setIdentity();
                    new_mat.scale(mat.scale_m[0],mat.scale_m[5],mat.scale_m[10]);
                    if (mat.rotz+1>360) mat.rotz =  mat.rotz-1;
                    new_mat.setRotationZ(mat.rotz+1);
                    new_mat.setRotationY(mat.roty);
                    new_mat.setRotationX(mat.rotx);
                    new_mat.setTranslate(Vec4(mat.translate_m[12],mat.translate_m[13],mat.translate_m[14]));
                    setTransformMatrixToObjectSelected(new_mat);
                    updateObjectInterface();
                    return;
                }
            }


        }
        else if(event->key() == Qt::Key_Left && event->modifiers()==Qt::ShiftModifier){ //scale -z
            for(int i=0;i<scene->objects.size();i++){
                if(scene->objects.at(i)->isSelected()){


                    Matrix4x4 mat = scene->objects.at(i)->getMatrixTransformation();
                    Matrix4x4 new_mat;
                    new_mat.setIdentity();
                    new_mat.scale(mat.scale_m[0],mat.scale_m[5],mat.scale_m[10]);
                    if (mat.rotz-1<0) mat.rotz = mat.rotz+1;
                    new_mat.setRotationZ(mat.rotz-1);
                    new_mat.setRotationY(mat.roty);
                    new_mat.setRotationX(mat.rotx);
                    new_mat.setTranslate(Vec4(mat.translate_m[12],mat.translate_m[13],mat.translate_m[14]));


                    setTransformMatrixToObjectSelected(new_mat);
                    updateObjectInterface();
                    return;
                }
            }
        }
        else if(event->key() == Qt::Key_Left ){ //scale -x
            for(int i=0;i<scene->objects.size();i++){
                if(scene->objects.at(i)->isSelected()){
                    Matrix4x4 mat = scene->objects.at(i)->getMatrixTransformation();
                    Matrix4x4 new_mat;
                    new_mat.setIdentity();
                    new_mat.scale(mat.scale_m[0],mat.scale_m[5],mat.scale_m[10]);
                    new_mat.setRotationZ(mat.rotz);
                    new_mat.setRotationY(mat.roty);
                    if (mat.rotx-1<0) mat.rotx = mat.rotx+1;
                    new_mat.setRotationX(mat.rotx-1);
                    new_mat.setTranslate(Vec4(mat.translate_m[12],mat.translate_m[13],mat.translate_m[14]));


                    setTransformMatrixToObjectSelected(new_mat);
                }
            }
        }
        else if(event->key() == Qt::Key_Right){//scale +x
            for(int i=0;i<scene->objects.size();i++){
                if(scene->objects.at(i)->isSelected()){
                    Matrix4x4 mat = scene->objects.at(i)->getMatrixTransformation();
                    Matrix4x4 new_mat;
                    new_mat.setIdentity();
                    new_mat.scale(mat.scale_m[0],mat.scale_m[5],mat.scale_m[10]);
                    new_mat.setRotationZ(mat.rotz);
                    new_mat.setRotationY(mat.roty);
                    if (mat.rotx+1>360) mat.rotx = mat.rotx-1;
                    new_mat.setRotationX(mat.rotx+1);
                    new_mat.setTranslate(Vec4(mat.translate_m[12],mat.translate_m[13],mat.translate_m[14]));


                    setTransformMatrixToObjectSelected(new_mat);
                }
            }
        }
        else if(event->key() == Qt::Key_Up){//scale +y
            for(int i=0;i<scene->objects.size();i++){
                if(scene->objects.at(i)->isSelected()){
                    Matrix4x4 mat = scene->objects.at(i)->getMatrixTransformation();
                    Matrix4x4 new_mat;
                    new_mat.setIdentity();
                    new_mat.scale(mat.scale_m[0],mat.scale_m[5],mat.scale_m[10]);
                    new_mat.setRotationZ(mat.rotz);
                    if (mat.roty+1>360) mat.roty = mat.roty-1;
                    new_mat.setRotationY(mat.roty+1);
                    new_mat.setRotationX(mat.rotx);
                    new_mat.setTranslate(Vec4(mat.translate_m[12],mat.translate_m[13],mat.translate_m[14]));


                    setTransformMatrixToObjectSelected(new_mat);
                }
            }
        }
        else if(event->key() == Qt::Key_Down){////scale -y
            for(int i=0;i<scene->objects.size();i++){
                if(scene->objects.at(i)->isSelected()){
                    Matrix4x4 mat = scene->objects.at(i)->getMatrixTransformation();
                    Matrix4x4 new_mat;
                    new_mat.setIdentity();
                    new_mat.scale(mat.scale_m[0],mat.scale_m[5],mat.scale_m[10]);
                    new_mat.setRotationZ(mat.rotz);
                    if (mat.roty-1<0) mat.roty = mat.roty+1;
                    new_mat.setRotationY(mat.roty-1);
                    new_mat.setRotationX(mat.rotx);
                    new_mat.setTranslate(Vec4(mat.translate_m[12],mat.translate_m[13],mat.translate_m[14]));


                    setTransformMatrixToObjectSelected(new_mat);
                }
            }
        }
        for(int i=0;i<scene->objects.size();i++){
            if(scene->objects.at(i)->isSelected()){

                showObjectSelected(scene->objects.at(i));

            }
        }
    }

    float step = 0.1;


    if(modeview == MODE_TRANSLATE){
        if(event->key() == Qt::Key_Right && event->modifiers()==Qt::ShiftModifier){ //scale +z
            for(int i=0;i<scene->objects.size();i++){
                if(scene->objects.at(i)->isSelected()){

                    Matrix4x4 mat = scene->objects.at(i)->getMatrixTransformation();
                    mat.translate(0,0,step);
                    setTransformMatrixToObjectSelected(mat);
                    updateObjectInterface();
                    return;
                }
            }


        }
        else if(event->key() == Qt::Key_Left && event->modifiers()==Qt::ShiftModifier){ //scale -z
            for(int i=0;i<scene->objects.size();i++){
                if(scene->objects.at(i)->isSelected()){

                    Matrix4x4 mat = scene->objects.at(i)->getMatrixTransformation();
                    mat.translate(0,0,-step);
                    setTransformMatrixToObjectSelected(mat);
                    updateObjectInterface();
                    return;
                }
            }
        }
        else if(event->key() == Qt::Key_Left ){ //scale -x
            for(int i=0;i<scene->objects.size();i++){
                if(scene->objects.at(i)->isSelected()){

                    Matrix4x4 mat = scene->objects.at(i)->getMatrixTransformation();
                    mat.translate(-step,0,0);
                    setTransformMatrixToObjectSelected(mat);
                }
            }
        }
        else if(event->key() == Qt::Key_Right){//scale +x
            for(int i=0;i<scene->objects.size();i++){
                if(scene->objects.at(i)->isSelected()){

                    Matrix4x4 mat = scene->objects.at(i)->getMatrixTransformation();
                    mat.translate(step,0,0);
                    setTransformMatrixToObjectSelected(mat);
                }
            }
        }
        else if(event->key() == Qt::Key_Up){//scale +y
            for(int i=0;i<scene->objects.size();i++){
                if(scene->objects.at(i)->isSelected()){

                    Matrix4x4 mat = scene->objects.at(i)->getMatrixTransformation();
                    mat.translate(0,step,0);
                    setTransformMatrixToObjectSelected(mat);
                }
            }
        }
        else if(event->key() == Qt::Key_Down){////scale -y
            for(int i=0;i<scene->objects.size();i++){
                if(scene->objects.at(i)->isSelected()){

                    Matrix4x4 mat = scene->objects.at(i)->getMatrixTransformation();
                    mat.translate(0,-step,0);
                    setTransformMatrixToObjectSelected(mat);
                }
            }
        }
        for(int i=0;i<scene->objects.size();i++){
            if(scene->objects.at(i)->isSelected()){

                showObjectSelected(scene->objects.at(i));

            }
        }
    }

    if(modeview == MODE_SCALE){
        if(event->key() == Qt::Key_Right && event->modifiers()==Qt::ShiftModifier){ //scale +z
            for(int i=0;i<scene->objects.size();i++){
                if(scene->objects.at(i)->isSelected()){
                    Matrix4x4 mat = scene->objects.at(i)->getMatrixTransformation();
                    mat.addscale(0,0,step);
                    setTransformMatrixToObjectSelected(mat);
                    updateObjectInterface();
                    return;
                }
            }


        }
        else if(event->key() == Qt::Key_Left && event->modifiers()==Qt::ShiftModifier){ //scale -z
            for(int i=0;i<scene->objects.size();i++){
                if(scene->objects.at(i)->isSelected()){

                    Matrix4x4 mat = scene->objects.at(i)->getMatrixTransformation();
                    mat.addscale(0,0,-step);
                    setTransformMatrixToObjectSelected(mat);
                    updateObjectInterface();
                    return;
                }
            }
        }
        else if(event->key() == Qt::Key_Left ){ //scale -x
            for(int i=0;i<scene->objects.size();i++){
                if(scene->objects.at(i)->isSelected()){

                    Matrix4x4 mat = scene->objects.at(i)->getMatrixTransformation();
                    mat.addscale(-step,0,0);
                    setTransformMatrixToObjectSelected(mat);
                }
            }
        }
        else if(event->key() == Qt::Key_Right){//scale +x
            for(int i=0;i<scene->objects.size();i++){
                if(scene->objects.at(i)->isSelected()){

                    Matrix4x4 mat = scene->objects.at(i)->getMatrixTransformation();
                    mat.addscale(step,0,0);
                    setTransformMatrixToObjectSelected(mat);
                }
            }
        }
        else if(event->key() == Qt::Key_Up){//scale +y
            for(int i=0;i<scene->objects.size();i++){
                if(scene->objects.at(i)->isSelected()){

                    Matrix4x4 mat = scene->objects.at(i)->getMatrixTransformation();
                    mat.addscale(0,step,0);
                    setTransformMatrixToObjectSelected(mat);
                }
            }
        }
        else if(event->key() == Qt::Key_Down){////scale -y
            for(int i=0;i<scene->objects.size();i++){
                if(scene->objects.at(i)->isSelected()){

                    Matrix4x4 mat = scene->objects.at(i)->getMatrixTransformation();
                    mat.addscale(0,-step,0);
                    setTransformMatrixToObjectSelected(mat);

                }
            }
        }
        updateObjectInterface();
    }

    if(state_key==0){
        if(event->key() == Qt::Key_Up && event->modifiers()==Qt::ShiftModifier){
            cam_at.x3 += 1;
            return;
        }else if(event->key() == Qt::Key_Down && event->modifiers()==Qt::ShiftModifier){
            cam_at.x3 -= 1;
            return;
        }else if(event->key() == Qt::Key_Left )
            cam_at.x1 -= 1;
        else if(event->key() == Qt::Key_Right)
            cam_at.x1 += 1;
        else if(event->key() == Qt::Key_Up)
            cam_at.x2 += 1;
        else if(event->key() == Qt::Key_Down)
            cam_at.x2 -= 1;
    }

    getCam(cam->eye,cam->at,cam->up);
    stateSelected(state_key);
    updateGL();


}

Scene * GLWidget::getScene()
{
    return scene;
}

void GLWidget::setObject(int id)
{
    scene->lights.clear();
    scene->pushObjects(id,id_material);
    if(scene->lights.size()>1){
        scene->iterl = scene->lights.begin();
        scene->iterl++;
        for(int i=0;i<scene->lights.size()+1;i++){
            scene->lights.erase(scene->iterl);

        }
    }
    updateLightingGL();
    listingObjects(scene->objects);
    listingLights(scene->lights);
    updateGL();
}

void GLWidget::setMaterialAllObjects(int id)
{
    id_material = id;
    scene->setMaterialAllObjects(id);

    updateGL();
}

void GLWidget::saveImagem(QString str)
{
    str.push_back(".tga");
    Functions::saveImage(width,height,str.toStdString());
}

void GLWidget::setSelectedObject(int k)
{
    for (int i=0;i<scene->objects.size();i++){
        scene->objects.at(i)->setSelected(false);
        if (i==k){
            scene->objects.at(k)->setSelected(true);
            showObjectSelected(scene->objects.at(k));
        }
    }

    //if ((int)scene->objects.<=(k+1)){

    //}
    updateGL();
}

void GLWidget::setMotionObjectSelected(Vec4 motion)
{
    for(int i=0;i<scene->objects.size();i++){
        if(scene->objects.at(i)->isSelected()) scene->objects.at(i)->setMotion(motion);
    }
}


void GLWidget::setSelectedObject(Object* obj)
{
    if(obj==NULL) return;
    for (int i=0;i<scene->objects.size();i++) scene->objects.at(i)->setSelected(false);
    if(obj!=NULL){
        obj->setSelected(true);
        showObjectSelected(obj);
    }
    updateCameraGL();


}

int GLWidget::getItemSelected()
{
    for(int i=0;i<scene->objects.size();i++){
        if(scene->objects.at(i)->isSelected()) return i;
    }
    return -1;

}

void GLWidget::setTransformMatrixToObjectSelected(Matrix4x4 m)
{
    for(int i=0;i<scene->objects.size();i++){
        if(scene->objects.at(i)->isSelected()) scene->objects.at(i)->setTransform(m);
    }
    updateGL();
}

void GLWidget::setIdMaterialToObjectSelected(int m)
{
    for(int i=0;i<scene->objects.size();i++){
        if(scene->objects.at(i)->isSelected()) scene->objects.at(i)->setMaterial(m);
    }
    updateGL();

}

void GLWidget::addCube()
{
    Object *obj = scene->addObject(OBJCUBE);
    listingObjects(scene->objects);
    setSelectedObject(obj);
    updateGL();
}

void GLWidget::addCone()
{
    Object *obj = scene->addObject(OBJCONE);
    listingObjects(scene->objects);
    setSelectedObject(obj);
    updateGL();
}

void GLWidget::addCylinder()
{
    Object *obj = scene->addObject(OBJCYLINDER);
    listingObjects(scene->objects);
    setSelectedObject(obj);
    updateGL();
}

void GLWidget::addSphere()
{
    Object *obj = scene->addObject(OBJSPHERE);
    listingObjects(scene->objects);
    setSelectedObject(obj);
    updateGL();
}

void GLWidget::addPlane()
{
    Object *obj = scene->addObject(OBJPLANE);
    listingObjects(scene->objects);
    setSelectedObject(obj);
    updateGL();
}

void GLWidget::addHemisphere()
{
    Object *obj = scene->addObject(OBJHEMISPHERE);
    listingObjects(scene->objects);
    setSelectedObject(obj);
    updateGL();
}

void GLWidget::addPrism()
{
    Object *obj = scene->addObject(OBJPRISM);
    listingObjects(scene->objects);
    setSelectedObject(obj);
    updateGL();
}

void GLWidget::addArea()
{
    Light *light = scene->addLight(LIGHT_AREA);
    listingLights(scene->lights);
    light->setEnabled(true);
    light->setVisible(true);
    showLightSelected(light);
    updateCameraGL();
}

void GLWidget::addDirectional()
{
    Light *light = scene->addLight(LIGHT_DIRECTIONAL);
    listingLights(scene->lights);
    light->setEnabled(true);
    light->setVisible(true);
    showLightSelected(light);
    updateCameraGL();
}

void GLWidget::addSpot()
{
    Light *light = scene->addLight(LIGHT_SPOT);
    listingLights(scene->lights);
    light->setEnabled(true);
    light->setVisible(true);
    showLightSelected(light);
    updateCameraGL();
}

void GLWidget::addPontual()
{
    Light *light = scene->addLight(LIGHT_PONTUAL);
    listingLights(scene->lights);
    light->setEnabled(true);
    light->setVisible(true);
    showLightSelected(light);
    updateCameraGL();
}

void GLWidget::setEnabledObjectSelected(bool b)
{
    for(int i=0;i<scene->objects.size();i++){
        if(scene->objects.at(i)->isSelected()) scene->objects.at(i)->setEnabled(b);
    }
    updateGL();

}

void GLWidget::setNameObjectSelected(QString s)
{
    for(int i=0;i<scene->objects.size();i++){
        if(scene->objects.at(i)->isSelected()) scene->objects.at(i)->setName(s);
    }
    updateGL();

}

std::vector<Object *> GLWidget::getObjectsScene()
{
    return scene->objects;
}

void GLWidget::addObject(int type)
{
    scene->addObject(type);
    listingObjects(scene->objects);
    updateGL();
}

void GLWidget::removeObjectSelected()
{
    scene->iter = scene->objects.begin();
    for(int i=0;i<scene->objects.size();i++){

        if(scene->objects.at(i)->isSelected()){
            scene->objects.erase(scene->iter);
            break;
        }
        scene->iter++;
    }
    listingObjects(scene->objects);
    updateGL();
}

void GLWidget::setSelectedLight(int k)
{
    for (int i=0;i<scene->lights.size();i++){
        scene->lights.at(i)->setSelected(false);
        if (i==k){
            scene->lights.at(k)->setSelected(true);
            showLightSelected(scene->lights.at(k));
        }
    }
    updateGL();
}

void GLWidget::setLightSelectedDiffuse(QColor color)
{
    for (int i=0;i<scene->lights.size();i++){
        if(scene->lights.at(i)->isSelected()) scene->lights.at(i)->setDiffuseColor(color);
    }
    updateGL();

}

void GLWidget::setLightSelectedAmbient(QColor color)
{
    for (int i=0;i<scene->lights.size();i++){
        if(scene->lights.at(i)->isSelected()) scene->lights.at(i)->setAmbientColor(color);
    }
    updateGL();
}

void GLWidget::setLightSelectedSpecular(QColor color)
{
    for (int i=0;i<scene->lights.size();i++){
        if(scene->lights.at(i)->isSelected()) scene->lights.at(i)->setSpecularColor(color);
    }
    updateGL();
}

void GLWidget::setEnabledLightSelected(bool b)
{
    for (int i=0;i<scene->lights.size();i++){
        if(scene->lights.at(i)->isSelected()) scene->lights.at(i)->setEnabled(b);
    }
    updateGL();
}

void GLWidget::setVisibleLightSelected(bool b)
{
    for (int i=0;i<scene->lights.size();i++){
        if(scene->lights.at(i)->isSelected()) scene->lights.at(i)->setVisible(b);
    }
    updateGL();
}

void GLWidget::setDOF(float radius, float focal)
{
    scene->setDOF(radius,focal);
    updateGL();
}

void GLWidget::setLightSelectedDirection(Vec4 dir)
{
    for (int i=0;i<scene->lights.size();i++){
        if(scene->lights.at(i)->isSelected()) scene->lights.at(i)->setDirection(dir);
    }
    updateGL();

}

void GLWidget::setLightSelectedPosition(Vec4 pos)
{
    for (int i=0;i<scene->lights.size();i++){
        if(scene->lights.at(i)->isSelected()) scene->lights.at(i)->setPosition(pos);
    }
    updateGL();
}

void GLWidget::setLightSelectedAttenuation(Vec4 att)
{
    for (int i=0;i<scene->lights.size();i++){
        if(scene->lights.at(i)->isSelected()) scene->lights.at(i)->setAttenuation(att);
    }
    updateGL();
}

void GLWidget::setLightSelectedAngle(int angle)
{
    for (int i=0;i<scene->lights.size();i++){
        if(scene->lights.at(i)->isSelected()) scene->lights.at(i)->setAngle(angle);
    }
    updateGL();
}

void GLWidget::setLightSelectedAngleInner(int angle)
{
    for (int i=0;i<scene->lights.size();i++){
        if(scene->lights.at(i)->isSelected()) scene->lights.at(i)->setAngleInner(angle);
    }
    updateGL();
}

void GLWidget::setLightSelectedExponent(int exp)
{
    for (int i=0;i<scene->lights.size();i++){
        if(scene->lights.at(i)->isSelected()) scene->lights.at(i)->setExponent(exp);
    }
    updateGL();
}

void GLWidget::setLightSelectedName(QString s)
{
    for (int i=0;i<scene->lights.size();i++){
        if(scene->lights.at(i)->isSelected()) scene->lights.at(i)->setName(s);
    }
    updateGL();
}

void GLWidget::setLightSelectedVecA(Vec4 a)
{
    for (int i=0;i<scene->lights.size();i++){
        if(scene->lights.at(i)->isSelected()) scene->lights.at(i)->setVecA(a);
    }
    updateGL();
}

void GLWidget::setLightSelectedVecB(Vec4 b)
{
    for (int i=0;i<scene->lights.size();i++){
        if(scene->lights.at(i)->isSelected()) scene->lights.at(i)->setVecB(b);
    }
    updateGL();
}

void GLWidget::setEnergyLight(int energy)
{
    for (int i=0;i<scene->lights.size();i++){
        if(scene->lights.at(i)->isSelected()) scene->lights.at(i)->setPower(energy);
    }
    updateGL();
}

std::vector<Light *> GLWidget::getLightsScene()
{
    return scene->lights;
}



void GLWidget::removeLightSelected()
{
    scene->iterl = scene->lights.begin();
    for(int i=0;i<scene->lights.size();i++){

        if(scene->lights.at(i)->isSelected()){
            scene->lights.erase(scene->iterl);
            break;
        }
        scene->iterl++;
    }
    listingLights(scene->lights);
    updateGL();
}

void GLWidget::setLightSelected(bool b)
{
    for (int i=0;i<scene->lights.size();i++){
        if(scene->lights.at(i)->isSelected()) scene->lights.at(i)->setSelected(b);
    }
    updateGL();
}

void GLWidget::addLight(int val)
{
    scene->addLight(val);
    listingLights(scene->lights);
    updateGL();
}

void GLWidget::showGrid(bool b)
{
    showgrid = b;
    updateGL();
}

void GLWidget::sizeGrid(int i)
{
    sizegrid = i;
    updateGL();
}

void GLWidget::solidGrid(bool b)
{
    solidgrid = b;
    updateGL();
}

void GLWidget::updateProjectionOut(Vec4 projection)
{
    angle = projection.x();
    this->projection.x1 = projection.x();
    this->projection.x3 = projection.z();
    this->projection.x4 = projection.w();
    updateCameraGL();
    updateGL();
}

void GLWidget::showViewports(bool b)
{
    showviewports = b;
    updateCameraGL();
    updateGL();
}

void GLWidget::showHBB(bool s)
{
    //create = true;
    showhbb = s;
    if (s) boundingboxes = new HBB(scene->objects,0);
    updateGL();

}

void GLWidget::saveScene(QString file,bool b)
{
    //file.push_back(".rc");
    scene->pushViewer(cam->eye,cam->at,cam->up);
    //Functions::saveScene(scene,file);
    Functions::saveSceneXML(scene,file,b);

}


void GLWidget::loadScene(QString file)
{
    showhbb = false;
    Functions::loadSceneXML(this->scene,file);
    std::vector<Object*> objects = this->scene->objects;
    for(int i=0;i<objects.size();i++) objects.at(i)->setSelected(false);
    updateProjection(scene->projection);
    cam->eye = scene->viewer[0];
    cam->at = scene->viewer[1];
    cam->up = scene->viewer[2];
    listingObjects(scene->objects);
    listingLights(scene->lights);
    radiusDOF(scene->radius);
    focalDOF(scene->focal);
    updateCameraGL();
    //getCam(scene->viewer[0],scene->viewer[1],scene->viewer[2]);

}

void GLWidget::drawInformation()
{
    if (modeview==0) return;
    QString dados;
    glDisable(GL_LIGHTING);
    glColor3f(1,1,0);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0.0, winWidth, 0.0, winHeight);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    int x = 680;
    int k = 0;
    glRasterPos2f(-0.99, -0.99);
    switch (modeview) {
    case MODE_OBJECT:{
        dados = "MODE OBJECT";
        k = 0;
        while (k<dados.size()){
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,dados.at(k).toLatin1());
            k++;
        }
        break;
    }
    case MODE_TRANSLATE:{
        dados = QString().sprintf("MODE TRANSLATE (ARROW LEFT & RIGHT - AXIS X; ARROW UP & DOWN - AXIS Y; SHIFT + ARROW LEFT & RIGHT - AXIS Z)");
        k = 0;
        while (k<dados.size()){
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,dados.at(k).toLatin1());
            k++;
        }
        break;
    }
    case MODE_ROTATE:{
        dados = QString().sprintf("MODE ROTATE (ARROW LEFT & RIGHT - AXIS X; ARROW UP & DOWN - AXIS Y; SHIFT + ARROW LEFT & RIGHT - AXIS Z)");
        k = 0;
        while (k<dados.size()){
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,dados.at(k).toLatin1());
            k++;
        }
        break;
    }
    case MODE_SCALE:{
        dados = QString().sprintf("MODE SCALE (ARROW LEFT & RIGHT - AXIS X; ARROW UP & DOWN - AXIS Y; SHIFT + ARROW LEFT & RIGHT - AXIS Z)");
        k = 0;
        while (k<dados.size()){
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,dados.at(k).toLatin1());
            k++;
        }
        break;
    }
    default:

        break;
    }

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glEnable(GL_LIGHTING);
}

void GLWidget::updateObjectInterface()
{
    for(int i=0;i<scene->objects.size();i++){
        if(scene->objects.at(i)->isSelected()){
            showObjectSelected(scene->objects.at(i));
        }
    }
}

void GLWidget::renderScene(QGraphicsView *qw, int percent, int samples)
{
    scene->pushViewer(cam->eye,cam->at,cam->up);
    RayTracing *tracing = new RayTracing(scene,this,Vec4(),true);
    int scenewidth = (int)(scene->viewport[0]*(percent/100.0));
    int sceneheight = (int)(scene->viewport[1]*(percent/100.0));
    QImage *image = new QImage(scenewidth,sceneheight,QImage::Format_RGB32);
    HBB *hbb = new HBB(scene->objects,0);
    tracing->hierachicalbb = hbb;
    tracing->withhbb = false;
    tracing->rayTracing(image,percent,samples);

}

int GLWidget::numberRays()
{
    return width*height;
}

void GLWidget::setValueProgressRay(int value)
{
    setProgressRay(value);
}

void GLWidget::showSampleRender(QImage *img)
{
    showSample(img);
}

void GLWidget::setPhotonsNearsCaustics(int val)
{
    scene->setPhotonsNearsCaustics(val);
}

void GLWidget::setPhotonsNearsGlobal(int val)
{
    scene->setPhotonsNearsGlobal(val);
}

void GLWidget::setFilterPhotonMap(bool b)
{
    scene->setFilterPhoton(b);
}

void GLWidget::setRenderGlobal(bool b)
{
    scene->renderGlobalRadiance(b);
}

void GLWidget::setRenderCaustic(bool b)
{
    scene->renderCausticRadiance(b);
}

void GLWidget::setVisiblePhotonCaustic(bool flag)
{
    showphotonscaustic = flag;
    updateGL();
}

void GLWidget::setVisiblePhoton(bool flag)
{
    showphotons = flag;
    updateGL();
}

void GLWidget::setSizePhotons(int size)
{
    scene->setSizePhotons(size);
}

void GLWidget::setSizePhotonsCaustic(int size)
{
    scene->setSizePhotonsCaustic(size);
}

void GLWidget::setRadiusGlobal(double val)
{
    scene->setRadiusGlobal(val);
}

void GLWidget::setRadiusCaustic(double val)
{
    scene->setRadiusCaustic(val);
}

void GLWidget::setDepthPhotons(int val)
{
    scene->setDepthPhotons(val);
}

void GLWidget::setEnabledPhotonMap(bool b)
{
    scene->setEnablePhotonMap(b);
}

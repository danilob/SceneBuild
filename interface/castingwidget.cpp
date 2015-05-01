#include "castingwidget.h"
#include <stdio.h>
#include <extra/functions.h>
#include <QFile>
#include "block/hbb.h"
//#define width  500
//#define height 400

//GLubyte checkImage[width][height][3];

CastingWidget::CastingWidget(QWidget *parent) :
    QGLWidget(parent)
{
    draw = false;
    otimized = true;
    back_color = Vec4(0,0,0);
    //scene = new Scene();
    //Cube *c = new Cube();
    //Matrix4x4 t;
    //t.setIdentity();
    //t.translate(0,1,0);
    //c->aplyTransform(t);
    //scene->pushObjects(BLOCK_HEMISPHERE,MATERIAL_EMERALD);
    //scene->pushViewer(Vec4(0,12,40),Vec4(0,0,0),Vec4(0,1,0));
    //scene->pushViewer(Vec4(-15.48,30.18,24.35),Vec4(0,0,0),Vec4(0,1,0));
    //scene->pushViewer(Vec4(2,2,2),Vec4(0,0,0),Vec4(0,1,0));
    //updateLightingGL();


}
void CastingWidget::updateLightingGL()
{

//    Vec4 *light1pos           = new Vec4(-10, 10, 10, 1.0 );
//    Vec4 *light1diffuse       = new Vec4( 0.8f, 0.8f, 0.8, 1.0);
//    Vec4 *light1specular      = new Vec4( 0.5f, 0.5f, 0.5f, 1.0 );
//    PontualLight* direct1     = new PontualLight();
//    direct1->setLight(light1pos,light1diffuse,light1specular);
//    scene->pushLights(direct1);


    Vec4 *light2dir           = new Vec4( -0.588, -0.80, -0.248, 0.0);
    Vec4 *light2pos           = new Vec4( 6.0, 7.0, 3.0, 1.0);
    Vec4 *light2diffuse       = new Vec4(1.0f, 1.0f, 1.0, 1.0);
    Vec4 *light2specular      = new Vec4( 1.0, 1.0f, 1.0f, 1.0 );
    Vec4 *light2ambient       = new Vec4( 0.2, 0.2f, 0.2f, 1.0 );

    SpotLight* direct2        = new SpotLight();
    //direct2->setLight(70.0,1.0,light2pos,light2dir,light2diffuse,light2specular,light2ambient);
    //scene->pushLights(direct2);

    Vec4* light3pos           = new Vec4( -0.5, 0.5, -0.5, 0.0 );
    Vec4* light3diffuse       = new Vec4( 0.798f, 0.838f, 1.0, 1.0 );
    Vec4* light3specular      = new Vec4( 0.06f, 0.0f, 0.0f, 1.0 );
    DirectionalLight* direct3 = new DirectionalLight();
    direct3->setLight(light3pos,light3diffuse,light3specular);
    scene->pushLights(direct3);


}


void CastingWidget::initializeGL()
{
    glClearColor(0.0,0.0,0.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT);
}

void CastingWidget::resizeGL(int w, int h)
{
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    width = w;
    height = h;

    //delete pixels;
    //int size = width * height * 3;
    //pixels = NULL;

   // TesteWindow();
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
bool init = true;
void CastingWidget::paintGL()
{
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //delete []pixels;
    //TesteWindow();

    if (init){
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(back_color.x(),back_color.y(),back_color.z(),1.0);
    }

    if(draw){
//        glClear(GL_COLOR_BUFFER_BIT);
//        //scene->viewport[0] = 300;
//        //scene->viewport[1] = 300;
//        GLubyte *pixel = new GLubyte[width*height*3];
//        RayTracing *casting = new RayTracing(scene,this,back_color,otimized);
//        //casting.setScene(scene);
//        HBB *hbb = new HBB(scene->objects,0);
//        casting->hierachicalbb = hbb;
//        casting->rayTracing(pixel);
//        glDrawPixels(width, height, GL_RGB, GL_UNSIGNED_BYTE, pixel);
//        //delete []casting;
//        delete []pixel;
//        init = false;

    }
    draw = false;





    //verifica se foi possível a alocação de memória
    //if (pixels == NULL) return;
    //glPixelStorei(GL_PACK_ALIGNMENT, 1);
    //glDrawBuffer(GL_BACK_LEFT);

}

void CastingWidget::TesteWindow()
{/*
    for(unsigned int i=0;i<width*height;i++){
        pixels[3*i] = 255;
        pixels[3*i+1] = 255;
        pixels[3*i+2] = 0;
    }*/


    //verifica se foi possível a alocação de memória
   // if (pixels == NULL) return;
   //  glPixelStorei(GL_PACK_ALIGNMENT, 1);
   // glDrawBuffer(GL_BACK_LEFT);
    //  glDrawPixels(width, height, GL_RGB, GL_UNSIGNED_BYTE, pixels);
    //glDrawPixels(width, height, GL_RGB, GL_UNSIGNED_BYTE, pixels);

}

void CastingWidget::testeRayCasting()
{
//glClear(GL_COLOR_BUFFER_BIT);
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //pixels = NULL;

    /*
    for(unsigned int i=0;i<width*height;i++){
        pixels[3*i] = 255;
        pixels[3*i+1] = 255;
        pixels[3*i+2] = 255;
    }

    //verifica se foi possível a alocação de memória
    if (pixels == NULL) return;
    draw = true;
    paintGL();
    */
    //pixels = NULL;
    //printf("\nCast Width: %d; Height: %d",width,height);
    draw = true;
    //scene->pushProjection(45.0,(float)width/height,0.01,1200000);
    //scene->pushViewport(width,height);

    //scene->calculatePixels(pixels,width,height);

    updateGL();
}

void CastingWidget::setScene(Scene *sc)
{
    scene = sc;
}

void CastingWidget::setValueProgress(int i)
{
    setProgress(i);
}

int CastingWidget::numberRays()
{
    return width*height;
}

void CastingWidget::backgroudColorRay(QColor color)
{
    back_color.setVec4(color.red()/255.0,color.green()/255.0,color.blue()/255.0);
    glClearColor(back_color.x(),back_color.y(),back_color.z(),1.0);
    init = true;
    updateGL();
}

void CastingWidget::setValueIntersectRay(int v)
{
    setIntersectRay(v);
}

void CastingWidget::setValueNotIntersectRay(int v)
{
    setNotIntersectRay(v);
}

void CastingWidget::setOtimized(bool b)
{
    otimized = b;
}

void CastingWidget::saveScreen(QString str)
{
    str.push_back(".tga");
    Functions::saveImage(width,height,str.toStdString());
}

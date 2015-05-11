#include "functions.h"
#include <QtXml/QDomDocument> //classes necessarias para criar a estrutura XML
#include <QtXml/QDomElement> //classes necessarias para criar a estrutura XML
#include <sstream>
#include <QFileInfo>
#include <QDebug>
#include <fstream>
#include <iostream>
#include <limits>
#include <GL/gl.h>

#include <QFileInfo>
#include "material.h"
#include "texture.h"
#include "bump.h"
using namespace std;

Functions::Functions()
{
}


bool Functions::saveImage(int width, int height, const std::string &fileName)
{

    FILE *fScreenshot;
    int size = width * height * 3;
    GLubyte *pixels = new GLubyte [size];

    //verifica se foi possível a alocação de memória
    if (pixels == NULL) return false;

    //fileName.push_back(".tga");
    fScreenshot = fopen(fileName.c_str(),"wb");

    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    glReadBuffer(GL_BACK_LEFT);
    glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, pixels);


    //converte para o formato RGB

    unsigned char temp;
    int i = 0;
    while (i < size)
    {
        temp = pixels[i];       //grab blue
        pixels[i] = pixels[i+2];//assign red to blue
        pixels[i+2] = temp;     //assign blue to red
        i += 3;     //skip to next blue byte
    }

    //contiguração do formato TGA
    unsigned char TGAheader[12]={0,0,2,0,0,0,0,0,0,0,0,0};
    unsigned char header[6] = {width%256,width/256,height%256,height/256,24,0};

    fwrite(TGAheader, sizeof(unsigned char), 12, fScreenshot);
    fwrite(header, sizeof(unsigned char), 6, fScreenshot);
    fwrite(pixels, sizeof(GLubyte), size, fScreenshot);
    fclose(fScreenshot);

    delete [] pixels;
    return true;

}

bool Functions::saveScene(Scene* scene, QString fileName)
{
    QFile sFile(fileName);
    QString saida,aux;
    saida = aux.sprintf("%.3f %.3f\n",scene->radius,scene->focal);
    saida += aux.sprintf("%.3f %.3f %.3f %.3f\n",scene->projection.x(),scene->projection.y(),scene->projection.z(),scene->projection.w());
    saida += aux.sprintf("%.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f\n",scene->viewer[0].x(),scene->viewer[0].y(),scene->viewer[0].z(),scene->viewer[1].x(),scene->viewer[1].y(),scene->viewer[1].z(),scene->viewer[2].x(),scene->viewer[2].y(),scene->viewer[2].z());
    saida += aux.sprintf("\n%d\n",(int)scene->objects.size());
    for (unsigned int i=0;i<scene->objects.size();i++){
        saida += scene->objects.at(i)->saveObject();
    }
    saida += aux.sprintf("\n%d \n",scene->lights.size());
    for (unsigned int i=0;i<scene->lights.size();i++){
        saida += scene->lights.at(i)->saveLight();
    }
    if(!fileName.isEmpty()){
        if(sFile.open(QFile::WriteOnly | QFile::Text)){
            QTextStream out(&sFile);
            out << saida;
            sFile.flush();
            sFile.close();
            return true;
        }
    }
    return false;

}

bool Functions::loadScene(Scene *scene, const string &fileName)
{
    scene->objects.clear();
    scene->lights.clear();

    ifstream file(fileName.data(), ios::in);
    if(!file)
    {
        cerr << "File \"" << fileName << "\" not found." << endl;
        return false;
    }

    string type;
    int obj_count;
    float r1,r2,r3,r4;
    file >> r1 >> r2;
    scene->setDOF(r1,r2);
    file >> r1 >> r2 >> r3 >> r4;
    scene->pushProjection(r1,r2,r3,r4);
    Vec4 eye,at,up;
    file >> eye.x1 >> eye.x2 >> eye.x3 >> at.x1 >> at.x2 >> at.x3 >> up.x1 >> up.x2 >> up.x3;
    //qDebug() << eye.x1 + eye.x2 + eye.x3 + at.x1 + at.x2 + at.x3 + up.x1 + up.x2 + up.x3;
    scene->pushViewer(eye,at,up);
    file >> obj_count;
    qDebug() << obj_count;
    for(int i=0;i<obj_count;i++){
        file >> type;
        if (type == "e"){
            float x,y,z;
            Vec4 aux;
            file >> x >> y >> z;
            aux.setVec4(x,y,z);
            Matrix4x4 transform;
            //transform.setTranslate(aux);
            file >> x >> y >> z;
            //aux.setVec4(x,y,z);
            transform.scale(x,y,z);
            file >> x >> y >> z;
            //aux.setVec4(x,y,z);
            transform.setRotationZ(z);
            transform.setRotationY(y);
            transform.setRotationX(x);
            transform.setTranslate(aux);
            int material;
            file >> material;
            Cone *cone = new Cone();
            cone->setTransform(transform);
            cone->setMaterial(material);
            file >> x >> y >> z;
            Vec4 amb = Vec4(x,y,z);
            file >> x >> y >> z;
            Vec4 diff = Vec4(x,y,z);
            file >> x >> y >> z;
            Vec4 spe = Vec4(x,y,z);
            float value;
            file >> value;
            float shine = value;
            cone->getMesh()->setMaterial(amb,diff,spe,shine,material);
            file >> value;
            float reflection = value;
            cone->getMesh()->setReflection(reflection);
            file >> value;
            float refraction = value;
            cone->getMesh()->setRefraction(refraction);
            float glossyrefraction,glossyreflection;
            file >> glossyreflection >> glossyrefraction;
            cone->getMesh()->setGlossyReflection(glossyreflection);
            cone->getMesh()->setGlossyRefraction(glossyrefraction);
            Vec4 motion;
            file >> motion.x1 >> motion.x2 >> motion.x3;
            cone->setMotion(motion);
            char val;
            file >> val;
            if (val == 'f')
                cone->setEnabled(false);
            else
                cone->setEnabled(true);
            file >> val;
            if (val == 'f')
                cone->setSelected(false);
            else
                cone->setSelected(true);
            char names[120];
            file.getline(names,120);
            //fgets(name,file);
            cone->setName(QString(names));
            scene->objects.push_back(cone);
        }
        else if (type == "c"){
            float x,y,z;
            Vec4 aux;
            file >> x >> y >> z;
            aux.setVec4(x,y,z);
            Matrix4x4 transform;
            //transform.setTranslate(aux);
            file >> x >> y >> z;
            //aux.setVec4(x,y,z);
            transform.scale(x,y,z);
            file >> x >> y >> z;
            //aux.setVec4(x,y,z);
            transform.setRotationZ(z);
            transform.setRotationY(y);
            transform.setRotationX(x);
            transform.setTranslate(aux);
            int material;
            file >> material;
            Cube *cube = new Cube();
            cube->setTransform(transform);
            cube->setMaterial(material);
            file >> x >> y >> z;
            Vec4 amb = Vec4(x,y,z);
            file >> x >> y >> z;
            Vec4 diff = Vec4(x,y,z);
            file >> x >> y >> z;
            Vec4 spe = Vec4(x,y,z);
            float value;
            file >> value;
            float shine = value;
            cube->getMesh()->setMaterial(amb,diff,spe,shine,material);
            file >> value;
            float reflection = value;
            cube->getMesh()->setReflection(reflection);
            file >> value;
            float refraction = value;
            cube->getMesh()->setRefraction(refraction);
            float glossyrefraction,glossyreflection;
            file >> glossyreflection >> glossyrefraction;
            cube->getMesh()->setGlossyReflection(glossyreflection);
            cube->getMesh()->setGlossyRefraction(glossyrefraction);
            Vec4 motion;
            file >> motion.x1 >> motion.x2 >> motion.x3;
            cube->setMotion(motion);
            char val;
            file >> val;
            if (val == 'f')
                cube->setEnabled(false);
            else
                cube->setEnabled(true);
            file >> val;
            if (val == 'f')
                cube->setSelected(false);
            else
                cube->setSelected(true);
            char names[120];
            file.getline(names,120);
            //fgets(name,file);
            cube->setName(QString(names));
            scene->objects.push_back(cube);
        }
        else if(type == "t"){
            float x,y,z;
            Vec4 aux;
            file >> x >> y >> z;
            aux.setVec4(x,y,z);
            Matrix4x4 transform;
            //transform.setTranslate(aux);
            file >> x >> y >> z;
            //aux.setVec4(x,y,z);
            transform.scale(x,y,z);
            file >> x >> y >> z;
            //aux.setVec4(x,y,z);
            transform.setRotationZ(z);
            transform.setRotationY(y);
            transform.setRotationX(x);
            transform.setTranslate(aux);
            int material;
            file >> material;
            Plane *plane = new Plane();
            plane->setTransform(transform);
            plane->setMaterial(material);
            file >> x >> y >> z;
            Vec4 amb = Vec4(x,y,z);
            file >> x >> y >> z;
            Vec4 diff = Vec4(x,y,z);
            file >> x >> y >> z;
            Vec4 spe = Vec4(x,y,z);
            float value;
            file >> value;
            float shine = value;
            plane->getMesh()->setMaterial(amb,diff,spe,shine,material);
            file >> value;
            float reflection = value;
            plane->getMesh()->setReflection(reflection);
            file >> value;
            float refraction = value;
            plane->getMesh()->setRefraction(refraction);
            float glossyrefraction,glossyreflection;
            file >> glossyreflection >> glossyrefraction;
            plane->getMesh()->setGlossyReflection(glossyreflection);
            plane->getMesh()->setGlossyRefraction(glossyrefraction);
            Vec4 motion;
            file >> motion.x1 >> motion.x2 >> motion.x3;
            plane->setMotion(motion);
            char val;
            file >> val;
            if (val == 'f')
                plane->setEnabled(false);
            else
                plane->setEnabled(true);
            file >> val;
            if (val == 'f')
                plane->setSelected(false);
            else
                plane->setSelected(true);
            char names[120];
            file.getline(names,120);
            //fgets(name,file);
            plane->setName(QString(names));
            scene->objects.push_back(plane);
        }
        else if(type == "s"){
            float x,y,z;
            Vec4 aux;
            file >> x >> y >> z;
            aux.setVec4(x,y,z);
            Matrix4x4 transform;
            //transform.setTranslate(aux);
            file >> x >> y >> z;
            //aux.setVec4(x,y,z);
            transform.scale(x,y,z);
            file >> x >> y >> z;
            //aux.setVec4(x,y,z);
            transform.setRotationZ(z);
            transform.setRotationY(y);
            transform.setRotationX(x);
            transform.setTranslate(aux);
            int material;
            file >> material;
            Sphere *sphere = new Sphere();
            sphere->setTransform(transform);
            sphere->setMaterial(material);
            file >> x >> y >> z;
            Vec4 amb = Vec4(x,y,z);
            file >> x >> y >> z;
            Vec4 diff = Vec4(x,y,z);
            file >> x >> y >> z;
            Vec4 spe = Vec4(x,y,z);
            float value;
            file >> value;
            float shine = value;
            sphere->getMesh()->setMaterial(amb,diff,spe,shine,material);
            file >> value;
            float reflection = value;
            sphere->getMesh()->setReflection(reflection);
            file >> value;
            float refraction = value;
            sphere->getMesh()->setRefraction(refraction);
            float glossyrefraction,glossyreflection;
            file >> glossyreflection >> glossyrefraction;
            sphere->getMesh()->setGlossyReflection(glossyreflection);
            sphere->getMesh()->setGlossyRefraction(glossyrefraction);
            Vec4 motion;
            file >> motion.x1 >> motion.x2 >> motion.x3;
            sphere->setMotion(motion);
            char val;
            file >> val;
            if (val == 'f')
                sphere->setEnabled(false);
            else
                sphere->setEnabled(true);
            file >> val;
            if (val == 'f')
                sphere->setSelected(false);
            else
                sphere->setSelected(true);
            char names[120];
            file.getline(names,120);
            //fgets(name,file);
            sphere->setName(QString(names));
            scene->objects.push_back(sphere);
        }
        else if(type == "y"){
            float x,y,z;
            Vec4 aux;
            file >> x >> y >> z;
            aux.setVec4(x,y,z);
            Matrix4x4 transform;
            //transform.setTranslate(aux);
            file >> x >> y >> z;
            //aux.setVec4(x,y,z);
            transform.scale(x,y,z);
            file >> x >> y >> z;
            //aux.setVec4(x,y,z);
            transform.setRotationZ(z);
            transform.setRotationY(y);
            transform.setRotationX(x);
            transform.setTranslate(aux);
            int material;
            file >> material;
            Cylinder *cylinder = new Cylinder();
            cylinder->setTransform(transform);
            cylinder->setMaterial(material);
            file >> x >> y >> z;
            Vec4 amb = Vec4(x,y,z);
            file >> x >> y >> z;
            Vec4 diff = Vec4(x,y,z);
            file >> x >> y >> z;
            Vec4 spe = Vec4(x,y,z);
            float value;
            file >> value;
            float shine = value;
            cylinder->getMesh()->setMaterial(amb,diff,spe,shine,material);
            file >> value;
            float reflection = value;
            cylinder->getMesh()->setReflection(reflection);
            file >> value;
            float refraction = value;
            cylinder->getMesh()->setRefraction(refraction);
            float glossyrefraction,glossyreflection;
            file >> glossyreflection >> glossyrefraction;
            cylinder->getMesh()->setGlossyReflection(glossyreflection);
            cylinder->getMesh()->setGlossyRefraction(glossyrefraction);
            Vec4 motion;
            file >> motion.x1 >> motion.x2 >> motion.x3;
            cylinder->setMotion(motion);
            char val;
            file >> val;
            if (val == 'f')
                cylinder->setEnabled(false);
            else
                cylinder->setEnabled(true);
            file >> val;
            if (val == 'f')
                cylinder->setSelected(false);
            else
                cylinder->setSelected(true);
            char names[120];
            file.getline(names,120);
            //fgets(name,file);
            cylinder->setName(QString(names));
            scene->objects.push_back(cylinder);
        }else if(type == "p"){
            float x,y,z;
            Vec4 aux;
            file >> x >> y >> z;
            aux.setVec4(x,y,z);
            Matrix4x4 transform;
            //transform.setTranslate(aux);
            file >> x >> y >> z;
            //aux.setVec4(x,y,z);
            transform.scale(x,y,z);
            file >> x >> y >> z;
            //aux.setVec4(x,y,z);
            transform.setRotationZ(z);
            transform.setRotationY(y);
            transform.setRotationX(x);
            transform.setTranslate(aux);
            int material;
            file >> material;
            Prism *prism = new Prism();
            prism->setTransform(transform);
            prism->setMaterial(material);
            file >> x >> y >> z;
            Vec4 amb = Vec4(x,y,z);
            file >> x >> y >> z;
            Vec4 diff = Vec4(x,y,z);
            file >> x >> y >> z;
            Vec4 spe = Vec4(x,y,z);
            float value;
            file >> value;
            float shine = value;
            prism->getMesh()->setMaterial(amb,diff,spe,shine,material);
            file >> value;
            float reflection = value;
            prism->getMesh()->setReflection(reflection);
            file >> value;
            float refraction = value;
            prism->getMesh()->setRefraction(refraction);
            float glossyrefraction,glossyreflection;
            file >> glossyreflection >> glossyrefraction;
            prism->getMesh()->setGlossyReflection(glossyreflection);
            prism->getMesh()->setGlossyRefraction(glossyrefraction);
            Vec4 motion;
            file >> motion.x1 >> motion.x2 >> motion.x3;
            prism->setMotion(motion);
            char val;
            file >> val;
            if (val == 'f')
                prism->setEnabled(false);
            else
                prism->setEnabled(true);
            file >> val;
            if (val == 'f')
                prism->setSelected(false);
            else
                prism->setSelected(true);
            char names[120];
            file.getline(names,120);
            //fgets(name,file);
            prism->setName(QString(names));
            scene->objects.push_back(prism);
        }else{
            float x,y,z;
            Vec4 aux;
            file >> x >> y >> z;
            aux.setVec4(x,y,z);
            Matrix4x4 transform;
            //transform.setTranslate(aux);
            file >> x >> y >> z;
            //aux.setVec4(x,y,z);
            transform.scale(x,y,z);
            file >> x >> y >> z;
            //aux.setVec4(x,y,z);
            transform.setRotationZ(z);
            transform.setRotationY(y);
            transform.setRotationX(x);
            transform.setTranslate(aux);
            int material;
            file >> material;
            HemiSphere *hemi = new HemiSphere();
            hemi->setTransform(transform);
            hemi->setMaterial(material);
            file >> x >> y >> z;
            Vec4 amb = Vec4(x,y,z);
            file >> x >> y >> z;
            Vec4 diff = Vec4(x,y,z);
            file >> x >> y >> z;
            Vec4 spe = Vec4(x,y,z);
            float value;
            file >> value;
            float shine = value;
            hemi->getMesh()->setMaterial(amb,diff,spe,shine,material);
            file >> value;
            float reflection = value;
            hemi->getMesh()->setReflection(reflection);
            file >> value;
            float refraction = value;
            hemi->getMesh()->setRefraction(refraction);
            float glossyrefraction,glossyreflection;
            file >> glossyreflection >> glossyrefraction;
            hemi->getMesh()->setGlossyReflection(glossyreflection);
            hemi->getMesh()->setGlossyRefraction(glossyrefraction);
            Vec4 motion;
            file >> motion.x1 >> motion.x2 >> motion.x3;
            hemi->setMotion(motion);
            char val;
            file >> val;
            if (val == 'f')
                hemi->setEnabled(false);
            else
                hemi->setEnabled(true);
            file >> val;
            if (val == 'f')
                hemi->setSelected(false);
            else
                hemi->setSelected(true);
            char names[120];
            file.getline(names,120);
            //fgets(name,file);
            hemi->setName(QString(names));
            scene->objects.push_back(hemi);
        }
    }

    int light_count;
    file >> light_count;
    qDebug() << light_count;
    for (int i=0;i<light_count;i++){
        file >> type;
        char val;
        if (type == "a"){
            AmbientLight *ambientelight = new AmbientLight();
            float x,y,z;
            file >> x >> y >> z;
            QColor color;
            color.setRgb(x*255,y*255,z*255);
            ambientelight->setAmbientColor(color);
            char val;
            file >> val;
            if(val == 'f')
                ambientelight->setSelected(false);
            else
                ambientelight->setSelected(true);
            char names[120];
            file.getline(names,120);
            ambientelight->setName(QString(names));
            scene->lights.push_back(ambientelight);
        }else if (type == "o"){
            PontualLight *pontuallight = new PontualLight();
            float x,y,z;
            file >> x >> y >> z;
            QColor color;
            color.setRgb(x*255,y*255,z*255);
            pontuallight->setAmbientColor(color);
            file >> x >> y >> z;
            color.setRgb(x*255,y*255,z*255);
            pontuallight->setSpecularColor(color);
            file >> x >> y >> z;
            color.setRgb(x*255,y*255,z*255);
            pontuallight->setDiffuseColor(color);
            file >> x >> y >> z;
            pontuallight->setPosition(Vec4(x,y,z));
            file >> x >> y >> z;
            pontuallight->setAttenuation(Vec4(x,y,z));
            file >> val;
            if(val == 'f')
                pontuallight->setEnabled(false);
            else
                pontuallight->setEnabled(true);
            file >> val;
            if(val == 'f')
                pontuallight->setVisible(false);
            else
                pontuallight->setVisible(true);
            file >> val;
            if(val == 'f')
                pontuallight->setSelected(false);
            else
                pontuallight->setSelected(true);
            char names[120];
            file.getline(names,120);
            pontuallight->setName(names);
            scene->lights.push_back(pontuallight);
        }else if (type == "r"){
            AreaLight *arealight = new AreaLight();
            float x,y,z;
            file >> x >> y >> z;
            QColor color;
            color.setRgb(x*255,y*255,z*255);
            arealight->setAmbientColor(color);
            file >> x >> y >> z;
            color.setRgb(x*255,y*255,z*255);
            arealight->setSpecularColor(color);
            file >> x >> y >> z;
            color.setRgb(x*255,y*255,z*255);
            arealight->setDiffuseColor(color);
            file >> x >> y >> z;
            arealight->setPosition(Vec4(x,y,z));
            file >> x >> y >> z;
            arealight->setAttenuation(Vec4(x,y,z));
            file >> x >> y >> z;
            arealight->setVecA(Vec4(x,y,z));
            file >> x >> y >> z;
            arealight->setVecB(Vec4(x,y,z));
            file >> val;
            if(val == 'f')
                arealight->setEnabled(false);
            else
                arealight->setEnabled(true);
            file >> val;
            if(val == 'f')
                arealight->setVisible(false);
            else
                arealight->setVisible(true);
            file >> val;
            if(val == 'f')
                arealight->setSelected(false);
            else
                arealight->setSelected(true);
            char names[120];
            file.getline(names,120);
            arealight->setName(names);
            scene->lights.push_back(arealight);

        }
        else if (type == "d"){
            DirectionalLight *directionlight = new DirectionalLight();
            float x,y,z;
            file >> x >> y >> z;
            QColor color;
            color.setRgb(x*255,y*255,z*255);
            directionlight->setAmbientColor(color);
            file >> x >> y >> z;
            color.setRgb(x*255,y*255,z*255);
            directionlight->setSpecularColor(color);
            file >> x >> y >> z;
            color.setRgb(x*255,y*255,z*255);
            directionlight->setDiffuseColor(color);
            file >> x >> y >> z;
            directionlight->setDirection(Vec4(x,y,z));
            file >> val;

            if(val == 'f')
                directionlight->setEnabled(false);
            else
                directionlight->setEnabled(true);
            file >> val;
            if(val == 'f')
                directionlight->setVisible(false);
            else
                directionlight->setVisible(true);
            file >> val;
            if(val == 'f')
                directionlight->setSelected(false);
            else
                directionlight->setSelected(true);
            char names[120];
            file.getline(names,120);
            directionlight->setName(names);
            scene->lights.push_back(directionlight);
        }else{ //caso spot
            SpotLight *spotlight = new SpotLight();
            float x,y,z;
            file >> x >> y >> z;
            QColor color;
            color.setRgb(x*255,y*255,z*255);
            spotlight->setAmbientColor(color);
            file >> x >> y >> z;
            color.setRgb(x*255,y*255,z*255);
            spotlight->setSpecularColor(color);
            file >> x >> y >> z;
            color.setRgb(x*255,y*255,z*255);
            spotlight->setDiffuseColor(color);
            file >> x >> y >> z;
            spotlight->setPosition(Vec4(x,y,z));
            file >> x >> y >> z;
            spotlight->setDirection(Vec4(x,y,z));
            file >> x >> y >> z;
            spotlight->setAttenuation(Vec4(x,y,z));
            int var;
            file >> var;
            spotlight->setAngle(var);
            file >> var;
            spotlight->setAngleInner(var);
            file >> var;
            spotlight->setExponent(var);
            file >> val;
            if(val == 'f')
                spotlight->setEnabled(false);
            else
                spotlight->setEnabled(true);
            file >> val;
            if(val == 'f')
                spotlight->setVisible(false);
            else
                spotlight->setVisible(true);
            file >> val;
            if(val == 'f')
                spotlight->setSelected(false);
            else
                spotlight->setSelected(true);
            char names[120];
            file.getline(names,120);
            spotlight->setName(names);
            scene->lights.push_back(spotlight);

        }
    }
    file.close();
    qDebug()<<"Qtde de Objeto(s): " << scene->objects.size();
    qDebug()<<"Qtde de Luz(es): " << scene->lights.size();
    return true;

}

bool Functions::saveSceneXML(Scene *scene, QString fileName, bool flag)
{
    QDomDocument doc( "SceneRayTracing" );
    QDomElement root = doc.createElement( "Scene" );
    doc.appendChild( root );
    QDomElement effects = doc.createElement( "Effects" ); //elemento que guarda o efeito da cena, no caso o DOF
    if (scene->getRadiusDOF()!=0){ //verifico se a cena esta configurada com Depth Of Field (DOF)
        effects.setAttribute("DOF",true); //caso exista o efeito de DOF
        effects.setAttribute("Radius",scene->getRadiusDOF()); //raio do DOF
        effects.setAttribute("FocalLength",scene->getFocalDOF()); //distancia focal do DOF
    }else{
        effects.setAttribute("DOF",false); //caso não exista o efeito de DOF
        effects.setAttribute("Radius",0); //raio do DOF
        effects.setAttribute("FocalLength",0); //distancia focal do DOF
    }
    root.appendChild(effects); //adiciona o elemento efeito na arvore

    QDomElement perspective = doc.createElement( "Perspective" ); //elemento que guarda as configurações da visualização em perspectiva
    perspective.setAttribute("Width",scene->viewport[0]); //largura da janela
    perspective.setAttribute("Height",scene->viewport[1]); //altura da janela
    perspective.setAttribute("Angle",scene->projection.x()); //angulo em graus da perspectiva
    perspective.setAttribute("Near",scene->projection.z()); //plano near da perspectiva
    perspective.setAttribute("Far",scene->projection.w()); //pano far da perspectiva
    root.appendChild(perspective); //adiciona o elemento perspectiva na arvore

    QDomElement camera = doc.createElement("Camera");   //Configurações da câmera
    Vec4 vec = scene->viewer[0]; //posição do observador
    QDomElement eye = doc.createElement("Eye");   //Posição do Eye
    eye.setAttribute("x",vec.x()); //posição x do eye
    eye.setAttribute("y",vec.y()); //posição y do eye
    eye.setAttribute("z",vec.z()); //posição z do eye
    camera.appendChild(eye);
    QDomElement at = doc.createElement("At");   //Posição do At
    vec = scene->viewer[1]; //posição do at, posição para onde o observador está olhando
    at.setAttribute("x",vec.x()); //posição x do at
    at.setAttribute("y",vec.y()); //posição y do at
    at.setAttribute("z",vec.z()); //posição z do at
    camera.appendChild(at);
    QDomElement up = doc.createElement("Up");   //Vetor Up
    vec = scene->viewer[2]; //vetor up
    up.setAttribute("x",vec.x()); //posição x do up
    up.setAttribute("y",vec.y()); //posição y do up
    up.setAttribute("z",vec.z()); //posição z do up
    camera.appendChild(up);
    root.appendChild(camera); //adiciona o elemento camera na arvore
    QDomElement objects = doc.createElement("Objects");   //Guarda todos os objetos da cena
    for(int i=0;i<scene->objects.size();i++){ //percorre a lista de objetos do cenário
        Object* obj = scene->objects.at(i);
        QDomElement object = doc.createElement("Object");
        object.setAttribute("Enabled",obj->isEnabled());
        object.setAttribute("Name",obj->getName());
        if (obj->getLenTexture()>0) //verifica se  o objeto possui alguma textura e guarda o caminho da textura
             object.setAttribute("Texture",obj->getTexture(0)->getPath());
        else
            object.setAttribute("Texture","");
        if (obj->getLenBump()>0) //verifica se o objeto tem alguma textura de bump mapping e guarda o caminho da textura
             object.setAttribute("Bump",obj->getBump(0)->getPath());
        else
            object.setAttribute("Bump","");
        object.setAttribute("Type",obj->getType()); //salva o tipo de objeto: cubo,esfera,...

        QDomElement pos = doc.createElement("Position");   //Posição do objeto
        vec = obj->getMatrixTransformation().getTranslateSeted(); //vetor de posição
        pos.setAttribute("x",vec.x());
        pos.setAttribute("y",vec.y());
        pos.setAttribute("z",vec.z());
        object.appendChild(pos);

        QDomElement rot = doc.createElement("Rotation");   //Rotação do objeto
        vec = obj->getMatrixTransformation().getRotationSeted(); //vetor de rotação
        rot.setAttribute("x",vec.x());
        rot.setAttribute("y",vec.y());
        rot.setAttribute("z",vec.z());
        object.appendChild(rot);

        QDomElement sca = doc.createElement("Scale");   //Escala do objeto
        vec = obj->getMatrixTransformation().getScaleSeted(); //vetor de escala
        sca.setAttribute("x",vec.x());
        sca.setAttribute("y",vec.y());
        sca.setAttribute("z",vec.z());
        object.appendChild(sca);

        QDomElement material = doc.createElement("Material");   //Propriedades do material
        material.setAttribute("Shininess",obj->getMesh()->getShininess());//pega o shininess do objeto //[0~1]
        material.setAttribute("Reflection",obj->getMesh()->getReflection());//pega o indice de refleção [0~1]
        material.setAttribute("Refraction",obj->getMesh()->getRefraction());//pega o indice de refração
        material.setAttribute("GLossyReflection",obj->getMesh()->getGlossyReflection());//pega o indice de refleção glossy [0~1]
        material.setAttribute("GLossyRefraction",obj->getMesh()->getGlossyRefraction());//pega o indice de refleção glossy [0~1]

            QDomElement ambient = doc.createElement("Ambient");   //Pega a contribuição ambiente do material
            vec = obj->getMesh()->getMaterialM()->getAmbiente(); //vetor de escala
            ambient.setAttribute("r",vec.x());
            ambient.setAttribute("g",vec.y());
            ambient.setAttribute("b",vec.z());
            material.appendChild(ambient);

            QDomElement specular = doc.createElement("Specular");   //Pega a contribuição ambiente do material
            vec = obj->getMesh()->getMaterialM()->getSpecular(); //vetor de escala
            specular.setAttribute("r",vec.x());
            specular.setAttribute("g",vec.y());
            specular.setAttribute("b",vec.z());
            material.appendChild(specular);

            QDomElement diffuse = doc.createElement("Diffuse");   //Pega a contribuição ambiente do material
            vec = obj->getMesh()->getMaterialM()->getDiffuse(); //vetor de escala
            diffuse.setAttribute("r",vec.x());
            diffuse.setAttribute("g",vec.y());
            diffuse.setAttribute("b",vec.z());
            material.appendChild(diffuse);

        object.appendChild(material);

        QDomElement effects = doc.createElement("Effects");   //Efeito de motion blur
        if (obj->getMotion()!=Vec4()){ //se o objeto tem uma direção de movimento
            effects.setAttribute("Motion",true); //informo que o objeto tem o efeito de motion blur
                QDomElement trans = doc.createElement("Translate");   //Direção de translação do efeito
                vec = obj->getMotion(); //vetor de posição de translação do efeito
                trans.setAttribute("x",vec.x());
                trans.setAttribute("y",vec.y());
                trans.setAttribute("z",vec.z());
                effects.appendChild(trans);

                QDomElement rots = doc.createElement("Rotate");   //Direção de rotação do efeito, no meu caso não tenho este efeito, então deixarei zerado
                vec = Vec4(); //vetor de posição de translação do efeito
                rots.setAttribute("x",vec.x());
                rots.setAttribute("y",vec.y());
                rots.setAttribute("z",vec.z());
                effects.appendChild(rots);

        }else{
            effects.setAttribute("Motion",true); //informo que o objeto não tem o efeito de motion blur
                QDomElement trans = doc.createElement("Translate");   //Direção de translação do efeito
                vec = Vec4(); //vetor de posição de translação do efeito
                trans.setAttribute("x",vec.x());
                trans.setAttribute("y",vec.y());
                trans.setAttribute("z",vec.z());
                effects.appendChild(trans);

                QDomElement rots = doc.createElement("Rotate");   //Direção de rotação do efeito, no meu caso não tenho este efeito, então deixarei zerado
                vec = Vec4(); //vetor de posição de translação do efeito
                rots.setAttribute("x",vec.x());
                rots.setAttribute("y",vec.y());
                rots.setAttribute("z",vec.z());
                effects.appendChild(rots);
        }
        object.appendChild(effects);
        objects.appendChild(object); //adiciona objeto na arvore de objetos
    }
    root.appendChild(objects);
    QDomElement lights = doc.createElement("Lights");   //Guarda todos os objetos da cena
    for(int i=0;i<scene->lights.size();i++){
        Light *lig = scene->lights.at(i);
        QDomElement light = doc.createElement("Light");
        light.setAttribute("Name",lig->getName());  //nome da luz, se existir
        light.setAttribute("Enable",lig->isEnabled()); //se a luz está habilitada
        light.setAttribute("Type",lig->getTypeLightS()); //o tipo de luz: ambient, spot, direcional,...
        light.setAttribute("Angle",lig->getAngle()); //o angulo da luz, se for do tipo Spot
        light.setAttribute("AngleInner",lig->getAngleInner()); //o angulo interno da luz, se for do tipo Spot
        light.setAttribute("Exponent",lig->getExponent()); //o expoente de suavidade, se for do tipo Spot

        QDomElement position = doc.createElement("Position"); //posição da luz
        vec = lig->getPosition();
        position.setAttribute("x",vec.x());
        position.setAttribute("y",vec.y());
        position.setAttribute("z",vec.z());
        light.appendChild(position);

        QDomElement direction = doc.createElement("Direction"); //direção da luz
        vec = lig->getDirection();
        direction.setAttribute("x",vec.x());
        direction.setAttribute("y",vec.y());
        direction.setAttribute("z",vec.z());
        light.appendChild(direction);

        //são dois vetores que determinam a dimensão area light, considerando a origem no centro e o produto vetorial determina a direção da luz
        QDomElement veca = doc.createElement("VecA"); //vetor que determina a area light, considerando a origem no centro
        vec = lig->getVecA();
        veca.setAttribute("x",vec.x());
        veca.setAttribute("y",vec.y());
        veca.setAttribute("z",vec.z());
        light.appendChild(veca);

        QDomElement vecb = doc.createElement("VecB"); //vetor que determina a area light, considerando a origem no centro
        vec = lig->getVecB();
        vecb.setAttribute("x",vec.x());
        vecb.setAttribute("y",vec.y());
        vecb.setAttribute("z",vec.z());
        light.appendChild(vecb);

        QDomElement attenuation = doc.createElement("Attenuation"); //determina os parametros de atenuação da luz de acordo com a distância
        vec = lig->getAttenuation();
        attenuation.setAttribute("x",vec.x());
        attenuation.setAttribute("y",vec.y());
        attenuation.setAttribute("z",vec.z());
        light.appendChild(attenuation);


        QDomElement material = doc.createElement("Material");   //Propriedades do material
            QColor color;
            QDomElement ambient = doc.createElement("Ambient");   //Pega a contribuição ambiente do material
            color = lig->getAmbientColor(); //vetor de escala
            ambient.setAttribute("r",(float)(color.red()/255.)); //[0~1]
            ambient.setAttribute("g",(float)(color.green()/255.)); //[0~1]
            ambient.setAttribute("b",(float)(color.blue()/255.)); //[0~1]
            material.appendChild(ambient);

            QDomElement specular = doc.createElement("Specular");   //Pega a contribuição ambiente do material
            color = lig->getSpecularColor(); //vetor de escala
            specular.setAttribute("r",(float)(color.red()/255.)); //[0~1]
            specular.setAttribute("g",(float)(color.green()/255.)); //[0~1]
            specular.setAttribute("b",(float)(color.blue()/255.)); //[0~1]
            material.appendChild(specular);

            QDomElement diffuse = doc.createElement("Diffuse");   //Pega a contribuição ambiente do material
            color = lig->getDiffuseColor(); //vetor de escala
            diffuse.setAttribute("r",(float)(color.red()/255.)); //[0~1]
            diffuse.setAttribute("g",(float)(color.green()/255.)); //[0~1]
            diffuse.setAttribute("b",(float)(color.blue()/255.)); //[0~1]
            material.appendChild(diffuse);

        light.appendChild(material);

        lights.appendChild(light);
    }
    root.appendChild(lights);

    QString f = fileName.toStdString().data();
    if(flag){
        ofstream ff((f+".xml").toLocal8Bit().data());
        ff << doc.toString().toLocal8Bit().data();
    }
    else{
        ofstream ff((f).toLocal8Bit().data());
        ff << doc.toString().toLocal8Bit().data();
    }

    return true;
}

bool Functions::loadSceneXML(Scene *scene, QString fileName)
{
    QDomDocument doc( "SceneRayTracing" );
    QFile file( fileName.toStdString().data() );
    if( !file.open(QIODevice::ReadOnly) )
        return false;
    if( !doc.setContent( &file ) )
    {
        file.close();
        return false;
    }
    file.close();

    QDomElement root = doc.documentElement();
    if( root.tagName() != "Scene" )
        return false;
    scene->objects.clear();
    scene->lights.clear();

    QDomNode n = root.firstChild();
    while( !n.isNull() )
    {
        Vec4 vec;
        QDomElement e = n.toElement();
        if( !e.isNull() ){

            if(e.tagName()=="Effects"){
                QDomElement effect = e.toElement();
                float radius,focallength;
                bool dof = effect.attribute("DOF","").toInt();
                if (dof){ //caso exista um efeito de DOF (Depth of Field)
                    radius = effect.attribute("Radius","").toFloat();
                    focallength = effect.attribute("FocalLength","").toFloat();
                    scene->setDOF(radius,focallength);
                }else{ //caso não exista DOF
                    scene->setDOF(0.0,0.0);
                }


            }

            if(e.tagName()=="Perspective"){
                QDomElement perspective = e;
                int width,height;
                float near,far,angle;
                width = perspective.attribute("Width","").toInt();
                height = perspective.attribute("Height","").toInt();
                angle = perspective.attribute("Angle","").toFloat();
                near = perspective.attribute("Near","").toFloat();
                far = perspective.attribute("Far","").toFloat();
                scene->pushProjection(angle,(float)width/height,near,far); //carrega a matriz de projeção
                scene->pushViewport(width,height);

            }

            if(e.tagName()=="Camera"){
                QDomElement eye = e.firstChildElement("Eye").toElement();
                vec.x1 = eye.attribute("x","").toFloat();
                vec.x2 = eye.attribute("y","").toFloat();
                vec.x3 = eye.attribute("z","").toFloat();
                Vec4 veye = vec;
                QDomElement up = e.firstChildElement("Up").toElement();
                vec.x1 = up.attribute("x","").toFloat();
                vec.x2 = up.attribute("y","").toFloat();
                vec.x3 = up.attribute("z","").toFloat();
                Vec4 vup = vec;
                QDomElement at = e.firstChildElement("At").toElement();
                vec.x1 = at.attribute("x","").toFloat();
                vec.x2 = at.attribute("y","").toFloat();
                vec.x3 = at.attribute("z","").toFloat();
                Vec4 vat = vec;
                scene->pushViewer(veye,vat,vup);
            }

            if(e.tagName()=="Objects"){
                QDomNode  objs = e.firstChildElement("Object");
                while (!objs.isNull()){
                    QDomNode elemento = objs;
                    QDomElement obj = elemento.toElement();
                    QString type = obj.attribute("Type","");
                    QString pathbump = obj.attribute("Bump","");
                    QString pathtexture = obj.attribute("Texture","");
                    QString name = obj.attribute("Name","");
                    bool enabled  = obj.attribute("Enabled","").toInt();
                    Object *object;
                    if (type=="OBJCUBE"){
                        object = new Cube();
                    }else if (type=="OBJCONE"){
                        object = new Cone();
                    }else if (type=="OBJCYLINDER"){
                        object = new Cylinder();
                    }else if (type=="OBJHEMISPHERE"){
                        object = new HemiSphere();
                    }else if (type=="OBJPLANE"){
                        object = new Plane();
                    }else if (type=="OBJPRISM"){
                        object = new Prism();
                    }else if (type=="OBJSPHERE"){
                        object = new Sphere();
                    }else{
                        break;
                    }
                    object->setName(name);
                    if(!pathbump.isEmpty()){
                        Bump* bump = new Bump(new QImage(pathbump),pathbump);
                        object->setBump(bump);
                    }
                    if(!pathtexture.isEmpty()){
                        Texture* texture = new Texture(new QImage(pathtexture),pathtexture);
                        object->setTexture(texture);
                    }
                    object->setEnabled(enabled);

                    //posição
                    QDomElement pos = obj.firstChildElement("Position").toElement();
                    vec.x1 = pos.attribute("x","").toFloat();
                    vec.x2 = pos.attribute("y","").toFloat();
                    vec.x3 = pos.attribute("z","").toFloat();
                    Vec4 position = vec;
                    //rotação
                    QDomElement rot = obj.firstChildElement("Rotation").toElement();
                    vec.x1 = rot.attribute("x","").toFloat();
                    vec.x2 = rot.attribute("y","").toFloat();
                    vec.x3 = rot.attribute("z","").toFloat();
                    Vec4 rotation = vec;
                    //escala
                    QDomElement scale = obj.firstChildElement("Scale").toElement();
                    vec.x1 = scale.attribute("x","").toFloat();
                    vec.x2 = scale.attribute("y","").toFloat();
                    vec.x3 = scale.attribute("z","").toFloat();
                    Vec4 sca = vec;
                    Matrix4x4 transform;
                    transform.scale(sca);
                    transform.setRotationZ(rotation.z());
                    transform.setRotationY(rotation.y());
                    transform.setRotationX(rotation.x());
                    transform.setTranslate(position);
                    object->setTransform(transform);

                    //material
                    QDomElement material = obj.firstChildElement("Material").toElement();
                    float refle,refra,grefra,grefle,shine;
                    refle = material.attribute("Reflection","").toFloat(); //reflexão
                    refra = material.attribute("Refraction","").toFloat(); //refração
                    grefle = material.attribute("GlossyReflection","").toFloat(); //reflexão glossy
                    grefra = material.attribute("GLossyRefraction","").toFloat(); //refração glossy
                    shine = material.attribute("Shininess","").toFloat(); //0~1 shininess do material
                    //contribuição ambiente
                    QDomElement amb = material.firstChildElement("Ambient").toElement();
                    vec.x1 = amb.attribute("r","").toFloat();
                    vec.x2 = amb.attribute("g","").toFloat();
                    vec.x3 = amb.attribute("b","").toFloat();
                    Vec4 ambient = vec;

                    //contribuição diffusa
                    QDomElement diff = material.firstChildElement("Diffuse").toElement();
                    vec.x1 = diff.attribute("r","").toFloat();
                    vec.x2 = diff.attribute("g","").toFloat();
                    vec.x3 = diff.attribute("b","").toFloat();
                    Vec4 diffuse = vec;

                    //contribuição diffusa
                    QDomElement spe = material.firstChildElement("Specular").toElement();
                    vec.x1 = spe.attribute("r","").toFloat();
                    vec.x2 = spe.attribute("g","").toFloat();
                    vec.x3 = spe.attribute("b","").toFloat();
                    Vec4 specular = vec;

                    object->getMesh()->setMaterial(ambient,diffuse,specular,shine);
                    object->getMesh()->setReflection(refle);
                    object->getMesh()->setGlossyReflection(grefle);
                    object->getMesh()->setRefraction(refra);
                    object->getMesh()->setGlossyRefraction(grefra);
                    //efeito
                    QDomElement effect = obj.firstChildElement("Effects").toElement();
                    bool has = effect.attribute("Motion","").toInt();
                    if(has){ //se exite algum efeito
                        QDomElement trans = effect.firstChildElement("Translate").toElement();
                        vec.x1 = trans.attribute("x","").toFloat();
                        vec.x2 = trans.attribute("y","").toFloat();
                        vec.x3 = trans.attribute("z","").toFloat();
                        object->setMotion(vec);
                        QDomElement rot = effect.firstChildElement("Rotate").toElement();
                        vec.x1 = rot.attribute("x","").toFloat();
                        vec.x2 = rot.attribute("y","").toFloat();
                        vec.x3 = rot.attribute("z","").toFloat();
                        //se tiver alguma efeito de rotação para motion blur colocar aqui!!! Depois farei um.
                    }
                    scene->objects.push_back(object);
                    objs = objs.nextSibling();
                }
            }

                if(e.tagName()=="Lights"){
                    QDomNode  ligs = e.firstChildElement("Light");
                    while (!ligs.isNull()){
                        QDomNode elemento = ligs;
                        QDomElement lig = elemento.toElement();
                        QString type = lig.attribute("Type","");
                        QString name = lig.attribute("Name","");
                        bool enable = lig.attribute("Enable","").toInt();
                        Light *light;
                        if (type=="LIGHT_AMBIENT"){
                            light = new AmbientLight();
                            QDomElement material = lig.firstChildElement("Material").toElement();
                            QDomElement amb = material.firstChildElement("Ambient").toElement();
                            vec.x1 = amb.attribute("r","").toFloat();
                            vec.x2 = amb.attribute("g","").toFloat();
                            vec.x3 = amb.attribute("b","").toFloat();
                            QColor color;
                            color.setRgb(vec.x()*255,vec.y()*255,vec.z()*255);
                            light->setAmbientColor(color);
                        }else if (type=="LIGHT_AREA"){
                            light = new AreaLight();
                            QDomElement pos = lig.firstChildElement("Position").toElement();
                            vec.x1 = pos.attribute("x","").toFloat();
                            vec.x2 = pos.attribute("y","").toFloat();
                            vec.x3 = pos.attribute("z","").toFloat();
                            light->setPosition(vec);
                            QDomElement veca = lig.firstChildElement("VecA").toElement();
                            vec.x1 = veca.attribute("x","").toFloat();
                            vec.x2 = veca.attribute("y","").toFloat();
                            vec.x3 = veca.attribute("z","").toFloat();
                            light->setVecA(vec);
                            QDomElement vecb = lig.firstChildElement("VecB").toElement();
                            vec.x1 = vecb.attribute("x","").toFloat();
                            vec.x2 = vecb.attribute("y","").toFloat();
                            vec.x3 = vecb.attribute("z","").toFloat();
                            light->setVecB(vec);

                        }else if (type=="LIGHT_DIRECTIONAL"){
                            light = new DirectionalLight();
                            QDomElement dir = lig.firstChildElement("Direction").toElement();
                            vec.x1 = dir.attribute("x","").toFloat();
                            vec.x2 = dir.attribute("y","").toFloat();
                            vec.x3 = dir.attribute("z","").toFloat();
                            light->setDirection(vec);

                        }else if(type=="LIGHT_PONTUAL"){
                            light = new PontualLight();
                            QDomElement pos = lig.firstChildElement("Position").toElement();
                            vec.x1 = pos.attribute("x","").toFloat();
                            vec.x2 = pos.attribute("y","").toFloat();
                            vec.x3 = pos.attribute("z","").toFloat();
                            light->setPosition(vec);
                        }else if (type=="LIGHT_SPOT"){
                            light = new SpotLight();
                            //AngleInner="-1" Angle="-1" Type="LIGHT_AMBIENT" Exponent="-1" Enable="1" Name="      Ambient Light"
                            float angle = lig.attribute("Angle","").toFloat();
                            float angleinner = lig.attribute("AngleInner","").toFloat();
                            float exp = lig.attribute("Exponent","").toFloat();
                            light->setAngle(angle);
                            light->setAngleInner(angleinner);
                            light->setExponent(exp);
                            QDomElement pos = lig.firstChildElement("Position").toElement();
                            vec.x1 = pos.attribute("x","").toFloat();
                            vec.x2 = pos.attribute("y","").toFloat();
                            vec.x3 = pos.attribute("z","").toFloat();
                            light->setPosition(vec);
                            QDomElement dir = lig.firstChildElement("Direction").toElement();
                            vec.x1 = dir.attribute("x","").toFloat();
                            vec.x2 = dir.attribute("y","").toFloat();
                            vec.x3 = dir.attribute("z","").toFloat();
                            light->setDirection(vec);


                        }else{
                            break;
                        }

                        if(!(type=="LIGHT_AMBIENT")){
                            QDomElement material = lig.firstChildElement("Material").toElement();
                            QDomElement amb = material.firstChildElement("Ambient").toElement();
                            vec.x1 = amb.attribute("r","").toFloat();
                            vec.x2 = amb.attribute("g","").toFloat();
                            vec.x3 = amb.attribute("b","").toFloat();
                            QColor color;
                            color.setRgb(vec.x()*255,vec.y()*255,vec.z()*255);
                            light->setAmbientColor(color);
                            QDomElement diff = material.firstChildElement("Diffuse").toElement();
                            vec.x1 = diff.attribute("r","").toFloat();
                            vec.x2 = diff.attribute("g","").toFloat();
                            vec.x3 = diff.attribute("b","").toFloat();
                            color.setRgb(vec.x()*255,vec.y()*255,vec.z()*255);
                            light->setDiffuseColor(color);
                            QDomElement spe = material.firstChildElement("Specular").toElement();
                            vec.x1 = spe.attribute("r","").toFloat();
                            vec.x2 = spe.attribute("g","").toFloat();
                            vec.x3 = spe.attribute("b","").toFloat();
                            color.setRgb(vec.x()*255,vec.y()*255,vec.z()*255);
                            light->setSpecularColor(color);
                            if(!(type=="LIGHT_DIRECTIONAL")){ //se não for direcional tem atenuação
                                QDomElement att = lig.firstChildElement("Attenuation").toElement();
                                vec.x1 = att.attribute("x","").toFloat();
                                vec.x2 = att.attribute("y","").toFloat();
                                vec.x3 = att.attribute("z","").toFloat();
                                light->setAttenuation(vec);
                            }
                        }

                        light->setName(name);
                        light->setEnabled(enable);
                        scene->lights.push_back(light);

                        ligs = ligs.nextSibling();
                    }



                }




        }
        n=n.nextSibling();
    }
    return true;
}

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "math/vec4.h"
#include <QPalette>
#include <QColorDialog>
#include <stdio.h>
bool type_view = false;
bool info = false;
bool infolight = false;
int  type_light = -1;
Object *ObjSelected = NULL;
Light *LightSelected = NULL;
QImage lastRender;
QImage* targetImage;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->showMaximized();
    defaultCamera();
    ui->ambMaterial->setText("");
    ui->diffMaterial->setText("");
    ui->speMaterial->setText("");
    ui->ambMaterial_2->setText("");
    ui->diffMaterial_2->setText("");
    ui->speMaterial_2->setText("");
    //inits framework
    ui->groupBoxPropertiesObj->setVisible(false);
    ui->onScreenImage->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->onScreenImage->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->onScreenImageBump->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->onScreenImageBump->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->widgetOpenGL->setFocusPolicy(Qt::StrongFocus);
    //connects da camera
    connect(ui->dEyex,SIGNAL(valueChanged(double)),this,SLOT(updadePositionCamera()));
    connect(ui->dEyey,SIGNAL(valueChanged(double)),this,SLOT(updadePositionCamera()));
    connect(ui->dEyez,SIGNAL(valueChanged(double)),this,SLOT(updadePositionCamera()));

    connect(ui->dAtx,SIGNAL(valueChanged(double)),this,SLOT(updadePositionCamera()));
    connect(ui->dAty,SIGNAL(valueChanged(double)),this,SLOT(updadePositionCamera()));
    connect(ui->dAtz,SIGNAL(valueChanged(double)),this,SLOT(updadePositionCamera()));

    connect(ui->dUpx,SIGNAL(valueChanged(double)),this,SLOT(updadePositionCamera()));
    connect(ui->dUpy,SIGNAL(valueChanged(double)),this,SLOT(updadePositionCamera()));
    connect(ui->dUpz,SIGNAL(valueChanged(double)),this,SLOT(updadePositionCamera()));

    //connects perspective
    connect(ui->widgetOpenGL,SIGNAL(updateProjection(Vec4)),this,SLOT(refreshPerspective(Vec4)));
    connect(ui->anglePerspective,SIGNAL(valueChanged(double)),this,SLOT(setProjection()));
    connect(ui->farPerspective,SIGNAL(valueChanged(double)),this,SLOT(setProjection()));
    connect(ui->nearPerspective,SIGNAL(valueChanged(double)),this,SLOT(setProjection()));
    connect(ui->widgetOpenGL,SIGNAL(getCam(Vec4,Vec4,Vec4)),this,SLOT(setCam(Vec4,Vec4,Vec4)));
    connect(ui->widgetOpenGL,SIGNAL(getCamEye(Vec4)),this,SLOT(setCamEye(Vec4)));


    //connects do cenário
    connect(ui->actionGrid,SIGNAL(toggled(bool)),ui->widgetOpenGL,SLOT(showGrid(bool)));
    connect(ui->sizeGrid,SIGNAL(valueChanged(int)),this,SLOT(callsizeGrid(int)));
    connect(ui->actionPropertiesScene,SIGNAL(toggled(bool)),this,SLOT(showPropertiesScene(bool)));
    connect(ui->widgetOpenGL,SIGNAL(widgetHeight(int)),ui->height_l,SLOT(setNum(int)));
    connect(ui->widgetOpenGL,SIGNAL(widgetWidth(int)),ui->width_l,SLOT(setNum(int)));
    connect(ui->widgetOpenGL,SIGNAL(radiusDOF(double)),ui->radiusDOF,SLOT(setValue(double)));
    connect(ui->widgetOpenGL,SIGNAL(focalDOF(double)),ui->focalDOF,SLOT(setValue(double)));
    connect(ui->radiusDOF,SIGNAL(valueChanged(double)),this,SLOT(setPropertyDOF()));
    connect(ui->focalDOF,SIGNAL(valueChanged(double)),this,SLOT(setPropertyDOF()));


    //connects dos objetos
    connect(ui->rotx,SIGNAL(valueChanged(int)),this,SLOT(setPropertyObject()));
    connect(ui->roty,SIGNAL(valueChanged(int)),this,SLOT(setPropertyObject()));
    connect(ui->rotz,SIGNAL(valueChanged(int)),this,SLOT(setPropertyObject()));
    connect(ui->transx,SIGNAL(valueChanged(double)),this,SLOT(setPropertyObject()));
    connect(ui->transy,SIGNAL(valueChanged(double)),this,SLOT(setPropertyObject()));
    connect(ui->transz,SIGNAL(valueChanged(double)),this,SLOT(setPropertyObject()));
    connect(ui->scalex,SIGNAL(valueChanged(double)),this,SLOT(setPropertyObject()));
    connect(ui->scaley,SIGNAL(valueChanged(double)),this,SLOT(setPropertyObject()));
    connect(ui->scalez,SIGNAL(valueChanged(double)),this,SLOT(setPropertyObject()));
    connect(ui->xmotion,SIGNAL(valueChanged(double)),this,SLOT(setPropertyObject()));
    connect(ui->ymotion,SIGNAL(valueChanged(double)),this,SLOT(setPropertyObject()));
    connect(ui->zmotion,SIGNAL(valueChanged(double)),this,SLOT(setPropertyObject()));

    connect(ui->reflection,SIGNAL(valueChanged(double)),this,SLOT(setPropertyObject()));
    connect(ui->refraction,SIGNAL(valueChanged(double)),this,SLOT(setPropertyObject()));
    connect(ui->glossyreflection,SIGNAL(valueChanged(double)),this,SLOT(setPropertyObject()));
    connect(ui->glossyrefraction,SIGNAL(valueChanged(double)),this,SLOT(setPropertyObject()));

    connect(ui->shiniMaterial,SIGNAL(valueChanged(double)),this,SLOT(setPropertyObject()));
    connect(ui->nomeObj,SIGNAL(editingFinished()),this,SLOT(updateListObjects()));
    connect(ui->materialobject,SIGNAL(activated(int)),this,SLOT(setPropertyObject()));
    connect(ui->widgetOpenGL,SIGNAL(listingObjects(std::vector<Object*>)),this,SLOT(objectsList(std::vector<Object*>)));
    connect(ui->objects_list,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(selectObject()));
    connect(ui->objects_list,SIGNAL(currentRowChanged(int)),this,SLOT(selectObject()));
    connect(ui->selectedObj,SIGNAL(clicked(bool)),this,SLOT(selectObject()));
    connect(ui->selectedObj,SIGNAL(clicked(bool)),this,SLOT(setPropertyObject()));
    connect(ui->enableObj,SIGNAL(clicked(bool)),this,SLOT(setPropertyObject()));
    connect(ui->widgetOpenGL,SIGNAL(showObjectSelected(Object*)),this,SLOT(infoObject(Object*)));
    connect(ui->selectedObj,SIGNAL(toggled(bool)),ui->groupBoxPropertiesObj,SLOT(setVisible(bool)));
    connect(ui->deleteObj,SIGNAL(clicked()),this,SLOT(delObtectSelected()));
    connect(ui->enableBump,SIGNAL(clicked(bool)),this,SLOT(setPropertyObject()));
    connect(ui->enableTexture,SIGNAL(clicked(bool)),this,SLOT(setPropertyObject()));
    connect(ui->choiceTexture,SIGNAL(activated(int)),this,SLOT(setPropertyObject()));


    //connects das luzes
    connect(ui->widgetOpenGL,SIGNAL(listingLights(std::vector<Light*>)),this,SLOT(lightsList(std::vector<Light*>)));
    connect(ui->lights_list,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(selectLight()));
    connect(ui->lights_list,SIGNAL(currentRowChanged(int)),this,SLOT(selectLight()));
    connect(ui->widgetOpenGL,SIGNAL(showLightSelected(Light*)),this,SLOT(infoLight(Light*)));
    connect(ui->nameLight,SIGNAL(editingFinished()),this,SLOT(updateListLights()));
    connect(ui->selectedLight,SIGNAL(clicked(bool)),this,SLOT(setPropertiesLights()));
    connect(ui->enableLight,SIGNAL(clicked(bool)),this,SLOT(setPropertiesLights()));
    connect(ui->visibleLight,SIGNAL(clicked(bool)),this,SLOT(setPropertiesLights()));
    connect(ui->positionxLight,SIGNAL(valueChanged(double)),this,SLOT(setPropertiesLights()));
    connect(ui->positionyLight,SIGNAL(valueChanged(double)),this,SLOT(setPropertiesLights()));
    connect(ui->positionzLight,SIGNAL(valueChanged(double)),this,SLOT(setPropertiesLights()));
    connect(ui->attenuationcLight,SIGNAL(valueChanged(double)),this,SLOT(setPropertiesLights()));
    connect(ui->attenuationlLight,SIGNAL(valueChanged(double)),this,SLOT(setPropertiesLights()));
    connect(ui->attenuationqLight,SIGNAL(valueChanged(double)),this,SLOT(setPropertiesLights()));
    connect(ui->vecAx,SIGNAL(valueChanged(double)),this,SLOT(setPropertiesLights()));
    connect(ui->vecAy,SIGNAL(valueChanged(double)),this,SLOT(setPropertiesLights()));
    connect(ui->vecAz,SIGNAL(valueChanged(double)),this,SLOT(setPropertiesLights()));
    connect(ui->vecBx,SIGNAL(valueChanged(double)),this,SLOT(setPropertiesLights()));
    connect(ui->vecBy,SIGNAL(valueChanged(double)),this,SLOT(setPropertiesLights()));
    connect(ui->vecBz,SIGNAL(valueChanged(double)),this,SLOT(setPropertiesLights()));
    connect(ui->directionxLight,SIGNAL(valueChanged(double)),this,SLOT(setPropertiesLights()));
    connect(ui->directionyLight,SIGNAL(valueChanged(double)),this,SLOT(setPropertiesLights()));
    connect(ui->directionzLight,SIGNAL(valueChanged(double)),this,SLOT(setPropertiesLights()));
    connect(ui->anglespotLight,SIGNAL(valueChanged(int)),this,SLOT(setPropertiesLights()));
    connect(ui->anglespotinnerLight,SIGNAL(valueChanged(int)),this,SLOT(setPropertiesLights()));
    connect(ui->exponentSpotLight,SIGNAL(valueChanged(int)),this,SLOT(setPropertiesLights()));
    connect(ui->energyLight,SIGNAL(valueChanged(int)),this,SLOT(setPropertiesLights()));
    connect(ui->widgetOpenGL,SIGNAL(showSample(QImage*)),this,SLOT(showSampleRender(QImage*)));

    //connects do photon mapping
    connect(ui->sizePhotons,SIGNAL(valueChanged(int)),ui->widgetOpenGL,SLOT(setSizePhotons(int)));
    connect(ui->sizePhotonsCaustic,SIGNAL(valueChanged(int)),ui->widgetOpenGL,SLOT(setSizePhotonsCaustic(int)));
    connect(ui->radiusCaustic,SIGNAL(valueChanged(double)),ui->widgetOpenGL,SLOT(setRadiusCaustic(double)));
    connect(ui->radiusGlobal,SIGNAL(valueChanged(double)),ui->widgetOpenGL,SLOT(setRadiusGlobal(double)));
    connect(ui->depthPhoton,SIGNAL(valueChanged(int)),ui->widgetOpenGL,SLOT(setDepthPhotons(int)));
    connect(ui->renderGlobal,SIGNAL(clicked(bool)),ui->widgetOpenGL,SLOT(setRenderGlobal(bool)));
    connect(ui->renderCaustics,SIGNAL(clicked(bool)),ui->widgetOpenGL,SLOT(setRenderCaustic(bool)));
    connect(ui->visiblePhotonMap,SIGNAL(clicked(bool)),ui->widgetOpenGL,SLOT(setVisiblePhoton(bool)));
    connect(ui->visiblePhotonMapCaustics,SIGNAL(clicked(bool)),ui->widgetOpenGL,SLOT(setVisiblePhotonCaustic(bool)));
    connect(ui->enablePhotonMap,SIGNAL(clicked(bool)),ui->widgetOpenGL,SLOT(setEnabledPhotonMap(bool)));
    connect(ui->nearsGlobal,SIGNAL(valueChanged(int)),ui->widgetOpenGL,SLOT(setPhotonsNearsGlobal(int)));
    connect(ui->nearsCaustics,SIGNAL(valueChanged(int)),ui->widgetOpenGL,SLOT(setPhotonsNearsCaustics(int)));
    connect(ui->useFilter,SIGNAL(clicked(bool)),ui->widgetOpenGL,SLOT(setFilterPhotonMap(bool)));

    //connects de render
    connect(ui->showHBB,SIGNAL(clicked(bool)),ui->widgetOpenGL,SLOT(showHBB(bool)));
    connect(ui->widgetOpenGL,SIGNAL(setProgressRay(int)),ui->progressRender,SLOT(setValue(int)));
    updateListObjects();
    updateListLights();
    selectedProperties(-1);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::updadePositionCamera()
{
    Vec4 eye,at,up;
    eye.setVec4(ui->dEyex->value(),ui->dEyey->value(),ui->dEyez->value());
    at.setVec4(ui->dAtx->value(),ui->dAty->value(),ui->dAtz->value());
    up.setVec4(ui->dUpx->value(),ui->dUpy->value(),ui->dUpz->value());
    ui->widgetOpenGL->updateCamera(eye,at,up);
//    //

//    QString valueEye = QString("(%1,%2,%3)").arg(ui->dEyex->value()).arg(ui->dEyey->value()).arg(ui->dEyez->value());
//    QString valueAt = QString("(%1,%2,%3)").arg(ui->dAtx->value()).arg(ui->dAty->value()).arg(ui->dAtz->value());
//    QString valueUp = QString("(%1,%2,%3)").arg(ui->dUpx->value()).arg(ui->dUpy->value()).arg(ui->dUpz->value());



    ui->widgetOpenGL->updateCameraGL();
//    if (type_view) ui->comboBox->setCurrentIndex(0);
//    type_view = false;

}

void MainWindow::defaultCamera()
{
    ui->dEyex->setValue(40.0);
    ui->dEyey->setValue(50.0);
    ui->dEyez->setValue(40.0);

    ui->dAtx->setValue(0.0);
    ui->dAty->setValue(0.0);
    ui->dAtz->setValue(0.0);

    ui->dUpx->setValue(0.0);
    ui->dUpy->setValue(1.0);
    ui->dUpz->setValue(0.0);

    ui->widgetOpenGL->setDefaultWorld();
    updadePositionCamera();
    //ui->comboBox->setCurrentIndex(0);

}

void MainWindow::defaultPositionCamera()
{
    defaultCamera();
    QString valueEye = QString("(%1,%2,%3)").arg(ui->dEyex->value()).arg(ui->dEyey->value()).arg(ui->dEyez->value());
    QString valueAt = QString("(%1,%2,%3)").arg(ui->dAtx->value()).arg(ui->dAty->value()).arg(ui->dAtz->value());
    QString valueUp = QString("(%1,%2,%3)").arg(ui->dUpx->value()).arg(ui->dUpy->value()).arg(ui->dUpz->value());


}

void MainWindow::typeViwer(int value) //vai sair
{
    switch (value){

    case 1:{ //top
        ui->dEyex->setValue(0.0);
        ui->dEyey->setValue(50.0);
        ui->dEyez->setValue(1.0);

        ui->dAtx->setValue(0.0);
        ui->dAty->setValue(0.0);
        ui->dAtz->setValue(0.0);

        ui->dUpx->setValue(0.0);
        ui->dUpy->setValue(1.0);
        ui->dUpz->setValue(0.0);
break;

        //updadePositionCamera();
    }
    case 2:{ //bottom
        ui->dEyex->setValue(0.0);
        ui->dEyey->setValue(-50.0);
        ui->dEyez->setValue(1.0);

        ui->dAtx->setValue(0.0);
        ui->dAty->setValue(0.0);
        ui->dAtz->setValue(0.0);

        ui->dUpx->setValue(0.0);
        ui->dUpy->setValue(1.0);
        ui->dUpz->setValue(0.0);
        break;


        //updadePositionCamera();
    }
    case 3:{ //right
        ui->dEyex->setValue(50.0);
        ui->dEyey->setValue(0.0);
        ui->dEyez->setValue(-4.0);

        ui->dAtx->setValue(0.0);
        ui->dAty->setValue(7.0);
        ui->dAtz->setValue(0.0);

        ui->dUpx->setValue(0.0);
        ui->dUpy->setValue(1.0);
        ui->dUpz->setValue(0.0);
 break;

        //updadePositionCamera();
    }
    case 4:{ //left
        ui->dEyex->setValue(-50.0);
        ui->dEyey->setValue(0.0);
        ui->dEyez->setValue(-3.0);

        ui->dAtx->setValue(0.0);
        ui->dAty->setValue(9.0);
        ui->dAtz->setValue(0.0);

        ui->dUpx->setValue(0.0);
        ui->dUpy->setValue(1.0);
        ui->dUpz->setValue(0.0);
break;

        //updadePositionCamera();
    }
    case 5:{ //front
        ui->dEyex->setValue(0.0);
        ui->dEyey->setValue(0.0);
        ui->dEyez->setValue(45.0);

        ui->dAtx->setValue(0.0);
        ui->dAty->setValue(5.0);
        ui->dAtz->setValue(0.0);

        ui->dUpx->setValue(0.0);
        ui->dUpy->setValue(1.0);
        ui->dUpz->setValue(0.0);

break;
        //updadePositionCamera();
    }
    case 6:{ //back
        ui->dEyex->setValue(-4.0);
        ui->dEyey->setValue(0.0);
        ui->dEyez->setValue(-45.0);

        ui->dAtx->setValue(0.0);
        ui->dAty->setValue(5.0);
        ui->dAtz->setValue(0.0);

        ui->dUpx->setValue(0.0);
        ui->dUpy->setValue(1.0);
        ui->dUpz->setValue(0.0);

break;

    }
    }
    updadePositionCamera();
    type_view = true;
}

void MainWindow::setCamEye(Vec4 eye)
{
    ui->dEyex->setValue(eye.x1);
    ui->dEyey->setValue(eye.x2);
    ui->dEyez->setValue(eye.x3);
    //ui->comboBox->setCurrentIndex(0);
}

void MainWindow::setCam(Vec4 eye, Vec4 at, Vec4 up)
{
    ui->dEyex->setValue(eye.x1);
    ui->dEyey->setValue(eye.x2);
    ui->dEyez->setValue(eye.x3);

    ui->dUpx->setValue(up.x1);
    ui->dUpy->setValue(up.x2);
    ui->dUpz->setValue(up.x3);

    ui->dAtx->setValue(at.x1);
    ui->dAty->setValue(at.x2);
    ui->dAtz->setValue(at.x3);

    //ui->comboBox->setCurrentIndex(0);

}

void MainWindow::refreshPerspective(Vec4 projection)
{
    ui->anglePerspective->setValue(projection.x());
    ui->nearPerspective->setValue(projection.z());
    ui->farPerspective->setValue(projection.w());
    QString value = QString("%1").arg(projection.y());
    //ui->label_aspect->setText(value);
}


void MainWindow::copyScene() //vai sair
{
    //ui->widgetOpenGLRay->setScene(ui->widgetOpenGL->getScene());
}

void MainWindow::setMaxProgress()
{
//    ui->progressBar->setMaximum(ui->widgetOpenGLRay->numberRays());
//    ui->l_rayt->setNum(ui->widgetOpenGLRay->numberRays());
//    ui->l_rayni->setNum(0);
//    ui->l_rayi->setNum(0);
}

void MainWindow::onColorBackgroudCastingChange()
{

}

void MainWindow::showSampleRender(QImage *image)
{
    QImage printImage = image->scaled((int)((ui->width_l->text().toInt()*ui->proportion->value())/100),(int)((ui->height_l->text().toInt()*ui->proportion->value())/100), Qt::KeepAspectRatio);
    lastRender = printImage;
    QGraphicsScene *sc = new QGraphicsScene();
    sc->addPixmap(QPixmap::fromImage(printImage));
    ui->graphicsRender->setScene(sc);


}

void MainWindow::setPropertyDOF()
{
    ui->widgetOpenGL->setDOF(ui->radiusDOF->value(),ui->focalDOF->value());
}


void MainWindow::objectsList(std::vector<Object*> objects)
{
    ui->objects_list->clear();
    for(unsigned int i=0;i<objects.size();i++){
        QString s;
        s.setNum(i);
        s.push_back(" - ");
        s.push_back(objects.at(i)->getName());
        ui->objects_list->addItem(s);
    }
    if (!ui->objects_list->hasFocus()) selectedProperties(-1);
}

void MainWindow::selectObject()
{
    int item = -1;
    if(ui->selectedObj->isChecked() || ui->objects_list->hasFocus()){
        ui->selectedObj->setChecked(true);
        for(int i=0;i < ui->objects_list->count();i++){
            if(ui->objects_list->item(i)->isSelected()){
                item = i;
                break;
            }
      }
    }
    if(item>-1){
        selectedProperties(0);
        ui->widgetOpenGL->setSelectedObject(item);
    }
    else selectedProperties(-1);


}

void MainWindow::infoObject(Object *obj)
{
    if (ui->widgetOpenGL->getItemSelected()<0) return;
    Vec4 rot,translate,scale;
    rot = obj->getMatrixTransformation().getRotationSeted();
    translate = obj->getMatrixTransformation().getTranslateSeted();
    scale = obj->getMatrixTransformation().getScaleSeted();
    QString s;
    info = true;
    ui->groupBoxPropertiesObj->setVisible(true);
    ObjSelected = obj;
    Material *mat = obj->getMesh()->getMaterialM();
    if(ui->rotx->value() != (int)rot.x())  ui->rotx->setValue((int)rot.x());
    if(ui->roty->value() != (int)rot.y())  ui->roty->setValue((int)rot.y());
    if(ui->rotz->value() != (int)rot.z())  ui->rotz->setValue((int)rot.z());

    if(ui->transx->value() != translate.x()) ui->transx->setValue(translate.x());
    if(ui->transy->value() != translate.y()) ui->transy->setValue(translate.y());
    if(ui->transz->value() != translate.z()) ui->transz->setValue(translate.z());

    if(ui->scalex->value() != scale.x()) ui->scalex->setValue(scale.x());
    if(ui->scaley->value() != scale.y()) ui->scaley->setValue(scale.y());
    if(ui->scalez->value() != scale.z()) ui->scalez->setValue(scale.z());

    if(ui->shiniMaterial->value()!=mat->getShininess()) ui->shiniMaterial->setValue(mat->shininess);

    //ui->nface->setNum(obj->getNumFaces());
    //ui->nvertex->setNum(obj->getNumVertexs());
    ui->materialobject->setCurrentIndex(obj->getIdMaterial());
    ui->objects_list->setItemSelected(ui->objects_list->item(ui->widgetOpenGL->getItemSelected()),true);

    QColor color = mat->getColorDiffuseMaterial();
    if(color.isValid())
    {
        ui->diffMaterial->setPalette(QPalette(color));
        ui->diffMaterial->setAutoFillBackground(true);
    }
    QString sd("background: #"
              + QString(color.red() < 16? "0" : "") + QString::number(color.red(),16)
              + QString(color.green() < 16? "0" : "") + QString::number(color.green(),16)
              + QString(color.blue() < 16? "0" : "") + QString::number(color.blue(),16) + ";"
              +"  border-radius: 5px;");
    ui->diffMaterial->setStyleSheet(sd);
    ui->diffMaterial->update();
    color = mat->getColorAmbienteMaterial();
    if(color.isValid())
    {
        ui->ambMaterial->setPalette(QPalette(color));
        ui->ambMaterial->setAutoFillBackground(true);
    }
    QString sa("background: #"
              + QString(color.red() < 16? "0" : "") + QString::number(color.red(),16)
              + QString(color.green() < 16? "0" : "") + QString::number(color.green(),16)
              + QString(color.blue() < 16? "0" : "") + QString::number(color.blue(),16) + ";"
              +"  border-radius: 5px;");
    ui->ambMaterial->setStyleSheet(sa);
    ui->ambMaterial->update();
    color = mat->getColorSpecularMaterial();
    if(color.isValid())
    {
        ui->speMaterial->setPalette(QPalette(color));
        ui->speMaterial->setAutoFillBackground(true);
    }
    QString ss("background: #"
              + QString(color.red() < 16? "0" : "") + QString::number(color.red(),16)
              + QString(color.green() < 16? "0" : "") + QString::number(color.green(),16)
              + QString(color.blue() < 16? "0" : "") + QString::number(color.blue(),16) + ";"
              +"  border-radius: 5px;");

    ui->shiniMaterial->setValue(mat->getShininess());
    ui->speMaterial->setStyleSheet(ss);
    ui->speMaterial->update();

    ui->reflection->setValue(mat->getReflection());
    ui->refraction->setValue(mat->getRefraction());
    ui->glossyreflection->setValue(mat->getGlossyReflection());
    ui->glossyrefraction->setValue(mat->getGlossyRefraction());

    ui->nomeObj->setText(obj->getName());
    ui->enableObj->setChecked(obj->isEnabled());
    Vec4 motion = obj->getMotion();
    ui->xmotion->setValue(motion.x());
    ui->ymotion->setValue(motion.y());
    ui->zmotion->setValue(motion.z());
    //informações de textura
    ui->enableBump->setChecked(obj->getEnabledBump());
    ui->enableTexture->setChecked(obj->getEnabledTexture());
    if(obj->getLenTexture()>0){
        ui->choiceTexture->setCurrentIndex(obj->getTexture(0)->getTypeTexture());
    }else{
        ui->choiceTexture->setCurrentIndex(0);
    }
    if(obj->getLenBump()>0){
        QGraphicsScene *sc = new QGraphicsScene();
        QPixmap *backgroundPixmap = new QPixmap(obj->getBump(0)->getPath());
        QPixmap sized = backgroundPixmap->scaled(
                QSize(ui->onScreenImageBump->width(),
                      ui->onScreenImageBump->height()),
                Qt::KeepAspectRatioByExpanding); // This scales the image too tall

        QImage sizedImage = QImage(sized.toImage());
        QImage sizedCroppedImage = QImage(sizedImage.copy(0,0,
           (ui->onScreenImageBump->width() - 1.5),
           (ui->onScreenImageBump->height() + 19)));
        // so I try to crop using copy(), and I have to use these values
        // and I am unsure why.

        QGraphicsPixmapItem *sizedBackground = sc->addPixmap(
            QPixmap::fromImage(sizedCroppedImage));
        sizedBackground->setZValue(1);
        ui->onScreenImageBump->setScene(sc);
    }else{
        QGraphicsScene *sc = new QGraphicsScene();
        ui->onScreenImageBump->setScene(sc);

    }
    if(obj->getLenTexture()>0){
                QGraphicsScene *sc = new QGraphicsScene();
        QPixmap *backgroundPixmap = new QPixmap(obj->getTexture(0)->getPath());
        QPixmap sized = backgroundPixmap->scaled(
                QSize(ui->onScreenImage->width(),
                      ui->onScreenImage->height()),
                Qt::KeepAspectRatioByExpanding); // This scales the image too tall

        QImage sizedImage = QImage(sized.toImage());
        QImage sizedCroppedImage = QImage(sizedImage.copy(0,0,
           (ui->onScreenImage->width() - 1.5),
           (ui->onScreenImage->height() + 19)));
        // so I try to crop using copy(), and I have to use these values
        // and I am unsure why.

        QGraphicsPixmapItem *sizedBackground = sc->addPixmap(
            QPixmap::fromImage(sizedCroppedImage));
        sizedBackground->setZValue(1);
        ui->onScreenImage->setScene(sc);

    }else{
        QGraphicsScene *sc = new QGraphicsScene();
        ui->onScreenImage->setScene(sc);
    }
    //fim de informações de textura

    info = false;
}

void MainWindow::setPropertyObject()
{

    if (!info){
        //propriedades de textura
        ObjSelected->setEnabledBump(ui->enableBump->isChecked());
        ObjSelected->setEnabledTexture(ui->enableTexture->isChecked());
        if(ObjSelected->getLenTexture()>0){
            ObjSelected->getTexture(0)->setTypeTexture(ui->choiceTexture->currentIndex());
        }
        //fim das propriedades de textura

        Matrix4x4 matrix;
        matrix.setIdentity();
        matrix.scale(ui->scalex->value(),ui->scaley->value(),ui->scalez->value());
        matrix.setRotationZ(ui->rotz->value());
        matrix.setRotationY(ui->roty->value());
        matrix.setRotationX(ui->rotx->value());
        matrix.translate(ui->transx->value(),ui->transy->value(),ui->transz->value());



        ui->widgetOpenGL->setTransformMatrixToObjectSelected(matrix);

        ui->widgetOpenGL->setIdMaterialToObjectSelected(ui->materialobject->currentIndex());
        ui->widgetOpenGL->setEnabledObjectSelected(ui->enableObj->isChecked());
        if (ObjSelected!=NULL) ObjSelected->setSelected(ui->selectedObj->isChecked());
        Vec4 motion = Vec4(ui->xmotion->value(),ui->ymotion->value(),ui->zmotion->value());
        ui->widgetOpenGL->setMotionObjectSelected(motion);



        Material *mat = ObjSelected->getMesh()->getMaterialM();
        QColor color = mat->getColorDiffuseMaterial();
        if(color.isValid())
        {
            ui->diffMaterial->setPalette(QPalette(color));
            ui->diffMaterial->setAutoFillBackground(true);
        }
        QString sd("background: #"
                   + QString(color.red() < 16? "0" : "") + QString::number(color.red(),16)
                   + QString(color.green() < 16? "0" : "") + QString::number(color.green(),16)
                   + QString(color.blue() < 16? "0" : "") + QString::number(color.blue(),16) + ";"
                   +"  border-radius: 5px;");
        ui->diffMaterial->setStyleSheet(sd);
        ui->diffMaterial->update();
        color = mat->getColorAmbienteMaterial();
        if(color.isValid())
        {
            ui->ambMaterial->setPalette(QPalette(color));
            ui->ambMaterial->setAutoFillBackground(true);
        }
        QString sa("background: #"
                   + QString(color.red() < 16? "0" : "") + QString::number(color.red(),16)
                   + QString(color.green() < 16? "0" : "") + QString::number(color.green(),16)
                   + QString(color.blue() < 16? "0" : "") + QString::number(color.blue(),16) + ";"
                   +"  border-radius: 5px;");
        ui->ambMaterial->setStyleSheet(sa);
        ui->ambMaterial->update();
        color = mat->getColorSpecularMaterial();
        if(color.isValid())
        {
            ui->speMaterial->setPalette(QPalette(color));
            ui->speMaterial->setAutoFillBackground(true);
        }
        QString ss("background: #"
                   + QString(color.red() < 16? "0" : "") + QString::number(color.red(),16)
                   + QString(color.green() < 16? "0" : "") + QString::number(color.green(),16)
                   + QString(color.blue() < 16? "0" : "") + QString::number(color.blue(),16) + ";"
                   +"  border-radius: 5px;");

        //ui->shiniMaterial->setValue(mat->getShininess());
        ui->speMaterial->setStyleSheet(ss);
        ui->speMaterial->update();

        mat->setShininess(ui->shiniMaterial->value());
        ui->widgetOpenGL->update();
        mat->setGlossyReflection(ui->glossyreflection->value());
        mat->setGlossyRefraction(ui->glossyrefraction->value());
        mat->setReflection(ui->reflection->value());
        mat->setRefraction(ui->refraction->value());


    }

}


void MainWindow::updateListObjects()
{
    ui->widgetOpenGL->setNameObjectSelected(ui->nomeObj->text());
    for(unsigned int i=0;i<ui->widgetOpenGL->getObjectsScene().size();i++){
        QString s;
        s.setNum(i);
        s.push_back(" - ");
        s.push_back(ui->widgetOpenGL->getObjectsScene().at(i)->getName());
        if(ui->objects_list->count()==i) ui->objects_list->addItem(s);
        ui->objects_list->item(i)->setText(s);
    }
}

void MainWindow::AddObjectCube()
{
    ui->widgetOpenGL->addObject(0);
    updateListObjects();
}

void MainWindow::AddObjectCylinder()
{
    ui->widgetOpenGL->addObject(1);
    updateListObjects();
}

void MainWindow::AddObjectHemiSphere()
{
    ui->widgetOpenGL->addObject(2);
    updateListObjects();
}

void MainWindow::AddObjectPrism()
{
    ui->widgetOpenGL->addObject(3);
    updateListObjects();
}

void MainWindow::delObtectSelected()
{
    ui->widgetOpenGL->removeObjectSelected();
}

void MainWindow::lightsList(std::vector<Light*> lights)
{
    ui->lights_list->clear();

    for(unsigned int i=0;i<lights.size();i++){
        QString s;
        s.setNum(i);
        s.push_back(" - ");
        s.push_back(lights.at(i)->getName());
        ui->lights_list->addItem(s);
    }

    //if (!ui->lights_list->hasFocus()) enableLightTab(false);
}

void MainWindow::selectLight()
{
    int item = -1;
    if(ui->selectedLight->isChecked() || ui->lights_list->hasFocus()){
        ui->selectedLight->setChecked(true);
        for(int i=0;i < ui->lights_list->count();i++){
            if(ui->lights_list->item(i)->isSelected()){
                item = i;
                break;
            }
      }
    }
    if(item<0) selectedProperties(-1);
    else selectedProperties(1);
    ui->widgetOpenGL->setSelectedLight(item);

}


void MainWindow::showPropertiesScene(bool b)
{
    ui->scrollAreaBottom->setVisible(b);
}

void MainWindow::infoLight(Light *light)
{

    infolight = true;
    LightSelected = light;
    type_light = light->getTypeLight();
    //enableLightTab(true);
    switch(type_light){
    case (LIGHT_AMBIENT):{
        //ui->visibleLight->setChecked(light->isVisible());
        QColor color = light->getAmbientColor();
        if(color.isValid())
        {
            ui->ambMaterial_2->setPalette(QPalette(color));
            ui->ambMaterial_2->setAutoFillBackground(true);
        }
        QString sa("background: #"
                  + QString(color.red() < 16? "0" : "") + QString::number(color.red(),16)
                  + QString(color.green() < 16? "0" : "") + QString::number(color.green(),16)
                  + QString(color.blue() < 16? "0" : "") + QString::number(color.blue(),16) + ";"
                  +"  border-radius: 5px;");
        ui->ambMaterial_2->setStyleSheet(sa);
        ui->ambMaterial_2->update();
        ui->attenuationLayoutLight->setVisible(false);
        ui->vectorsLayoutLight->setVisible(false);
        ui->diffuseProperty->setVisible(false);
        ui->specularProperty->setVisible(false);
        ui->orientationLight->setVisible(false);
        ui->angleSpotLayoutLight->setVisible(false);
        ui->deleteLight->setEnabled(false);
        ui->enableLight->setEnabled(false);
        ui->visibleLight->setEnabled(false);
        ui->nameLight->setText(light->getName());
        ui->energyFrame->setVisible(false);

        break;
    }
    case (LIGHT_SPOT):{
        QColor color = light->getDiffuseColor();
        if(color.isValid())
        {
            ui->diffMaterial_2->setPalette(QPalette(color));
            ui->diffMaterial_2->setAutoFillBackground(true);
        }
        QString sd("background: #"
                  + QString(color.red() < 16? "0" : "") + QString::number(color.red(),16)
                  + QString(color.green() < 16? "0" : "") + QString::number(color.green(),16)
                  + QString(color.blue() < 16? "0" : "") + QString::number(color.blue(),16) + ";"
                  +"  border-radius: 5px;");
        ui->diffMaterial_2->setStyleSheet(sd);
        ui->diffMaterial_2->update();
        color = light->getAmbientColor();
        if(color.isValid())
        {
            ui->ambMaterial_2->setPalette(QPalette(color));
            ui->ambMaterial_2->setAutoFillBackground(true);
        }
        QString sa("background: #"
                  + QString(color.red() < 16? "0" : "") + QString::number(color.red(),16)
                  + QString(color.green() < 16? "0" : "") + QString::number(color.green(),16)
                  + QString(color.blue() < 16? "0" : "") + QString::number(color.blue(),16) + ";"
                  +"  border-radius: 5px;");
        ui->ambMaterial_2->setStyleSheet(sa);
        ui->ambMaterial_2->update();
        color = light->getSpecularColor();
        if(color.isValid())
        {
            ui->speMaterial_2->setPalette(QPalette(color));
            ui->speMaterial_2->setAutoFillBackground(true);
        }
        QString ss("background: #"
                  + QString(color.red() < 16? "0" : "") + QString::number(color.red(),16)
                  + QString(color.green() < 16? "0" : "") + QString::number(color.green(),16)
                  + QString(color.blue() < 16? "0" : "") + QString::number(color.blue(),16) + ";"
                  +"  border-radius: 5px;");

        //ui->shiniMaterial->setValue(mat->getShininess());
        ui->speMaterial_2->setStyleSheet(ss);
        ui->speMaterial_2->update();

        ui->nameLight->setText(light->getName());
        Vec4 position = light->getPosition();
        ui->positionxLight->setValue(position.x());
        ui->positionyLight->setValue(position.y());
        ui->positionzLight->setValue(position.z());
        Vec4 direction = light->getDirection();
        ui->directionxLight->setValue(direction.x());
        ui->directionyLight->setValue(direction.y());
        ui->directionzLight->setValue(direction.z());
        Vec4 attenuation = light->getAttenuation();
        ui->attenuationcLight->setValue(attenuation.x());
        ui->attenuationlLight->setValue(attenuation.y());
        ui->attenuationqLight->setValue(attenuation.z());
        ui->exponentSpotLight->setValue(light->getExponent());
        ui->anglespotLight->setValue(light->getAngle());
        ui->enableLight->setChecked(light->isEnabled());
        ui->visibleLight->setChecked(light->isVisible());

        ui->energyFrame->setVisible(false);
        ui->orientationLight->setVisible(true);
        ui->positionLayoutLight->setVisible(true);
        ui->directionLayoutLight->setVisible(true);
        ui->vectorsLayoutLight->setVisible(false);
        ui->angleSpotLayoutLight->setVisible(true);
        ui->deleteLight->setEnabled(true);
        ui->ambienteProperty->setVisible(true);
        ui->diffuseProperty->setVisible(true);
        ui->specularProperty->setVisible(true);
        ui->attenuationLayoutLight->setVisible(true);
        ui->visibleLight->setEnabled(true);
        ui->enableLight->setEnabled(true);

        break;
    }
    case (LIGHT_DIRECTIONAL):{
        QColor color = light->getDiffuseColor();
        if(color.isValid())
        {
            ui->diffMaterial_2->setPalette(QPalette(color));
            ui->diffMaterial_2->setAutoFillBackground(true);
        }
        QString sd("background: #"
                  + QString(color.red() < 16? "0" : "") + QString::number(color.red(),16)
                  + QString(color.green() < 16? "0" : "") + QString::number(color.green(),16)
                  + QString(color.blue() < 16? "0" : "") + QString::number(color.blue(),16) + ";"
                  +"  border-radius: 5px;");
        ui->diffMaterial_2->setStyleSheet(sd);
        ui->diffMaterial_2->update();
        color = light->getAmbientColor();
        if(color.isValid())
        {
            ui->ambMaterial_2->setPalette(QPalette(color));
            ui->ambMaterial_2->setAutoFillBackground(true);
        }
        QString sa("background: #"
                  + QString(color.red() < 16? "0" : "") + QString::number(color.red(),16)
                  + QString(color.green() < 16? "0" : "") + QString::number(color.green(),16)
                  + QString(color.blue() < 16? "0" : "") + QString::number(color.blue(),16) + ";"
                  +"  border-radius: 5px;");
        ui->ambMaterial_2->setStyleSheet(sa);
        ui->ambMaterial_2->update();
        color = light->getSpecularColor();
        if(color.isValid())
        {
            ui->speMaterial_2->setPalette(QPalette(color));
            ui->speMaterial_2->setAutoFillBackground(true);
        }
        QString ss("background: #"
                  + QString(color.red() < 16? "0" : "") + QString::number(color.red(),16)
                  + QString(color.green() < 16? "0" : "") + QString::number(color.green(),16)
                  + QString(color.blue() < 16? "0" : "") + QString::number(color.blue(),16) + ";"
                  +"  border-radius: 5px;");

        //ui->shiniMaterial->setValue(mat->getShininess());
        ui->energyFrame->setVisible(false);
        ui->speMaterial_2->setStyleSheet(ss);
        ui->speMaterial_2->update();
        ui->nameLight->setText(light->getName());
        Vec4 direction = light->getDirection();
        ui->directionxLight->setValue(direction.x());
        ui->directionyLight->setValue(direction.y());
        ui->directionzLight->setValue(direction.z());
        ui->enableLight->setChecked(light->isEnabled());
        ui->visibleLight->setChecked(light->isVisible());
        ui->orientationLight->setVisible(true);
        ui->positionLayoutLight->setVisible(false);
        ui->directionLayoutLight->setVisible(true);
        ui->vectorsLayoutLight->setVisible(false);
        ui->angleSpotLayoutLight->setVisible(false);
        ui->deleteLight->setEnabled(true);
        ui->ambienteProperty->setVisible(true);
        ui->diffuseProperty->setVisible(true);
        ui->specularProperty->setVisible(true);
        ui->attenuationLayoutLight->setVisible(false);
        ui->visibleLight->setEnabled(true);
        ui->enableLight->setEnabled(true);
        break;
    }
    case (LIGHT_PONTUAL):{
        QColor color = light->getDiffuseColor();
        if(color.isValid())
        {
            ui->diffMaterial_2->setPalette(QPalette(color));
            ui->diffMaterial_2->setAutoFillBackground(true);
        }
        QString sd("background: #"
                  + QString(color.red() < 16? "0" : "") + QString::number(color.red(),16)
                  + QString(color.green() < 16? "0" : "") + QString::number(color.green(),16)
                  + QString(color.blue() < 16? "0" : "") + QString::number(color.blue(),16) + ";"
                  +"  border-radius: 5px;");
        ui->diffMaterial_2->setStyleSheet(sd);
        ui->diffMaterial_2->update();
        color = light->getAmbientColor();
        if(color.isValid())
        {
            ui->ambMaterial_2->setPalette(QPalette(color));
            ui->ambMaterial_2->setAutoFillBackground(true);
        }
        QString sa("background: #"
                  + QString(color.red() < 16? "0" : "") + QString::number(color.red(),16)
                  + QString(color.green() < 16? "0" : "") + QString::number(color.green(),16)
                  + QString(color.blue() < 16? "0" : "") + QString::number(color.blue(),16) + ";"
                  +"  border-radius: 5px;");
        ui->ambMaterial_2->setStyleSheet(sa);
        ui->ambMaterial_2->update();
        color = light->getSpecularColor();
        if(color.isValid())
        {
            ui->speMaterial_2->setPalette(QPalette(color));
            ui->speMaterial_2->setAutoFillBackground(true);
        }
        QString ss("background: #"
                  + QString(color.red() < 16? "0" : "") + QString::number(color.red(),16)
                  + QString(color.green() < 16? "0" : "") + QString::number(color.green(),16)
                  + QString(color.blue() < 16? "0" : "") + QString::number(color.blue(),16) + ";"
                  +"  border-radius: 5px;");

        //ui->shiniMaterial->setValue(mat->getShininess());
        ui->energyFrame->setVisible(true);
        ui->speMaterial_2->setStyleSheet(ss);
        ui->speMaterial_2->update();
        ui->visibleLight->setChecked(light->isVisible());
        ui->enableLight->setChecked(light->isEnabled());
        ui->nameLight->setText(light->getName());
        Vec4 position = light->getPosition();
        ui->positionxLight->setValue(position.x());
        ui->positionyLight->setValue(position.y());
        ui->positionzLight->setValue(position.z());
        Vec4 attenuation = light->getAttenuation();
        ui->attenuationcLight->setValue(attenuation.x());
        ui->attenuationlLight->setValue(attenuation.y());
        ui->attenuationqLight->setValue(attenuation.z());
        ui->orientationLight->setVisible(true);
        ui->positionLayoutLight->setVisible(true);
        ui->directionLayoutLight->setVisible(false);
        ui->vectorsLayoutLight->setVisible(false);
        ui->angleSpotLayoutLight->setVisible(false);
        ui->deleteLight->setEnabled(true);
        ui->ambienteProperty->setVisible(true);
        ui->diffuseProperty->setVisible(true);
        ui->specularProperty->setVisible(true);
        ui->attenuationLayoutLight->setVisible(true);
        ui->visibleLight->setEnabled(true);
        ui->enableLight->setEnabled(true);


        break;
    }
    case (LIGHT_AREA):{
        QColor color = light->getDiffuseColor();
        if(color.isValid())
        {
            ui->diffMaterial_2->setPalette(QPalette(color));
            ui->diffMaterial_2->setAutoFillBackground(true);
        }
        QString sd("background: #"
                  + QString(color.red() < 16? "0" : "") + QString::number(color.red(),16)
                  + QString(color.green() < 16? "0" : "") + QString::number(color.green(),16)
                  + QString(color.blue() < 16? "0" : "") + QString::number(color.blue(),16) + ";"
                  +"  border-radius: 5px;");
        ui->diffMaterial_2->setStyleSheet(sd);
        ui->diffMaterial_2->update();
        color = light->getAmbientColor();
        if(color.isValid())
        {
            ui->ambMaterial_2->setPalette(QPalette(color));
            ui->ambMaterial_2->setAutoFillBackground(true);
        }
        QString sa("background: #"
                  + QString(color.red() < 16? "0" : "") + QString::number(color.red(),16)
                  + QString(color.green() < 16? "0" : "") + QString::number(color.green(),16)
                  + QString(color.blue() < 16? "0" : "") + QString::number(color.blue(),16) + ";"
                  +"  border-radius: 5px;");
        ui->ambMaterial_2->setStyleSheet(sa);
        ui->ambMaterial_2->update();
        color = light->getSpecularColor();
        if(color.isValid())
        {
            ui->speMaterial_2->setPalette(QPalette(color));
            ui->speMaterial_2->setAutoFillBackground(true);
        }
        QString ss("background: #"
                  + QString(color.red() < 16? "0" : "") + QString::number(color.red(),16)
                  + QString(color.green() < 16? "0" : "") + QString::number(color.green(),16)
                  + QString(color.blue() < 16? "0" : "") + QString::number(color.blue(),16) + ";"
                  +"  border-radius: 5px;");

        //ui->shiniMaterial->setValue(mat->getShininess());
        ui->energyFrame->setVisible(true);
        ui->speMaterial_2->setStyleSheet(ss);
        ui->speMaterial_2->update();
        ui->visibleLight->setChecked(light->isVisible());
        ui->enableLight->setChecked(light->isEnabled());
        ui->nameLight->setText(light->getName());
        Vec4 position = light->getPosition();
        ui->positionxLight->setValue(position.x());
        ui->positionyLight->setValue(position.y());
        ui->positionzLight->setValue(position.z());
        Vec4 attenuation = light->getAttenuation();
        ui->attenuationcLight->setValue(attenuation.x());
        ui->attenuationlLight->setValue(attenuation.y());
        ui->attenuationqLight->setValue(attenuation.z());
        Vec4 a = light->getVecA();
        ui->vecAx->setValue(a.x());
        ui->vecAy->setValue(a.y());
        ui->vecAz->setValue(a.z());
        Vec4 b = light->getVecB();
        ui->vecBx->setValue(b.x());
        ui->vecBy->setValue(b.y());
        ui->vecBz->setValue(b.z());
        ui->orientationLight->setVisible(true);
        ui->positionLayoutLight->setVisible(true);
        ui->directionLayoutLight->setVisible(false);
        ui->vectorsLayoutLight->setVisible(true);
        ui->angleSpotLayoutLight->setVisible(false);
        ui->deleteLight->setEnabled(true);
        ui->ambienteProperty->setVisible(true);
        ui->diffuseProperty->setVisible(true);
        ui->specularProperty->setVisible(true);
        ui->attenuationLayoutLight->setVisible(true);
        ui->visibleLight->setEnabled(true);
        ui->enableLight->setEnabled(true);

        break;
    }
    }
    infolight = false;

}

void MainWindow::setPropertiesLights()
{
    if (!infolight){
        switch(type_light){
        case (LIGHT_PONTUAL):{
            ui->widgetOpenGL->setEnabledLightSelected(ui->enableLight->isChecked());
            ui->widgetOpenGL->setVisibleLightSelected(ui->visibleLight->isChecked());
            Vec4 position(ui->positionxLight->value(),ui->positionyLight->value(),ui->positionzLight->value());
            ui->widgetOpenGL->setLightSelectedPosition(position);
            Vec4 attenuation(ui->attenuationcLight->value(),ui->attenuationlLight->value(),ui->attenuationqLight->value());
            ui->widgetOpenGL->setLightSelectedAttenuation(attenuation);
            ui->widgetOpenGL->setEnergyLight(ui->energyLight->value());
            break;
        }
        case (LIGHT_SPOT):{
            ui->widgetOpenGL->setEnabledLightSelected(ui->enableLight->isChecked());
            ui->widgetOpenGL->setVisibleLightSelected(ui->visibleLight->isChecked());
            Vec4 position(ui->positionxLight->value(),ui->positionyLight->value(),ui->positionzLight->value());
            ui->widgetOpenGL->setLightSelectedPosition(position);
            Vec4 direction(ui->directionxLight->value(),ui->directionyLight->value(),ui->directionzLight->value());
            ui->widgetOpenGL->setLightSelectedDirection(direction);
            Vec4 attenuation(ui->attenuationcLight->value(),ui->attenuationlLight->value(),ui->attenuationqLight->value());
            ui->widgetOpenGL->setLightSelectedAttenuation(attenuation);
            ui->widgetOpenGL->setLightSelectedAngle(ui->anglespotLight->value());
            ui->widgetOpenGL->setLightSelectedAngleInner(ui->anglespotinnerLight->value());
            ui->widgetOpenGL->setLightSelectedExponent(ui->exponentSpotLight->value());
            break;
        }
        case (LIGHT_DIRECTIONAL):{
            ui->widgetOpenGL->setEnabledLightSelected(ui->enableLight->isChecked());
            ui->widgetOpenGL->setVisibleLightSelected(ui->visibleLight->isChecked());
            Vec4 direction(ui->directionxLight->value(),ui->directionyLight->value(),ui->directionzLight->value());
            ui->widgetOpenGL->setLightSelectedDirection(direction);
            break;
        }
        case (LIGHT_AMBIENT):{
            break;
        }
        case (LIGHT_AREA):{
            ui->widgetOpenGL->setEnabledLightSelected(ui->enableLight->isChecked());
            ui->widgetOpenGL->setVisibleLightSelected(ui->visibleLight->isChecked());
            Vec4 position(ui->positionxLight->value(),ui->positionyLight->value(),ui->positionzLight->value());
            ui->widgetOpenGL->setLightSelectedPosition(position);
            Vec4 attenuation(ui->attenuationcLight->value(),ui->attenuationlLight->value(),ui->attenuationqLight->value());
            ui->widgetOpenGL->setLightSelectedAttenuation(attenuation);
            Vec4 veca(ui->vecAx->value(),ui->vecAy->value(),ui->vecAz->value());
            ui->widgetOpenGL->setLightSelectedVecA(veca);
            Vec4 vecb(ui->vecBx->value(),ui->vecBy->value(),ui->vecBz->value());
            ui->widgetOpenGL->setLightSelectedVecB(vecb);
            ui->widgetOpenGL->setEnergyLight(ui->energyLight->value());
            break;
        }
        }
    }


}

void MainWindow::updateListLights()
{

    ui->widgetOpenGL->setLightSelectedName(ui->nameLight->text());
    for(unsigned int i=0;i<ui->widgetOpenGL->getLightsScene().size();i++){
        QString s;
        s.setNum(i);
        s.push_back(" - ");
        s.push_back(ui->widgetOpenGL->getLightsScene().at(i)->getName());
        if(ui->lights_list->count()==i) ui->lights_list->addItem(s);
        ui->lights_list->item(i)->setText(s);
    }

}

void MainWindow::delLightSelected()
{

}

void MainWindow::addPontualLight()
{
    ui->widgetOpenGL->addLight(LIGHT_PONTUAL);
}

void MainWindow::addDirectionalLight()
{
    ui->widgetOpenGL->addLight(LIGHT_DIRECTIONAL);
}

void MainWindow::addSpotLight()
{
    ui->widgetOpenGL->addLight(LIGHT_SPOT);
}

void MainWindow::callshowGrid(bool b)
{
    ui->widgetOpenGL->showGrid(b);
}

void MainWindow::callsizeGrid(int val)
{
    ui->widgetOpenGL->sizeGrid(val);
}


void MainWindow::callsolidGrid(bool b)
{
    ui->widgetOpenGL->solidGrid(b);
}

void MainWindow::stateSelected(int)
{
//    if(st==0){
//        ui->stateSelected->setText("Set Vector At View Camera");
//    }
//    if(st==Qt::Key_R){
//        ui->stateSelected->setText("Mode Rotate Object");
//    }
//    if(st==Qt::Key_S){
//        ui->stateSelected->setText("Mode Scale Object");
//    }
//    if(st==Qt::Key_T){
//        ui->stateSelected->setText("Mode Translate Object");
//    }
}

void MainWindow::setProjection()
{
    ui->widgetOpenGL->updateProjectionOut(Vec4(ui->anglePerspective->value(),0,ui->nearPerspective->value(),ui->farPerspective->value()));
}

void MainWindow::on_actionScreenShot_triggered()
{
    if(ui->tabOpenGL->isVisible()){
        QString mfile = QFileDialog::getSaveFileName(this,"Save Screen Shot OpenGL");
        if(!mfile.isEmpty()) ui->widgetOpenGL->saveImagem(mfile);
    }
}

void MainWindow::on_actionQuit_triggered()
{
    this->close();
}

void MainWindow::on_actionOpen_triggered()
{
    QString mfile = QFileDialog::getOpenFileName(this,"Load Scene","../models/xml/");
    if(!mfile.isEmpty()){
        ui->showHBB->setChecked(false);
        ui->widgetOpenGL->loadScene(mfile);
        ui->groupBoxPropertiesObj->setVisible(false);
    }
}

void MainWindow::on_actionSave_triggered()
{
    QString mfile = QFileDialog::getSaveFileName(this,"Save Scene","../models/xml/");
    if(!mfile.isEmpty()) ui->widgetOpenGL->saveScene(mfile);


}



//void MainWindow::on_spe_clicked()
//{
//    QColor initialColor = ui->spe->palette().color(QPalette::Background);

//    QColor color = QColorDialog::getColor(initialColor, this);

//    if(color.isValid())
//    {
//        ui->spe->setPalette(QPalette(color));
//        ui->spe->setAutoFillBackground(true);
//    }
//    QString s("background: #"
//                              + QString(color.red() < 16? "0" : "") + QString::number(color.red(),16)
//                              + QString(color.green() < 16? "0" : "") + QString::number(color.green(),16)
//                              + QString(color.blue() < 16? "0" : "") + QString::number(color.blue(),16) + ";"
//            +"  border-radius: 5px;");
//        ui->spe->setStyleSheet(s);
//        ui->spe->update();
//}

void MainWindow::on_ambMaterial_clicked()
{
    ui->ambMaterial->setText("");
    QColor initialColor = ui->ambMaterial->palette().color(QPalette::Background);

    QColor color = QColorDialog::getColor(initialColor, this);

    if(color.isValid())
    {
        ui->ambMaterial->setPalette(QPalette(color));
        ui->ambMaterial->setAutoFillBackground(true);

    }else{
        return;
    }
    QString s("background: #"
              + QString(color.red() < 16? "0" : "") + QString::number(color.red(),16)
              + QString(color.green() < 16? "0" : "") + QString::number(color.green(),16)
              + QString(color.blue() < 16? "0" : "") + QString::number(color.blue(),16) + ";"
              +"  border-radius: 5px;");
    ui->ambMaterial->setStyleSheet(s);
    ui->ambMaterial->update();
    ObjSelected->getMesh()->getMaterialM()->setAmbienteMaterial(Vec4((float)color.red()/256.0,(float)color.green()/256.0,(float)color.blue()/256.0));//Vec4((color.red()*255)%256,(color.green()*255)%256,(color.blue()*255)%256));
    ui->materialobject->setCurrentIndex(0);
    ObjSelected->getMesh()->id_material = 0;

}

void MainWindow::on_diffMaterial_clicked()
{
    ui->diffMaterial->setText("");
    QColor initialColor = ui->diffMaterial->palette().color(QPalette::Background);

    QColor color = QColorDialog::getColor(initialColor, this);

    if(color.isValid())
    {
        ui->diffMaterial->setPalette(QPalette(color));
        ui->diffMaterial->setAutoFillBackground(true);
    }else{
        return;
    }
    QString s("background: #"
              + QString(color.red() < 16? "0" : "") + QString::number(color.red(),16)
              + QString(color.green() < 16? "0" : "") + QString::number(color.green(),16)
              + QString(color.blue() < 16? "0" : "") + QString::number(color.blue(),16) + ";"
              +"  border-radius: 5px;");
    ui->diffMaterial->setStyleSheet(s);
    ui->diffMaterial->update();
    ObjSelected->getMesh()->getMaterialM()->setDiffuseMaterial(Vec4((float)color.red()/256.0,(float)color.green()/256.0,(float)color.blue()/256.0));
    ui->materialobject->setCurrentIndex(0);
    ObjSelected->getMesh()->id_material = 0;


}

void MainWindow::on_speMaterial_clicked()
{
    ui->speMaterial->setText("");
    QColor initialColor = ui->speMaterial->palette().color(QPalette::Background);

    QColor color = QColorDialog::getColor(initialColor, this);

    if(color.isValid())
    {
        ui->speMaterial->setPalette(QPalette(color));
        ui->speMaterial->setAutoFillBackground(true);
    }else{
        return;
    }
    QString s("background: #"
              + QString(color.red() < 16? "0" : "") + QString::number(color.red(),16)
              + QString(color.green() < 16? "0" : "") + QString::number(color.green(),16)
              + QString(color.blue() < 16? "0" : "") + QString::number(color.blue(),16) + ";"
              +"  border-radius: 5px;");
    ui->speMaterial->setStyleSheet(s);
    ui->speMaterial->update();
    ObjSelected->getMesh()->getMaterialM()->setSpecularMaterial(Vec4((float)color.red()/256.0,(float)color.green()/256.0,(float)color.blue()/256.0));
    ui->materialobject->setCurrentIndex(0);
    ObjSelected->getMesh()->id_material = 0;
    //printf("\n(%.3f,%.3f,%.3f)",(float)color.red()/256.0,(float)color.green()/256.0,(float)color.blue()/256.0);

}

void MainWindow::on_shiniMaterial_valueChanged(double arg1)
{
    ObjSelected->getMesh()->getMaterialM()->setShininess(arg1);
    ObjSelected->getMesh()->id_material = 0;
}

void MainWindow::on_btnRender_clicked()
{
    ui->tabWidget->setCurrentIndex(1);
    int nr = ui->widgetOpenGL->numberRays();
    nr = (int)(nr*((float)ui->proportion->value()/100.0)*((float)ui->proportion->value()/100.0))*ui->numSamples->value();
    ui->progressRender->setMaximum(nr);
    ui->widgetOpenGL->renderScene(ui->graphicsRender,ui->proportion->value(),ui->numSamples->value());
}

void MainWindow::selectedProperties(int value)
{
    switch (value){
    case -1:{
        ui->scrollObject->setVisible(true);
        ui->groupBoxPropertiesObj->setVisible(false);
        ui->scrollLight->setVisible(false);
        break;
    }
    case 0:{
        ui->scrollObject->setVisible(true);
        ui->groupBoxPropertiesObj->setVisible(true);
        ui->scrollLight->setVisible(false);
        break;
    }
    case 1:{
        ui->scrollObject->setVisible(false);
        ui->groupBoxPropertiesObj->setVisible(false);
        ui->scrollLight->setVisible(true);
        break;
    }
    }
}

void MainWindow::on_ambMaterial_2_clicked()
{
    ui->ambMaterial_2->setText("");
    QColor initialColor = ui->ambMaterial_2->palette().color(QPalette::Background);

    QColor color = QColorDialog::getColor(initialColor, this);

    if(color.isValid())
    {
        ui->ambMaterial_2->setPalette(QPalette(color));
        ui->ambMaterial_2->setAutoFillBackground(true);
    }else{
        return;
    }
    QString s("background: #"
              + QString(color.red() < 16? "0" : "") + QString::number(color.red(),16)
              + QString(color.green() < 16? "0" : "") + QString::number(color.green(),16)
              + QString(color.blue() < 16? "0" : "") + QString::number(color.blue(),16) + ";"
              +"  border-radius: 5px;");
    ui->ambMaterial_2->setStyleSheet(s);
    ui->ambMaterial_2->update();
    LightSelected->setAmbientColor(color);
    //ObjSelected->getMesh()->getMaterialM()->setDiffuseMaterial(Vec4((float)color.red()/255.0,(float)color.green()/255.0,(float)color.blue()/255.0));
    //ui->materialobject->setCurrentIndex(0);

}

void MainWindow::on_diffMaterial_2_clicked()
{
    ui->diffMaterial_2->setText("");
    QColor initialColor = ui->diffMaterial_2->palette().color(QPalette::Background);

    QColor color = QColorDialog::getColor(initialColor, this);

    if(color.isValid())
    {
        ui->diffMaterial_2->setPalette(QPalette(color));
        ui->diffMaterial_2->setAutoFillBackground(true);
    }else{
        return;
    }
    QString s("background: #"
              + QString(color.red() < 16? "0" : "") + QString::number(color.red(),16)
              + QString(color.green() < 16? "0" : "") + QString::number(color.green(),16)
              + QString(color.blue() < 16? "0" : "") + QString::number(color.blue(),16) + ";"
              +"  border-radius: 5px;");
    ui->diffMaterial_2->setStyleSheet(s);
    ui->diffMaterial_2->update();
    LightSelected->setDiffuseColor(color);
}

void MainWindow::on_speMaterial_2_clicked()
{
    ui->speMaterial_2->setText("");
    QColor initialColor = ui->speMaterial_2->palette().color(QPalette::Background);

    QColor color = QColorDialog::getColor(initialColor, this);

    if(color.isValid())
    {
        ui->speMaterial_2->setPalette(QPalette(color));
        ui->speMaterial_2->setAutoFillBackground(true);
    }else{
        return;
    }
    QString s("background: #"
              + QString(color.red() < 16? "0" : "") + QString::number(color.red(),16)
              + QString(color.green() < 16? "0" : "") + QString::number(color.green(),16)
              + QString(color.blue() < 16? "0" : "") + QString::number(color.blue(),16) + ";"
              +"  border-radius: 5px;");
    ui->speMaterial_2->setStyleSheet(s);
    ui->speMaterial_2->update();
    LightSelected->setSpecularColor(color);
}

void MainWindow::on_actionCube_triggered()
{
    ui->widgetOpenGL->addObject(BLOCK_CUBE);
}

void MainWindow::on_actionCylinder_triggered()
{
    ui->widgetOpenGL->addObject(BLOCK_CYLINDER);
}

void MainWindow::on_actionHemisphere_triggered()
{
    ui->widgetOpenGL->addObject(BLOCK_HEMISPHERE);
}

void MainWindow::on_actionPrism_triggered()
{
    ui->widgetOpenGL->addObject(BLOCK_PRISM);
}

void MainWindow::on_actionSphere_triggered()
{
    ui->widgetOpenGL->addObject(BLOCK_SPHERE);
}

void MainWindow::on_actionArea_triggered()
{
    ui->widgetOpenGL->addLight(LIGHT_AREA);
}

void MainWindow::on_actionDirectional_triggered()
{
    ui->widgetOpenGL->addLight(LIGHT_DIRECTIONAL);
}

void MainWindow::on_actionPontual_triggered()
{
    ui->widgetOpenGL->addLight(LIGHT_PONTUAL);
}

void MainWindow::on_actionSpot_triggered()
{
    ui->widgetOpenGL->addLight(LIGHT_SPOT);
}

void MainWindow::on_deleteLight_clicked()
{
    ui->widgetOpenGL->removeLightSelected();
}

void MainWindow::on_actionScreanShot_Render_triggered()
{
    if(ui->tabRender->isVisible()){
        QString mfile = QFileDialog::getSaveFileName(this,"Save Screen Shot Render","../renderImg/");
        if(!mfile.isEmpty()) lastRender.save(mfile+".png","PNG");
    }
}

void MainWindow::on_actionCone_triggered()
{
    ui->widgetOpenGL->addObject(BLOCK_CONE);
}

void MainWindow::on_loadTexture_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "../texture/", tr("Image Files (*.png *.tga *.bmp *.rgb *.jpg)"));
    // you could have a BMP or Targa file at this point
    // Qt has no Targa format support out of the box
    if (!fileName.isEmpty())
    {
    targetImage = new QImage(fileName);
    // Not much good if the file is not a PNG
    // You allocate memory you do not free: memory leak
    // No need for this to be on the heap at all

    if(targetImage->isNull())
    {
    QMessageBox::information(this,
    tr("Viewer"),
    tr("Cannot load %1.").arg(fileName));
    return;
    }

    //ui->onScreenImage->setBackgroundRole(QPalette::Base);
    //ui->onScreenImage->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    //ui->onScreenImage->setScaledContents(true);
    //ui->onScreenImage->setPixmap(QPixmap::fromImage(*targetImage));
    QGraphicsScene *sc = new QGraphicsScene();
    sc->addPixmap(QPixmap::fromImage(*targetImage));
    ui->onScreenImage->setScene(sc);
    Texture* texture = new Texture(targetImage,fileName);
    if (ObjSelected!=NULL) ObjSelected->setTexture(texture);

    // the graphicsView still scrolls if the image is too large, but
    // displays no scrollbars. I would like it not to scroll (I want to
    // add a scrolling widget into the QGraphicsScene later, on top of
    // the background image.)


    QPixmap *backgroundPixmap = new QPixmap(fileName);
    QPixmap sized = backgroundPixmap->scaled(
            QSize(ui->onScreenImage->width(),
                  ui->onScreenImage->height()),
            Qt::KeepAspectRatioByExpanding); // This scales the image too tall

    QImage sizedImage = QImage(sized.toImage());
    QImage sizedCroppedImage = QImage(sizedImage.copy(0,0,
       (ui->onScreenImage->width() - 1.5),
       (ui->onScreenImage->height() + 19)));
    // so I try to crop using copy(), and I have to use these values
    // and I am unsure why.

    QGraphicsPixmapItem *sizedBackground = sc->addPixmap(
        QPixmap::fromImage(sizedCroppedImage));
    sizedBackground->setZValue(1);
    ui->onScreenImage->setScene(sc);

    // Why did you use a QImage if you require a QPixmap ultimately?
    }
}

void MainWindow::on_loadBump_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "../texture/", tr("Image Files (*.png *.tga *.bmp *.rgb *.jpg)"));
    // you could have a BMP or Targa file at this point
    // Qt has no Targa format support out of the box
    if (!fileName.isEmpty())
    {
        targetImage = new QImage(fileName);
        // Not much good if the file is not a PNG
        // You allocate memory you do not free: memory leak
        // No need for this to be on the heap at all

        if(targetImage->isNull())
        {
            QMessageBox::information(this,
                                     tr("Viewer"),
                                     tr("Cannot load %1.").arg(fileName));
            return;
        }

        //ui->onScreenImage->setBackgroundRole(QPalette::Base);
        //ui->onScreenImage->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        //ui->onScreenImage->setScaledContents(true);
        //ui->onScreenImage->setPixmap(QPixmap::fromImage(*targetImage));
        QGraphicsScene *sc = new QGraphicsScene();
        sc->addPixmap(QPixmap::fromImage(*targetImage));
        ui->onScreenImageBump->setScene(sc);
        Bump* bump = new Bump(targetImage,fileName);
        if (ObjSelected!=NULL) ObjSelected->setBump(bump);

        // Why did you use a QImage if you require a QPixmap ultimately?
        QPixmap *backgroundPixmap = new QPixmap(fileName);
        QPixmap sized = backgroundPixmap->scaled(
                QSize(ui->onScreenImageBump->width(),
                      ui->onScreenImageBump->height()),
                Qt::KeepAspectRatioByExpanding); // This scales the image too tall

        QImage sizedImage = QImage(sized.toImage());
        QImage sizedCroppedImage = QImage(sizedImage.copy(0,0,
           (ui->onScreenImageBump->width() - 1.5),
           (ui->onScreenImageBump->height() + 19)));
        // so I try to crop using copy(), and I have to use these values
        // and I am unsure why.

        QGraphicsPixmapItem *sizedBackground = sc->addPixmap(
            QPixmap::fromImage(sizedCroppedImage));
        sizedBackground->setZValue(1);
        ui->onScreenImageBump->setScene(sc);

    }
}

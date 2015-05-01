#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "math/matrix4x4.h"
#include <QMainWindow>
#include <QColor>
#include "block/object.h"
#include "structure/light.h"
namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color NOTIFY colorBackgroudCastingChange)
    Q_PROPERTY(QColor colorDif READ colorDif NOTIFY colorDiffuseChange)
    Q_PROPERTY(QColor colorAmb READ colorAmb NOTIFY colorAmbientChange)
    Q_PROPERTY(QColor colorSpe READ colorSpe NOTIFY colorSpecularChange)
    Q_PROPERTY(QColor colorMatView READ colorMatView NOTIFY colorMaterialView)
    Q_PROPERTY(QColor colorMatObj READ colorMatObj NOTIFY colorMaterialObject)

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void defaultCamera();
    QColor color() const{
        return m_color;
    }
    QColor colorDif() const{
        return m_color_difuse;
    }
    QColor colorAmb() const{
        return m_color_ambient;
    }
    QColor colorSpe() const{
        return m_color_specular;
    }
    QColor colorMatView() const{
        return m_color_material_view;
    }
    QColor colorMatObj() const{
        return m_color_material_object;
    }



public slots:
    void stateSelected(int st);
    void callshowGrid(bool b);
    void callsizeGrid(int val);
    void callsolidGrid(bool b);
    void updadePositionCamera();
    void defaultPositionCamera();
    void typeViwer(int t);
    void setCamEye(Vec4 eye);
    void setProjection();
    void setCam(Vec4 eye,Vec4 at,Vec4 up);
    void refreshPerspective(Vec4 projection);
    void copyScene();
    void setMaxProgress();
    void onColorBackgroudCastingChange();
    void showSampleRender(QImage*);
    //slots do cenário
    void setPropertyDOF();

    //slots de objeto
    void objectsList(std::vector<Object*> objects);
    void selectObject();
    void infoObject(Object* obj);
    void setPropertyObject();
    void updateListObjects();
    void AddObjectCube();
    void AddObjectCylinder();
    void AddObjectPrism();
    void AddObjectHemiSphere();
    void delObtectSelected();
    //slots de light
    void lightsList(std::vector<Light*> ligths);
    void setPropertiesLights();
    void infoLight(Light* obj);
    void selectLight();
    void updateListLights();
    void delLightSelected();
    void addPontualLight();
    void addDirectionalLight();
    void addSpotLight();


signals:
    void colorBackgroudCastingChange(QColor arg);
    void colorMaterialView(QColor arg);
    void colorMaterialObject(QColor arg);
    void colorSpecularChange(QColor arg);
    void colorDiffuseChange(QColor arg);
    void colorAmbientChange(QColor arg);


private slots:
//    void on_btnSaveImgRay_clicked();

//    void on_btnSaveSceneOpenGL_clicked();

//    void on_SaveScene_clicked();

//    void on_pushButton_2_clicked();

//    void on_pushButton_3_clicked();

//    void on_pushButton_4_clicked();

//    void on_createHBB_clicked();
    void on_actionScreenShot_triggered();
    void on_actionQuit_triggered();
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void showPropertiesScene(bool b);


    //void on_spe_clicked();

    void on_ambMaterial_clicked();

    void on_diffMaterial_clicked();

    void on_speMaterial_clicked();

    void on_shiniMaterial_valueChanged(double arg1);

    void on_btnRender_clicked();
    void selectedProperties(int value);

    void on_ambMaterial_2_clicked();

    void on_diffMaterial_2_clicked();

    void on_speMaterial_2_clicked();

    void on_actionCube_triggered();

    void on_actionCylinder_triggered();

    void on_actionHemisphere_triggered();

    void on_actionPrism_triggered();

    void on_actionSphere_triggered();

    void on_actionArea_triggered();

    void on_actionDirectional_triggered();

    void on_actionPontual_triggered();

    void on_actionSpot_triggered();

    void on_deleteLight_clicked();

    void on_actionScreanShot_Render_triggered();

    void on_actionCone_triggered();

    void on_loadTexture_clicked();

    void on_loadBump_clicked();

private:
    Ui::MainWindow *ui;
    QColor m_color;
    QColor m_color_specular;
    QColor m_color_ambient;
    QColor m_color_difuse;
    QColor m_color_material_view;
    QColor m_color_material_object;

};

#endif // MAINWINDOW_H

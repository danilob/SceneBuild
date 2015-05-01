#ifndef CASTINGWIDGET_H
#define CASTINGWIDGET_H
#include "interface/scene.h"
#include "math/raycasting.h"
#include "math/raytracing.h"
#include <QColor>
#include <QGLWidget>
#include <QString>

class CastingWidget : public QGLWidget
{
    Q_OBJECT
public:
    bool draw,otimized;
    int width, height;
    Scene* scene;

    Vec4 back_color;

    explicit CastingWidget(QWidget *parent = 0);
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void updateLightingGL();
    void TesteWindow();

signals:
    void setProgress(int);
    void setIntersectRay(int);
    void setNotIntersectRay(int);


public slots:
    void setValueProgress(int);
    void setValueIntersectRay(int);
    void setValueNotIntersectRay(int);
    void setScene(Scene *sc);
    int numberRays();
    void testeRayCasting();
    void backgroudColorRay(QColor color);
    void setOtimized(bool b);
    void saveScreen(QString str);

};

#endif // CASTINGWIDGET_H

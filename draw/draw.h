#ifndef DRAW_H
#define DRAW_H
#include "math/vec4.h"
//#include "block/cube.h"
//#include "block/cylinder.h"
//#include "block/prism.h"
//#include "block/hemisphere.h"
class Draw
{

public:
    Draw();
    static void drawPlane(int size,bool solid,bool texture=false);       //desenho da grid
    static void drawArrow(Vec4* position_,double size=1.0);              //desenha uma "flecha"
    static void drawSpot(Vec4* position_,Vec4* direction,double angle);  //desenha um cone spot
    static void drawPoint(Vec4 v,int size=1,Vec4 color=Vec4(1,1,1));     //desenha um ponto
    static void drawSelection(Vec4 max,Vec4 min);                        //desenha um cubo selecionado o objeto

};

#endif // DRAW_H

#include "draw.h"
#include "GL/glut.h"
#include "interface/scene.h"
Draw::Draw()
{

}

void Draw::drawPlane(int size, bool solid, bool texture)
{

    if(!solid){
        glLineWidth(0.7);
        glDisable(GL_LIGHTING);
        glPushMatrix();
        glColor3f(0.5,0.5,0.5);
        glBegin(GL_LINES);
        for(int i=-size;i<=size;i+=2){
            for(int j=size;j>=-size;j-=2){
                glVertex3f(i,0,j);
                glVertex3f(i,0,-j);
                glVertex3f(i,0,j);
                glVertex3f(-i,0,j);
            }
        }
        glEnd();
        glPopMatrix();
        glEnable(GL_LIGHTING);
    }else{
        Material *mat = new Material();
        mat->setMaterial(mat,MATERIAL_GUMMI);
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,mat->ambient);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat->diffuse);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat->specular);
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, mat->shininess*128);
        glPushMatrix();

        glBegin(GL_QUADS);
            glNormal3f(0,1,0);
            glVertex3f(size,0,size);
            glVertex3f(size,0,-size);
            glVertex3f(-size,0,-size);
            glVertex3f(-size,0,size);
        glEnd();
        glPopMatrix();
    }
}



void Draw::drawArrow(Vec4 *position_,double size)
{
    glPushMatrix();
    int _pbase = 30;
    double length_ = 1.5;
    double radius = 0.7*length_;
    double alpha  = 2*M_PI/_pbase;
        Vec4 vertexs[_pbase+1];
        for (int i=0;i<_pbase;i++){
            vertexs[i].setVec4(cos(alpha*i)*radius+position_->x1*length_,position_->x2*length_,sin(alpha*i)*radius+position_->x3*length_);
        }
        vertexs[_pbase] = Vec4(-position_->x1,-position_->x2,-position_->x3);
        Vec4 normal;
        glTranslated(size*position_->x1,size*position_->x2,size*position_->x3);
        glBegin(GL_POLYGON);
            for (int i=0;i<_pbase;i++){
                glVertex3d(vertexs[i].x1,vertexs[i].x2,vertexs[i].x3);
            }
        glEnd();
        glBegin(GL_TRIANGLES);
            for (int i=0;i<_pbase;i++){
                if(i<_pbase-1){

                    glVertex3d(vertexs[i].x1,vertexs[i].x2,vertexs[i].x3);
                    glVertex3d(vertexs[i+1].x1,vertexs[i+1].x2,vertexs[i+1].x3);
                    glVertex3d(vertexs[_pbase].x1,vertexs[_pbase].x2,vertexs[_pbase].x3);
                }else{

                    glVertex3d(vertexs[i].x1,vertexs[i].x2,vertexs[i].x3);
                    glVertex3d(vertexs[0].x1,vertexs[0].x2,vertexs[0].x3);
                    glVertex3d(vertexs[_pbase].x1,vertexs[_pbase].x2,vertexs[_pbase].x3);
                }
            }
        glEnd();
        glPopMatrix();
}

void Draw::drawSpot(Vec4 *position_, Vec4 *direction,double angle)
{
    glPushMatrix();
    int _pbase = 30;
    //double length_ = 1.0;
    double radius = atan(M_PI*angle/180.0);
    double alpha  = 2*M_PI/_pbase;

        Vec4 vertexs[_pbase+1];
        for (int i=0;i<_pbase;i++){
            vertexs[i].setVec4(cos(alpha*i)*radius+(position_->x1+direction->x1),(position_->x2+direction->x2),sin(alpha*i)*radius+(position_->x3+direction->x3));
        }
        vertexs[_pbase] = Vec4(position_->x1,position_->x2,position_->x3);
        glBegin(GL_LINES);
            for (int i=0;i<_pbase;i++){
                    glVertex3d(vertexs[_pbase].x1,vertexs[_pbase].x2,vertexs[_pbase].x3) ;
                    glVertex3d(vertexs[i].x1,vertexs[i].x2,vertexs[i].x3);
            }
        glEnd();

        glPopMatrix();
}

void Draw::drawPoint(Vec4 v,int size, Vec4 color)
{
    glDisable(GL_LIGHTING);
    glPointSize(size);
    glColor3f(color.x(),color.y(),color.z());
    glBegin(GL_POINTS);
    glVertex3f(v.x(),v.y(),v.z());
    glEnd();
    glPointSize(1);
    glEnable(GL_LIGHTING);
}

void Draw::drawSelection(Vec4 max, Vec4 min)
{
    Vec4 center = (max+min)/2.0;
    //float diag = (max - center).module();
    float h    = (max - Vec4(max.x(),center.y(),max.z())).module(); //eixo y
    float c    = (Vec4(max.x(),center.y(),center.z())-Vec4(max.x(),center.y(),max.z())).module(); //eixo z
    float l    = (center - Vec4(max.x(),center.y(),center.z())).module(); //eixo x

    float less  = fmin(fmin(h,c),l)*0.5;
    glColor3f(1,1,1);
    glDisable(GL_LIGHTING);
    glBegin(GL_LINES);
        //canto maximo
        glVertex3f(max.x(),max.y(),max.z());
        glVertex3f(max.x(),max.y(),max.z()-less);

        glVertex3f(max.x(),max.y(),max.z());
        glVertex3f(max.x()-less,max.y(),max.z());

        glVertex3f(max.x(),max.y(),max.z());
        glVertex3f(max.x(),max.y()-less,max.z());
        //canto minimo
        glVertex3f(min.x(),min.y(),min.z());
        glVertex3f(min.x(),min.y(),min.z()+less);

        glVertex3f(min.x(),min.y(),min.z());
        glVertex3f(min.x(),min.y()+less,min.z());

        glVertex3f(min.x(),min.y(),min.z());
        glVertex3f(min.x()+less,min.y(),min.z());

        //canto baixo
        glVertex3f(max.x(),min.y(),min.z());
        glVertex3f(max.x(),min.y()+less,min.z());

        glVertex3f(max.x(),min.y(),min.z());
        glVertex3f(max.x(),min.y(),min.z()+less);

        glVertex3f(max.x(),min.y(),min.z());
        glVertex3f(max.x()-less,min.y(),min.z());

        //canto baixo
        glVertex3f(max.x(),min.y(),max.z());
        glVertex3f(max.x(),min.y()+less,max.z());

        glVertex3f(max.x(),min.y(),max.z());
        glVertex3f(max.x(),min.y(),max.z()-less);

        glVertex3f(max.x(),min.y(),max.z());
        glVertex3f(max.x()-less,min.y(),max.z());

        //canto baixo
        glVertex3f(min.x(),min.y(),max.z());
        glVertex3f(min.x(),min.y(),max.z()-less);

        glVertex3f(min.x(),min.y(),max.z());
        glVertex3f(min.x(),min.y()+less,max.z());

        glVertex3f(min.x(),min.y(),max.z());
        glVertex3f(min.x()+less,min.y(),max.z());

        //canto cima
        glVertex3f(max.x(),max.y(),min.z());
        glVertex3f(max.x(),max.y()-less,min.z());

        glVertex3f(max.x(),max.y(),min.z());
        glVertex3f(max.x()-less,max.y(),min.z());

        glVertex3f(max.x(),max.y(),min.z());
        glVertex3f(max.x(),max.y(),min.z()+less);

        //canto cima
        glVertex3f(min.x(),max.y(),max.z());
        glVertex3f(min.x(),max.y(),max.z()-less);

        glVertex3f(min.x(),max.y(),max.z());
        glVertex3f(min.x(),max.y()-less,max.z());

        glVertex3f(min.x(),max.y(),max.z());
        glVertex3f(min.x()+less,max.y(),max.z());

        //canto cima
        glVertex3f(min.x(),max.y(),min.z());
        glVertex3f(min.x()+less,max.y(),min.z());

        glVertex3f(min.x(),max.y(),min.z());
        glVertex3f(min.x(),max.y(),min.z()+less);

        glVertex3f(min.x(),max.y(),min.z());
        glVertex3f(min.x(),max.y()-less,min.z());

    glEnd();
    glEnable(GL_LIGHTING);
    return;

}

#include "camera.h"

Camera::Camera()
{
    eye = Vec4();
    at =  Vec4();
    up =  Vec4();

    eye.x1=40;
    eye.x2=50;
    eye.x3=40;

    at.x1=0;
    at.x2=0;
    at.x3=0;
    //c.z=0 ou e.z-1;

    up.x1=0;
    up.x2=1;
    up.x3=0;

    axis_y = false;
    axis_z = false;
    axis_x = false;

    type = CAMERA_FAR;
}

Camera::Camera(Vec4 e, Vec4 c, Vec4 u)
{
    this->eye = Vec4();
    this->at =  Vec4();
    this->up =  Vec4();

    this->eye = e;
    this->at  = c;
    this->up  = u;

    type = CAMERA_FAR;
}

Camera::Camera(float ex, float ey, float ez, float cx, float cy, float cz, float ux, float uy, float uz)
{
    this->eye = Vec4();
    this->at =  Vec4();
    this->up =  Vec4();

    eye.x1=ex;
    eye.x2=ey;
    eye.x3=ez;

    at.x1=cx;
    at.x2=cy;
    at.x3=cz;

    up.x1=ux;
    up.x2=uy;
    up.x3=uz;

    type = CAMERA_FAR;

}

Camera::~Camera()
{
}

void Camera::zoom(float win_y, float last_y)
{
    if(type==CAMERA_FAR){
        //vetor do olho(eye) ao centro(center)
        Vec4 Vec = at - eye;
        //normalizando o Vec
        Vec.normalize();

        //GLfloat moduloVec = Vec.modulo();
        //if ((moduloVec > 1) || (last_y > win_y)){
        //  e = e.soma(Vec.multiplicacao( (win_y - last_y)/2 ));
        //}
        //nova estrategia bem melhor
        Vec4 eNovo = eye + Vec*( (win_y - last_y)/20.0 );
        if ( (at-eNovo)*(Vec) >= 0.0001 ){
            eye = eNovo;
        }
    }
}

void Camera::translatex(float win_x, float last_x)
{
    if(type==CAMERA_FAR){
        Vec4 Vec = at - eye;
        //vetor no sentido positivo da direcao x
        Vec4 Xpos = Vec^(up);
        Xpos.normalize();
        float x = at.x();
        float y = at.y();
        float z = at.z();

        float x2 = eye.x();
        float y2 = eye.y();
        float z2 = eye.z();

        at =  at +( Xpos*( Vec.module()*(last_x - win_x)/300.0 ) );
        eye = eye+( Xpos*( Vec.module()*(last_x - win_x)/300.0 ) );
        if(axis_x){
            eye.x1 = x2;
            at.x1 = x;
        }
        if(axis_y){
            eye.x2 = y2;
            at.x2 = y;
        }
        if(axis_z){
            eye.x3 = z2;
            at.x3 = z;
        }



    }
}

void Camera::translatey(float win_y, float last_y)
{
    if(type==CAMERA_FAR){
        //vetor do olho(eye) ao centro(center)
          Vec4 Vec = at - eye;
          float x = at.x();
          float y = at.y();
          float z = at.z();

          float x2 = eye.x();
          float y2 = eye.y();
          float z2 = eye.z();

          at  = at  - ( up*( Vec.module()*(last_y - win_y)/300.0 ) );
          eye = eye - ( up*( Vec.module()*(last_y - win_y)/300.0 ) );
          if(axis_x){
              eye.x1 = x2;
              at.x1 = x;
          }
          if(axis_y){
              eye.x2 = y2;
              at.x2 = y;
          }
          if(axis_z){
              eye.x3 = z2;
              at.x3 = z;
          }



    }
}

void Camera::rotatex(float win_y, float last_y)
{
    if(type==CAMERA_FAR){
        float y = at.y();
        float x = at.x();
        float z = at.z();
    Vec4 aux = at;//Vetor3D(c.x, c.y, c.z);
      at = at*(2.0)-(eye);
      eye = aux;//.recebe(aux);

      //vetor do olho(eye) ao centro(center)
      Vec4 Vec = at-(eye);
      GLfloat moduloVecant = Vec.module();
      at = at+(up*( ((1.0/30.0)*moduloVecant)*(last_y - win_y)/5.0 ));
      Vec = at-(eye);
      GLfloat moduloVec = Vec.module();
        Vec = Vec*(moduloVecant/moduloVec);
      at = eye+(Vec);
      if(axis_y){
          at.x2 = y;
      }
      if(axis_x){
          at.x1 = x;
      }
      if(axis_z){
          at.x3 = z;
      }
      Vec = at-(eye);

      //vetor no sentido positivo da direcao x
      Vec4 u;
      if (up.y()>=0.0) {
        u = Vec4(0.0,1.0,0.0);
      } else {
        u = Vec4(0.0,-1.0,0.0);
      }
      Vec4 XposUp = Vec^(u);
      up = XposUp^(Vec);
      up.normalize();

      aux = eye;//.recebe(e);
      eye = eye*(2.0)-(at);
      at = aux;//.recebe(aux);
      if(axis_y){
          at.x2 = y;
      }
      if(axis_x){
          at.x1 = x;
      }
      if(axis_z){
          at.x3 = z;
      }
      }else{

        float y = at.y();
        float x = at.x();
        float z = at.z();
        at = at +( up*( (last_y - win_y)/100.0 ) );

        //Vec normalizado
        Vec4 N = at - eye;
        N.normalize();
        at = eye +(N);
        if(axis_y){
            at.x2 = y;
        }
        if(axis_x){
            at.x1 = x;
        }
        if(axis_z){
            at.x3 = z;
        }

        //vetor no sentido positivo da direcao x
        if(!axis_x && !axis_y && !axis_z){
            Vec4 Xpos = N^(up);
            up = Xpos^(N);
            up.normalize();
        }


    }
}

void Camera::rotatey(float win_x, float last_x)
{

    if(type==CAMERA_FAR){
        float y = at.y();
        float x = at.x();
        float z = at.z();
    Vec4 aux = at;//Vetor3D(c.x, c.y, c.z);
    at = at*2 - eye;
    eye = aux;//.recebe(aux);

    //vetor do olho(eye) ao centro(center)
    Vec4 Vec = at-eye;
    GLfloat moduloVecant = Vec.module();
    //vetor no sentido positivo da direcao x
    Vec4 Xpos = Vec^(up);
    Xpos.normalize();

    at = at-(Xpos*( ((1.0/30.0)*moduloVecant)*(last_x - win_x)/5.0 ));

    Vec = at -(eye);
    GLfloat moduloVec = Vec.module();
      Vec = Vec*( moduloVecant/moduloVec );
    at = eye+(Vec);
    if(axis_y){
        at.x2 = y;
    }
    if(axis_x){
        at.x1 = x;
    }
    if(axis_z){
        at.x3 = z;
    }
    //novo-----------------------------------
    //atualizando u
    Vec4 u;
    if (up.y()>=0.0) {
      u = Vec4(0.0,1.0,0.0);
    } else {
      u = Vec4(0.0,-1.0,0.0);
    }
    Vec4 XposUp = Vec^(u);
    up = XposUp^(Vec);
    up.normalize();
    //fim_novo-------------------------------

    aux = eye;//.recebe(e);
    eye = eye*(2.0)-(at);
    at = aux;//.recebe(aux);

    }else{
        float y = at.y();
        float x = at.x();
        float z = at.z();
        //vetor do olho(eye) ao centro(center)
          Vec4 Vec = at-(eye);
          //vetor no sentido positivo da direcao x
          Vec4 Xpos = Vec^(up);

          at = at-( Xpos*( (last_x - win_x)/100.0 ) );

          //Vec normalizado
          Vec4 N = at-(eye);
          N.normalize();
          at = eye+(N);
          if(axis_y){
              at.x2 = y;
          }
          if(axis_x){
              at.x1 = x;
          }
          if(axis_z){
              at.x3 = z;
          }
    }

}

void Camera::rotatez(float win_x, float last_x)
{
    if(type==CAMERA_FAR){
        float y = at.y();
        float x = at.x();
        float z = at.z();
        //vetor do olho(eye) ao centro(center)
        Vec4 Vec = at-(eye);
        //vetor no sentido positivo da direcao x
        Vec4 Xpos = Vec^(up);
        Xpos.normalize();

        //modificando o vetor up
        up = up-( Xpos*( (last_x - win_x)/300.0 ) );
        up.normalize();
        if(axis_y){
            at.x2 = y;
        }
        if(axis_x){
            at.x1 = x;
        }
        if(axis_z){
            at.x3 = z;
        }
    }else{

                float y = at.y();
                float x = at.x();
                float z = at.z();
                //vetor do olho(eye) ao centro(center)
                Vec4 Vec = at -(eye);

                //vetor no sentido positivo da direcao x
                Vec4 Xpos = Vec^(up);
                at = at - ( Xpos*( (last_x - win_x)/100.0 ) );
                if(axis_y){
                    at.x2 = y;
                }
                if(axis_x){
                    at.x1 = x;
                }
                if(axis_z){
                    at.x3 = z;
                }


                //Vec normalizado
                Vec4 N = at -(eye);
                N.normalize();
                at = eye + (N);

                if(axis_y){
                    at.x2 = y;
                }
                if(axis_x){
                    at.x1 = x;
                }
                if(axis_z){
                    at.x3 = z;
                }





    }
}

Vec4 Camera::getPickedPoint(float x, float y)
{
    //calculando a base da camera
    //vetor do centro(center) ao olho(eye) - Zpos
    Vec4 Vce = eye-(at);
    Vce.normalize();
    //vetor no sentido positivo da direcao x
    Vec4 Xpos = up^(Vce);
    Xpos.normalize();

    //mudanca da base da camera para a base do mundo (canonica)
    float dx = Xpos.x1 * x + up.x1 * y + Vce.x1 * -1;
    float dy = Xpos.x2 * x + up.x2 * y + Vce.x2 * -1;
    float dz = Xpos.x3 * x + up.x3 * y + Vce.x3 * -1;

    //translacao em relacao a posicao da camera
    dx += eye.x1;
    dy += eye.x2;
    dz += eye.x3;

    return Vec4(dx,dy,dz);
}

void Camera::adapteVetorAtDist2Game()
{
    Vec4 Vec = at - eye;
    //normalizando o Vec
    Vec.normalize();
    //adaptando o vetor c
    at = eye + Vec;
}

void Camera::adapteVetorAtGame2Dist(float r)
{
    //vetor do olho(eye) ao centro(center)
    Vec4 Vec = at - eye;
    //adaptando o vetor c
    at = eye + Vec*r;
}

void Camera::lockAxisX(bool b)
{
    axis_x = b;
}

void Camera::lockAxisY(bool b)
{
    axis_y = b;
}

void Camera::lockAxisZ(bool b)
{
    axis_z = b;
}


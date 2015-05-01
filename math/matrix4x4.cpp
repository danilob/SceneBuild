#include "matrix4x4.h"
#include <stdio.h>

Matrix4x4::Matrix4x4()
{
    for(int i=0;i<16;i++){
        if(i%5==0){
            matrix[i]=1;
        }else{
            matrix[i]=0;
        }
    }
    for(int i=0;i<16;i++){
        if(i%5==0){
            translate_m[i]=1;
        }else{
            translate_m[i]=0;
        }
    }
    for(int i=0;i<16;i++){
        if(i%5==0){
            rotate_m[i]=1;
        }else{
            rotate_m[i]=0;
        }
    }
    for(int i=0;i<16;i++){
        if(i%5==0){
            scale_m[i]=1;
        }else{
            scale_m[i]=0;
        }
    }
    rotx = roty = rotz = 0;
}

Matrix4x4::Matrix4x4(float vet[16])
{
    for(int i=0;i<16;i++) matrix[i] = vet[i];
}

void Matrix4x4::setMatrix4x4(float vet[16])
{
    for(int i=0;i<16;i++) matrix[i] = vet[i];
}


//void Matrix4x4::set(Matrix4x4 *matrix)
//{
//    memcpy(this->matrix, matrix->matrix, 16*sizeof(float));
//}

float * Matrix4x4::getMatrix()
{
    return matrix;
}

void Matrix4x4::showMatrix4x4()
{
    for(int i=0;i<16;i++){
        if(i%4==0)
            printf("\n");
        printf(" %.3f ",matrix[i]);
    }
}

void Matrix4x4::get(float output[]) const
{
    memcpy(output, matrix, 16*sizeof(float));
}

float Matrix4x4::get(int index) const
{
    if(index > 0 and index < 16){
        return matrix[index];
    }else{
        return 0;
    }
}

void Matrix4x4::translate(float x, float y, float z)
{
    matrix[12] += x;
    matrix[13] += y;
    matrix[14] += z;

    translate_m[12] += x;
    translate_m[13] += y;
    translate_m[14] += z;
}

void Matrix4x4::translate(Vec4 vector)
{
    matrix[12] += vector.x1;
    matrix[13] += vector.x2;
    matrix[14] += vector.x3;

    translate_m[12] += vector.x1;
    translate_m[13] += vector.x2;
    translate_m[14] += vector.x3;
}




Matrix4x4 Matrix4x4::multMatrix(Matrix4x4 a, Matrix4x4 b)
{
    Matrix4x4 m;
    m.matrix[0] = a.matrix[0] * b.matrix[0] + a.matrix[1] * b.matrix[4] + a.matrix[2] * b.matrix[8] + a.matrix[3] * b.matrix[12];
    m.matrix[1] = a.matrix[0] * b.matrix[1] + a.matrix[1] * b.matrix[5] + a.matrix[2] * b.matrix[9] + a.matrix[3] * b.matrix[13];
    m.matrix[2] = a.matrix[0] * b.matrix[2] + a.matrix[1] * b.matrix[6] + a.matrix[2] * b.matrix[10] + a.matrix[3] * b.matrix[14];
    m.matrix[3] = a.matrix[0] * b.matrix[3] + a.matrix[1] * b.matrix[7] + a.matrix[2] * b.matrix[11] + a.matrix[3] * b.matrix[15];

    m.matrix[4] = a.matrix[4] * b.matrix[0] + a.matrix[5] * b.matrix[4] + a.matrix[6] * b.matrix[8] + a.matrix[7] * b.matrix[12];
    m.matrix[5] = a.matrix[4] * b.matrix[1] + a.matrix[5] * b.matrix[5] + a.matrix[6] * b.matrix[9] + a.matrix[7] * b.matrix[13];
    m.matrix[6] = a.matrix[4] * b.matrix[2] + a.matrix[5] * b.matrix[6] + a.matrix[6] * b.matrix[10] + a.matrix[7] * b.matrix[14];
    m.matrix[7] = a.matrix[4] * b.matrix[3] + a.matrix[5] * b.matrix[7] + a.matrix[6] * b.matrix[11] + a.matrix[7] * b.matrix[15];

    m.matrix[8] = a.matrix[8] * b.matrix[0] + a.matrix[9] * b.matrix[4] + a.matrix[10] * b.matrix[8] + a.matrix[11] * b.matrix[12];
    m.matrix[9] = a.matrix[8] * b.matrix[1] + a.matrix[9] * b.matrix[5] + a.matrix[10] * b.matrix[9] + a.matrix[11] * b.matrix[13];
    m.matrix[10] = a.matrix[8] * b.matrix[2] + a.matrix[9] * b.matrix[6] + a.matrix[10] * b.matrix[10] + a.matrix[11] * b.matrix[14];
    m.matrix[11] = a.matrix[8] * b.matrix[3] + a.matrix[9] * b.matrix[7] + a.matrix[10] * b.matrix[11] + a.matrix[11] * b.matrix[15];

    m.matrix[12] = a.matrix[12] * b.matrix[0] + a.matrix[13] * b.matrix[4] + a.matrix[14] * b.matrix[8] + a.matrix[15] * b.matrix[12];
    m.matrix[13] = a.matrix[12] * b.matrix[1] + a.matrix[13] * b.matrix[5] + a.matrix[14] * b.matrix[9] + a.matrix[15] * b.matrix[13];
    m.matrix[14] = a.matrix[12] * b.matrix[2] + a.matrix[13] * b.matrix[6] + a.matrix[14] * b.matrix[10] + a.matrix[15] * b.matrix[14];
    m.matrix[15] = a.matrix[12] * b.matrix[3] + a.matrix[13] * b.matrix[7] + a.matrix[14] * b.matrix[11] + a.matrix[15] * b.matrix[15];

    return m;

}

Matrix4x4 Matrix4x4::transpose()
{
    Matrix4x4 m;
    m.setMatrix4x4(this->matrix);
    for(int i=0;i<4;i++){
        for(int j=i+1;j<4;j++){
            int i1 = i+4*j, i2 = j+4*i;
            float aux = m.matrix[i1];
            m.matrix[i1] = m.matrix[i2];
            m.matrix[i2] = aux;
        }
    }
    return m;
}

Vec4 Matrix4x4::vector(Vec4 p)
{
   // p.setVec4(0,0,0,1);
    Vec4 v;
    p.x4 = 1;
    //v = p;
    v.x1 = matrix[0]*p.x1 + matrix[1]*p.x2 + matrix[2]*p.x3 + matrix[3]*p.x4;
    v.x2 = matrix[4]*p.x1 + matrix[5]*p.x2 + matrix[6]*p.x3 + matrix[7]*p.x4;
    v.x3 = matrix[8]*p.x1 + matrix[9]*p.x2 + matrix[10]*p.x3 + matrix[11]*p.x4;
    v.x4 = matrix[12]*p.x1 + matrix[13]*p.x2 + matrix[14]*p.x3 + matrix[15]*p.x4;
    return v;
}

void Matrix4x4::scale(float x, float y, float z)
{
    matrix[0]  *= x;
    matrix[5]  *= y;
    matrix[10] *= z;

    scale_m[0]  *= x;
    scale_m[5]  *= y;
    scale_m[10] *= z;

}


void Matrix4x4::scale(Vec4 vector)
{
    matrix[0]  *= vector.x1;
    matrix[5]  *= vector.x2;
    matrix[10] *= vector.x3;

    scale_m[0]  *= vector.x1;
    scale_m[5]  *= vector.x2;
    scale_m[10] *= vector.x3;

}

void Matrix4x4::setIdentity()
{
    for(int i=0;i<16;i++){
        if(i%5==0){
            matrix[i]=1;
        }else{
            matrix[i]=0;
        }
    }
    for(int i=0;i<16;i++){
        if(i%5==0){
            translate_m[i]=1;
        }else{
            translate_m[i]=0;
        }
    }
    for(int i=0;i<16;i++){
        if(i%5==0){
            rotate_m[i]=1;
        }else{
            rotate_m[i]=0;
        }
    }
    for(int i=0;i<16;i++){
        if(i%5==0){
            scale_m[i]=1;
        }else{
            scale_m[i]=0;
        }
    }
    rotx = 0;roty = 0;rotz = 0;

}


void Matrix4x4::set(int pos,float value)
{
    matrix[pos] = value;
}

void Matrix4x4::setRotationY(float angle)
{
    roty += angle;
    float angle_pi = angle*M_PI/180.0;
    Matrix4x4 m,m2,aux,aux2;
    m2.setIdentity();

    aux.setMatrix4x4(this->matrix);
    aux2.setMatrix4x4(rotate_m);
    m.matrix[0] = cos(angle_pi);
    m.matrix[8] = sin(angle_pi);
    m.matrix[2] = -sin(angle_pi);
    m.matrix[10] = cos(angle_pi);

    m2.matrix[0] = cos(angle_pi);
    m2.matrix[8] = sin(angle_pi);
    m2.matrix[2] = -sin(angle_pi);
    m2.matrix[10] = cos(angle_pi);

    m = m.multMatrix(aux,m);
    m2 = m2.multMatrix(aux2,m2);
    this->setMatrix4x4Rot(m2.matrix);
    this->setMatrix4x4(m.matrix);
}

void Matrix4x4::setRotationX(float angle)
{
    rotx += angle;
    float angle_pi = angle*M_PI/180.0;
    Matrix4x4 m,m2,aux,aux2;
    m2.setIdentity();

    aux.setMatrix4x4(this->matrix);
    aux2.setMatrix4x4(rotate_m);

    m.matrix[5] = cos(angle_pi);
    m.matrix[9] = -sin(angle_pi);
    m.matrix[6] = sin(angle_pi);
    m.matrix[10] = cos(angle_pi);

    m2.matrix[5] = cos(angle_pi);
    m2.matrix[9] = -sin(angle_pi);
    m2.matrix[6] = sin(angle_pi);
    m2.matrix[10] = cos(angle_pi);

    m = m.multMatrix(aux,m);
    m2 = m2.multMatrix(aux2,m2);
    this->setMatrix4x4Rot(m2.matrix);
    this->setMatrix4x4(m.matrix);
}

void Matrix4x4::setRotationZ(float angle)
{
    rotz += angle;
    float angle_pi = angle*M_PI/180.0;
    Matrix4x4 m,m2,aux,aux2;
    m2.setIdentity();
    aux.setMatrix4x4(this->matrix);
    aux2.setMatrix4x4(rotate_m);

    m.matrix[0] = cos(angle_pi);
    m.matrix[4] = -sin(angle_pi);
    m.matrix[1] = sin(angle_pi);
    m.matrix[5] = cos(angle_pi);

    m2.matrix[0] = cos(angle_pi);
    m2.matrix[4] = -sin(angle_pi);
    m2.matrix[1] = sin(angle_pi);
    m2.matrix[5] = cos(angle_pi);

    m = m.multMatrix(aux,m);
    m2 = m2.multMatrix(aux2,m2);

    this->setMatrix4x4Rot(m2.matrix);
    this->setMatrix4x4(m.matrix);
}

void Matrix4x4::setAxisX(Vec4 ax)
{
    matrix[0] = ax.x1;
    matrix[4] = ax.x2;
    matrix[8] = ax.x3;

}

void Matrix4x4::setAxisY(Vec4 ay)
{
    matrix[1] = ay.x1;
    matrix[5] = ay.x2;
    matrix[9] = ay.x3;

}

void Matrix4x4::setAxisZ(Vec4 az)
{
    matrix[2]  = az.x1;
    matrix[6]  = az.x2;
    matrix[10] = az.x3;

}

void Matrix4x4::setTranslate(Vec4 tl)
{
    matrix[12]  = tl.x1;
    matrix[13]  = tl.x2;
    matrix[14]  = tl.x3;
    matrix[15]  = 1.0;

    translate_m[12]  = tl.x1;
    translate_m[13]  = tl.x2;
    translate_m[14]  = tl.x3;


}

Vec4 Matrix4x4::transform_origin_ray(Matrix4x4 t,Vec4 p)
{
    Matrix4x4 inv_trans,inv_scale,inv_rot;
    inv_trans.setMatrix4x4(t.translate_m);
    inv_scale.setMatrix4x4(t.scale_m);
    inv_rot.setMatrix4x4(t.rotate_m);
    //inv_scale.showMatrix4x4();

    inv_trans.matrix[12] = -inv_trans.matrix[12];
    inv_trans.matrix[13] = -inv_trans.matrix[13];
    inv_trans.matrix[14] = -inv_trans.matrix[14];
    //inv_trans.showMatrix4x4();

    inv_scale.matrix[0] = 1.0/inv_scale.matrix[0];
    inv_scale.matrix[5] = 1.0/inv_scale.matrix[5];
    inv_scale.matrix[10] = 1.0/inv_scale.matrix[10];
    //inv_trans.showMatrix4x4();

    inv_rot = inv_rot.transpose();
    //inv_rot.showMatrix4x4();
    Matrix4x4 result;
    result = result.multMatrix(result.multMatrix(inv_scale,inv_rot),inv_trans);
    Vec4 out = inv_trans.transpose().vector(p);
    out = inv_rot.transpose().vector(out);
    out = inv_scale.transpose().vector(out);
    return out;
}

Vec4 Matrix4x4::transform_direction_ray(Matrix4x4 t,Vec4 p)
{
    Matrix4x4 inv_scale,inv_rot;

    inv_scale.setMatrix4x4(t.scale_m);
    inv_rot.setMatrix4x4(t.rotate_m);
//    inv_scale.showMatrix4x4();

    inv_scale.matrix[0] = 1.0/inv_scale.matrix[0];
    inv_scale.matrix[5] = 1.0/inv_scale.matrix[5];
    inv_scale.matrix[10] = 1.0/inv_scale.matrix[10];

    inv_rot = inv_rot.transpose();

    Matrix4x4 result;
    result = result.multMatrix(inv_scale,inv_rot);
    Vec4 out = inv_rot.transpose().vector(p);

    out = inv_scale.transpose().vector(out);
    return out;
}

Vec4 Matrix4x4::transform_position_ray(Matrix4x4 t,Vec4 p)
{
    Matrix4x4 trans,scale,rot;
    trans.setMatrix4x4(t.translate_m);
    scale.setMatrix4x4(t.scale_m);
    rot.setMatrix4x4(t.rotate_m);
    //inv_scale.showMatrix4x4();

//    inv_trans.matrix[12] = -inv_trans.matrix[12];
//    inv_trans.matrix[13] = -inv_trans.matrix[13];
//    inv_trans.matrix[14] = -inv_trans.matrix[14];

//    inv_scale.matrix[0] = 1.0/inv_scale.matrix[0];
//    inv_scale.matrix[5] = 1.0/inv_scale.matrix[5];
//    inv_scale.matrix[10] = 1.0/inv_scale.matrix[10];

//    inv_rot = inv_rot.transpose();
    Matrix4x4 result;
    result = result.multMatrix(result.multMatrix(trans,rot),scale);
    Vec4 out = scale.transpose().vector(p);
    out = rot.transpose().vector(out);
    out = scale.transpose().vector(out);
    return this->transpose().vector(p);
}

Vec4 Matrix4x4::transform_normal_ray(Matrix4x4 t,Vec4 p)
{
    Matrix4x4 scale,rot;

    scale.setMatrix4x4(t.scale_m);
    rot.setMatrix4x4(t.rotate_m);
    scale.matrix[0] = 1.0/scale.matrix[0];
    scale.matrix[5] = 1.0/scale.matrix[5];
    scale.matrix[10] = 1.0/scale.matrix[10];

    Matrix4x4 result;
    result = result.multMatrix(rot,scale);
    Vec4 out = scale.transpose().vector(p);
    out = rot.transpose().vector(out);
//    out = inv_scale.transpose().vector(out);
    return out;
}

Vec4 Matrix4x4::getRotationSeted()
{
    return Vec4(rotx,roty,rotz);
}

Vec4 Matrix4x4::getScaleSeted()
{
    return Vec4(scale_m[0],scale_m[5],scale_m[10]);
}

Vec4 Matrix4x4::getTranslateSeted()
{
    return Vec4(translate_m[12],translate_m[13],translate_m[14]);
}

void Matrix4x4::setMatrix4x4Rot(float vet[])
{
    for(int i=0;i<16;i++) rotate_m[i] = vet[i];
}

void Matrix4x4::addscale(float x, float y, float z)
{
    matrix[0]  += x;
    matrix[5]  += y;
    matrix[10] += z;

    scale_m[0]  += x;
    scale_m[5]  += y;
    scale_m[10] += z;

}

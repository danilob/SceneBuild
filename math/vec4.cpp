#include "vec4.h"

Vec4::Vec4(float x1,float x2,float x3,float x4)
{
    this->x1 = x1;
    this->x2 = x2;
    this->x3 = x3;
    this->x4 = x4;
}

void Vec4::setVec4(Vec4 p){
    this->x1 = p.x1;
    this->x2 = p.x2;
    this->x3 = p.x3;
}

bool Vec4::operator == (Vec4 v){
    if ((this->x1==v.x1)&&(this->x2==v.x2)&&(this->x3==v.x3)){
        return true;
    }else{
        return false;
    }
}

bool Vec4::operator != (Vec4 v){
    if ((this->x1==v.x1)&&(this->x2==v.x2)&&(this->x3==v.x3)){
        return false;
    }else{
        return true;
    }
}

Vec4 Vec4::operator + (Vec4 v){
    Vec4 r;
    r.x1 = this->x1+v.x1;
    r.x2 = this->x2+v.x2;
    r.x3 = this->x3+v.x3;
    return r;
}

void Vec4::operator += (Vec4 v){

    this->x1 = this->x1+v.x1;
    this->x2 = this->x2+v.x2;
    this->x3 = this->x3+v.x3;

}

Vec4 Vec4::operator - (Vec4 v){
    Vec4 r;
    r.x1 = this->x1-v.x1;
    r.x2 = this->x2-v.x2;
    r.x3 = this->x3-v.x3;
    return r;
}

Vec4 Vec4::operator / (float k){
    Vec4 r;
    r.x1 = this->x1/k;
    r.x2 = this->x2/k;
    r.x3 = this->x3/k;
    return r;
}

void Vec4::operator /= (float k){

    this->x1 = this->x1/k;
    this->x2 = this->x2/k;
    this->x3 = this->x3/k;

}

Vec4 Vec4::operator * (float k){
    Vec4 r;
    r.x1 = this->x1*k;
    r.x2 = this->x2*k;
    r.x3 = this->x3*k;
    return r;
}


float Vec4::operator * (Vec4 v){
    return this->x1*v.x1+this->x2*v.x2+this->x3*v.x3;
}

void Vec4::normalize()
{
    float mod = this->module();
    this->x1 = this->x()/mod;
    this->x2 = this->y()/mod;
    this->x3 = this->z()/mod;
}

Vec4 Vec4::mult(Vec4 v)
{
    return Vec4(this->x1*v.x1,this->x2*v.x2,this->x3*v.x3);
}

float Vec4::dot(Vec4 v)
{
    return this->x1*v.x1+this->x2*v.x2+this->x3*v.x3;
}


void Vec4::setVec4(float x1,float x2, float x3, float x4){
    this->x1 = x1;
    this->x2 = x2;
    this->x3 = x3;
    this->x4 = x4;
}

float Vec4::module(){
    return sqrt(pow(x1,2)+pow(x2,2)+pow(x3,2));
}

float Vec4::distSquared(Vec4 p1, Vec4 p2)
{
    double distance = pow((p1.x()-p2.x()),2)+pow((p1.y()-p2.y()),2)+pow((p1.z()-p2.z()),2);
//    if (dist(p1,p2)<1)
//        distance = pow(dist(p1,p2),0.5);
    return distance;
}

float Vec4::dist(Vec4 p1, Vec4 p2)
{
    return sqrt(pow((p1.x()-p2.x()),2)+pow((p1.y()-p2.y()),2)+pow((p1.z()-p2.z()),2));
}

float Vec4::distPlane(Vec4 p, Vec4 plane,Vec4 ponto, float s)
{
    Vec4 n = plane.unitary();
    if (s<0) n = n*(-1);
    return (p-ponto)*n;
}

Vec4 Vec4::unitary(){
    return *this/this->module();
}

void Vec4::showVec4(){
    printf("(%.4f;%.4f;%.4f;%.4f)\n",x1,x2,x3,x4);
}



Vec4 Vec4::crossProduct(Vec4 a,Vec4 b){
    Vec4 r;
    r.x1 = a.x2*b.x3 - b.x2*a.x3;
    r.x2 = a.x3*b.x1 - b.x3*a.x1;
    r.x3 = a.x1*b.x2 - a.x2*b.x1;
    return r;
}

Vec4 Vec4::operator ^(Vec4 b){
    Vec4 r;
    r.x1 = this->x2*b.x3 - b.x2*this->x3;
    r.x2 = this->x3*b.x1 - b.x3*this->x1;
    r.x3 = this->x1*b.x2 - this->x2*b.x1;
    return r;
}


float Vec4::x()
{
    return x1;
}

float Vec4::y()
{
    return x2;
}

float Vec4::z()
{
    return x3;
}

float Vec4::w()
{
    return x4;
}

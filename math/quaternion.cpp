#include "quaternion.h"
//#include "matrix4f.h"
//functions publics
const float epsilon = 0.0001;

Quaternion::Quaternion()
{
    this->s = 1;
    this->x = 0;
    this->y = 0;
    this->z = 0;

}


Quaternion::Quaternion(float r, float x, float y, float z)
{
    this->s = r;
    this->x = x;
    this->y = y;
    this->z = z;
}

Quaternion::Quaternion(float thetaX, float thetaY, float thetaZ)
{
    thetaX = (thetaX / 2.0) * (M_PI / 180.0);
    thetaY = (thetaY / 2.0) * (M_PI / 180.0);
    thetaZ = (thetaZ / 2.0) * (M_PI / 180.0);

    Quaternion qThetaX(cos(thetaX), sin(thetaX), 0.0, 0.0);
    Quaternion qThetaY(cos(thetaY), 0.0, sin(thetaY), 0.0);
    Quaternion qThetaZ(cos(thetaZ), 0.0, 0.0, sin(thetaZ));

    Quaternion q = qThetaZ* qThetaY;
    q = q*qThetaX;
    Quaternion norm = q.normalize();

    *this = norm;

}

Quaternion::Quaternion(float r, Vec4 v)
{
    this->s = r;
    this->x = v.x1;
    this->y = v.x2;
    this->z = v.x3;
}

//sets

void Quaternion::setScalar(float x)
{
    this->s = x;
}

void Quaternion::setPosX(float x)
{
    this->x = x;
}

void Quaternion::setPosY(float x)
{
    this->y = x;
}

void Quaternion::setPosZ(float x)
{
    this->z = x;
}

void Quaternion::setQuaternion(float r, float x, float y, float z)
{
    this->s = r;
    this->x = x;
    this->y = y;
    this->z = z;
}

void Quaternion::setQuaternion(float r, Vec4 v)
{
    this->s = r;
    this->x = v.x1;
    this->y = v.x2;
    this->z = v.x3;
}

//end sets
//gets

float Quaternion::getScalar()
{
    return this->s;
}

float Quaternion::getPosX()
{
    return this->x;
}

float Quaternion::getPosY()
{
    return this->y;
}

float Quaternion::getPosZ()
{
    return this->z;
}

Vec4 Quaternion::getVector()
{
    Vec4 v;
    v.setVec4(this->getPosX(),this->getPosY(),this->getPosZ());
    return v;
}

//end gets
//functions

Quaternion Quaternion::conjugate()
{
    Quaternion res(this->getScalar(),this->getVector()*(-1));
    return res;
}

float Quaternion::normal()
{
    float res;
    res = sqrt(this->getScalar()*this->getScalar()+
               this->getPosX()*this->getPosX()+
               this->getPosY()*this->getPosY()+
               this->getPosZ()*this->getPosZ());
    return res;
}

void Quaternion::setQuaternion(Vec4 AxisAngle)
{
    float radius = AxisAngle.x4*M_PI/360.0;
    float scale_ = cos(radius);
    Vec4 axis  = AxisAngle*sin(radius);
    setQuaternion(scale_,axis.x1,axis.x2,axis.x3);
}

void Quaternion::toAxisAngle(Vec4 *axis, float *angle)
{
    float scale = this->getVector().module();
    axis->x1 = getPosX()/scale;
    axis->x2 = getPosY()/scale;
    axis->x3 = getPosZ()/scale;
    *angle = acos(getScalar()) * 2.0;
}

//operadores

//Quaternion Quaternion::operator +(Quaternion q)
//{
//    Quaternion res;
//    res.setScalar(this->getScalar()+q.getScalar());
//    res.setPosX(this->getPosX()+q.getPosX());
//    res.setPosY(this->getPosY()+q.getPosY());
//    res.setPosZ(this->getPosZ()+q.getPosZ());
//    return res;
//}

bool operator==(Quaternion p, Quaternion q)
{
    if(p.getScalar()==q.getScalar() && p.getPosX()==q.getPosX() && p.getPosY()==q.getPosX() && p.getPosZ()==q.getPosZ()) return true;
    return false;
}


Quaternion operator+(Quaternion p, Quaternion q)
{
    return Quaternion(p.getScalar() + q.getScalar(), p.getPosX() + q.getPosX(), p.getPosY() + q.getPosY(), p.getPosZ() + q.getPosZ());
}

Quaternion operator-(Quaternion p, Quaternion q)
{
    return Quaternion(p.getScalar() - q.getScalar(), p.getPosX() - q.getPosX(), p.getPosY() - q.getPosY(), p.getPosZ() - q.getPosZ());
}

//Quaternion Quaternion::operator -(Quaternion q)
//{
//    Quaternion res;
//    res.setScalar(this->getScalar()-q.getScalar());
//    res.setPosX(this->getPosX()-q.getPosX());
//    res.setPosY(this->getPosY()-q.getPosY());
//    res.setPosZ(this->getPosZ()-q.getPosZ());
//    return res;
//}

Quaternion Quaternion::operator *(float k)
{
    Quaternion res;
    res.setScalar(this->getScalar()*k);
    res.setPosX(this->getPosX()*k);
    res.setPosY(this->getPosY()*k);
    res.setPosZ(this->getPosZ()*k);
    return res;
}

Quaternion Quaternion::operator /(float k)
{
    Quaternion res;
    res.setScalar(this->getScalar()/k);
    res.setPosX(this->getPosX()/k);
    res.setPosY(this->getPosY()/k);
    res.setPosZ(this->getPosZ()/k);
    return res;
}

//Quaternion Quaternion::operator *(Quaternion q)
//{
//    //q1q2 = (s1 , v1)(s2 , v2) = (s1*s2 − v1⋅v 2 , s1v2 + s2v1 + v1 × v2 )
//    Quaternion res;
//    Vec4 v;
//    res.setScalar(this->getScalar()*q.getScalar() - this->getVector()*this->getVector());
//    v.setVec4(q.getVector()*this->getScalar()+this->getVector()*q.getScalar()+Vec4::crossProduct(this->getVector(),q.getVector()));
//    res.setPosX(v.x1);
//    res.setPosY(v.x2);
//    res.setPosZ(v.x3);
//    return res;
//}

Quaternion operator*(Quaternion q1, Quaternion q2) {

    Quaternion qr;
    qr.setScalar(q1.getScalar()*q2.getScalar() - q1.getPosX()*q2.getPosX() - q1.getPosY()*q2.getPosY() - q1.getPosZ()*q2.getPosZ());
    qr.setPosX(q1.getScalar()*q2.getPosX() + q2.getScalar()*q1.getPosX() + q1.getPosY()*q2.getPosZ() - q1.getPosZ()*q2.getPosY());
    qr.setPosY(q1.getScalar()*q2.getPosY() + q2.getScalar()*q1.getPosY() + q1.getPosZ()*q2.getPosX() - q1.getPosX()*q2.getPosZ());
    qr.setPosZ(q1.getScalar()*q2.getPosZ() + q2.getScalar()*q1.getPosZ() + q1.getPosX()*q2.getPosY() - q1.getPosY()*q2.getPosX());


    return qr;
//    return Quaternion(p.getScalar()*q.getScalar() - p.getPosX()*q.getPosX() - p.getPosY()*q.getPosY() - p.getPosZ()*q.getPosZ(),
//                      p.getScalar()*q.getPosX() + p.getPosX()*q.getScalar() + p.getPosY()*q.getPosZ() - p.getPosZ()*q.getPosY(),
//                      p.getScalar()*q.getPosY() - p.getPosX()*q.getPosZ() + p.getPosY()*q.getScalar() + p.getPosZ()*q.getPosX(),
//                      p.getScalar()*q.getPosZ() + p.getPosX()*q.getPosY() - p.getPosY()*q.getPosX() + p.getPosZ()*q.getScalar());
}

Quaternion operator/(Quaternion p, Quaternion q) {
    return p * q.inverse();
}


Quaternion Quaternion::normalize()
{
    float norm=1.0;
    Quaternion q = this->getQuaternion();
    if( (norm = q.normal()) < epsilon)
        return Quaternion(1,0,0,0);
    return q*(1.0/norm);
}

Quaternion Quaternion::getQuaternion()
{
    Quaternion res;
    res.setScalar(this->getScalar());
    res.setPosX(this->getPosX());
    res.setPosY(this->getPosY());
    res.setPosZ(this->getPosZ());
    return res;
}

void Quaternion::toEulerAngle(Vec4 *axis)
{
}

Quaternion Quaternion::inverse()
{
    return (this->conjugate() / this->normal());
}

float Quaternion::dot(Quaternion p, Quaternion q)
{

    return sqrt(p.getScalar()*q.getScalar() + p.getPosX()*q.getPosX() + p.getPosY()*q.getPosY() + p.getPosZ()*q.getPosZ());

}

Vec4 Quaternion::toAxis()
{
    float scale = this->getVector().module();
    Vec4 axis;
    axis.x1 = getPosX()/scale;
    axis.x2 = getPosY()/scale;
    axis.x3 = getPosZ()/scale;

    return axis;
}

float Quaternion::toAngle()
{
    float angle = acos(this->getScalar()) * 2.0;
    return angle;
}

//end operadores

void Quaternion::printQuaternion()
{
    printf("\nQuaternion (%.3f , %.3f, %.3f, %.3f)",this->getScalar(),this->getPosX(),this->getPosY(),this->getPosZ());
}





Matrix4x4 Quaternion::getMatrix()
{

        float x2 = this->getPosX() * this->getPosX();
        float y2 = this->getPosY() * this->getPosY();
        float z2 = this->getPosZ() * this->getPosZ();
        float xy = this->getPosX() * this->getPosY();
        float xz = this->getPosX() * this->getPosZ();
        float yz = this->getPosY() * this->getPosZ();
        float wx = this->getScalar() * this->getPosX();
        float wy = this->getScalar() * this->getPosY();
        float wz = this->getScalar() * this->getPosZ();

        // This calculation would be a lot more complicated for non-unit length quaternions
        // Note: The constructor of Matrix4 expects the Matrix in column-major format like expected by
        //   OpenGL
//        float rot[16] = {1.0f - 2.0f * (y2 + z2), 2.0f * (xy - wz), 2.0f * (xz + wy), 0.0f,
//                         2.0f * (xy + wz), 1.0f - 2.0f * (x2 + z2), 2.0f * (yz - wx), 0.0f,
//                         2.0f * (xz - wy), 2.0f * (yz + wx), 1.0f - 2.0f * (x2 + y2), 0.0f,
//                         0.0f, 0.0f, 0.0f, 1.0f};

        float rot[16] = {1.0f - 2.0f * (y2 + z2), 2.0f * (xy + wz) ,2.0f * (xz - wy) , 0.0f,
                         2.0f * (xy - wz), 1.0f - 2.0f * (x2 + z2), 2.0f * (yz + wx), 0.0f,
                         2.0f * (xz + wy),  2.0f * (yz - wx), 1.0f - 2.0f * (x2 + y2), 0.0f,
                         0.0f, 0.0f, 0.0f, 1.0f};


//        this->normalize();
//        float rot[16] = {getScalar(),-getPosX(),getPosZ(),-getPosY(),
//                         getPosX(),getScalar(),-getPosY(),-getPosZ(),
//                         -getPosZ(),getPosY(),getScalar(),-getPosX(),
//                         getPosY(),getPosZ(),getPosX(),getScalar()



//        };
        return Matrix4x4(rot);
}

Quaternion Quaternion::toRotation(Quaternion q)
{

    Quaternion p;
    p.setScalar((acos(q.getScalar())*180)/M_PI_2);
    p.setPosX(q.getPosX());
    p.setPosY(q.getPosY());
    p.setPosZ(q.getPosZ());
    return p;
}

Quaternion Quaternion::fromRotation(Quaternion q){
    Quaternion qr;
    float halftheta;
    float sinhalftheta;
    float axisnorm;
    float n = q.getPosX()*q.getPosX()+q.getPosY()*q.getPosY()+q.getPosZ()*q.getPosZ();
    if (axisnorm = sqrt(n) < epsilon)
    {
        qr.setQuaternion(1,0,0,0);
        return qr;
    }
    halftheta = (q.getScalar()*M_PI_2)/180;
    sinhalftheta = sin(halftheta);
    qr.setScalar(cos(halftheta));
    qr.setPosX(sinhalftheta * (q.getPosX()/axisnorm));
    qr.setPosY(sinhalftheta * (q.getPosY()/axisnorm));
    qr.setPosZ(sinhalftheta * (q.getPosZ()/axisnorm));
    return qr;


}

Vec4 Quaternion::getVecRotation(Quaternion q, Vec4 v)
{
    Quaternion res;
    Quaternion pos(0,v.x1,v.x2,v.x3);
    q.normalize();
    res = (q)*(pos*((q.conjugate())));
    Vec4 r(res.getPosX(),res.getPosY(),res.getPosZ());
    return r;

}

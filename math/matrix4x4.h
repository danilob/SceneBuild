#ifndef MATRIX4X4_H
#define MATRIX4X4_H
#include "math/vec4.h"

class Matrix4x4
{
public:
    float matrix[16];        //matriz de tranformação geral
    float scale_m[16];       //matriz de tranformação de escala
    float translate_m[16];   //matriz de tranformação de translação
    float rotate_m[16];      //matriz de tranformação de rotação
    float rotx;              //angulo de rotaçao no eixo x
    float roty;              //angulo de rotaçao no eixo y
    float rotz;              //angulo de rotaçao no eixo z
public:
    Matrix4x4();                                       //construtor default aplicando a matriz identidade a todas as matrizes
    Matrix4x4(float vet[16]);                          //construtor da matriz passando uma matriz
    void setMatrix4x4(float vet[16]);                  //seta uma matriz de transformação geral
    void setMatrix4x4Rot(float vet[16]);               //seta uma matriz de rotação 3x3
    float* getMatrix();                                //retorna um ponteiro para matriz de transformação geral
    void showMatrix4x4();                              //imprimi os valores da matriz
    void get(float output[]) const;                    //adiciona uma matriz a matriz de transformação
    Matrix4x4 multMatrix(Matrix4x4 a,Matrix4x4 b);     //multiplicação de matriz 4x4
    float get(int index) const;                        //retorna um valor de uma determinada posição
    void translate(float x, float y, float z);         //adiciona uma translação de acordo com os valores x,y,z
    void scale(float x,float y, float z);              //multiplica os parametros de escala de acordo com os valores x,y,z
    void addscale(float x,float y, float z);           //adiciona os parametros de escala de acordo com as posições vetor
    void scale(Vec4 vector);                           //multiplica os parametros de escala de acordo com as posições vetor
    void translate( Vec4 vector );                     //adiciona uma translação de acordo com as posições vetor
    void setIdentity();                                //seta todas as matrizes como matriz identidade
    Matrix4x4 transpose();                             //retorna a matriz transposta
    void set(int pos,float value);                     //seta em uma determina posição um determinado valor
    void setRotationX(float angle);                    //aplica a matriz de rotação no eixo x do angulo em graus
    void setRotationY(float angle);                    //aplica a matriz de rotação no eixo y do angulo em graus
    void setRotationZ(float angle);                    //aplica a matriz de rotação no eixo z do angulo em graus
    void setAxisX(Vec4 ax);                            //seta um vetor na linha relativa ao eixo de rotação x
    void setAxisY(Vec4 ay);                            //seta um vetor na linha relativa ao eixo de rotação y
    void setAxisZ(Vec4 az);                            //seta um vetor na linha relativa ao eixo de rotação z
    void setTranslate(Vec4 tl);                        //setar uma translação a matriz
    Vec4 getRotationSeted();                           //extrai o vetor com os angulos em graus
    Vec4 getScaleSeted();                              //extrai o vetor de escala aplicada
    Vec4 getTranslateSeted();                          //extrai o vetor de translação aplicada
    Vec4 vector(Vec4 p);                               //retorna o vetor aplicado a uma matriz de translação

    /* funções utilizadas para computar a interseção do raio com o objeto */

    Vec4 transform_origin_ray(Matrix4x4 t,Vec4 p);     //calcula a origem do raio de acordo com transformações inversas
    Vec4 transform_direction_ray(Matrix4x4 t,Vec4 p);  //calcula a direção do raio de acordo com transformações inversas
    Vec4 transform_position_ray(Matrix4x4 t,Vec4 p);   //calcula a posição de um vetor de acordo com transformações inversas
    Vec4 transform_normal_ray(Matrix4x4 t,Vec4 p);     //calcula a normal de um vetor de acordo com transformações inversas



};
#endif // MATRIX4X4_H

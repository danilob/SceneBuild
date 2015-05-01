#ifndef KDTREE_H
#define KDTREE_H
#include <vector>
#include <QList>
#include <string>
#include "math/vec4.h"
class Photon;

class KdTree
{
public:

    QList<Photon*> maxHeap;
    std::vector<Photon*> photons;

    KdTree();
    void addPhoton(Photon* p){photons.push_back(p);}
    void createHeap();
    void balance(std::vector<Photon*>* photons,int begin,int end, int index);
    int getLargestDimCube(std::vector<Photon*> *photons, int begin, int end); //retorna o eixo onde o cubo é maior
    void quickSort(int flag,int left,int right,std::vector<Photon *> *list);
    void locatePhotons(int p,Vec4 pos,int maxphotons,float radius);
    void swap(std::vector<Photon *> *list, unsigned int _i, unsigned int _j);
    int particion(int flag,int left,int right, std::vector<Photon*> *list);
    void clearHeap(); //heap que guarda os photons proximos
    void maxHeapify(QList<Photon*> photons,int i,Vec4 pos);
    void buildingMaxHeap(QList<Photon*> photons,Vec4 pos);
    void imprimeKdtree(std::string s = "",int i=0);
    void clearMemory();

};

#endif // KDTREE_H

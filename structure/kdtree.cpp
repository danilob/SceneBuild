#include "kdtree.h"
#include "photon.h"
#include <iostream>

#include <algorithm>
#include <cmath>
bool flag;


KdTree::KdTree()
{
}

void KdTree::createHeap()
{
    std::vector<Photon*> list(photons);
    balance(&list, 0, photons.size(), 0);
}

void KdTree::balance(std::vector<Photon*> *list, int begin, int end, int index)
{

    if(end <= begin) return;

    unsigned int axis = getLargestDimCube(list, begin, end);

    quickSort(axis,begin, end - 1,list);

    int median = floor((begin + end)/2.0);

    photons[index] = (*list)[median];
    photons[index]->flag = axis;


    balance(list, begin, median, (2*index) + 1);
    balance(list, median + 1, end, (2*index) + 2);

}




int KdTree::getLargestDimCube(std::vector<Photon*>* photons,int begin,int end)
{
    Vec4 min = (*photons)[begin]->getPosition()
        ,max = (*photons)[begin]->getPosition();
    for(unsigned int i=begin+1;i<end;i++){
        Vec4 p = (*photons)[i]->getPosition();
        if (max.x()<p.x()) max.x1 = p.x();
        if (max.y()<p.y()) max.x2 = p.y();
        if (max.z()<p.z()) max.x3 = p.z();

        if (min.x()>p.x()) min.x1 = p.x();
        if (min.y()>p.y()) min.x2 = p.y();
        if (min.z()>p.z()) min.x3 = p.z();
    }
    double z = (max - Vec4(max.x(),max.y(),min.z())).module();
    double y = (min - Vec4(min.x(),max.y(),min.z())).module();
    double x = (min - Vec4(max.x(),min.y(),min.z())).module();

    if(x>y)
        if(x>z)
            return 0;
        else
            return 2;
    else if(y>x)
        if (y>z)
            return 1;
        else
            return 2;

}



void KdTree::swap(std::vector<Photon *> *list, unsigned int i, unsigned int j)
{
    Photon *aux = (*list)[j];
    (*list)[j] = (*list)[i];
    (*list)[i] = aux;
}


int KdTree::particion(int flag,int left,int right,std::vector<Photon *>* list){

    Photon *x = (*list)[right];
        int i = left - 1;
        for(int j = left; j < right; j++)
        {
            if(flag==0)
                if((*list)[j]->position.x() < x->position.x())
                {
                    i++;
                    swap(list, i, j);
                }
            if(flag==1)
                if((*list)[j]->position.y() < x->position.y())
                {
                    i++;
                    swap(list, i, j);
                }
            if(flag==2)
                if((*list)[j]->position.z() < x->position.z())
                {
                    i++;
                    swap(list, i, j);
                }
        }
        swap(list, i + 1, right);

        return i+1;

}



void KdTree::quickSort(int flag,int left, int right,std::vector<Photon *>* list) { //modifica a estrutura do Points
  if (left < right){
          int q = particion(flag,left,right,list);
          quickSort(flag, left, q - 1,list);
          quickSort(flag, q + 1, right,list);
  }

}



void KdTree::clearHeap()
{
    maxHeap.clear();
    flag = false;

}



void KdTree::maxHeapify(QList<Photon *> photons, int i,Vec4 pos)
{
    Vec4 root = this->maxHeap[i-1]->position;
    Vec4 left=root,right=root;

    int largest = i;
    int size = this->maxHeap.size();
    if(2*i<=size)
        left = this->maxHeap[2*i-1]->position;
    if((2*i+1)<=size)
        right = this->maxHeap[2*i]->position;
    if(2*i<=size && Vec4::distSquared(left,pos)>Vec4::distSquared(root,pos))
        largest = 2*i;
    else
        largest = i;
    if((2*i+1)<=size && Vec4::distSquared(right,pos)>Vec4::distSquared(root,pos))
        largest = 2*i+1;
    if (largest!=i){
        //swap
        this->maxHeap.move(i-1,largest-1);
        maxHeapify(this->maxHeap,largest,pos);
    }

}

void KdTree::buildingMaxHeap(QList<Photon *> photons,Vec4 pos)
{
    int len = this->maxHeap.size();
    for (int i=len/2;i>0;i--){
        maxHeapify(this->maxHeap,i,pos);
    }
}


void KdTree::imprimeKdtree(std::string s, int i)
{
    std::cout << s;
    printf("Node (%d): <%3.3f>,<%3.3f>,<%3.3f> (flag-%d)\n",i,photons[i]->position.x(),photons[i]->position.y(),photons[i]->position.z(),photons[i]->getFlag());
    if (2*i+1<photons.size())
        imprimeKdtree(s+"   ",2*i+1);
    if(2*i+2<photons.size())
        imprimeKdtree(s+"   ",2*i+2);
}

void KdTree::clearMemory()
{
    std::vector<Photon *>::iterator iter = photons.begin();
     for (iter = photons.begin(); iter != photons.end(); ++iter)
     {
         delete *iter;
     }
     photons.clear();

}

void KdTree::locatePhotons(int p,Vec4 pos,int maxphotons, float radius)
{

    if( (2*p+2) < photons.size()) { //examine child nodes
        //Compute distance to plane (just a subtract)
        double delta;
        if(photons[p]->getFlag()==0){
            delta = pos.x()-photons[p]->position.x();
        }else if(photons[p]->getFlag()==1){
            delta = pos.y()-photons[p]->position.y();
        }else if(photons[p]->getFlag()==2){
            delta = pos.z()-photons[p]->position.z();
        }

        double d2 = radius*radius;
        if (flag) d2 = Vec4::distSquared(maxHeap[0]->position,pos);

        if (delta>0.0) { //We are left of the plane - search left subtree first
            locatePhotons( (2*p+2),pos,maxphotons,radius);
            if ( delta*delta < d2 )
                    locatePhotons( (2*p+1),pos,maxphotons,radius ); //check right subtree
        } else { //We are right of the plane - search right subtree first
            locatePhotons( (2*p+1),pos,maxphotons,radius );
            if ( delta*delta < d2 )
                    locatePhotons( (2*p+2),pos,maxphotons,radius ); //check left subtree
        }
    }
    double delta2 = Vec4::distSquared(photons[p]->position,pos);
    double d2 = radius*radius;
    if (flag) d2 = Vec4::distSquared(maxHeap[0]->position,pos);
    int ind = (p+1)/2 - 1;
    if ((delta2 < d2) && (!flag) && maxHeap.size()>0)
        if(Vec4::distSquared(photons[((int)fmax(ind,0))]->position,pos) > radius*radius) flag = true;

    if((maxHeap.size()<maxphotons)){
        if(delta2 < d2){
            maxHeap.append(photons[p]);
            buildingMaxHeap(maxHeap,pos);
        }
    }else{
        if(delta2 < Vec4::distSquared(maxHeap[0]->position,pos)){
            maxHeap.pop_front();
            maxHeap.append(photons[p]);
            buildingMaxHeap(maxHeap,pos);
        }
    }

    //Compute true squared distance to photon
}


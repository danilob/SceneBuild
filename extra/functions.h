#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <string>
#include <interface/scene.h>

class Functions
{
public:
    Functions();
    static bool saveImage(int width,int height,const std::string &fileName);
    static bool saveScene(Scene* scene,QString fileName);
    static bool loadScene(Scene* scene,const std::string &fileName);
    static bool saveSceneXML(Scene* scene,QString fileName,bool flag=true);
    static bool loadSceneXML(Scene* scene,QString fileName);
};




#endif // FUNCTIONS_H

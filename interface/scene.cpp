#include "scene.h"
#include "math/ray.h"


Scene::Scene()
{
    objects.clear();
    lights.clear();
    AmbientLight *ambient = new AmbientLight();
    lights.push_back(ambient);
    background_color = Vec4(100/255.0,189/255.0,176/255.0,1.0);
    push_obj = true;
    focal = 0;
    radius = 0;
    enablephoton = false;
    sizePhotons = 0;
    sizePhotonsCaustic = 0;
    photonMap.kdtree->photons.clear();
    photonMap.caustic->photons.clear();
    //kdtree = new KdTree();
}

void Scene::pushObjects(Object *obj){
    objects.push_back(obj);
}

void Scene::pushObjects(int define,int material)
{
    objects.clear();
    //if(!push_obj) return;
    Matrix4x4 t;
    t.setIdentity();
    switch (define){
    case BLOCK_CUBE:{
        Cube *cube = new Cube();
        t.scale(3,3,3);
        cube->setTransform(t);
        cube->setName("Cubo");
        cube->setMaterial(material);
        objects.push_back(cube);
        break;
    }
    case BLOCK_PRISM:{
        t.scale(3,3,3);
        Prism *prism = new Prism();
        prism->setName("Prisma");
        prism->setTransform(t);
        prism->setMaterial(material);
        objects.push_back(prism);
        break;
    }
    case BLOCK_SPHERE:{
        Sphere *sphere = new Sphere();
        t.scale(10,10,10);
        sphere->setName("Esfera");
        sphere->setTransform(t);
        sphere->setMaterial(material);
        objects.push_back(sphere);
        break;
    }
    case BLOCK_HEMISPHERE:{
        HemiSphere *hemisphere = new HemiSphere();
        t.scale(3,3,3);
        hemisphere->setName("Semi-Esfera");
        hemisphere->setTransform(t);
        hemisphere->setMaterial(material);
        objects.push_back(hemisphere);
        break;
    }
    case BLOCK_PLANE:{
        Plane *plane = new Plane();
        plane->setName("Plano");
        plane->setMaterial(5);
        objects.push_back(plane);
        break;
    }

    case BLOCK_CYLINDER:{
        Cylinder *cylinder = new Cylinder();
        t.scale(3,3,3);
        cylinder->setName("Cilindro");
        cylinder->setTransform(t);
        cylinder->setMaterial(material);
        objects.push_back(cylinder);
        break;
    }
    case BLOCK_CONE:{
        Cone *cone = new Cone();
        t.scale(3,3,3);
        cone->setName("Cone");
        cone->setTransform(t);
        cone->setMaterial(material);
        objects.push_back(cone);
        break;
    }
    case PLANALTO:{


        Cube* cube_predio_direito = new Cube();
        cube_predio_direito->setName("Predio direito");
        Cube* cube_predio_esquerdo = new Cube();
        cube_predio_esquerdo->setName("Predio esquerdo");
        Cube* cube_rampa_predios = new Cube();
        cube_rampa_predios->setName("Rampa entre os predios");
        Cube* cube_rampa_camara = new Cube();
        cube_rampa_camara->setName("Rampa da camara");
        Cube* cube_rampa_camara_01 = new Cube();
        cube_rampa_camara_01->setName("Rampa da camara 01");
        Cube* cube_rampa_superior = new Cube();
        cube_rampa_superior->setName("Rampa superior da camara");
        Cube* cube_rampa_superior_01 = new Cube();
        cube_rampa_superior_01->setName("Rampa superior da camara parte 01");
        Cube* cube_rampa_superior_02 = new Cube();
        cube_rampa_superior_02->setName("Rampa superior da camara parte 02");
        Cube* cube_laje_superior = new Cube();
        cube_laje_superior->setName("Laje superior");
        Cube* cube_laje_inferior = new Cube();
        cube_laje_inferior->setName("Laje inferior");
        Cube* cube_base_interna = new Cube();
        cube_base_interna->setName("Laje interna");
        HemiSphere* hemisphere_maior = new HemiSphere();
        hemisphere_maior->setName("Semi-esfera maior");
        HemiSphere* hemisphere_menor = new HemiSphere();
        hemisphere_menor->setName("Semi-esfera menor");
        Prism* prism_canto_01 = new Prism();
        prism_canto_01->setName("Canto da laje superior 01");
        Prism* prism_canto_02 = new Prism();
        prism_canto_02->setName("Canto da laje superior 02");
        Prism* prism_canto_03 = new Prism();
        prism_canto_03->setName("Canto da laje superior 03");
        Prism* prism_canto_04 = new Prism();
        prism_canto_04->setName("Canto da laje superior 04");
        Cylinder* coluna_lajes[17];
        Prism* prism_predio_esquerdo_01  = new Prism();
        prism_predio_esquerdo_01->setName("Canto da frente do predio a esqueda");
        Prism* prism_predio_esquerdo_02  = new Prism();
        prism_predio_esquerdo_02->setName("Canto de tras do predio a esqueda");
        Prism* prism_predio_direito_01  = new Prism();
        prism_predio_direito_01->setName("Canto da frente do predio a direita");
        Prism* prism_predio_direito_02  = new Prism();
        prism_predio_direito_02->setName("Canto da tras do predio a direita");
        Cube* cubo_entre_prism_direito = new Cube();
        cubo_entre_prism_direito->setName("Coluna entre os os cantos do predio direito");
        Cube* cubo_entre_prism_esquerdo = new Cube();
        cubo_entre_prism_esquerdo->setName("Coluna entre os os cantos do predio esquerdo");
        Cube* cubo_linha_predios = new Cube();
        cubo_linha_predios->setName("Linha superior entre os predios");
        Cube* cubo_corredor_predios = new Cube();
        cubo_corredor_predios->setName("Corredor entre os predios");

        Cube* cubo_saida_predio_direito = new Cube();
        cubo_saida_predio_direito->setName("Saida predio esquerdo");

        Cube* cubo_saida_predio_esquerdo = new Cube();
        cubo_saida_predio_esquerdo->setName("Saida predio direito");

        Cube* cubo_chao = new Cube();
        cubo_chao->setName("Piso");

        Cylinder* coluna_laje_inclinada = new Cylinder();
        coluna_laje_inclinada->setName("Coluna da laje inclinada");

        Cylinder* coluna_laje_reta = new Cylinder();
        coluna_laje_reta->setName("Coluna da laje reta");



        t.setIdentity();
        t.scale(2,22,6);
        t.translate(-8,0,-20);
        cube_predio_esquerdo->setIdentityTransform();
        cube_predio_esquerdo->aplyTransform(t);
        cube_predio_esquerdo->setTransform(t);
        objects.push_back(cube_predio_esquerdo);

        t.setIdentity();
        t.scale(2,22,6);
        t.translate(-3,0,-20);
        cube_predio_direito->setIdentityTransform();
        cube_predio_direito->aplyTransform(t);
        cube_predio_direito->setTransform(t);
        objects.push_back(cube_predio_direito);

        //desenhando a rampa entre os predios
        t.setIdentity();
        t.scale(3,0.25,8);
        t.translate(-6,0,-17);
        cube_rampa_predios->setIdentityTransform();
        cube_rampa_predios->aplyTransform(t);
        cube_rampa_predios->setTransform(t);
        objects.push_back(cube_rampa_predios);

        //desenhando a rampa da câmera
        t.setIdentity();
        t.scale(1.5,0.25,7);
        t.translate(-4.5,0.5,7);
        cube_rampa_camara->setIdentityTransform();
        cube_rampa_camara->aplyTransform(t);
        cube_rampa_camara->setTransform(t);
        objects.push_back(cube_rampa_camara);

        //desenhando a rampa da câmera superior
        t.setIdentity();
        //t.scale(0,0.5,10);
        t.scale(1.5,0.22,5.50);
        t.setRotationX(17);
        t.translate(-6,2.15,6.8);
        cube_rampa_superior->setIdentityTransform();
        cube_rampa_superior->aplyTransform(t);
        cube_rampa_superior->setTransform(t);
        objects.push_back(cube_rampa_superior);

        //desenhando a rampa da câmera superior reto
        t.setIdentity();
        t.scale(1.5,0.25,2);
        //t.setRotationX(20);
        t.translate(-6,0.5,12);
        cube_rampa_superior_01->setIdentityTransform();
        cube_rampa_superior_01->aplyTransform(t);
        cube_rampa_superior_01->setTransform(t);
        objects.push_back(cube_rampa_superior_01);

        //desenhando a rampa da câmera superior parte 2
        t.setIdentity();
        t.scale(1.5,0.25,4);
        t.setRotationX(10);
        t.translate(-6,0.5,13.90);
        cube_rampa_superior_02->setIdentityTransform();
        cube_rampa_superior_02->aplyTransform(t);
        cube_rampa_superior_02->setTransform(t);
        objects.push_back(cube_rampa_superior_02);

        //desenhando a rampa da câmera parte 1
        t.setIdentity();
        //t.scale(0,0.5,10);
        t.scale(1.5,0.25,4);
        t.setRotationX(10);
        t.translate(-4.5,0.5,13.90);
        cube_rampa_camara_01->setIdentityTransform();
        cube_rampa_camara_01->aplyTransform(t);
        cube_rampa_camara_01->setTransform(t);
        objects.push_back(cube_rampa_camara_01);

        //desenhando a laje superior
        t.setIdentity();
        t.scale(34,0.25,16);
        t.translate(-17,2.1,-9);
        cube_laje_superior->setIdentityTransform();
        cube_laje_superior->aplyTransform(t);
        cube_laje_superior->setTransform(t);
        objects.push_back(cube_laje_superior);

        //desenhando a laje inferior
        t.setIdentity();
        t.scale(34,0.25,16);
        t.translate(-17,0.5,-9);
        cube_laje_inferior->setIdentityTransform();
        cube_laje_inferior->aplyTransform(t);
        cube_laje_inferior->setTransform(t);
        objects.push_back(cube_laje_inferior);

        //desenhando a base interna
        t.setIdentity();
        t.scale(34,2.25,14.9);
        t.translate(-17,0,-9);
        cube_base_interna->setIdentityTransform();
        cube_base_interna->aplyTransform(t);
        cube_base_interna->setTransform(t);
        objects.push_back(cube_base_interna);


        //desenhando as hemiesferas
        t.setIdentity();
        t.scale(3.5,2.5,3.5);
        t.translate(-10.5,2.5,-1);
        hemisphere_menor->setIdentityTransform();
        hemisphere_menor->aplyTransform(t);
        //t.showMatrix4x4();
        hemisphere_menor->setTransform(t);
        objects.push_back(hemisphere_menor);

        t.setIdentity();
        t.setRotationZ(180);
        t.scale(6,3.0,6);
        t.translate(8,5,-1);
        hemisphere_maior->setIdentityTransform();
        hemisphere_maior->aplyTransform(t);
        hemisphere_maior->setTransform(t);
        objects.push_back(hemisphere_maior);



        //desenhando os cantos
        t.setIdentity();
        t.scale(2.0,0.25,2.0);
        t.translate(17,2.1,-9);
        prism_canto_01->setIdentityTransform();
        prism_canto_01->aplyTransform(t);
        prism_canto_01->setTransform(t);
        objects.push_back(prism_canto_01);


        t.setIdentity();

        t.scale(2.0,0.25,2.0);
        t.setRotationX(180);
        t.translate(17,2.35,7);
        prism_canto_02->setIdentityTransform();
        prism_canto_02->aplyTransform(t);
        prism_canto_02->setTransform(t);
        objects.push_back(prism_canto_02);

        t.setIdentity();

        t.scale(2.0,0.25,2.0);
        t.setRotationZ(180);
        t.translate(-17,2.35,-9);
        prism_canto_03->setIdentityTransform();
        prism_canto_03->aplyTransform(t);
        prism_canto_03->setTransform(t);
        objects.push_back(prism_canto_03);

        t.setIdentity();

        t.scale(2.0,0.25,2.0);
        t.setRotationY(180);
        t.translate(-17,2.10,7);
        prism_canto_04->setIdentityTransform();
        prism_canto_04->aplyTransform(t);
        prism_canto_04->setTransform(t);
        objects.push_back(prism_canto_04);

        //desenhando as colunas entre as lajes

        //coluna 1
        coluna_lajes[0] = new Cylinder();
        coluna_lajes[0]->setName("Coluna 00");
        t.setIdentity();
        t.scale(0.15,2.0,0.15);
        t.translate(16.6,0.05,6.7);
        coluna_lajes[0]->setIdentityTransform();
        coluna_lajes[0]->aplyTransform(t);
        objects.push_back(coluna_lajes[0]);

        //coluna 2
        coluna_lajes[1] = new Cylinder();
        coluna_lajes[1]->setName("Coluna 01");
        t.setIdentity();
        t.scale(0.15,2.0,0.15);
        t.translate(14.54,0.05,6.7);
        coluna_lajes[1]->setIdentityTransform();
        coluna_lajes[1]->aplyTransform(t);
        objects.push_back(coluna_lajes[1]);

        //coluna 3
        coluna_lajes[2] = new Cylinder();
        coluna_lajes[2]->setName("Coluna 02");
        t.setIdentity();
        t.scale(0.15,2.0,0.15);
        t.translate(12.3,0.05,6.7);
        coluna_lajes[2]->setIdentityTransform();
        coluna_lajes[2]->aplyTransform(t);
        objects.push_back(coluna_lajes[2]);

        //coluna 4
        coluna_lajes[3] = new Cylinder();
        coluna_lajes[3]->setName("Coluna 03");
        t.setIdentity();
        t.scale(0.15,2.0,0.15);
        t.translate(9.9,0.05,6.7);
        coluna_lajes[3]->setIdentityTransform();
        coluna_lajes[3]->aplyTransform(t);
        objects.push_back(coluna_lajes[3]);

        //coluna 5
        coluna_lajes[4] = new Cylinder();
        coluna_lajes[4]->setName("Coluna 04");
        t.setIdentity();
        t.scale(0.15,2.0,0.15);
        t.translate(7.6,0.05,6.7);
        coluna_lajes[4]->setIdentityTransform();
        coluna_lajes[4]->aplyTransform(t);
        objects.push_back(coluna_lajes[4]);

        //coluna 6
        coluna_lajes[5] = new Cylinder();
        coluna_lajes[5]->setName("Coluna 05");
        t.setIdentity();
        t.scale(0.15,2.0,0.15);
        t.translate(5.4,0.05,6.7);
        coluna_lajes[5]->setIdentityTransform();
        coluna_lajes[5]->aplyTransform(t);
        objects.push_back(coluna_lajes[5]);

        //coluna 7
        coluna_lajes[6] = new Cylinder();
        coluna_lajes[6]->setName("Coluna 06");
        t.setIdentity();
        t.scale(0.15,2.0,0.15);
        t.translate(3.44,0.05,6.7);
        coluna_lajes[6]->setIdentityTransform();
        coluna_lajes[6]->aplyTransform(t);
        objects.push_back(coluna_lajes[6]);

        //coluna 8
        coluna_lajes[7] = new Cylinder();
        coluna_lajes[7]->setName("Coluna 07");
        t.setIdentity();
        t.scale(0.15,2.0,0.15);
        t.translate(1.38,0.05,6.7);
        coluna_lajes[7]->setIdentityTransform();
        coluna_lajes[7]->aplyTransform(t);
        objects.push_back(coluna_lajes[7]);

        //coluna 9
        coluna_lajes[8] = new Cylinder();
        coluna_lajes[8]->setName("Coluna 08");
        t.setIdentity();
        t.scale(0.15,2.0,0.15);
        t.translate(-0.7,0.05,6.7);
        coluna_lajes[8]->setIdentityTransform();
        coluna_lajes[8]->aplyTransform(t);
        objects.push_back(coluna_lajes[8]);

        //coluna 10
        coluna_lajes[9] = new Cylinder();
        coluna_lajes[9]->setName("Coluna 09");
        t.setIdentity();
        t.scale(0.15,2.0,0.15);
        t.translate(-2.84,0.05,6.7);
        coluna_lajes[9]->setIdentityTransform();
        coluna_lajes[9]->aplyTransform(t);
        objects.push_back(coluna_lajes[9]);

        //coluna 11
        coluna_lajes[10] = new Cylinder();
        coluna_lajes[10]->setName("Coluna 10");
        t.setIdentity();
        t.scale(0.15,2.0,0.15);
        t.translate(-4.70,0.05,6.7);
        coluna_lajes[10]->setIdentityTransform();
        coluna_lajes[10]->aplyTransform(t);
        objects.push_back(coluna_lajes[10]);

        //coluna 12
        coluna_lajes[11] = new Cylinder();
        coluna_lajes[11]->setName("Coluna 11");
        t.setIdentity();
        t.scale(0.15,2.0,0.15);
        t.translate(-6.5,0.05,6.7);
        coluna_lajes[11]->setIdentityTransform();
        coluna_lajes[11]->aplyTransform(t);
        objects.push_back(coluna_lajes[11]);

        //coluna 13
        coluna_lajes[12] = new Cylinder();
        coluna_lajes[12]->setName("Coluna 12");
        t.setIdentity();
        t.scale(0.15,2.0,0.15);
        t.translate(-8.6,0.05,6.7);
        coluna_lajes[12]->setIdentityTransform();
        coluna_lajes[12]->aplyTransform(t);
        objects.push_back(coluna_lajes[12]);

        //coluna 14
        coluna_lajes[13] = new Cylinder();
        coluna_lajes[13]->setName("Coluna 13");
        t.setIdentity();
        t.scale(0.15,2.0,0.15);
        t.translate(-10.58,0.05,6.7);
        coluna_lajes[13]->setIdentityTransform();
        coluna_lajes[13]->aplyTransform(t);
        objects.push_back(coluna_lajes[13]);

        //coluna 15
        coluna_lajes[14] = new Cylinder();
        coluna_lajes[14]->setName("Coluna 14");
        t.setIdentity();
        t.scale(0.15,2.0,0.15);
        t.translate(-12.55,0.05,6.7);
        coluna_lajes[14]->setIdentityTransform();
        coluna_lajes[14]->aplyTransform(t);
        objects.push_back(coluna_lajes[14]);

        //coluna 16
        coluna_lajes[15] = new Cylinder();
        coluna_lajes[15]->setName("Coluna 15");
        t.setIdentity();
        t.scale(0.15,2.0,0.15);
        t.translate(-14.5,0.05,6.7);
        coluna_lajes[15]->setIdentityTransform();
        coluna_lajes[15]->aplyTransform(t);
        objects.push_back(coluna_lajes[15]);

        //coluna 17
        coluna_lajes[16] = new Cylinder();
        coluna_lajes[16]->setName("Coluna 16");
        t.setIdentity();
        t.scale(0.15,2.0,0.15);
        t.translate(-16.46,0.05,6.7);
        coluna_lajes[16]->setIdentityTransform();
        coluna_lajes[16]->aplyTransform(t);
        objects.push_back(coluna_lajes[16]);








        //
        t.setIdentity();
        t.scale(8,0.25,1.5);
        t.translate(-1,0,-16);
        cubo_saida_predio_direito->setIdentityTransform();
        cubo_saida_predio_direito->setTransform(t);

        objects.push_back(cubo_saida_predio_direito);

        t.setIdentity();
        t.scale(3.5,0.25,1.5);
        t.translate(-11,0,-16);
        cubo_saida_predio_esquerdo->setIdentityTransform();
        cubo_saida_predio_esquerdo->setTransform(t);

        objects.push_back(cubo_saida_predio_esquerdo);



        t.setIdentity();
        t.scale(0.15,1.25,0.15);
        t.translate(-5.20,0,10);
        coluna_laje_inclinada->setIdentityTransform();
        coluna_laje_inclinada->setTransform(t);

        objects.push_back(coluna_laje_inclinada);

        t.setIdentity();
        t.scale(0.15,0.5,0.15);
        t.translate(-3.7,0,10);
        coluna_laje_reta->setIdentityTransform();
        coluna_laje_reta->setTransform(t);

        objects.push_back(coluna_laje_reta);
        for(unsigned int i=0;i<objects.size();i++){
            objects.at(i)->setMaterial(material);
        }
        t.setIdentity();

        t.scale(2.5,22,1);
        t.setRotationY(90);
        t.translate(-6,0.0,-17.5);
        prism_predio_esquerdo_01->setIdentityTransform();
        prism_predio_esquerdo_01->setTransform(t);

        objects.push_back(prism_predio_esquerdo_01);


        t.setIdentity();
        t.scale(1.0,22,2.5);
        t.translate(-6,0.0,-16.5);
        prism_predio_esquerdo_02->setIdentityTransform();
        prism_predio_esquerdo_02->setTransform(t);

        objects.push_back(prism_predio_esquerdo_02);


        t.setIdentity();
        t.setRotationZ(180);
        t.scale(1.0,22,2.5);
        t.translate(-3,22,-16.5);
        prism_predio_direito_01->setIdentityTransform();
        prism_predio_direito_01->setTransform(t);

        objects.push_back(prism_predio_direito_01);

        t.setIdentity();
        t.setRotationY(180);
        t.scale(1.0,22,2.5);
        t.translate(-3,0,-17.5);
        prism_predio_direito_02->setIdentityTransform();
        prism_predio_direito_02->setTransform(t);

        objects.push_back(prism_predio_direito_02);

        t.setIdentity();
        t.scale(1,22,1);
        t.translate(-4,0,-17.5);
        cubo_entre_prism_direito->setIdentityTransform();
        cubo_entre_prism_direito->setTransform(t);

        objects.push_back(cubo_entre_prism_direito);

        t.setIdentity();
        t.scale(1,22,1);
        t.translate(-6,0,-17.5);
        cubo_entre_prism_esquerdo->setIdentityTransform();
        cubo_entre_prism_esquerdo->setTransform(t);

        objects.push_back(cubo_entre_prism_esquerdo);

        t.setIdentity();
        t.scale(2,0.15,1);
        t.translate(-5.5,22,-17.5);
        cubo_linha_predios->setIdentityTransform();
        cubo_linha_predios->setTransform(t);

        objects.push_back(cubo_linha_predios);

        t.setIdentity();
        t.scale(1,1.5,1);
        t.translate(-5,11,-17.5);
        cubo_corredor_predios->setIdentityTransform();
        cubo_corredor_predios->setTransform(t);

        objects.push_back(cubo_corredor_predios);
        Plane *plan = new Plane();
        t.setIdentity();
        t.scale(40,1,40);
        //t.translate(-20,0.05,-20);
        plan->setIdentityTransform();
        plan->setTransform(t);
        plan->setMaterial(MATERIAL_BLACK_PLASTIC);
        for(int i=0;i<objects.size();i++){
            objects.at(i)->setMaterial(material);
        }
        objects.push_back(plan);
        break;
    }
    }


    push_obj = false;
}

void Scene::drawObjectsOpenGL(bool wireframe)
{

    glPushMatrix();
    for(int i=0;i<objects.size();i++){
        if(wireframe){
            glLineWidth(1.2);
            glDisable(GL_DEPTH_TEST);
            objects.at(i)->wireframe();
            //qDebug() << objects.at(i)->getName();
        }else{
            glLineWidth(1.0);
            glEnable(GL_DEPTH_TEST);
            objects.at(i)->draw();
            //qDebug() << objects.at(i)->getName();
        }
    }
    glPopMatrix();
}

void Scene::pushLights(Light *light)
{
    if(lights.size()==0){
        AmbientLight *ambient = new AmbientLight();
        lights.push_back(ambient);
    }
    lights.push_back(light);
}

void Scene::renderLightsOpenGL()
{
    glEnable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHT1);
    glDisable(GL_LIGHT2);
    glDisable(GL_LIGHT3);
    glDisable(GL_LIGHT4);
    glDisable(GL_LIGHT5);
    glDisable(GL_LIGHT6);
    glDisable(GL_LIGHT7);
    lights.at(0)->drawLightOpenGL();
    for(int i=1;i<lights.size();i++){
        if(i>8) return;  //capacidade máxima de luz do opengl 7 fontes de luz
        if(i==1){
            if(lights.at(i)->isEnabled()) glEnable(GL_LIGHT0);
            else glDisable(GL_LIGHT0);
            lights.at(i)->drawLightOpenGL(GL_LIGHT0);
            lights.at(i)->drawReferenceLight();
        }
        if(i==2){
            if(lights.at(i)->isEnabled()) glEnable(GL_LIGHT1);
            else glDisable(GL_LIGHT1);
            lights.at(i)->drawLightOpenGL(GL_LIGHT1);
            lights.at(i)->drawReferenceLight();
        }
        if(i==3){
            if(lights.at(i)->isEnabled()) glEnable(GL_LIGHT2);
            else glDisable(GL_LIGHT2);
            lights.at(i)->drawLightOpenGL(GL_LIGHT2);
            lights.at(i)->drawReferenceLight();
        }
        if(i==4){
            if(lights.at(i)->isEnabled()) glEnable(GL_LIGHT3);
            else glDisable(GL_LIGHT3);
            lights.at(i)->drawLightOpenGL(GL_LIGHT3);
            lights.at(i)->drawReferenceLight();
        }
        if(i==5){
            if(lights.at(i)->isEnabled()) glEnable(GL_LIGHT4);
            else glDisable(GL_LIGHT4);
            lights.at(i)->drawLightOpenGL(GL_LIGHT4);
            lights.at(i)->drawReferenceLight();
        }
        if(i==6){
            if(lights.at(i)->isEnabled()) glEnable(GL_LIGHT5);
            else glDisable(GL_LIGHT5);
            lights.at(i)->drawLightOpenGL(GL_LIGHT5);
            lights.at(i)->drawReferenceLight();
        }
        if(i==7){
            if(lights.at(i)->isEnabled()) glEnable(GL_LIGHT6);
            else glDisable(GL_LIGHT6);
            lights.at(i)->drawLightOpenGL(GL_LIGHT6);
            lights.at(i)->drawReferenceLight();
        }
        if(i==8){
            if(lights.at(i)->isEnabled()) glEnable(GL_LIGHT7);
            else glDisable(GL_LIGHT7);
            lights.at(i)->drawLightOpenGL(GL_LIGHT7);
            lights.at(i)->drawReferenceLight();
        }
    }
}


void Scene::pushViewer(Vec4 eye, Vec4 at, Vec4 up)
{
    viewer[0] = eye;
    viewer[1] = at;
    viewer[2] = up;
}

//void Scene::calculatePixels(GLubyte *pixels, int width, int height)
//{
//    Matrix4x4 changetoviewer;
//    changetoviewer.setIdentity();
//    Vec4 kv,iv,jv;


//    kv = (viewer[0] - viewer[1])/((viewer[0] - viewer[1]).module());
//    iv = (viewer[2] ^ kv)/(viewer[2] ^ kv).module();
//    jv = (kv ^ iv)/(kv ^ iv).module();
//    kv.showVec4();
//    iv.showVec4();
//    jv.showVec4();

//    Vec4 translate(-(iv*viewer[0]),-(jv*viewer[0]),-(kv*viewer[0]));

//    changetoviewer.setAxisX(iv);
//    changetoviewer.setAxisY(jv);
//    changetoviewer.setAxisZ(kv);

//    changetoviewer.setTranslate(translate);
//    //changetoviewer.showMatrix4x4();

//    //mudança de coordenadas dos objetos
//    for(int i=0;i<objects.size();i++){
//        objects.at(i)->changeCoords(changetoviewer);
//    }

//    Vec4 color[width*height];

//    float aspect = (float)width/height;
//    float h = 2*0.01*(tan(M_PI*45.0/360.0));
//    float w = h*aspect;
//    float deltax = w/width;   /*45.0/(2.0*width);*/
//    float deltay = h/height;//(2*(tan(M_PI*45.0/360.0)));
//    int hits = 0;

//    for(int j=0;j<height;j++){
//        //
//        for (int i=0;i<width;i++){
//            float alfa  = -w/2.0 + deltax/2.0  + i*deltax;
//            float beta  = -h/2.0 + deltay/2.0 + j*deltay;
//            Vec4 dir(alfa,beta,-0.01);

//            Ray ray_intersection(Vec4(0,0,0),dir);

//            color[(width*j)+(i)] = ray_intersection.RayInterceptionVec4(objects,lights);
//            if(ray_intersection.RayInterceptionVec4(objects,lights).x4!=-1) hits++;
//        }
//    }
//    for(int i=0;i<width*height;i++){
//        pixels[3*i]   = ((int)(color[i].x1*255));
//        pixels[3*i+1] = ((int)(color[i].x2*255));
//        pixels[3*i+2] = ((int)(color[i].x3*255));
//    }
//    printf("\nDe %d raios, %d acertos.",width*height,hits);

//}

void Scene::pushViewport(int width, int height)
{
    viewport[0] = width;
    viewport[1] = height;
}

void Scene::pushProjection(float angle, float aspect, float near, float far)
{
    projection.x1 = angle;
    projection.x2 = aspect;
    projection.x3 = near;
    projection.x4 = far;
}

void Scene::pushBackgroundColor(Vec4 background)
{
    background_color = background;
}

void Scene::setMaterialAllObjects(int id)
{
    for (int i=0;i<objects.size();i++){
        objects.at(i)->setMaterial(id);
    }
}

void Scene::setDOF(float radius, float focal)
{
    this->focal = focal;
    this->radius = radius;
}

float Scene::getRadiusDOF()
{
    return radius;
}

float Scene::getFocalDOF()
{
    return focal;
}

void Scene::drawPhotons(bool flag)
{
    if (!flag){
        glEnable(GL_LIGHTING);
        return;
    }else{
        if(!photonMap.kdtree->photons.empty()){
            photonMap.drawPhotonMap();
            if (flag) glDisable(GL_LIGHTING);
            return;
        }
        generatePhotons();
    }
    photonMap.drawPhotonMap();
    if (flag) glDisable(GL_LIGHTING);
}

void Scene::drawPhotonsCaustic(bool flag)
{
    if (!flag){
        glEnable(GL_LIGHTING);
        return;
    }else{
        if(!photonMap.caustic->photons.empty()){
            photonMap.drawPhotonMapCaustics();
            if (flag) glDisable(GL_LIGHTING);
            return;
        }
        generatePhotons();
    }
    photonMap.drawPhotonMapCaustics();
    if (flag) glDisable(GL_LIGHTING);
}

void Scene::generatePhotons()
{
    std::vector<Photon*> photons;
    std::vector<Photon*> totalphotons;
    std::vector<Object*> objectsRefracted;
    if(sizePhotonsCaustic==0) photonMap.caustic->photons.clear();
    for(unsigned int i=0;i<objects.size();i++){
        if (objects.at(i)->isEnabled())
            if(objects.at(i)->getMesh()->getRefraction()!=0)
                objectsRefracted.push_back(objects.at(i));
    }
    if(!objectsRefracted.empty())
        if(!photonMap.caustic->photons.empty() && !photonMap.kdtree->photons.empty()) return;
        else
            if(!photonMap.kdtree->photons.empty()) return;
    int energy = 0; //energia total do sistema
    for(unsigned int i=1;i<lights.size();i++){
        energy += lights.at(i)->getPower();
    }
    int energyCaustic,energyGlobal;
    if (objectsRefracted.size()!=0){
        energyCaustic = energy/3.0;
        energyGlobal = 2*energy/3.0;
    }else{
        energyGlobal = energy;
    }

    //photons caustica
    if(objectsRefracted.size()!=0)
        if (sizePhotonsCaustic!=0)
            for(unsigned int i=1;i<lights.size();i++){
                for(unsigned int k=0;k<objectsRefracted.size();k++){
                    photons = lights.at(i)->emitPhotons(sizePhotonsCaustic,energyCaustic/(lights.size()-1),objectsRefracted.at(k));
                    for(unsigned int j=0;j<photons.size();j++) totalphotons.push_back(photons.at(j));
                }
            }
    //photons globais
    if (sizePhotons!=0)
        for(unsigned int i=1;i<lights.size();i++){
            photons = lights.at(i)->emitPhotons(sizePhotons,energyGlobal/(lights.size()-1));
            for(unsigned int j=0;j<photons.size();j++) totalphotons.push_back(photons.at(j));
        }


    photonMap.setScene(this);
    int size = totalphotons.size();
    for(unsigned int i=0;i<size;i++)
        totalphotons.at(i)->setPower(Vec4((float)energy/size,(float)energy/size,(float)energy/size));
    photonMap.constructPhotonMap(totalphotons);
    //kdtree = new KdTree(photonMap.photons);
}

void Scene::setSizePhotons(int value)
{
    sizePhotons = value;
    photonMap.kdtree->photons.clear();
}

void Scene::setSizePhotonsCaustic(int value)
{
    sizePhotonsCaustic = value;
    photonMap.caustic->photons.clear();
}

void Scene::renderGlobalRadiance(bool b)
{
    photonMap.renderGlobal = b;
}

void Scene::renderCausticRadiance(bool b)
{
    photonMap.renderCaustic = b;
}

void Scene::setPhotonsNearsCaustics(int val)
{
    photonMap.setNearsPhotonsCaustics(val);
}

void Scene::setPhotonsNearsGlobal(int val)
{
    photonMap.setNearsPhotonsGlobal(val);
}

void Scene::setEnablePhotonMap(bool b)
{
    enablephoton = b;
}

void Scene::setRadiusGlobal(float val)
{

    photonMap.setRadiusGlogal(val);
}

void Scene::setRadiusCaustic(float val)
{
    photonMap.setRadiusCaustic(val);
}

void Scene::setDepthPhotons(int val)
{
    photonMap.setDepth(val);
}

void Scene::setFilterPhoton(bool b)
{
    photonMap.setFilter(b);
}

Object *Scene::getObjecSelected()
{
    for(int i=0;i<this->objects.size();i++)
        if(this->objects.at(i)->isSelected()) return this->objects.at(i);
    return NULL;
}

void Scene::makeClone(Object *obj)
{
    if (obj==NULL) return;
    Object *clone = addObject(obj->getTypeInt());
    clone->setTransform(obj->getMatrixTransformation());
    if(obj->getLenBump()>0)
        clone->setBump(obj->getBump(0));
    if(obj->getLenTexture()>0)
        clone->setTexture(obj->getTexture(0));
    clone->setMaterial(obj->getIdMaterial());
    clone->setMotion(obj->getMotion());
    clone->setEnabledBump(obj->getEnabledBump());
    clone->setEnabledTexture(obj->getEnabledTexture());
    clone->setName(obj->getName()+"_CLONE");
    clone->getMesh()->setReflection(obj->getMesh()->getReflection());
    clone->getMesh()->setGlossyReflection(obj->getMesh()->getGlossyReflection());
    clone->getMesh()->setRefraction(obj->getMesh()->getRefraction());
    clone->getMesh()->setGlossyRefraction(obj->getMesh()->getGlossyRefraction());
    clone->getMesh()->setMaterial(obj->getMesh()->getMaterialM()->getAmbiente(),obj->getMesh()->getMaterialM()->getDiffuse(),obj->getMesh()->getMaterialM()->getSpecular(),obj->getMesh()->getMaterialM()->getShininess());
    obj->setSelected(false);
    clone->setSelected(true);
    Matrix4x4 m = clone->getMatrixTransformation();
    m.setTranslate(m.getTranslateSeted()+Vec4(0.5,0.5,0.5));
    clone->setTransform(m);

}

Scene::~Scene()
{

    free(*iter);
    free(*iterl);
}

Object* Scene::addObject(int type)
{
    switch (type){
    case BLOCK_CUBE:{
        Cube *cube = new Cube();
        cube->setName("Cubo");
        cube->setMaterial(MATERIAL_EMERALD);
        objects.push_back(cube);
        return cube;
        break;
    }
    case BLOCK_PRISM:{
        Prism *prism = new Prism();
        prism->setName("Prisma");
        prism->setMaterial(MATERIAL_RUBY);
        objects.push_back(prism);
        return prism;
        break;
    }

    case BLOCK_HEMISPHERE:{
        HemiSphere *hemisphere = new HemiSphere();
        hemisphere->setName("Semi-Esfera");
        hemisphere->setMaterial(MATERIAL_BRASS);
        objects.push_back(hemisphere);
        return hemisphere;
        break;
    }
    case BLOCK_SPHERE:{
        Sphere *sphere = new Sphere();
        sphere->setName("Esfera");
        sphere->setMaterial(MATERIAL_GOLD);
        objects.push_back(sphere);
        return sphere;
        break;
    }
    case BLOCK_CONE:{
        Cone *cone = new Cone();
        cone->setName("Cone");
        cone->setMaterial(MATERIAL_BRONZE);
        objects.push_back(cone);
        return cone;
        break;
    }
    case BLOCK_PLANE:{
            Plane *plane = new Plane();
            plane->setName("Plano");
            plane->setMaterial(MATERIAL_TURQUOSIE);
            objects.push_back(plane);
            return plane;
            break;
        }

    case BLOCK_CYLINDER:{
        Cylinder *cylinder = new Cylinder();
        cylinder->setName("Cilindro");
        cylinder->setMaterial(MATERIAL_RUBY);
        objects.push_back(cylinder);
        return cylinder;
        break;
    }
    }

}

Light *Scene::addLight(int type)
{
    switch (type){
    case (LIGHT_AMBIENT):{
        AmbientLight* newDir = new AmbientLight();
        newDir->setEnabled(false);
        this->pushLights(newDir);
        return newDir;
        break;
    }
    case (LIGHT_DIRECTIONAL):{
        DirectionalLight* newDir = new DirectionalLight();
        newDir->setEnabled(false);
        this->pushLights(newDir);
        return newDir;
        break;
    }
    case (LIGHT_SPOT):{
        SpotLight* newDir = new SpotLight();
        newDir->setEnabled(false);
        this->pushLights(newDir);
        return newDir;
        break;
    }
    case (LIGHT_PONTUAL):{
        PontualLight* newDir = new PontualLight();
        newDir->setEnabled(false);
        this->pushLights(newDir);
        return newDir;
        break;
    }
    case (LIGHT_AREA):{
        AreaLight* newDir = new AreaLight();
        newDir->setEnabled(false);
        this->pushLights(newDir);
        return newDir;
        break;
    }
    }
}

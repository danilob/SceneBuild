/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <interface/glwidget.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionQuit;
    QAction *actionGrid;
    QAction *actionPropertiesScene;
    QAction *actionCube;
    QAction *actionCylinder;
    QAction *actionHemisphere;
    QAction *actionPrism;
    QAction *actionSphere;
    QAction *actionArea;
    QAction *actionDirectional;
    QAction *actionPontual;
    QAction *actionSpot;
    QAction *actionGlossy_Reflection;
    QAction *actionGlossy_Refraction;
    QAction *actionMotion_Blur;
    QAction *actionDepth_of_Field;
    QAction *actionScreenShot;
    QAction *actionScreanShot_Render;
    QAction *actionCone;
    QAction *actionD;
    QAction *actionSave_As;
    QAction *actionAbout;
    QAction *actionShortcuts;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout_9;
    QScrollArea *scrollObject;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBoxPropertiesObj;
    QGridLayout *gridLayout_11;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *selectedObj;
    QCheckBox *enableObj;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *ambMaterial;
    QPushButton *diffMaterial;
    QPushButton *speMaterial;
    QLineEdit *nomeObj;
    QLabel *label_10;
    QLabel *label_13;
    QComboBox *materialobject;
    QVBoxLayout *verticalLayout_3;
    QDoubleSpinBox *transx;
    QDoubleSpinBox *transy;
    QDoubleSpinBox *transz;
    QLabel *label_12;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_10;
    QHBoxLayout *horizontalLayout_17;
    QLabel *label_35;
    QDoubleSpinBox *glossyreflection;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_34;
    QDoubleSpinBox *glossyrefraction;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_33;
    QDoubleSpinBox *reflection;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_32;
    QDoubleSpinBox *refraction;
    QHBoxLayout *horizontalLayout_18;
    QDoubleSpinBox *xmotion;
    QDoubleSpinBox *ymotion;
    QDoubleSpinBox *zmotion;
    QLabel *label_36;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_14;
    QDoubleSpinBox *shiniMaterial;
    QVBoxLayout *verticalLayout_4;
    QSpinBox *rotx;
    QSpinBox *roty;
    QSpinBox *rotz;
    QHBoxLayout *horizontalLayout_19;
    QLabel *label_16;
    QLabel *label_15;
    QLabel *label_17;
    QLabel *label_11;
    QPushButton *deleteObj;
    QVBoxLayout *verticalLayout_5;
    QDoubleSpinBox *scalex;
    QDoubleSpinBox *scaley;
    QDoubleSpinBox *scalez;
    QGroupBox *groupBox_6;
    QGridLayout *gridLayout_13;
    QGraphicsView *onScreenImage;
    QPushButton *loadBump;
    QPushButton *loadTexture;
    QCheckBox *enableTexture;
    QCheckBox *enableBump;
    QGraphicsView *onScreenImageBump;
    QComboBox *choiceTexture;
    QScrollArea *scrollLight;
    QWidget *scrollAreaWidgetContents_4;
    QFormLayout *formLayout;
    QGroupBox *groupBoxPropertieLight;
    QVBoxLayout *verticalLayout_8;
    QFrame *nameLightLayout;
    QVBoxLayout *verticalLayout_7;
    QLabel *label_20;
    QLineEdit *nameLight;
    QHBoxLayout *optionLayout;
    QCheckBox *selectedLight;
    QCheckBox *visibleLight;
    QCheckBox *enableLight;
    QFrame *orientationLight;
    QGridLayout *gridLayout_7;
    QFrame *positionLayoutLight;
    QVBoxLayout *positionLayout;
    QLabel *label_21;
    QDoubleSpinBox *positionxLight;
    QDoubleSpinBox *positionyLight;
    QDoubleSpinBox *positionzLight;
    QFrame *directionLayoutLight;
    QVBoxLayout *directionLayout;
    QLabel *label_22;
    QDoubleSpinBox *directionxLight;
    QDoubleSpinBox *directionyLight;
    QDoubleSpinBox *directionzLight;
    QFrame *energyFrame;
    QHBoxLayout *energyLayout;
    QLabel *label_44;
    QSpinBox *energyLight;
    QFrame *vectorsLayoutLight;
    QVBoxLayout *vectorsLayout;
    QVBoxLayout *verticalLayout_9;
    QLabel *label_24;
    QHBoxLayout *horizontalLayout_10;
    QDoubleSpinBox *vecAx;
    QDoubleSpinBox *vecAy;
    QDoubleSpinBox *vecAz;
    QVBoxLayout *verticalLayout_10;
    QLabel *label_25;
    QHBoxLayout *horizontalLayout_11;
    QDoubleSpinBox *vecBx;
    QDoubleSpinBox *vecBy;
    QDoubleSpinBox *vecBz;
    QFrame *attenuationLayoutLight;
    QVBoxLayout *attenuationLayout;
    QLabel *label_23;
    QHBoxLayout *horizontalLayout_9;
    QDoubleSpinBox *attenuationcLight;
    QDoubleSpinBox *attenuationlLight;
    QDoubleSpinBox *attenuationqLight;
    QFrame *ADSLight;
    QHBoxLayout *horizontalLayout;
    QFrame *ambienteProperty;
    QVBoxLayout *verticalLayout_11;
    QLabel *label_26;
    QPushButton *ambMaterial_2;
    QFrame *diffuseProperty;
    QVBoxLayout *verticalLayout_12;
    QLabel *label_27;
    QPushButton *diffMaterial_2;
    QFrame *specularProperty;
    QVBoxLayout *verticalLayoutSpe;
    QLabel *label_28;
    QPushButton *speMaterial_2;
    QFrame *angleSpotLayoutLight;
    QVBoxLayout *angleSpotLayout;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_29;
    QSpinBox *anglespotLight;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label_30;
    QSpinBox *anglespotinnerLight;
    QHBoxLayout *horizontalLayout_16;
    QLabel *label_31;
    QSpinBox *exponentSpotLight;
    QPushButton *deleteLight;
    QFrame *frame_3;
    QGridLayout *gridLayout_2;
    QTabWidget *tabWidget;
    QWidget *tabOpenGL;
    QGridLayout *gridLayout_3;
    GLWidget *widgetOpenGL;
    QWidget *tabRender;
    QGridLayout *gridLayout_6;
    QGraphicsView *graphicsRender;
    QScrollArea *scrollArea_3;
    QWidget *scrollAreaWidgetContents_3;
    QGridLayout *gridLayout_4;
    QToolBox *toolBox;
    QWidget *page;
    QGridLayout *gridLayout_5;
    QListWidget *objects_list;
    QWidget *page_3;
    QGridLayout *gridLayout_8;
    QListWidget *lights_list;
    QWidget *page_2;
    QCheckBox *showHBB;
    QGroupBox *groupBox_5;
    QGridLayout *gridLayout_12;
    QHBoxLayout *horizontalLayout_21;
    QLabel *label_37;
    QDoubleSpinBox *radiusDOF;
    QHBoxLayout *horizontalLayout_20;
    QLabel *label_38;
    QDoubleSpinBox *focalDOF;
    QWidget *page_5;
    QGridLayout *gridLayout_15;
    QVBoxLayout *verticalLayout_14;
    QFormLayout *formLayout_3;
    QLabel *label_39;
    QSpinBox *sizePhotons;
    QHBoxLayout *horizontalLayout_23;
    QLabel *label_40;
    QDoubleSpinBox *radiusGlobal;
    QHBoxLayout *horizontalLayout_28;
    QLabel *label_46;
    QSpinBox *nearsGlobal;
    QHBoxLayout *horizontalLayout_25;
    QLabel *label_42;
    QSpinBox *sizePhotonsCaustic;
    QHBoxLayout *horizontalLayout_24;
    QLabel *label_41;
    QDoubleSpinBox *radiusCaustic;
    QHBoxLayout *horizontalLayout_27;
    QLabel *label_45;
    QSpinBox *nearsCaustics;
    QHBoxLayout *horizontalLayout_26;
    QLabel *label_43;
    QSpinBox *depthPhoton;
    QGroupBox *groupBox_7;
    QGridLayout *gridLayout_16;
    QCheckBox *enablePhotonMap;
    QCheckBox *visiblePhotonMap;
    QCheckBox *visiblePhotonMapCaustics;
    QGroupBox *groupBox_8;
    QGridLayout *gridLayout_14;
    QCheckBox *useFilter;
    QCheckBox *renderCaustics;
    QCheckBox *renderGlobal;
    QWidget *page_4;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_18;
    QSpinBox *numSamples;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_19;
    QSpinBox *proportion;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *btnRender;
    QProgressBar *progressRender;
    QScrollArea *scrollAreaBottom;
    QWidget *scrollAreaWidgetContents_2;
    QGroupBox *groupBox;
    QDoubleSpinBox *dEyex;
    QDoubleSpinBox *dEyey;
    QDoubleSpinBox *dEyez;
    QDoubleSpinBox *dAtx;
    QDoubleSpinBox *dAty;
    QDoubleSpinBox *dAtz;
    QDoubleSpinBox *dUpx;
    QDoubleSpinBox *dUpy;
    QDoubleSpinBox *dUpz;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QGroupBox *groupBox_2;
    QDoubleSpinBox *anglePerspective;
    QDoubleSpinBox *nearPerspective;
    QDoubleSpinBox *farPerspective;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QGroupBox *groupBox_3;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QSpinBox *sizeGrid;
    QLabel *height_l;
    QLabel *width_l;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuOpen_Recent_File;
    QMenu *menuObject;
    QMenu *menuLights;
    QMenu *menuObject_2;
    QMenu *menuLight;
    QMenu *menuOptions;
    QMenu *menuHelp;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(913, 843);
        MainWindow->setMaximumSize(QSize(2000000, 16777215));
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QStringLiteral("actionQuit"));
        actionGrid = new QAction(MainWindow);
        actionGrid->setObjectName(QStringLiteral("actionGrid"));
        actionGrid->setCheckable(true);
        actionGrid->setChecked(true);
        actionPropertiesScene = new QAction(MainWindow);
        actionPropertiesScene->setObjectName(QStringLiteral("actionPropertiesScene"));
        actionPropertiesScene->setCheckable(true);
        actionPropertiesScene->setChecked(true);
        actionCube = new QAction(MainWindow);
        actionCube->setObjectName(QStringLiteral("actionCube"));
        actionCylinder = new QAction(MainWindow);
        actionCylinder->setObjectName(QStringLiteral("actionCylinder"));
        actionHemisphere = new QAction(MainWindow);
        actionHemisphere->setObjectName(QStringLiteral("actionHemisphere"));
        actionPrism = new QAction(MainWindow);
        actionPrism->setObjectName(QStringLiteral("actionPrism"));
        actionSphere = new QAction(MainWindow);
        actionSphere->setObjectName(QStringLiteral("actionSphere"));
        actionArea = new QAction(MainWindow);
        actionArea->setObjectName(QStringLiteral("actionArea"));
        actionDirectional = new QAction(MainWindow);
        actionDirectional->setObjectName(QStringLiteral("actionDirectional"));
        actionPontual = new QAction(MainWindow);
        actionPontual->setObjectName(QStringLiteral("actionPontual"));
        actionSpot = new QAction(MainWindow);
        actionSpot->setObjectName(QStringLiteral("actionSpot"));
        actionGlossy_Reflection = new QAction(MainWindow);
        actionGlossy_Reflection->setObjectName(QStringLiteral("actionGlossy_Reflection"));
        actionGlossy_Refraction = new QAction(MainWindow);
        actionGlossy_Refraction->setObjectName(QStringLiteral("actionGlossy_Refraction"));
        actionMotion_Blur = new QAction(MainWindow);
        actionMotion_Blur->setObjectName(QStringLiteral("actionMotion_Blur"));
        actionDepth_of_Field = new QAction(MainWindow);
        actionDepth_of_Field->setObjectName(QStringLiteral("actionDepth_of_Field"));
        actionScreenShot = new QAction(MainWindow);
        actionScreenShot->setObjectName(QStringLiteral("actionScreenShot"));
        actionScreanShot_Render = new QAction(MainWindow);
        actionScreanShot_Render->setObjectName(QStringLiteral("actionScreanShot_Render"));
        actionCone = new QAction(MainWindow);
        actionCone->setObjectName(QStringLiteral("actionCone"));
        actionD = new QAction(MainWindow);
        actionD->setObjectName(QStringLiteral("actionD"));
        actionSave_As = new QAction(MainWindow);
        actionSave_As->setObjectName(QStringLiteral("actionSave_As"));
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        actionShortcuts = new QAction(MainWindow);
        actionShortcuts->setObjectName(QStringLiteral("actionShortcuts"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        gridLayout_9 = new QGridLayout();
        gridLayout_9->setSpacing(6);
        gridLayout_9->setObjectName(QStringLiteral("gridLayout_9"));
        scrollObject = new QScrollArea(centralWidget);
        scrollObject->setObjectName(QStringLiteral("scrollObject"));
        scrollObject->setMinimumSize(QSize(250, 0));
        scrollObject->setMaximumSize(QSize(250, 16777215));
        scrollObject->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 248, 925));
        verticalLayout_2 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        groupBoxPropertiesObj = new QGroupBox(scrollAreaWidgetContents);
        groupBoxPropertiesObj->setObjectName(QStringLiteral("groupBoxPropertiesObj"));
        groupBoxPropertiesObj->setEnabled(true);
        groupBoxPropertiesObj->setMaximumSize(QSize(230, 16777215));
        QFont font;
        font.setPointSize(9);
        font.setBold(true);
        font.setWeight(75);
        groupBoxPropertiesObj->setFont(font);
        groupBoxPropertiesObj->setStyleSheet(QLatin1String("QGroupBox::title { \n"
"   \n"
"     subcontrol-position: top left; /* position at the top left*/ \n"
"  padding: 2px 13px;\n"
"   margin-top: -5px;\n"
"    \n"
" }\n"
"\n"
"QGroupBox{\n"
"   border: 1px solid rgb(182, 181, 179);\n"
"  border-radius: 5px;\n"
"}"));
        groupBoxPropertiesObj->setFlat(false);
        gridLayout_11 = new QGridLayout(groupBoxPropertiesObj);
        gridLayout_11->setSpacing(2);
        gridLayout_11->setContentsMargins(11, 11, 11, 11);
        gridLayout_11->setObjectName(QStringLiteral("gridLayout_11"));
        gridLayout_11->setContentsMargins(2, 5, 2, 2);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        selectedObj = new QCheckBox(groupBoxPropertiesObj);
        selectedObj->setObjectName(QStringLiteral("selectedObj"));

        horizontalLayout_2->addWidget(selectedObj);

        enableObj = new QCheckBox(groupBoxPropertiesObj);
        enableObj->setObjectName(QStringLiteral("enableObj"));

        horizontalLayout_2->addWidget(enableObj);


        gridLayout_11->addLayout(horizontalLayout_2, 2, 0, 1, 2);

        frame = new QFrame(groupBoxPropertiesObj);
        frame->setObjectName(QStringLiteral("frame"));
        horizontalLayout_3 = new QHBoxLayout(frame);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setSizeConstraint(QLayout::SetDefaultConstraint);
        ambMaterial = new QPushButton(frame);
        ambMaterial->setObjectName(QStringLiteral("ambMaterial"));
        ambMaterial->setAutoFillBackground(true);
        ambMaterial->setFlat(false);

        horizontalLayout_3->addWidget(ambMaterial);

        diffMaterial = new QPushButton(frame);
        diffMaterial->setObjectName(QStringLiteral("diffMaterial"));

        horizontalLayout_3->addWidget(diffMaterial);

        speMaterial = new QPushButton(frame);
        speMaterial->setObjectName(QStringLiteral("speMaterial"));

        horizontalLayout_3->addWidget(speMaterial);


        gridLayout_11->addWidget(frame, 8, 0, 1, 2);

        nomeObj = new QLineEdit(groupBoxPropertiesObj);
        nomeObj->setObjectName(QStringLiteral("nomeObj"));

        gridLayout_11->addWidget(nomeObj, 1, 0, 1, 2);

        label_10 = new QLabel(groupBoxPropertiesObj);
        label_10->setObjectName(QStringLiteral("label_10"));

        gridLayout_11->addWidget(label_10, 0, 0, 1, 1);

        label_13 = new QLabel(groupBoxPropertiesObj);
        label_13->setObjectName(QStringLiteral("label_13"));

        gridLayout_11->addWidget(label_13, 5, 1, 1, 1);

        materialobject = new QComboBox(groupBoxPropertiesObj);
        materialobject->setObjectName(QStringLiteral("materialobject"));

        gridLayout_11->addWidget(materialobject, 10, 0, 1, 2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        transx = new QDoubleSpinBox(groupBoxPropertiesObj);
        transx->setObjectName(QStringLiteral("transx"));
        transx->setLayoutDirection(Qt::LeftToRight);
        transx->setWrapping(false);
        transx->setAlignment(Qt::AlignCenter);
        transx->setMinimum(-9999);
        transx->setMaximum(9999);
        transx->setValue(0);

        verticalLayout_3->addWidget(transx);

        transy = new QDoubleSpinBox(groupBoxPropertiesObj);
        transy->setObjectName(QStringLiteral("transy"));
        transy->setAlignment(Qt::AlignCenter);
        transy->setMinimum(-9999);
        transy->setMaximum(9999);
        transy->setValue(0);

        verticalLayout_3->addWidget(transy);

        transz = new QDoubleSpinBox(groupBoxPropertiesObj);
        transz->setObjectName(QStringLiteral("transz"));
        transz->setAlignment(Qt::AlignCenter);
        transz->setMinimum(-9999);
        transz->setMaximum(9999);
        transz->setValue(0);

        verticalLayout_3->addWidget(transz);


        gridLayout_11->addLayout(verticalLayout_3, 4, 0, 1, 2);

        label_12 = new QLabel(groupBoxPropertiesObj);
        label_12->setObjectName(QStringLiteral("label_12"));

        gridLayout_11->addWidget(label_12, 5, 0, 1, 1);

        groupBox_4 = new QGroupBox(groupBoxPropertiesObj);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setFont(font);
        gridLayout_10 = new QGridLayout(groupBox_4);
        gridLayout_10->setSpacing(0);
        gridLayout_10->setContentsMargins(11, 11, 11, 11);
        gridLayout_10->setObjectName(QStringLiteral("gridLayout_10"));
        gridLayout_10->setContentsMargins(0, 5, 0, 5);
        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setSpacing(6);
        horizontalLayout_17->setObjectName(QStringLiteral("horizontalLayout_17"));
        label_35 = new QLabel(groupBox_4);
        label_35->setObjectName(QStringLiteral("label_35"));

        horizontalLayout_17->addWidget(label_35);

        glossyreflection = new QDoubleSpinBox(groupBox_4);
        glossyreflection->setObjectName(QStringLiteral("glossyreflection"));
        glossyreflection->setDecimals(3);
        glossyreflection->setMaximum(1);
        glossyreflection->setSingleStep(0.25);

        horizontalLayout_17->addWidget(glossyreflection);


        gridLayout_10->addLayout(horizontalLayout_17, 3, 0, 1, 1);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        label_34 = new QLabel(groupBox_4);
        label_34->setObjectName(QStringLiteral("label_34"));

        horizontalLayout_13->addWidget(label_34);

        glossyrefraction = new QDoubleSpinBox(groupBox_4);
        glossyrefraction->setObjectName(QStringLiteral("glossyrefraction"));
        glossyrefraction->setDecimals(3);
        glossyrefraction->setMaximum(1);
        glossyrefraction->setSingleStep(0.25);

        horizontalLayout_13->addWidget(glossyrefraction);


        gridLayout_10->addLayout(horizontalLayout_13, 2, 0, 1, 1);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        label_33 = new QLabel(groupBox_4);
        label_33->setObjectName(QStringLiteral("label_33"));

        horizontalLayout_12->addWidget(label_33);

        reflection = new QDoubleSpinBox(groupBox_4);
        reflection->setObjectName(QStringLiteral("reflection"));
        reflection->setDecimals(3);
        reflection->setMaximum(1);
        reflection->setSingleStep(0.25);

        horizontalLayout_12->addWidget(reflection);


        gridLayout_10->addLayout(horizontalLayout_12, 1, 0, 1, 1);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        label_32 = new QLabel(groupBox_4);
        label_32->setObjectName(QStringLiteral("label_32"));

        horizontalLayout_8->addWidget(label_32);

        refraction = new QDoubleSpinBox(groupBox_4);
        refraction->setObjectName(QStringLiteral("refraction"));
        refraction->setDecimals(3);
        refraction->setMinimum(0);
        refraction->setMaximum(5);
        refraction->setSingleStep(0.25);

        horizontalLayout_8->addWidget(refraction);


        gridLayout_10->addLayout(horizontalLayout_8, 0, 0, 1, 1);

        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setSpacing(0);
        horizontalLayout_18->setObjectName(QStringLiteral("horizontalLayout_18"));
        xmotion = new QDoubleSpinBox(groupBox_4);
        xmotion->setObjectName(QStringLiteral("xmotion"));
        xmotion->setDecimals(1);
        xmotion->setMinimum(-99);

        horizontalLayout_18->addWidget(xmotion);

        ymotion = new QDoubleSpinBox(groupBox_4);
        ymotion->setObjectName(QStringLiteral("ymotion"));
        ymotion->setDecimals(1);
        ymotion->setMinimum(-99);

        horizontalLayout_18->addWidget(ymotion);

        zmotion = new QDoubleSpinBox(groupBox_4);
        zmotion->setObjectName(QStringLiteral("zmotion"));
        zmotion->setDecimals(1);
        zmotion->setMinimum(-99);

        horizontalLayout_18->addWidget(zmotion);


        gridLayout_10->addLayout(horizontalLayout_18, 5, 0, 1, 1);

        label_36 = new QLabel(groupBox_4);
        label_36->setObjectName(QStringLiteral("label_36"));

        gridLayout_10->addWidget(label_36, 4, 0, 1, 1);


        gridLayout_11->addWidget(groupBox_4, 11, 0, 1, 2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_14 = new QLabel(groupBoxPropertiesObj);
        label_14->setObjectName(QStringLiteral("label_14"));

        horizontalLayout_4->addWidget(label_14);

        shiniMaterial = new QDoubleSpinBox(groupBoxPropertiesObj);
        shiniMaterial->setObjectName(QStringLiteral("shiniMaterial"));
        shiniMaterial->setDecimals(3);
        shiniMaterial->setMaximum(1);
        shiniMaterial->setSingleStep(0.05);

        horizontalLayout_4->addWidget(shiniMaterial);


        gridLayout_11->addLayout(horizontalLayout_4, 9, 0, 1, 2);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setSizeConstraint(QLayout::SetMinimumSize);
        rotx = new QSpinBox(groupBoxPropertiesObj);
        rotx->setObjectName(QStringLiteral("rotx"));
        rotx->setAlignment(Qt::AlignCenter);
        rotx->setMinimum(0);
        rotx->setMaximum(360);

        verticalLayout_4->addWidget(rotx);

        roty = new QSpinBox(groupBoxPropertiesObj);
        roty->setObjectName(QStringLiteral("roty"));
        roty->setAlignment(Qt::AlignCenter);
        roty->setMinimum(0);
        roty->setMaximum(360);

        verticalLayout_4->addWidget(roty);

        rotz = new QSpinBox(groupBoxPropertiesObj);
        rotz->setObjectName(QStringLiteral("rotz"));
        rotz->setAlignment(Qt::AlignCenter);
        rotz->setMinimum(0);
        rotz->setMaximum(360);

        verticalLayout_4->addWidget(rotz);


        gridLayout_11->addLayout(verticalLayout_4, 6, 0, 1, 1);

        horizontalLayout_19 = new QHBoxLayout();
        horizontalLayout_19->setSpacing(6);
        horizontalLayout_19->setObjectName(QStringLiteral("horizontalLayout_19"));
        label_16 = new QLabel(groupBoxPropertiesObj);
        label_16->setObjectName(QStringLiteral("label_16"));

        horizontalLayout_19->addWidget(label_16);

        label_15 = new QLabel(groupBoxPropertiesObj);
        label_15->setObjectName(QStringLiteral("label_15"));

        horizontalLayout_19->addWidget(label_15);

        label_17 = new QLabel(groupBoxPropertiesObj);
        label_17->setObjectName(QStringLiteral("label_17"));

        horizontalLayout_19->addWidget(label_17);


        gridLayout_11->addLayout(horizontalLayout_19, 7, 0, 1, 2);

        label_11 = new QLabel(groupBoxPropertiesObj);
        label_11->setObjectName(QStringLiteral("label_11"));

        gridLayout_11->addWidget(label_11, 3, 0, 1, 1);

        deleteObj = new QPushButton(groupBoxPropertiesObj);
        deleteObj->setObjectName(QStringLiteral("deleteObj"));

        gridLayout_11->addWidget(deleteObj, 14, 0, 1, 2);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(0);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        scalex = new QDoubleSpinBox(groupBoxPropertiesObj);
        scalex->setObjectName(QStringLiteral("scalex"));
        scalex->setAlignment(Qt::AlignCenter);
        scalex->setMinimum(0);
        scalex->setMaximum(9999);
        scalex->setSingleStep(0.5);
        scalex->setValue(0);

        verticalLayout_5->addWidget(scalex);

        scaley = new QDoubleSpinBox(groupBoxPropertiesObj);
        scaley->setObjectName(QStringLiteral("scaley"));
        scaley->setAlignment(Qt::AlignCenter);
        scaley->setMinimum(0);
        scaley->setMaximum(9999);
        scaley->setSingleStep(0.5);
        scaley->setValue(0);

        verticalLayout_5->addWidget(scaley);

        scalez = new QDoubleSpinBox(groupBoxPropertiesObj);
        scalez->setObjectName(QStringLiteral("scalez"));
        scalez->setAlignment(Qt::AlignCenter);
        scalez->setMinimum(0);
        scalez->setMaximum(9999);
        scalez->setSingleStep(0.5);
        scalez->setValue(0);

        verticalLayout_5->addWidget(scalez);


        gridLayout_11->addLayout(verticalLayout_5, 6, 1, 1, 1);

        groupBox_6 = new QGroupBox(groupBoxPropertiesObj);
        groupBox_6->setObjectName(QStringLiteral("groupBox_6"));
        groupBox_6->setFont(font);
        gridLayout_13 = new QGridLayout(groupBox_6);
        gridLayout_13->setSpacing(1);
        gridLayout_13->setContentsMargins(11, 11, 11, 11);
        gridLayout_13->setObjectName(QStringLiteral("gridLayout_13"));
        onScreenImage = new QGraphicsView(groupBox_6);
        onScreenImage->setObjectName(QStringLiteral("onScreenImage"));

        gridLayout_13->addWidget(onScreenImage, 3, 0, 1, 1);

        loadBump = new QPushButton(groupBox_6);
        loadBump->setObjectName(QStringLiteral("loadBump"));

        gridLayout_13->addWidget(loadBump, 4, 0, 1, 1);

        loadTexture = new QPushButton(groupBox_6);
        loadTexture->setObjectName(QStringLiteral("loadTexture"));

        gridLayout_13->addWidget(loadTexture, 0, 0, 1, 1);

        enableTexture = new QCheckBox(groupBox_6);
        enableTexture->setObjectName(QStringLiteral("enableTexture"));

        gridLayout_13->addWidget(enableTexture, 2, 0, 1, 1);

        enableBump = new QCheckBox(groupBox_6);
        enableBump->setObjectName(QStringLiteral("enableBump"));

        gridLayout_13->addWidget(enableBump, 5, 0, 1, 1);

        onScreenImageBump = new QGraphicsView(groupBox_6);
        onScreenImageBump->setObjectName(QStringLiteral("onScreenImageBump"));

        gridLayout_13->addWidget(onScreenImageBump, 6, 0, 1, 1);

        choiceTexture = new QComboBox(groupBox_6);
        choiceTexture->setObjectName(QStringLiteral("choiceTexture"));

        gridLayout_13->addWidget(choiceTexture, 1, 0, 1, 1);

        loadTexture->raise();
        onScreenImage->raise();
        enableTexture->raise();
        loadBump->raise();
        enableBump->raise();
        onScreenImageBump->raise();
        choiceTexture->raise();

        gridLayout_11->addWidget(groupBox_6, 12, 0, 1, 2);


        verticalLayout_2->addWidget(groupBoxPropertiesObj);

        scrollObject->setWidget(scrollAreaWidgetContents);

        gridLayout_9->addWidget(scrollObject, 0, 0, 1, 1);

        scrollLight = new QScrollArea(centralWidget);
        scrollLight->setObjectName(QStringLiteral("scrollLight"));
        scrollLight->setMinimumSize(QSize(250, 0));
        scrollLight->setMaximumSize(QSize(250, 16777215));
        scrollLight->setWidgetResizable(true);
        scrollAreaWidgetContents_4 = new QWidget();
        scrollAreaWidgetContents_4->setObjectName(QStringLiteral("scrollAreaWidgetContents_4"));
        scrollAreaWidgetContents_4->setGeometry(QRect(0, 0, 254, 672));
        formLayout = new QFormLayout(scrollAreaWidgetContents_4);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        groupBoxPropertieLight = new QGroupBox(scrollAreaWidgetContents_4);
        groupBoxPropertieLight->setObjectName(QStringLiteral("groupBoxPropertieLight"));
        groupBoxPropertieLight->setMinimumSize(QSize(230, 0));
        groupBoxPropertieLight->setMaximumSize(QSize(230, 16777215));
        groupBoxPropertieLight->setFont(font);
        groupBoxPropertieLight->setStyleSheet(QLatin1String("QGroupBox::title { \n"
"   \n"
"     subcontrol-position: top left; /* position at the top left*/ \n"
"  padding: 2px 13px;\n"
"   margin-top: -5px;\n"
"    \n"
" }\n"
"\n"
"QGroupBox{\n"
"   border: 1px solid rgb(182, 181, 179);\n"
"  border-radius: 5px;\n"
"}"));
        verticalLayout_8 = new QVBoxLayout(groupBoxPropertieLight);
        verticalLayout_8->setSpacing(2);
        verticalLayout_8->setContentsMargins(11, 11, 11, 11);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        verticalLayout_8->setContentsMargins(2, 1, 1, 3);
        nameLightLayout = new QFrame(groupBoxPropertieLight);
        nameLightLayout->setObjectName(QStringLiteral("nameLightLayout"));
        verticalLayout_7 = new QVBoxLayout(nameLightLayout);
        verticalLayout_7->setSpacing(1);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(0, 5, 0, 0);
        label_20 = new QLabel(nameLightLayout);
        label_20->setObjectName(QStringLiteral("label_20"));

        verticalLayout_7->addWidget(label_20);

        nameLight = new QLineEdit(nameLightLayout);
        nameLight->setObjectName(QStringLiteral("nameLight"));

        verticalLayout_7->addWidget(nameLight);


        verticalLayout_8->addWidget(nameLightLayout);

        optionLayout = new QHBoxLayout();
        optionLayout->setSpacing(0);
        optionLayout->setObjectName(QStringLiteral("optionLayout"));
        selectedLight = new QCheckBox(groupBoxPropertieLight);
        selectedLight->setObjectName(QStringLiteral("selectedLight"));
        selectedLight->setTristate(false);

        optionLayout->addWidget(selectedLight);

        visibleLight = new QCheckBox(groupBoxPropertieLight);
        visibleLight->setObjectName(QStringLiteral("visibleLight"));

        optionLayout->addWidget(visibleLight);

        enableLight = new QCheckBox(groupBoxPropertieLight);
        enableLight->setObjectName(QStringLiteral("enableLight"));

        optionLayout->addWidget(enableLight);


        verticalLayout_8->addLayout(optionLayout);

        orientationLight = new QFrame(groupBoxPropertieLight);
        orientationLight->setObjectName(QStringLiteral("orientationLight"));
        gridLayout_7 = new QGridLayout(orientationLight);
        gridLayout_7->setSpacing(6);
        gridLayout_7->setContentsMargins(11, 11, 11, 11);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        gridLayout_7->setHorizontalSpacing(1);
        gridLayout_7->setContentsMargins(0, 0, 0, 0);
        positionLayoutLight = new QFrame(orientationLight);
        positionLayoutLight->setObjectName(QStringLiteral("positionLayoutLight"));
        positionLayout = new QVBoxLayout(positionLayoutLight);
        positionLayout->setSpacing(1);
        positionLayout->setContentsMargins(11, 11, 11, 11);
        positionLayout->setObjectName(QStringLiteral("positionLayout"));
        positionLayout->setContentsMargins(0, 0, 0, 0);
        label_21 = new QLabel(positionLayoutLight);
        label_21->setObjectName(QStringLiteral("label_21"));

        positionLayout->addWidget(label_21);

        positionxLight = new QDoubleSpinBox(positionLayoutLight);
        positionxLight->setObjectName(QStringLiteral("positionxLight"));
        positionxLight->setMinimum(-5000);
        positionxLight->setMaximum(5000);

        positionLayout->addWidget(positionxLight);

        positionyLight = new QDoubleSpinBox(positionLayoutLight);
        positionyLight->setObjectName(QStringLiteral("positionyLight"));
        positionyLight->setMinimum(-5000);
        positionyLight->setMaximum(5000);

        positionLayout->addWidget(positionyLight);

        positionzLight = new QDoubleSpinBox(positionLayoutLight);
        positionzLight->setObjectName(QStringLiteral("positionzLight"));
        positionzLight->setMinimum(-5000);
        positionzLight->setMaximum(5000);

        positionLayout->addWidget(positionzLight);


        gridLayout_7->addWidget(positionLayoutLight, 0, 0, 1, 1);

        directionLayoutLight = new QFrame(orientationLight);
        directionLayoutLight->setObjectName(QStringLiteral("directionLayoutLight"));
        directionLayout = new QVBoxLayout(directionLayoutLight);
        directionLayout->setSpacing(1);
        directionLayout->setContentsMargins(11, 11, 11, 11);
        directionLayout->setObjectName(QStringLiteral("directionLayout"));
        directionLayout->setContentsMargins(0, 0, 0, 0);
        label_22 = new QLabel(directionLayoutLight);
        label_22->setObjectName(QStringLiteral("label_22"));

        directionLayout->addWidget(label_22);

        directionxLight = new QDoubleSpinBox(directionLayoutLight);
        directionxLight->setObjectName(QStringLiteral("directionxLight"));
        directionxLight->setMinimum(-5000);
        directionxLight->setMaximum(5000);

        directionLayout->addWidget(directionxLight);

        directionyLight = new QDoubleSpinBox(directionLayoutLight);
        directionyLight->setObjectName(QStringLiteral("directionyLight"));
        directionyLight->setMinimum(-5000);
        directionyLight->setMaximum(5000);

        directionLayout->addWidget(directionyLight);

        directionzLight = new QDoubleSpinBox(directionLayoutLight);
        directionzLight->setObjectName(QStringLiteral("directionzLight"));
        directionzLight->setMinimum(-5000);
        directionzLight->setMaximum(5000);

        directionLayout->addWidget(directionzLight);


        gridLayout_7->addWidget(directionLayoutLight, 0, 1, 1, 1);


        verticalLayout_8->addWidget(orientationLight);

        energyFrame = new QFrame(groupBoxPropertieLight);
        energyFrame->setObjectName(QStringLiteral("energyFrame"));
        energyLayout = new QHBoxLayout(energyFrame);
        energyLayout->setSpacing(6);
        energyLayout->setContentsMargins(11, 11, 11, 11);
        energyLayout->setObjectName(QStringLiteral("energyLayout"));
        label_44 = new QLabel(energyFrame);
        label_44->setObjectName(QStringLiteral("label_44"));

        energyLayout->addWidget(label_44);

        energyLight = new QSpinBox(energyFrame);
        energyLight->setObjectName(QStringLiteral("energyLight"));
        energyLight->setMaximum(10000000);
        energyLight->setSingleStep(50);

        energyLayout->addWidget(energyLight);


        verticalLayout_8->addWidget(energyFrame);

        vectorsLayoutLight = new QFrame(groupBoxPropertieLight);
        vectorsLayoutLight->setObjectName(QStringLiteral("vectorsLayoutLight"));
        vectorsLayout = new QVBoxLayout(vectorsLayoutLight);
        vectorsLayout->setSpacing(1);
        vectorsLayout->setContentsMargins(11, 11, 11, 11);
        vectorsLayout->setObjectName(QStringLiteral("vectorsLayout"));
        vectorsLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        label_24 = new QLabel(vectorsLayoutLight);
        label_24->setObjectName(QStringLiteral("label_24"));

        verticalLayout_9->addWidget(label_24);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(1);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        vecAx = new QDoubleSpinBox(vectorsLayoutLight);
        vecAx->setObjectName(QStringLiteral("vecAx"));
        vecAx->setMinimum(-5000);
        vecAx->setMaximum(5000);

        horizontalLayout_10->addWidget(vecAx);

        vecAy = new QDoubleSpinBox(vectorsLayoutLight);
        vecAy->setObjectName(QStringLiteral("vecAy"));
        vecAy->setMinimum(-5000);
        vecAy->setMaximum(5000);

        horizontalLayout_10->addWidget(vecAy);

        vecAz = new QDoubleSpinBox(vectorsLayoutLight);
        vecAz->setObjectName(QStringLiteral("vecAz"));
        vecAz->setMinimum(-5000);
        vecAz->setMaximum(5000);

        horizontalLayout_10->addWidget(vecAz);


        verticalLayout_9->addLayout(horizontalLayout_10);


        vectorsLayout->addLayout(verticalLayout_9);

        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));
        label_25 = new QLabel(vectorsLayoutLight);
        label_25->setObjectName(QStringLiteral("label_25"));

        verticalLayout_10->addWidget(label_25);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(1);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        vecBx = new QDoubleSpinBox(vectorsLayoutLight);
        vecBx->setObjectName(QStringLiteral("vecBx"));
        vecBx->setMinimum(-5000);
        vecBx->setMaximum(5000);

        horizontalLayout_11->addWidget(vecBx);

        vecBy = new QDoubleSpinBox(vectorsLayoutLight);
        vecBy->setObjectName(QStringLiteral("vecBy"));
        vecBy->setMinimum(-5000);
        vecBy->setMaximum(5000);

        horizontalLayout_11->addWidget(vecBy);

        vecBz = new QDoubleSpinBox(vectorsLayoutLight);
        vecBz->setObjectName(QStringLiteral("vecBz"));
        vecBz->setMinimum(-5000);
        vecBz->setMaximum(5000);

        horizontalLayout_11->addWidget(vecBz);


        verticalLayout_10->addLayout(horizontalLayout_11);


        vectorsLayout->addLayout(verticalLayout_10);


        verticalLayout_8->addWidget(vectorsLayoutLight);

        attenuationLayoutLight = new QFrame(groupBoxPropertieLight);
        attenuationLayoutLight->setObjectName(QStringLiteral("attenuationLayoutLight"));
        attenuationLayout = new QVBoxLayout(attenuationLayoutLight);
        attenuationLayout->setSpacing(2);
        attenuationLayout->setContentsMargins(11, 11, 11, 11);
        attenuationLayout->setObjectName(QStringLiteral("attenuationLayout"));
        attenuationLayout->setContentsMargins(0, 0, 0, 0);
        label_23 = new QLabel(attenuationLayoutLight);
        label_23->setObjectName(QStringLiteral("label_23"));

        attenuationLayout->addWidget(label_23);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(1);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        attenuationcLight = new QDoubleSpinBox(attenuationLayoutLight);
        attenuationcLight->setObjectName(QStringLiteral("attenuationcLight"));
        attenuationcLight->setMinimum(-5000);
        attenuationcLight->setMaximum(5000);

        horizontalLayout_9->addWidget(attenuationcLight);

        attenuationlLight = new QDoubleSpinBox(attenuationLayoutLight);
        attenuationlLight->setObjectName(QStringLiteral("attenuationlLight"));
        attenuationlLight->setMinimum(-5000);
        attenuationlLight->setMaximum(5000);

        horizontalLayout_9->addWidget(attenuationlLight);

        attenuationqLight = new QDoubleSpinBox(attenuationLayoutLight);
        attenuationqLight->setObjectName(QStringLiteral("attenuationqLight"));
        attenuationqLight->setMinimum(-5000);
        attenuationqLight->setMaximum(5000);

        horizontalLayout_9->addWidget(attenuationqLight);


        attenuationLayout->addLayout(horizontalLayout_9);


        verticalLayout_8->addWidget(attenuationLayoutLight);

        ADSLight = new QFrame(groupBoxPropertieLight);
        ADSLight->setObjectName(QStringLiteral("ADSLight"));
        horizontalLayout = new QHBoxLayout(ADSLight);
        horizontalLayout->setSpacing(2);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        ambienteProperty = new QFrame(ADSLight);
        ambienteProperty->setObjectName(QStringLiteral("ambienteProperty"));
        verticalLayout_11 = new QVBoxLayout(ambienteProperty);
        verticalLayout_11->setSpacing(6);
        verticalLayout_11->setContentsMargins(11, 11, 11, 11);
        verticalLayout_11->setObjectName(QStringLiteral("verticalLayout_11"));
        verticalLayout_11->setContentsMargins(1, 1, 1, 1);
        label_26 = new QLabel(ambienteProperty);
        label_26->setObjectName(QStringLiteral("label_26"));

        verticalLayout_11->addWidget(label_26);

        ambMaterial_2 = new QPushButton(ambienteProperty);
        ambMaterial_2->setObjectName(QStringLiteral("ambMaterial_2"));
        ambMaterial_2->setAutoFillBackground(true);
        ambMaterial_2->setFlat(false);

        verticalLayout_11->addWidget(ambMaterial_2);


        horizontalLayout->addWidget(ambienteProperty);

        diffuseProperty = new QFrame(ADSLight);
        diffuseProperty->setObjectName(QStringLiteral("diffuseProperty"));
        verticalLayout_12 = new QVBoxLayout(diffuseProperty);
        verticalLayout_12->setSpacing(6);
        verticalLayout_12->setContentsMargins(11, 11, 11, 11);
        verticalLayout_12->setObjectName(QStringLiteral("verticalLayout_12"));
        verticalLayout_12->setContentsMargins(1, 1, 1, 1);
        label_27 = new QLabel(diffuseProperty);
        label_27->setObjectName(QStringLiteral("label_27"));

        verticalLayout_12->addWidget(label_27);

        diffMaterial_2 = new QPushButton(diffuseProperty);
        diffMaterial_2->setObjectName(QStringLiteral("diffMaterial_2"));

        verticalLayout_12->addWidget(diffMaterial_2);


        horizontalLayout->addWidget(diffuseProperty);

        specularProperty = new QFrame(ADSLight);
        specularProperty->setObjectName(QStringLiteral("specularProperty"));
        specularProperty->setAutoFillBackground(false);
        verticalLayoutSpe = new QVBoxLayout(specularProperty);
        verticalLayoutSpe->setSpacing(6);
        verticalLayoutSpe->setContentsMargins(11, 11, 11, 11);
        verticalLayoutSpe->setObjectName(QStringLiteral("verticalLayoutSpe"));
        verticalLayoutSpe->setContentsMargins(1, 1, 1, 1);
        label_28 = new QLabel(specularProperty);
        label_28->setObjectName(QStringLiteral("label_28"));

        verticalLayoutSpe->addWidget(label_28);

        speMaterial_2 = new QPushButton(specularProperty);
        speMaterial_2->setObjectName(QStringLiteral("speMaterial_2"));

        verticalLayoutSpe->addWidget(speMaterial_2);


        horizontalLayout->addWidget(specularProperty);


        verticalLayout_8->addWidget(ADSLight);

        angleSpotLayoutLight = new QFrame(groupBoxPropertieLight);
        angleSpotLayoutLight->setObjectName(QStringLiteral("angleSpotLayoutLight"));
        angleSpotLayout = new QVBoxLayout(angleSpotLayoutLight);
        angleSpotLayout->setSpacing(1);
        angleSpotLayout->setContentsMargins(11, 11, 11, 11);
        angleSpotLayout->setObjectName(QStringLiteral("angleSpotLayout"));
        angleSpotLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setSpacing(6);
        horizontalLayout_14->setObjectName(QStringLiteral("horizontalLayout_14"));
        label_29 = new QLabel(angleSpotLayoutLight);
        label_29->setObjectName(QStringLiteral("label_29"));

        horizontalLayout_14->addWidget(label_29);

        anglespotLight = new QSpinBox(angleSpotLayoutLight);
        anglespotLight->setObjectName(QStringLiteral("anglespotLight"));
        anglespotLight->setMaximum(180);

        horizontalLayout_14->addWidget(anglespotLight);


        angleSpotLayout->addLayout(horizontalLayout_14);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setSpacing(6);
        horizontalLayout_15->setObjectName(QStringLiteral("horizontalLayout_15"));
        label_30 = new QLabel(angleSpotLayoutLight);
        label_30->setObjectName(QStringLiteral("label_30"));

        horizontalLayout_15->addWidget(label_30);

        anglespotinnerLight = new QSpinBox(angleSpotLayoutLight);
        anglespotinnerLight->setObjectName(QStringLiteral("anglespotinnerLight"));
        anglespotinnerLight->setMaximum(180);

        horizontalLayout_15->addWidget(anglespotinnerLight);


        angleSpotLayout->addLayout(horizontalLayout_15);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setSpacing(6);
        horizontalLayout_16->setObjectName(QStringLiteral("horizontalLayout_16"));
        label_31 = new QLabel(angleSpotLayoutLight);
        label_31->setObjectName(QStringLiteral("label_31"));

        horizontalLayout_16->addWidget(label_31);

        exponentSpotLight = new QSpinBox(angleSpotLayoutLight);
        exponentSpotLight->setObjectName(QStringLiteral("exponentSpotLight"));
        exponentSpotLight->setMaximum(128);

        horizontalLayout_16->addWidget(exponentSpotLight);


        angleSpotLayout->addLayout(horizontalLayout_16);


        verticalLayout_8->addWidget(angleSpotLayoutLight);

        deleteLight = new QPushButton(groupBoxPropertieLight);
        deleteLight->setObjectName(QStringLiteral("deleteLight"));

        verticalLayout_8->addWidget(deleteLight);


        formLayout->setWidget(0, QFormLayout::LabelRole, groupBoxPropertieLight);

        scrollLight->setWidget(scrollAreaWidgetContents_4);

        gridLayout_9->addWidget(scrollLight, 0, 1, 1, 1);

        frame_3 = new QFrame(centralWidget);
        frame_3->setObjectName(QStringLiteral("frame_3"));
        frame_3->setFrameShape(QFrame::NoFrame);
        frame_3->setFrameShadow(QFrame::Plain);
        gridLayout_2 = new QGridLayout(frame_3);
        gridLayout_2->setSpacing(0);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        tabWidget = new QTabWidget(frame_3);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setStyleSheet(QStringLiteral(""));
        tabWidget->setTabPosition(QTabWidget::North);
        tabWidget->setTabShape(QTabWidget::Rounded);
        tabOpenGL = new QWidget();
        tabOpenGL->setObjectName(QStringLiteral("tabOpenGL"));
        gridLayout_3 = new QGridLayout(tabOpenGL);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        widgetOpenGL = new GLWidget(tabOpenGL);
        widgetOpenGL->setObjectName(QStringLiteral("widgetOpenGL"));

        gridLayout_3->addWidget(widgetOpenGL, 0, 0, 1, 1);

        tabWidget->addTab(tabOpenGL, QString());
        tabRender = new QWidget();
        tabRender->setObjectName(QStringLiteral("tabRender"));
        gridLayout_6 = new QGridLayout(tabRender);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        graphicsRender = new QGraphicsView(tabRender);
        graphicsRender->setObjectName(QStringLiteral("graphicsRender"));

        gridLayout_6->addWidget(graphicsRender, 0, 0, 1, 1);

        tabWidget->addTab(tabRender, QString());

        gridLayout_2->addWidget(tabWidget, 0, 0, 1, 1);


        gridLayout_9->addWidget(frame_3, 0, 2, 1, 1);

        scrollArea_3 = new QScrollArea(centralWidget);
        scrollArea_3->setObjectName(QStringLiteral("scrollArea_3"));
        scrollArea_3->setMinimumSize(QSize(250, 0));
        scrollArea_3->setMaximumSize(QSize(250, 16777215));
        scrollArea_3->setStyleSheet(QStringLiteral(""));
        scrollArea_3->setFrameShape(QFrame::StyledPanel);
        scrollArea_3->setFrameShadow(QFrame::Plain);
        scrollArea_3->setLineWidth(2);
        scrollArea_3->setWidgetResizable(true);
        scrollAreaWidgetContents_3 = new QWidget();
        scrollAreaWidgetContents_3->setObjectName(QStringLiteral("scrollAreaWidgetContents_3"));
        scrollAreaWidgetContents_3->setGeometry(QRect(0, 0, 248, 688));
        gridLayout_4 = new QGridLayout(scrollAreaWidgetContents_3);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        toolBox = new QToolBox(scrollAreaWidgetContents_3);
        toolBox->setObjectName(QStringLiteral("toolBox"));
        toolBox->setStyleSheet(QStringLiteral(""));
        toolBox->setFrameShape(QFrame::NoFrame);
        toolBox->setFrameShadow(QFrame::Sunken);
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        page->setGeometry(QRect(0, 0, 230, 515));
        gridLayout_5 = new QGridLayout(page);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        objects_list = new QListWidget(page);
        objects_list->setObjectName(QStringLiteral("objects_list"));

        gridLayout_5->addWidget(objects_list, 0, 0, 1, 1);

        toolBox->addItem(page, QStringLiteral("Objects"));
        page_3 = new QWidget();
        page_3->setObjectName(QStringLiteral("page_3"));
        page_3->setGeometry(QRect(0, 0, 230, 515));
        gridLayout_8 = new QGridLayout(page_3);
        gridLayout_8->setSpacing(6);
        gridLayout_8->setContentsMargins(11, 11, 11, 11);
        gridLayout_8->setObjectName(QStringLiteral("gridLayout_8"));
        lights_list = new QListWidget(page_3);
        lights_list->setObjectName(QStringLiteral("lights_list"));

        gridLayout_8->addWidget(lights_list, 0, 0, 1, 1);

        toolBox->addItem(page_3, QStringLiteral("Lights"));
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        page_2->setGeometry(QRect(0, 0, 230, 515));
        showHBB = new QCheckBox(page_2);
        showHBB->setObjectName(QStringLiteral("showHBB"));
        showHBB->setGeometry(QRect(0, 0, 219, 22));
        groupBox_5 = new QGroupBox(page_2);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        groupBox_5->setGeometry(QRect(0, 20, 221, 84));
        groupBox_5->setFont(font);
        groupBox_5->setStyleSheet(QLatin1String("QGroupBox::title { \n"
"   \n"
"     subcontrol-position: top left; /* position at the top left*/ \n"
"  padding: 2px 13px;\n"
"   margin-top: -5px;\n"
"    \n"
" }\n"
"\n"
"QGroupBox{\n"
"   border: 1px solid rgb(182, 181, 179);\n"
"  border-radius: 5px;\n"
"}"));
        gridLayout_12 = new QGridLayout(groupBox_5);
        gridLayout_12->setSpacing(6);
        gridLayout_12->setContentsMargins(11, 11, 11, 11);
        gridLayout_12->setObjectName(QStringLiteral("gridLayout_12"));
        horizontalLayout_21 = new QHBoxLayout();
        horizontalLayout_21->setSpacing(6);
        horizontalLayout_21->setObjectName(QStringLiteral("horizontalLayout_21"));
        label_37 = new QLabel(groupBox_5);
        label_37->setObjectName(QStringLiteral("label_37"));

        horizontalLayout_21->addWidget(label_37);

        radiusDOF = new QDoubleSpinBox(groupBox_5);
        radiusDOF->setObjectName(QStringLiteral("radiusDOF"));

        horizontalLayout_21->addWidget(radiusDOF);


        gridLayout_12->addLayout(horizontalLayout_21, 0, 0, 1, 1);

        horizontalLayout_20 = new QHBoxLayout();
        horizontalLayout_20->setSpacing(6);
        horizontalLayout_20->setObjectName(QStringLiteral("horizontalLayout_20"));
        label_38 = new QLabel(groupBox_5);
        label_38->setObjectName(QStringLiteral("label_38"));

        horizontalLayout_20->addWidget(label_38);

        focalDOF = new QDoubleSpinBox(groupBox_5);
        focalDOF->setObjectName(QStringLiteral("focalDOF"));

        horizontalLayout_20->addWidget(focalDOF);


        gridLayout_12->addLayout(horizontalLayout_20, 1, 0, 1, 1);

        toolBox->addItem(page_2, QStringLiteral("Scene"));
        page_5 = new QWidget();
        page_5->setObjectName(QStringLiteral("page_5"));
        page_5->setGeometry(QRect(0, 0, 230, 515));
        gridLayout_15 = new QGridLayout(page_5);
        gridLayout_15->setSpacing(6);
        gridLayout_15->setContentsMargins(11, 11, 11, 11);
        gridLayout_15->setObjectName(QStringLiteral("gridLayout_15"));
        verticalLayout_14 = new QVBoxLayout();
        verticalLayout_14->setSpacing(2);
        verticalLayout_14->setObjectName(QStringLiteral("verticalLayout_14"));
        formLayout_3 = new QFormLayout();
        formLayout_3->setSpacing(6);
        formLayout_3->setObjectName(QStringLiteral("formLayout_3"));
        label_39 = new QLabel(page_5);
        label_39->setObjectName(QStringLiteral("label_39"));

        formLayout_3->setWidget(0, QFormLayout::LabelRole, label_39);

        sizePhotons = new QSpinBox(page_5);
        sizePhotons->setObjectName(QStringLiteral("sizePhotons"));
        sizePhotons->setMaximum(1000000);

        formLayout_3->setWidget(0, QFormLayout::FieldRole, sizePhotons);


        verticalLayout_14->addLayout(formLayout_3);

        horizontalLayout_23 = new QHBoxLayout();
        horizontalLayout_23->setSpacing(6);
        horizontalLayout_23->setObjectName(QStringLiteral("horizontalLayout_23"));
        label_40 = new QLabel(page_5);
        label_40->setObjectName(QStringLiteral("label_40"));

        horizontalLayout_23->addWidget(label_40);

        radiusGlobal = new QDoubleSpinBox(page_5);
        radiusGlobal->setObjectName(QStringLiteral("radiusGlobal"));
        radiusGlobal->setDecimals(3);
        radiusGlobal->setMaximum(30);
        radiusGlobal->setValue(0.75);

        horizontalLayout_23->addWidget(radiusGlobal);


        verticalLayout_14->addLayout(horizontalLayout_23);

        horizontalLayout_28 = new QHBoxLayout();
        horizontalLayout_28->setSpacing(6);
        horizontalLayout_28->setObjectName(QStringLiteral("horizontalLayout_28"));
        label_46 = new QLabel(page_5);
        label_46->setObjectName(QStringLiteral("label_46"));

        horizontalLayout_28->addWidget(label_46);

        nearsGlobal = new QSpinBox(page_5);
        nearsGlobal->setObjectName(QStringLiteral("nearsGlobal"));
        nearsGlobal->setMaximum(2000);
        nearsGlobal->setValue(100);

        horizontalLayout_28->addWidget(nearsGlobal);


        verticalLayout_14->addLayout(horizontalLayout_28);

        horizontalLayout_25 = new QHBoxLayout();
        horizontalLayout_25->setSpacing(6);
        horizontalLayout_25->setObjectName(QStringLiteral("horizontalLayout_25"));
        label_42 = new QLabel(page_5);
        label_42->setObjectName(QStringLiteral("label_42"));

        horizontalLayout_25->addWidget(label_42);

        sizePhotonsCaustic = new QSpinBox(page_5);
        sizePhotonsCaustic->setObjectName(QStringLiteral("sizePhotonsCaustic"));
        sizePhotonsCaustic->setMaximum(1000000);

        horizontalLayout_25->addWidget(sizePhotonsCaustic);


        verticalLayout_14->addLayout(horizontalLayout_25);

        horizontalLayout_24 = new QHBoxLayout();
        horizontalLayout_24->setSpacing(6);
        horizontalLayout_24->setObjectName(QStringLiteral("horizontalLayout_24"));
        label_41 = new QLabel(page_5);
        label_41->setObjectName(QStringLiteral("label_41"));

        horizontalLayout_24->addWidget(label_41);

        radiusCaustic = new QDoubleSpinBox(page_5);
        radiusCaustic->setObjectName(QStringLiteral("radiusCaustic"));
        radiusCaustic->setDecimals(3);
        radiusCaustic->setMaximum(30);
        radiusCaustic->setValue(0.15);

        horizontalLayout_24->addWidget(radiusCaustic);


        verticalLayout_14->addLayout(horizontalLayout_24);

        horizontalLayout_27 = new QHBoxLayout();
        horizontalLayout_27->setSpacing(6);
        horizontalLayout_27->setObjectName(QStringLiteral("horizontalLayout_27"));
        label_45 = new QLabel(page_5);
        label_45->setObjectName(QStringLiteral("label_45"));

        horizontalLayout_27->addWidget(label_45);

        nearsCaustics = new QSpinBox(page_5);
        nearsCaustics->setObjectName(QStringLiteral("nearsCaustics"));
        nearsCaustics->setMaximum(2000);
        nearsCaustics->setValue(60);

        horizontalLayout_27->addWidget(nearsCaustics);


        verticalLayout_14->addLayout(horizontalLayout_27);

        horizontalLayout_26 = new QHBoxLayout();
        horizontalLayout_26->setSpacing(6);
        horizontalLayout_26->setObjectName(QStringLiteral("horizontalLayout_26"));
        label_43 = new QLabel(page_5);
        label_43->setObjectName(QStringLiteral("label_43"));

        horizontalLayout_26->addWidget(label_43);

        depthPhoton = new QSpinBox(page_5);
        depthPhoton->setObjectName(QStringLiteral("depthPhoton"));
        depthPhoton->setValue(4);

        horizontalLayout_26->addWidget(depthPhoton);


        verticalLayout_14->addLayout(horizontalLayout_26);


        gridLayout_15->addLayout(verticalLayout_14, 0, 0, 1, 1);

        groupBox_7 = new QGroupBox(page_5);
        groupBox_7->setObjectName(QStringLiteral("groupBox_7"));
        groupBox_7->setFont(font);
        groupBox_7->setStyleSheet(QLatin1String("QGroupBox::title { \n"
"   \n"
"     subcontrol-position: top left; /* position at the top left*/ \n"
"  padding: 2px 13px;\n"
"   margin-top: -5px;\n"
"    \n"
" }\n"
"\n"
"QGroupBox{\n"
"   border: 1px solid rgb(182, 181, 179);\n"
"  border-radius: 5px;\n"
"}"));
        gridLayout_16 = new QGridLayout(groupBox_7);
        gridLayout_16->setSpacing(6);
        gridLayout_16->setContentsMargins(11, 11, 11, 11);
        gridLayout_16->setObjectName(QStringLiteral("gridLayout_16"));
        gridLayout_16->setVerticalSpacing(2);
        enablePhotonMap = new QCheckBox(groupBox_7);
        enablePhotonMap->setObjectName(QStringLiteral("enablePhotonMap"));

        gridLayout_16->addWidget(enablePhotonMap, 0, 0, 1, 1);

        visiblePhotonMap = new QCheckBox(groupBox_7);
        visiblePhotonMap->setObjectName(QStringLiteral("visiblePhotonMap"));

        gridLayout_16->addWidget(visiblePhotonMap, 1, 0, 1, 1);

        visiblePhotonMapCaustics = new QCheckBox(groupBox_7);
        visiblePhotonMapCaustics->setObjectName(QStringLiteral("visiblePhotonMapCaustics"));

        gridLayout_16->addWidget(visiblePhotonMapCaustics, 2, 0, 1, 1);


        gridLayout_15->addWidget(groupBox_7, 1, 0, 1, 1);

        groupBox_8 = new QGroupBox(page_5);
        groupBox_8->setObjectName(QStringLiteral("groupBox_8"));
        groupBox_8->setFont(font);
        groupBox_8->setStyleSheet(QLatin1String("QGroupBox::title { \n"
"   \n"
"     subcontrol-position: top left; /* position at the top left*/ \n"
"  padding: 2px 13px;\n"
"   margin-top: -5px;\n"
"    \n"
" }\n"
"\n"
"QGroupBox{\n"
"   border: 1px solid rgb(182, 181, 179);\n"
"  border-radius: 5px;\n"
"}"));
        gridLayout_14 = new QGridLayout(groupBox_8);
        gridLayout_14->setSpacing(2);
        gridLayout_14->setContentsMargins(11, 11, 11, 11);
        gridLayout_14->setObjectName(QStringLiteral("gridLayout_14"));
        useFilter = new QCheckBox(groupBox_8);
        useFilter->setObjectName(QStringLiteral("useFilter"));
        QFont font1;
        font1.setBold(false);
        font1.setWeight(50);
        useFilter->setFont(font1);

        gridLayout_14->addWidget(useFilter, 0, 0, 1, 1);

        renderCaustics = new QCheckBox(groupBox_8);
        renderCaustics->setObjectName(QStringLiteral("renderCaustics"));
        renderCaustics->setFont(font1);

        gridLayout_14->addWidget(renderCaustics, 2, 0, 1, 1);

        renderGlobal = new QCheckBox(groupBox_8);
        renderGlobal->setObjectName(QStringLiteral("renderGlobal"));

        gridLayout_14->addWidget(renderGlobal, 1, 0, 1, 1);


        gridLayout_15->addWidget(groupBox_8, 2, 0, 1, 1);

        toolBox->addItem(page_5, QStringLiteral("Photon Mapping"));
        page_4 = new QWidget();
        page_4->setObjectName(QStringLiteral("page_4"));
        page_4->setGeometry(QRect(0, 0, 230, 515));
        layoutWidget = new QWidget(page_4);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 10, 221, 129));
        verticalLayout_6 = new QVBoxLayout(layoutWidget);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_18 = new QLabel(layoutWidget);
        label_18->setObjectName(QStringLiteral("label_18"));

        horizontalLayout_5->addWidget(label_18);

        numSamples = new QSpinBox(layoutWidget);
        numSamples->setObjectName(QStringLiteral("numSamples"));
        numSamples->setMinimum(1);
        numSamples->setMaximum(100000);

        horizontalLayout_5->addWidget(numSamples);


        verticalLayout_6->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_19 = new QLabel(layoutWidget);
        label_19->setObjectName(QStringLiteral("label_19"));

        horizontalLayout_6->addWidget(label_19);

        proportion = new QSpinBox(layoutWidget);
        proportion->setObjectName(QStringLiteral("proportion"));
        proportion->setMinimum(5);
        proportion->setMaximum(500);
        proportion->setSingleStep(5);
        proportion->setValue(100);

        horizontalLayout_6->addWidget(proportion);


        verticalLayout_6->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        btnRender = new QPushButton(layoutWidget);
        btnRender->setObjectName(QStringLiteral("btnRender"));
        btnRender->setMaximumSize(QSize(60, 16777215));

        horizontalLayout_7->addWidget(btnRender);

        progressRender = new QProgressBar(layoutWidget);
        progressRender->setObjectName(QStringLiteral("progressRender"));
        progressRender->setValue(0);

        horizontalLayout_7->addWidget(progressRender);


        verticalLayout_6->addLayout(horizontalLayout_7);

        toolBox->addItem(page_4, QStringLiteral("Render Options"));

        gridLayout_4->addWidget(toolBox, 0, 0, 1, 1);

        scrollArea_3->setWidget(scrollAreaWidgetContents_3);

        gridLayout_9->addWidget(scrollArea_3, 0, 3, 1, 1);


        verticalLayout->addLayout(gridLayout_9);

        scrollAreaBottom = new QScrollArea(centralWidget);
        scrollAreaBottom->setObjectName(QStringLiteral("scrollAreaBottom"));
        scrollAreaBottom->setMinimumSize(QSize(0, 100));
        scrollAreaBottom->setMaximumSize(QSize(16777215, 100));
        scrollAreaBottom->setFrameShape(QFrame::NoFrame);
        scrollAreaBottom->setFrameShadow(QFrame::Plain);
        scrollAreaBottom->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QStringLiteral("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 893, 100));
        groupBox = new QGroupBox(scrollAreaWidgetContents_2);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 321, 80));
        groupBox->setFont(font);
        groupBox->setStyleSheet(QLatin1String("QGroupBox::title { \n"
"   \n"
"     subcontrol-position: top left; /* position at the top left*/ \n"
"  padding: 2px 13px;\n"
"   margin-top: -5px;\n"
"    \n"
" }\n"
"\n"
"QGroupBox{\n"
"   border: 1px solid rgb(182, 181, 179);\n"
"  border-radius: 5px;\n"
"}"));
        dEyex = new QDoubleSpinBox(groupBox);
        dEyex->setObjectName(QStringLiteral("dEyex"));
        dEyex->setGeometry(QRect(70, 10, 78, 21));
        dEyex->setMinimum(-9000);
        dEyex->setMaximum(9000);
        dEyey = new QDoubleSpinBox(groupBox);
        dEyey->setObjectName(QStringLiteral("dEyey"));
        dEyey->setGeometry(QRect(150, 10, 78, 21));
        dEyey->setMinimum(-9000);
        dEyey->setMaximum(9000);
        dEyez = new QDoubleSpinBox(groupBox);
        dEyez->setObjectName(QStringLiteral("dEyez"));
        dEyez->setGeometry(QRect(230, 10, 78, 21));
        QFont font2;
        font2.setPointSize(11);
        dEyez->setFont(font2);
        dEyez->setMinimum(-9000);
        dEyez->setMaximum(9000);
        dAtx = new QDoubleSpinBox(groupBox);
        dAtx->setObjectName(QStringLiteral("dAtx"));
        dAtx->setGeometry(QRect(70, 30, 78, 21));
        dAtx->setMinimum(-9000);
        dAtx->setMaximum(9000);
        dAty = new QDoubleSpinBox(groupBox);
        dAty->setObjectName(QStringLiteral("dAty"));
        dAty->setGeometry(QRect(150, 30, 78, 21));
        dAty->setMinimum(-9000);
        dAty->setMaximum(9000);
        dAtz = new QDoubleSpinBox(groupBox);
        dAtz->setObjectName(QStringLiteral("dAtz"));
        dAtz->setGeometry(QRect(230, 30, 78, 21));
        dAtz->setMinimum(-9000);
        dAtz->setMaximum(9000);
        dUpx = new QDoubleSpinBox(groupBox);
        dUpx->setObjectName(QStringLiteral("dUpx"));
        dUpx->setGeometry(QRect(70, 50, 78, 21));
        dUpx->setMaximum(1);
        dUpy = new QDoubleSpinBox(groupBox);
        dUpy->setObjectName(QStringLiteral("dUpy"));
        dUpy->setGeometry(QRect(150, 50, 78, 21));
        dUpy->setMaximum(1);
        dUpz = new QDoubleSpinBox(groupBox);
        dUpz->setObjectName(QStringLiteral("dUpz"));
        dUpz->setGeometry(QRect(230, 50, 78, 21));
        dUpz->setMaximum(1);
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 10, 66, 17));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 30, 66, 17));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 50, 66, 17));
        groupBox_2 = new QGroupBox(scrollAreaWidgetContents_2);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(340, 10, 191, 80));
        groupBox_2->setFont(font);
        groupBox_2->setStyleSheet(QLatin1String("QGroupBox::title { \n"
"   \n"
"     subcontrol-position: top left; /* position at the top left*/ \n"
"  padding: 2px 13px;\n"
"   margin-top: -5px;\n"
"    \n"
" }\n"
"\n"
"QGroupBox{\n"
"   border: 1px solid rgb(182, 181, 179);\n"
"  border-radius: 5px;\n"
"}"));
        anglePerspective = new QDoubleSpinBox(groupBox_2);
        anglePerspective->setObjectName(QStringLiteral("anglePerspective"));
        anglePerspective->setGeometry(QRect(70, 10, 120, 21));
        anglePerspective->setMinimum(5);
        anglePerspective->setMaximum(180);
        nearPerspective = new QDoubleSpinBox(groupBox_2);
        nearPerspective->setObjectName(QStringLiteral("nearPerspective"));
        nearPerspective->setGeometry(QRect(70, 30, 120, 21));
        nearPerspective->setMinimum(0.01);
        nearPerspective->setMaximum(100);
        farPerspective = new QDoubleSpinBox(groupBox_2);
        farPerspective->setObjectName(QStringLiteral("farPerspective"));
        farPerspective->setGeometry(QRect(70, 50, 120, 21));
        farPerspective->setMinimum(0.01);
        farPerspective->setMaximum(1e+07);
        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 10, 66, 17));
        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(10, 30, 66, 17));
        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(10, 50, 66, 17));
        groupBox_3 = new QGroupBox(scrollAreaWidgetContents_2);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(540, 10, 141, 80));
        QFont font3;
        font3.setPointSize(9);
        font3.setBold(true);
        font3.setUnderline(false);
        font3.setWeight(75);
        font3.setStrikeOut(false);
        font3.setKerning(true);
        groupBox_3->setFont(font3);
        groupBox_3->setStyleSheet(QLatin1String("QGroupBox::title { \n"
"   \n"
"     subcontrol-position: top left; /* position at the top left*/ \n"
"  padding: 2px 13px;\n"
"   margin-top: -5px;\n"
"    \n"
" }\n"
"\n"
"QGroupBox{\n"
"   border: 1px solid rgb(182, 181, 179);\n"
"  border-radius: 5px;\n"
"}"));
        label_7 = new QLabel(groupBox_3);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(10, 10, 66, 17));
        label_8 = new QLabel(groupBox_3);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(10, 30, 66, 17));
        label_9 = new QLabel(groupBox_3);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(10, 50, 66, 17));
        sizeGrid = new QSpinBox(groupBox_3);
        sizeGrid->setObjectName(QStringLiteral("sizeGrid"));
        sizeGrid->setGeometry(QRect(80, 10, 60, 21));
        sizeGrid->setMinimum(0);
        sizeGrid->setMaximum(900);
        sizeGrid->setValue(20);
        height_l = new QLabel(groupBox_3);
        height_l->setObjectName(QStringLiteral("height_l"));
        height_l->setGeometry(QRect(80, 30, 66, 17));
        width_l = new QLabel(groupBox_3);
        width_l->setObjectName(QStringLiteral("width_l"));
        width_l->setGeometry(QRect(80, 50, 66, 17));
        scrollAreaBottom->setWidget(scrollAreaWidgetContents_2);

        verticalLayout->addWidget(scrollAreaBottom);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 913, 25));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuOpen_Recent_File = new QMenu(menuFile);
        menuOpen_Recent_File->setObjectName(QStringLiteral("menuOpen_Recent_File"));
        menuObject = new QMenu(menuBar);
        menuObject->setObjectName(QStringLiteral("menuObject"));
        menuLights = new QMenu(menuBar);
        menuLights->setObjectName(QStringLiteral("menuLights"));
        menuObject_2 = new QMenu(menuLights);
        menuObject_2->setObjectName(QStringLiteral("menuObject_2"));
        menuLight = new QMenu(menuLights);
        menuLight->setObjectName(QStringLiteral("menuLight"));
        menuOptions = new QMenu(menuBar);
        menuOptions->setObjectName(QStringLiteral("menuOptions"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuObject->menuAction());
        menuBar->addAction(menuLights->menuAction());
        menuBar->addAction(menuOptions->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addAction(menuOpen_Recent_File->menuAction());
        menuFile->addAction(actionSave);
        menuFile->addAction(actionSave_As);
        menuFile->addSeparator();
        menuFile->addAction(actionQuit);
        menuObject->addAction(actionGrid);
        menuObject->addAction(actionPropertiesScene);
        menuLights->addAction(menuObject_2->menuAction());
        menuLights->addAction(menuLight->menuAction());
        menuLights->addSeparator();
        menuObject_2->addAction(actionCube);
        menuObject_2->addAction(actionCone);
        menuObject_2->addAction(actionCylinder);
        menuObject_2->addAction(actionHemisphere);
        menuObject_2->addAction(actionPrism);
        menuObject_2->addAction(actionSphere);
        menuLight->addSeparator();
        menuLight->addAction(actionArea);
        menuLight->addAction(actionDirectional);
        menuLight->addAction(actionPontual);
        menuLight->addAction(actionSpot);
        menuOptions->addAction(actionScreenShot);
        menuOptions->addAction(actionScreanShot_Render);
        menuHelp->addAction(actionAbout);
        menuHelp->addAction(actionShortcuts);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);
        toolBox->setCurrentIndex(3);
        toolBox->layout()->setSpacing(6);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Scene Build by Danilo Silva", 0));
        actionOpen->setText(QApplication::translate("MainWindow", "Open", 0));
        actionOpen->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", 0));
        actionSave->setText(QApplication::translate("MainWindow", "Save", 0));
        actionSave->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", 0));
        actionQuit->setText(QApplication::translate("MainWindow", "Quit", 0));
        actionQuit->setShortcut(QApplication::translate("MainWindow", "Ctrl+Q", 0));
        actionGrid->setText(QApplication::translate("MainWindow", "Grid", 0));
        actionGrid->setShortcut(QApplication::translate("MainWindow", "G", 0));
        actionPropertiesScene->setText(QApplication::translate("MainWindow", "Properties Scene", 0));
        actionPropertiesScene->setShortcut(QApplication::translate("MainWindow", "Ctrl+P", 0));
        actionCube->setText(QApplication::translate("MainWindow", "Cube", 0));
        actionCube->setShortcut(QApplication::translate("MainWindow", "Ctrl+C", 0));
        actionCylinder->setText(QApplication::translate("MainWindow", "Cylinder", 0));
        actionCylinder->setShortcut(QApplication::translate("MainWindow", "Ctrl+Y", 0));
        actionHemisphere->setText(QApplication::translate("MainWindow", "Hemisphere", 0));
        actionHemisphere->setShortcut(QApplication::translate("MainWindow", "Ctrl+H", 0));
        actionPrism->setText(QApplication::translate("MainWindow", "Prism", 0));
        actionPrism->setShortcut(QApplication::translate("MainWindow", "Ctrl+P", 0));
        actionSphere->setText(QApplication::translate("MainWindow", "Sphere", 0));
        actionSphere->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", 0));
        actionArea->setText(QApplication::translate("MainWindow", "Area", 0));
        actionArea->setShortcut(QApplication::translate("MainWindow", "Shift+A", 0));
        actionDirectional->setText(QApplication::translate("MainWindow", "Directional", 0));
        actionDirectional->setShortcut(QApplication::translate("MainWindow", "Shift+D", 0));
        actionPontual->setText(QApplication::translate("MainWindow", "Pontual", 0));
        actionPontual->setShortcut(QApplication::translate("MainWindow", "Shift+P", 0));
        actionSpot->setText(QApplication::translate("MainWindow", "Spot", 0));
        actionSpot->setShortcut(QApplication::translate("MainWindow", "Shift+S", 0));
        actionGlossy_Reflection->setText(QApplication::translate("MainWindow", "Glossy Reflection", 0));
        actionGlossy_Refraction->setText(QApplication::translate("MainWindow", "Glossy Refraction", 0));
        actionMotion_Blur->setText(QApplication::translate("MainWindow", "Motion Blur", 0));
        actionDepth_of_Field->setText(QApplication::translate("MainWindow", "Depth of Field", 0));
        actionScreenShot->setText(QApplication::translate("MainWindow", "ScreenShot OpenGL", 0));
        actionScreenShot->setShortcut(QApplication::translate("MainWindow", "Alt+S", 0));
        actionScreanShot_Render->setText(QApplication::translate("MainWindow", "ScreenShot Render", 0));
        actionCone->setText(QApplication::translate("MainWindow", "Cone", 0));
        actionCone->setShortcut(QApplication::translate("MainWindow", "Ctrl+E", 0));
        actionD->setText(QApplication::translate("MainWindow", "d", 0));
        actionSave_As->setText(QApplication::translate("MainWindow", "Save As", 0));
        actionAbout->setText(QApplication::translate("MainWindow", "About", 0));
        actionShortcuts->setText(QApplication::translate("MainWindow", "Shortcuts", 0));
        groupBoxPropertiesObj->setTitle(QApplication::translate("MainWindow", "Properties Object", 0));
        selectedObj->setText(QApplication::translate("MainWindow", "Select", 0));
        enableObj->setText(QApplication::translate("MainWindow", "Enable", 0));
        ambMaterial->setText(QApplication::translate("MainWindow", "amb", 0));
        diffMaterial->setText(QApplication::translate("MainWindow", "diff", 0));
        speMaterial->setText(QApplication::translate("MainWindow", "spe", 0));
        label_10->setText(QApplication::translate("MainWindow", "Name", 0));
        label_13->setText(QApplication::translate("MainWindow", "Scale", 0));
        materialobject->clear();
        materialobject->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "NO DEFINE", 0)
         << QApplication::translate("MainWindow", "EMERALD", 0)
         << QApplication::translate("MainWindow", "JADE", 0)
         << QApplication::translate("MainWindow", "OBSIDIAN", 0)
         << QApplication::translate("MainWindow", "PEARL", 0)
         << QApplication::translate("MainWindow", "RUBY", 0)
         << QApplication::translate("MainWindow", "TURQUOSIE", 0)
         << QApplication::translate("MainWindow", "BRONZE", 0)
         << QApplication::translate("MainWindow", "BRONZE POLIERT", 0)
         << QApplication::translate("MainWindow", "CHROME", 0)
         << QApplication::translate("MainWindow", "GOLD", 0)
         << QApplication::translate("MainWindow", "GOLD POLIERT", 0)
         << QApplication::translate("MainWindow", "COPPER", 0)
         << QApplication::translate("MainWindow", "COPPER POLIERT", 0)
         << QApplication::translate("MainWindow", "BRASS", 0)
         << QApplication::translate("MainWindow", "SILVER", 0)
         << QApplication::translate("MainWindow", "SILVER POLIERT", 0)
         << QApplication::translate("MainWindow", "ZINN", 0)
         << QApplication::translate("MainWindow", "GUMMI", 0)
         << QApplication::translate("MainWindow", "PLASTIC", 0)
         << QApplication::translate("MainWindow", "BLACK PLASTIC", 0)
         << QApplication::translate("MainWindow", "CYAN PLASTIC", 0)
         << QApplication::translate("MainWindow", "GREEN PLASTIC", 0)
         << QApplication::translate("MainWindow", "RED PLASTIC", 0)
         << QApplication::translate("MainWindow", "WHITE PLASTIC", 0)
         << QApplication::translate("MainWindow", "YELLOW PLASTIC", 0)
         << QApplication::translate("MainWindow", "BLACK RUBBER", 0)
         << QApplication::translate("MainWindow", "CYAN RUBBER", 0)
         << QApplication::translate("MainWindow", "GREEN RUBBER", 0)
         << QApplication::translate("MainWindow", "RED RUBBER", 0)
         << QApplication::translate("MainWindow", "WHITE RUBBER", 0)
         << QApplication::translate("MainWindow", "YELLOW RUBBER", 0)
        );
        transx->setPrefix(QApplication::translate("MainWindow", "x : ", 0));
        transx->setSuffix(QString());
        transy->setPrefix(QApplication::translate("MainWindow", "y : ", 0));
        transz->setPrefix(QApplication::translate("MainWindow", "z : ", 0));
        label_12->setText(QApplication::translate("MainWindow", "Rotate", 0));
        groupBox_4->setTitle(QApplication::translate("MainWindow", "Effects", 0));
        label_35->setText(QApplication::translate("MainWindow", "Glossy Reflection", 0));
        label_34->setText(QApplication::translate("MainWindow", "Glossy Refraction", 0));
        label_33->setText(QApplication::translate("MainWindow", "Reflection", 0));
        label_32->setText(QApplication::translate("MainWindow", "Refraction", 0));
        xmotion->setPrefix(QApplication::translate("MainWindow", "x: ", 0));
        ymotion->setPrefix(QApplication::translate("MainWindow", "y: ", 0));
        zmotion->setPrefix(QApplication::translate("MainWindow", "z: ", 0));
        label_36->setText(QApplication::translate("MainWindow", "Motion Blur", 0));
        label_14->setText(QApplication::translate("MainWindow", "Shininess", 0));
        rotx->setPrefix(QApplication::translate("MainWindow", "x : ", 0));
        roty->setPrefix(QApplication::translate("MainWindow", "y : ", 0));
        rotz->setPrefix(QApplication::translate("MainWindow", "z : ", 0));
        label_16->setText(QApplication::translate("MainWindow", "Ambient", 0));
        label_15->setText(QApplication::translate("MainWindow", "Diffuse", 0));
        label_17->setText(QApplication::translate("MainWindow", "Specular", 0));
        label_11->setText(QApplication::translate("MainWindow", "Translate", 0));
        deleteObj->setText(QApplication::translate("MainWindow", "Delete", 0));
        scalex->setPrefix(QApplication::translate("MainWindow", "x : ", 0));
        scaley->setPrefix(QApplication::translate("MainWindow", "y : ", 0));
        scalez->setPrefix(QApplication::translate("MainWindow", "z : ", 0));
        groupBox_6->setTitle(QApplication::translate("MainWindow", "Texture and Bump", 0));
        loadBump->setText(QApplication::translate("MainWindow", "Add Bump", 0));
        loadTexture->setText(QApplication::translate("MainWindow", "Add Texture", 0));
        enableTexture->setText(QApplication::translate("MainWindow", "Enable Texture", 0));
        enableBump->setText(QApplication::translate("MainWindow", "Enable Bump Mapping", 0));
        choiceTexture->clear();
        choiceTexture->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "ONLY TEXTURE", 0)
         << QApplication::translate("MainWindow", "REPLACE WITH TEXTURE", 0)
        );
        groupBoxPropertieLight->setTitle(QApplication::translate("MainWindow", "Properties Light", 0));
        label_20->setText(QApplication::translate("MainWindow", "Name", 0));
        selectedLight->setText(QApplication::translate("MainWindow", "Select", 0));
        visibleLight->setText(QApplication::translate("MainWindow", "Visible", 0));
        enableLight->setText(QApplication::translate("MainWindow", "Enable", 0));
        label_21->setText(QApplication::translate("MainWindow", "Position", 0));
        positionxLight->setPrefix(QApplication::translate("MainWindow", "x : ", 0));
        positionyLight->setPrefix(QApplication::translate("MainWindow", "y : ", 0));
        positionzLight->setPrefix(QApplication::translate("MainWindow", "z : ", 0));
        label_22->setText(QApplication::translate("MainWindow", "Direction", 0));
        directionxLight->setPrefix(QApplication::translate("MainWindow", "x : ", 0));
        directionyLight->setPrefix(QApplication::translate("MainWindow", "y : ", 0));
        directionzLight->setPrefix(QApplication::translate("MainWindow", "z : ", 0));
        label_44->setText(QApplication::translate("MainWindow", "Energy", 0));
        label_24->setText(QApplication::translate("MainWindow", "Vec A", 0));
        vecAx->setPrefix(QApplication::translate("MainWindow", "x : ", 0));
        vecAy->setPrefix(QApplication::translate("MainWindow", "y : ", 0));
        vecAz->setPrefix(QApplication::translate("MainWindow", "z : ", 0));
        label_25->setText(QApplication::translate("MainWindow", "Vec B", 0));
        vecBx->setPrefix(QApplication::translate("MainWindow", "x : ", 0));
        vecBy->setPrefix(QApplication::translate("MainWindow", "y : ", 0));
        vecBz->setPrefix(QApplication::translate("MainWindow", "z : ", 0));
        label_23->setText(QApplication::translate("MainWindow", "Attenuation", 0));
        attenuationcLight->setPrefix(QApplication::translate("MainWindow", "c : ", 0));
        attenuationlLight->setPrefix(QApplication::translate("MainWindow", "l : ", 0));
        attenuationqLight->setPrefix(QApplication::translate("MainWindow", "q : ", 0));
        label_26->setText(QApplication::translate("MainWindow", "Ambient", 0));
        ambMaterial_2->setText(QApplication::translate("MainWindow", "amb", 0));
        label_27->setText(QApplication::translate("MainWindow", "   Diffuse", 0));
        diffMaterial_2->setText(QApplication::translate("MainWindow", "diff", 0));
        label_28->setText(QApplication::translate("MainWindow", "Specular", 0));
        speMaterial_2->setText(QApplication::translate("MainWindow", "spe", 0));
        label_29->setText(QApplication::translate("MainWindow", "Angle", 0));
        label_30->setText(QApplication::translate("MainWindow", "Inner Angle", 0));
        label_31->setText(QApplication::translate("MainWindow", "Exp", 0));
        deleteLight->setText(QApplication::translate("MainWindow", "Delete", 0));
        tabWidget->setTabText(tabWidget->indexOf(tabOpenGL), QApplication::translate("MainWindow", "OpenGL", 0));
        tabWidget->setTabText(tabWidget->indexOf(tabRender), QApplication::translate("MainWindow", "Render", 0));
        toolBox->setItemText(toolBox->indexOf(page), QApplication::translate("MainWindow", "Objects", 0));
        toolBox->setItemText(toolBox->indexOf(page_3), QApplication::translate("MainWindow", "Lights", 0));
        showHBB->setText(QApplication::translate("MainWindow", "Show HBB", 0));
        groupBox_5->setTitle(QApplication::translate("MainWindow", "Effect Depth of Field", 0));
        label_37->setText(QApplication::translate("MainWindow", "Radius", 0));
        label_38->setText(QApplication::translate("MainWindow", "Focal Length", 0));
        toolBox->setItemText(toolBox->indexOf(page_2), QApplication::translate("MainWindow", "Scene", 0));
        label_39->setText(QApplication::translate("MainWindow", "Photons Global", 0));
        label_40->setText(QApplication::translate("MainWindow", "Radius Global", 0));
        label_46->setText(QApplication::translate("MainWindow", "Nears Global", 0));
        label_42->setText(QApplication::translate("MainWindow", "Photons Caustic", 0));
        label_41->setText(QApplication::translate("MainWindow", "Radius Caustic", 0));
        label_45->setText(QApplication::translate("MainWindow", "Nears Caustic", 0));
        label_43->setText(QApplication::translate("MainWindow", "Depth", 0));
        groupBox_7->setTitle(QApplication::translate("MainWindow", "Options", 0));
        enablePhotonMap->setText(QApplication::translate("MainWindow", "Enable", 0));
        visiblePhotonMap->setText(QApplication::translate("MainWindow", "Show Photons Globais", 0));
        visiblePhotonMapCaustics->setText(QApplication::translate("MainWindow", "Show Photons Caustics", 0));
        groupBox_8->setTitle(QApplication::translate("MainWindow", "Radiance", 0));
        useFilter->setText(QApplication::translate("MainWindow", "Enable Filter", 0));
        renderCaustics->setText(QApplication::translate("MainWindow", "Render Caustics", 0));
        renderGlobal->setText(QApplication::translate("MainWindow", "Render Global", 0));
        toolBox->setItemText(toolBox->indexOf(page_5), QApplication::translate("MainWindow", "Photon Mapping", 0));
        label_18->setText(QApplication::translate("MainWindow", "Samples", 0));
        label_19->setText(QApplication::translate("MainWindow", "Out Proportion", 0));
        proportion->setSuffix(QApplication::translate("MainWindow", "%", 0));
        btnRender->setText(QApplication::translate("MainWindow", "Render", 0));
        progressRender->setFormat(QApplication::translate("MainWindow", "%p% Done!", 0));
        toolBox->setItemText(toolBox->indexOf(page_4), QApplication::translate("MainWindow", "Render Options", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "Camera", 0));
        label->setText(QApplication::translate("MainWindow", "Eye", 0));
        label_2->setText(QApplication::translate("MainWindow", "At", 0));
        label_3->setText(QApplication::translate("MainWindow", "Up", 0));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Perspective", 0));
        label_4->setText(QApplication::translate("MainWindow", "Angle", 0));
        label_5->setText(QApplication::translate("MainWindow", "Near", 0));
        label_6->setText(QApplication::translate("MainWindow", "Far", 0));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "Info", 0));
        label_7->setText(QApplication::translate("MainWindow", "Size Grid", 0));
        label_8->setText(QApplication::translate("MainWindow", "Height", 0));
        label_9->setText(QApplication::translate("MainWindow", "Width", 0));
        height_l->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        width_l->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
        menuOpen_Recent_File->setTitle(QApplication::translate("MainWindow", "Open Recent File", 0));
        menuObject->setTitle(QApplication::translate("MainWindow", "Edit", 0));
        menuLights->setTitle(QApplication::translate("MainWindow", "Add", 0));
        menuObject_2->setTitle(QApplication::translate("MainWindow", "Object", 0));
        menuLight->setTitle(QApplication::translate("MainWindow", "Light", 0));
        menuOptions->setTitle(QApplication::translate("MainWindow", "Options", 0));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

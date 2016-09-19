//
//  MainVizScene.cpp
//  IrrlichtV3
//
//  Created by Benjamin Trapani on 2/19/16.
//  Copyright © 2016 Benjamin Trapani. All rights reserved.
//

#include "MainVizScene.hpp"
#include "Affects.h"
#include <stdio.h>
#include <iostream>

using namespace Viz3d;
using namespace irr::scene;
using namespace irr;
using namespace irr::core;

char * MainVizScene::getResourcePath(char **argv, const char * file){
    char tempPath[1024];
    strncpy( tempPath, argv[0], 1023 );
    int	x = (int)strlen(tempPath) -1;
    while( tempPath[x] != '/' && x > 0 )
        tempPath[x--] = 0;
        
    strncat( tempPath, "../Resources/Resources/", 1023 );
    return strncat( tempPath, file, 1023 );
}

MainVizScene::MainVizScene(ISceneManager * pManager, irr::gui::IGUIEnvironment * pGui, char ** argv):_pSmgr(pManager),
_pGui(pGui), _argv(argv){
    _pAudioListener = new V3dAudioListener(64, 64); //128, 64

    _pEffectManager = new EffectManager_t(2);
    _pAffectedPropManager = new AffectedPropertyManager(10);
    
    createFilters();
    setupScene();
}

void MainVizScene::createFilters(){
    DampedVelocityProperty<double> colorVelCore(0.0, 1000000.0, 1000.0, 1.0);
    DampedBoundedVelocityProperty<double> colorVelProp(colorVelCore, 0.1, 10);
    
    for(int i = 0; i < _pAudioListener->getFftBinCount(); i++){
        Effect_t * uniformColorFilter = new Effect_t(i, i+1, 2300000000000000000.0, colorVelProp);
        _pEffectManager->addEffect(uniformColorFilter);
    }
}

void MainVizScene::setupScene(){
    _pDriver = _pSmgr->getVideoDriver();
    
    std::vector<std::string> deviceNames = _pAudioListener->getDevices();
    for (auto iter = deviceNames.begin(); iter != deviceNames.end(); ++iter) {
        std::cout << *iter << std::endl;
    }
    int index=1;

    /*const float xPos = _pDriver->getScreenSize().Width*0.5f;
    float yPos = _pDriver->getScreenSize().Height;
    const float buttonWidth = 100.0f;
    const float buttonHeight = 25.0f;
    const float yPadding = 25.0f;
    for(auto iter = deviceNames.begin(); iter != deviceNames.end(); ++iter){
        yPos -= buttonHeight + yPadding;
        std::wstring widestr = std::wstring(iter->begin(), iter->end());
        _pGui->addButton(rect<s32>(xPos - buttonWidth*0.5f,yPos - buttonHeight*0.5f,xPos + buttonWidth*0.5f,
                                   yPos + buttonHeight*0.5f), 0, 0, widestr.c_str(), L"Output Device");

    }
    
    _pGui->addButton(rect<s32>(10,240,110,240 + 32), 0, 0,
                   L"Quit", L"Exits Program");
    _pGui->addButton(rect<s32>(10,280,110,280 + 32), 0, 0,
                   L"New Window", L"Launches a new Window");
    _pGui->addButton(rect<s32>(10,320,110,320 + 32), 0, 0,
                   L"File Open", L"Opens a file");*/
    
    _pFPSCam = _pSmgr->addCameraSceneNodeFPS();
    _pFPSCam->setPosition(vector3df(0,30,-40));
    _pFPSCam->setTarget(vector3df(0,5,0));
    _pFPSCam->setFarValue(5000.0f);
    
    _pNormalCam = _pSmgr->addCameraSceneNode();
    _pNormalCam->setPosition(vector3df(0,30,-40));
    _pNormalCam->setTarget(vector3df(0,5,0));
    _pNormalCam->setFarValue(5000.0f);
    _pSmgr->setActiveCamera(_pFPSCam);
    //smgr->addCameraSceneNode(0, vector3df(0,30,-40), vector3df(0,5,0));
    _pSmgr->addLightSceneNode();
    
    IAnimatedMesh* mesh = _pSmgr->getMesh(getResourcePath(_argv,"sydney.md2"));
    IAnimatedMeshSceneNode* node = _pSmgr->addAnimatedMeshSceneNode( mesh );
    
    node->setMaterialFlag(irr::video::EMF_LIGHTING, true);
    node->setMD2Animation(scene::EMAT_STAND);
    node->setMaterialTexture( 0, _pDriver->getTexture(getResourcePath(_argv, "sydney.bmp")));
    
    /*for (unsigned long i = _pAudioListener->getFftBinCount()/2; i < _pAudioListener->getFftBinCount(); i++) {
        IAnimatedMesh * pSpongMesh = _pSmgr->getMesh(getResourcePath(_argv, "spongebob.obj"));
        IAnimatedMeshSceneNode * pSpongeNode = _pSmgr->addAnimatedMeshSceneNode( pSpongMesh);
        pSpongeNode->setScale(vector3df(10,10,10));
        pSpongeNode->setPosition(vector3df(25 * i,0,0));
        pSpongeNode->setMaterialFlag(irr::video::EMF_LIGHTING, true);
        pSpongeNode->setMaterialTexture(0, _pDriver->getTexture(getResourcePath(_argv, "Lava.jpg")));
        
        UniformColorAffect * spongeColorAff = new UniformColorAffect(_pEffectManager->getFilterForIndex(i),
                                                                     pSpongeNode, irr::video::SColor(255,rand()%255,rand()%255,rand()%255));
        _pAffectedPropManager->addAffectedProperty(spongeColorAff);
    }*/
    
   /* IAnimatedMesh * boatMEsh = _pSmgr->getMesh(getResourcePath(_argv, "lor-starcutter.obj"));
    IAnimatedMeshSceneNode * pBoadNoad = _pSmgr->addAnimatedMeshSceneNode(boatMEsh);
    pBoadNoad->setPosition(vector3df(800, 800, 800));
    pBoadNoad->setScale(vector3df(100,100,100));
    pBoadNoad->setMaterialFlag(irr::video::EMF_LIGHTING, true);
    
    
   UniformColorAffect * pBoatEffect = new UniformColorAffect(_pEffectManager->getFilterForIndex(
                                                            _pAudioListener->getFftBinCount()/2),
                                                                 pBoadNoad, irr::video::SColor(255,0,0,255));
    _pAffectedPropManager->addAffectedProperty(pBoatEffect);*/
    
    createDeer(16, vector3df(2000, 2000, 2000), "untitled-scene.obj" , 10, vector3df(-1000,-1000,-1000));
    createDeer(32, vector3df(2000, 2000, 2000), "bird.obj" , 4, vector3df(-1000,-1000,-1000));
    createDeer(16, vector3df(2000, 2000, 2000), "clock.obj" , 4, vector3df(-1000,-1000,-1000));
    _pAudioListener->start(index);
    //createDeer(10, vector3df(500,500,500), "tim-island-base-2000-with-bar-area.obj", 80);
}

void MainVizScene::createDeer(unsigned int count, const irr::core::vector3df & maxBounds,
                              const char * file, const int iscale, const irr::core::vector3df & origin){
    for(int i = 0; i < count; i++){
        IAnimatedMesh * deerMesh = _pSmgr->getMesh(getResourcePath(_argv, file));
        IAnimatedMeshSceneNode * pDeerNode = _pSmgr->addAnimatedMeshSceneNode(deerMesh);
        pDeerNode->setMaterialFlag(irr::video::EMF_LIGHTING, true);
        
        int randTexture = rand()%4;
        switch(randTexture){
            case 0:{
                pDeerNode->setMaterialTexture(0, _pDriver->getTexture(getResourcePath(_argv, "Lava.jpg")));
                break;
            }
            case 1:{
                pDeerNode->setMaterialTexture(0, _pDriver->getTexture(getResourcePath(_argv, "Leaf_Alpha.png")));
                break;
            }
            case 2:{
                pDeerNode->setMaterialTexture(0, _pDriver->getTexture(getResourcePath(_argv, "longtiles.jpg")));
                break;
            }
            case 3:{
                pDeerNode->setMaterialTexture(0, _pDriver->getTexture(getResourcePath(_argv, "posz.jpg")));
                break;
            }
        }
        
        pDeerNode->setPosition(vector3df(rand()%(int)maxBounds.X, rand()%(int)maxBounds.Y, rand()%(int)maxBounds.Z)
                               + origin);
        int scale = rand()%(int)iscale +1;
        pDeerNode->setScale(vector3df(scale, scale, scale));
        pDeerNode->setRotation(vector3df(rand()%4, rand()%4, rand()%4));
        pDeerNode->setMaterialFlag(irr::video::EMF_LIGHTING, true);
        int index = rand()%_pAudioListener->getFftBinCount();
        AffectedProperty<K_AFFECTTYPE_COLOR, Effect_t> * pDeerColor = new AffectedProperty<K_AFFECTTYPE_COLOR, Effect_t>(
                                                                                                                         _pEffectManager->getFilterForIndex(index),
                                                                                                                          pDeerNode, irr::video::SColor(rand()%255+128,rand()%255+128,rand()%255+128,255));
        AffectedProperty<K_AFFECTTYPE_SCALE, Effect_t> * pDeerScale = new
            AffectedProperty<K_AFFECTTYPE_SCALE, Effect_t>(_pEffectManager->getFilterForIndex(index), pDeerNode,
                                                           irr::core::vector3df(1.0f, 1.0f, 1.0f));
        _pAffectedPropManager->addAffectedProperty(pDeerColor);
        _pAffectedPropManager->addAffectedProperty(pDeerScale);
    }
}

void MainVizScene::update(const double dt){
    const std::atomic<double> * pFftResult = _pAudioListener->getFftResult();
    _pEffectManager->updateEffectsWithBuffer(pFftResult,dt);
    _pAffectedPropManager->updateProps();
}

MainVizScene::~MainVizScene(){
    delete _pEffectManager;
    _pEffectManager = nullptr;
    
    delete _pAudioListener;
    _pAudioListener = nullptr;
}
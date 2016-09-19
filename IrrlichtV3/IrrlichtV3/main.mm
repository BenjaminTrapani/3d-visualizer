//
//  main.m
//  IrrlichtV3
//
//  Created by Benjamin Trapani on 2/15/16.
//  Copyright © 2016 Benjamin Trapani. All rights reserved.
//

#import <Cocoa/Cocoa.h>

//
//  main.cpp
//  IrrlichtVis
//
//  Created by Benjamin Trapani on 2/15/16.
//  Copyright © 2016 Benjamin Trapani. All rights reserved.
//

#include <OpenGL/OpenGL.h>
#include <irrlicht/irrlicht.h>
#include <iostream>
#include "MainVizScene.hpp"

using namespace irr;
#pragma comment(lib, "libMacOSX.a")

class MyEventReceiver : public IEventReceiver
{
public:
    // This is the one method that we have to implement
    virtual bool OnEvent(const SEvent& event)
    {
        // Remember whether each key is down or up
        if (event.EventType == irr::EET_KEY_INPUT_EVENT)
            KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
        
        return false;
    }
    
    // This is used to check whether a key is being held down
    virtual bool IsKeyDown(EKEY_CODE keyCode) const
    {
        return KeyIsDown[keyCode];
    }
    
    MyEventReceiver()
    {
        for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
            KeyIsDown[i] = false;
    }
    
private:
    // We use this array to store the current state of each key
    bool KeyIsDown[KEY_KEY_CODES_COUNT];
};

using namespace irr::scene;
using namespace irr;
using namespace irr::core;
using namespace Viz3d;

int main(int argc, char** argv)
{
    // start up the engine using Open GL
    MyEventReceiver eventReciever;
    IrrlichtDevice *device =
    createDevice( video::EDT_OPENGL, irr::core::dimension2d<u32>(640, 480), 16,
                 false, false, false, &eventReciever);
    device->setResizable(true);
    
    video::IVideoDriver* driver = device->getVideoDriver();
    // Create a scene
    scene::ISceneManager* smgr = device->getSceneManager();
    gui::IGUIEnvironment * pGui = device->getGUIEnvironment();
    MainVizScene * vizScene = new MainVizScene(smgr, pGui, argv);
    int lastFPS = -1;
    
    const unsigned int goalMPF = 16;
    std::chrono::time_point<std::chrono::high_resolution_clock> lastFrameTime;
    std::chrono::time_point<std::chrono::high_resolution_clock> curFrameTime;
    std::chrono::high_resolution_clock clock;
    lastFrameTime = clock.now();
    curFrameTime = clock.now();
    
    
    while(device->run() && driver && device->isWindowActive())
    {
        if(eventReciever.IsKeyDown(irr::KEY_ESCAPE)){
            break;
        }
        lastFrameTime = clock.now();
        driver->beginScene(); // darkgray
        
        smgr->drawAll();
        pGui->drawAll();
        driver->endScene();
        
        int fps = driver->getFPS();
        double dt = 400.0/(double)fps;
        vizScene->update(dt);
        
        if (lastFPS != fps)
        {
            core::stringw str = L"Hello Mac [";
            str += driver->getName();
            str += "] FPS:";
            str += fps;
            device->setWindowCaption(str.c_str());
            lastFPS = fps;
        }
        
        curFrameTime = clock.now();
        auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(curFrameTime - lastFrameTime);
        if(milliseconds.count() < goalMPF){
            std::this_thread::sleep_for(std::chrono::milliseconds(goalMPF - milliseconds.count()));
        }
    }
    
    delete vizScene;
    
    device->drop();
    return 0;
}

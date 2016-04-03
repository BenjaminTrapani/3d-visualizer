//
//  MainVizScene.hpp
//  IrrlichtV3
//
//  Created by Benjamin Trapani on 2/19/16.
//  Copyright © 2016 Benjamin Trapani. All rights reserved.
//

#ifndef MainVizScene_hpp
#define MainVizScene_hpp

#include <stdio.h>
#include "EffectManager.hpp"
#include "AffectedPropertyManager.hpp"
#include "V3dAudioListener.hpp"
#include <irrlicht/irrlicht.h>

namespace Viz3d {
    class MainVizScene{
    public:
        MainVizScene(irr::scene::ISceneManager * pSmgr, irr::gui::IGUIEnvironment * pGui, char ** argv);
        ~MainVizScene();
        void update(const double dt);
        static char * getResourcePath(char ** argv, const char * file);
    private:
        void setupScene();
        void createTerrain();
        void createFilters();
        
        void createDeer(unsigned int count, const irr::core::vector3df & maxBounds,
                        const char * file, const int scale, const irr::core::vector3df & origin);
        
        irr::scene::ISceneManager * _pSmgr;
        irr::gui::IGUIEnvironment * _pGui;
        irr::video::IVideoDriver * _pDriver;
        irr::scene::ICameraSceneNode * _pFPSCam;
        irr::scene::ICameraSceneNode * _pNormalCam;
        char ** _argv;
        V3dAudioListener * _pAudioListener;
        
        typedef EffectFilter<double, std::atomic<double>> Effect_t;
        typedef EffectManager<Effect_t> EffectManager_t;
        EffectManager_t * _pEffectManager;
        AffectedPropertyManager * _pAffectedPropManager;
    };
}

#endif /* MainVizScene_hpp */

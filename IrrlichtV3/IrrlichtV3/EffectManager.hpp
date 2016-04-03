//
//  EffectManager.hpp
//  IrrlichtV3
//
//  Created by Benjamin Trapani on 2/18/16.
//  Copyright © 2016 Benjamin Trapani. All rights reserved.
//

#ifndef EffectManager_hpp
#define EffectManager_hpp

#include <stdio.h>
#include <vector>

namespace Viz3d {
    template<class EffectType>
    class EffectManager{
    public:
        typedef typename EffectType::Buffer_t buffer_t;
        
        EffectManager(const size_t initialSize){
            _effects.reserve(initialSize);
        }
        
        ~EffectManager(){
            for (auto iter = _effects.begin(); iter != _effects.end(); ++iter) {
                delete *iter;
            }
        }
        
        void addEffect(EffectType * pEffect){
            _effects.push_back(pEffect);
        }
        
        EffectType * getFilterForIndex(const size_t index){
            return _effects[index];
        }
        
        void updateEffectsWithBuffer(const buffer_t * buffer, const double dt){
            for (auto iter = _effects.begin(); iter != _effects.end(); ++iter) {
                (*iter)->applyFilter(buffer, dt);
            }
        }
        
    private:
        std::vector<EffectType*> _effects;
    };
}
#endif /* EffectManager_hpp */

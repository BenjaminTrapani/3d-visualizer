//
//  UniformColorAffect.hpp
//  IrrlichtV3
//
//  Created by Benjamin Trapani on 2/18/16.
//  Copyright © 2016 Benjamin Trapani. All rights reserved.
//

#ifndef UniformColorAffect_hpp
#define UniformColorAffect_hpp

#include <stdio.h>

#include "AffectedProperty.hpp"

namespace Viz3d {
    template<class EffectType>
    class AffectedProperty<K_AFFECTTYPE_COLOR, EffectType>: public AffectedPropertyBase{
    public:
        AffectedProperty(const EffectType * pEffectFilter,
                         irr::scene::ISceneNode * pMeshSceneNode,
                         const irr::video::SColor & bitsToMod):_pFilter(pEffectFilter),
        _pMeshNode(pMeshSceneNode), _bitsToMod(bitsToMod){}
        
        void applyEffect()override{
            typedef irr::video::SColor color_t;
            color_t curColor(_pFilter->getMostRecentResult()*_bitsToMod.getAlpha(),
                             _pFilter->getMostRecentResult()*_bitsToMod.getRed(),
                             _pFilter->getMostRecentResult()*_bitsToMod.getGreen(),
                             _pFilter->getMostRecentResult()*_bitsToMod.getBlue());
            irr::u32 matCount = _pMeshNode->getMaterialCount();
            for (irr::u32 i = 0; i < matCount; ++i) {
                auto pMat = &_pMeshNode->getMaterial(i);
                pMat->EmissiveColor = curColor;
                pMat->DiffuseColor = curColor;
                pMat->AmbientColor = curColor;
            }
        }
    protected:
        const EffectType * _pFilter;
        irr::scene::ISceneNode * _pMeshNode;
        irr::video::SColor _bitsToMod;
    };
}

#endif /* UniformColorAffect_hpp */

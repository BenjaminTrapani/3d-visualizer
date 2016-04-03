//
//  ScaleAffect.hpp
//  IrrlichtV3
//
//  Created by Benjamin Trapani on 2/18/16.
//  Copyright © 2016 Benjamin Trapani. All rights reserved.
//

#ifndef ScaleAffect_hpp
#define ScaleAffect_hpp

#include <stdio.h>
#include "AffectedProperty.hpp"

namespace Viz3d {
    
    template<class EffectType>
    class AffectedProperty<K_AFFECTTYPE_SCALE, EffectType>: public AffectedPropertyBase{
    public:
        AffectedProperty(const EffectType * pEffectFilter,
                         irr::scene::ISceneNode * pMeshSceneNode,
                         const irr::core::vector3df & scaleWeights):_pFilter(pEffectFilter),
        _pMeshNode(pMeshSceneNode), _scaleWeights(scaleWeights){
            _originalScale = pMeshSceneNode->getScale();
        }
        
        void applyEffect()override{
            _pMeshNode->setScale(_originalScale + _scaleWeights*_pFilter->getMostRecentResult() *
                                 _originalScale.getLength() * 0.25f);

        }
    protected:
        const EffectType * _pFilter;
        irr::scene::ISceneNode * _pMeshNode;
        const irr::core::vector3df _scaleWeights;
        irr::core::vector3df _originalScale;
    };
}
#endif /* ScaleAffect_hpp */

//
//  AffectedProperty.hpp
//  IrrlichtV3
//
//  Created by Benjamin Trapani on 2/18/16.
//  Copyright © 2016 Benjamin Trapani. All rights reserved.
//

#ifndef AffectedProperty_hpp
#define AffectedProperty_hpp

#include <stdio.h>
#include <irrlicht/irrlicht.h>
#include "EffectFilter.hpp"

namespace Viz3d{
    enum AffectType{
        K_AFFECTTYPE_COLOR,
        K_AFFECTTYPE_SCALE
    };
    class AffectedPropertyBase{
    public:
        virtual void applyEffect()=0;
    };
    
    template<AffectType affectType, class EffectType>
    class AffectedProperty: public AffectedPropertyBase{
    public:
        void applyEffect();
    };
}
#endif /* AffectedProperty_hpp */

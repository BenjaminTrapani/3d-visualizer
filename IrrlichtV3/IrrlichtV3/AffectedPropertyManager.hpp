//
//  AffectedPropertyManager.hpp
//  IrrlichtV3
//
//  Created by Benjamin Trapani on 2/19/16.
//  Copyright © 2016 Benjamin Trapani. All rights reserved.
//

#ifndef AffectedPropertyManager_hpp
#define AffectedPropertyManager_hpp

#include <stdio.h>
#include <vector>
#include "AffectedProperty.hpp"

namespace Viz3d{
    class AffectedPropertyManager{
    public:
        AffectedPropertyManager(const size_t initialSize);
        void addAffectedProperty(AffectedPropertyBase * pProp);
        void updateProps();
    private:
        std::vector<AffectedPropertyBase*> _affectedProps;
    };
}

#endif /* AffectedPropertyManager_hpp */

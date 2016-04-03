//
//  AffectedPropertyManager.cpp
//  IrrlichtV3
//
//  Created by Benjamin Trapani on 2/19/16.
//  Copyright © 2016 Benjamin Trapani. All rights reserved.
//

#include "AffectedPropertyManager.hpp"
using namespace Viz3d;

AffectedPropertyManager::AffectedPropertyManager(const size_t initialSize){
    _affectedProps.reserve(initialSize);
}
void AffectedPropertyManager::addAffectedProperty(AffectedPropertyBase * pProp){
    _affectedProps.push_back(pProp);
}
void AffectedPropertyManager::updateProps(){
    for (auto iter = _affectedProps.begin(); iter != _affectedProps.end(); ++iter) {
        (*iter)->applyEffect();
    }
}
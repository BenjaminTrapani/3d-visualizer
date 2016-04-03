//
//  EffectFiler.hpp
//  IrrlichtV3
//
//  Created by Benjamin Trapani on 2/18/16.
//  Copyright © 2016 Benjamin Trapani. All rights reserved.
//

#ifndef EffectFiler_hpp
#define EffectFiler_hpp

#include <stdio.h>
#include "DampedBoundedVelocityProperty.hpp"

namespace Viz3d {
    template<class CoreType, class BufferType>
    class EffectFilter{
    public:
        
        typedef BufferType Buffer_t;
        
        EffectFilter(const unsigned long minIndex, const unsigned long maxIndex, const double multStrength,
                     DampedBoundedVelocityProperty<double> boundedAggregate):
        _minIndex(minIndex), _maxIndex(maxIndex), _multStrength(multStrength), _boundedAggregate(boundedAggregate)
        {}
        
        ~EffectFilter(){}
        
        void applyFilter(const BufferType * inputBuffer, const double dt){
            _boundedAggregate.setScale(dt);
            
            double mostRecentResult = 0.0;
            for (unsigned long i = _minIndex; i < _maxIndex; ++i) {
                mostRecentResult += inputBuffer[i] * _multStrength;
            }
            
            _boundedAggregate.offsetTowards(mostRecentResult);
        }
        
        inline double getMostRecentResult()const{
            return _boundedAggregate.getOrigin();
        }
    private:
        unsigned long _minIndex;
        unsigned long _maxIndex;
        double _multStrength;
        DampedBoundedVelocityProperty<double> _boundedAggregate;
    };
}

#endif /* EffectFiler_hpp */

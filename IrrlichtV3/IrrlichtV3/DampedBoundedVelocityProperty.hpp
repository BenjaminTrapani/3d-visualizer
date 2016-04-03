//
//  DampedBoundedVelocityProperty.h
//  IrrlichtV3
//
//  Created by Benjamin Trapani on 2/19/16.
//  Copyright © 2016 Benjamin Trapani. All rights reserved.
//

#ifndef DampedBoundedVelocityProperty_h
#define DampedBoundedVelocityProperty_h
#include "DampedVelocityProperty.hpp"

namespace Viz3d {
    template<class T>
    class DampedBoundedVelocityProperty{
    public:
        DampedBoundedVelocityProperty(const DampedVelocityProperty<T> & coreType,
                                      const T & minBound, const T & maxBound):_coreType(coreType),
        _minBound(minBound), _maxBound(maxBound){}
        
        T offsetTowards(const T & value){
            const T newPos = _coreType.offsetTowards(value);
            if (newPos>_maxBound) {
                _coreType.hardResetOrigin(_maxBound);
            }else if(newPos < _minBound){
                _coreType.hardResetOrigin(_minBound);
            }
            return _coreType.getOrigin();
        }
        
        T getOrigin()const{
            return _coreType.getOrigin();
        }
        
        void setScale(const T & scale){
            _coreType.setScale(scale);
        }
        
    private:
        DampedVelocityProperty<T> _coreType;
        T _minBound;
        T _maxBound;
    };
}

#endif /* DampedBoundedVelocityProperty_h */

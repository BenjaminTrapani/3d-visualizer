//
//  DampedVelocityProperty.hpp
//  IrrlichtV3
//
//  Created by Benjamin Trapani on 2/19/16.
//  Copyright © 2016 Benjamin Trapani. All rights reserved.
//

#ifndef DampedVelocityProperty_h
#define DampedVelocityProperty_h

namespace Viz3d {
    template<class T>
    class DampedVelocityProperty{
    public:
        DampedVelocityProperty(const T & origin, const T forwardCap, const T downwardCap,
                               const T & scale):_origin(origin),
        _forwardCap(forwardCap), _downwardCap(downwardCap), _scale(scale){
        }
        
        T offsetTowards(const T & newValue){
            T dist = newValue - _origin;
            const T scaledForwardCap = _forwardCap * _scale;
            const T scaledDownwardCap = _downwardCap * _scale;
            if (dist > 0 && dist > scaledForwardCap) {
                dist = scaledForwardCap;
            }
            if (dist < 0 && dist < scaledDownwardCap) {
                dist = scaledDownwardCap*-1.0;
            }
            _origin += dist;
            return _origin;
        }
        void hardResetOrigin(const T & newValue){
            _origin = newValue;
        }
        T getOrigin()const{
            return _origin;
        }
        void setScale(const T & scale){
            _scale = scale;
        }
    private:
        T _origin;
        T _forwardCap;
        T _downwardCap;
        T _scale;
    };
}

#endif /* DampedVelocityProperty_h */

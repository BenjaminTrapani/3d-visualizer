//
//  EventReciever.hpp
//  IrrlichtV3
//
//  Created by Benjamin Trapani on 3/11/16.
//  Copyright © 2016 Benjamin Trapani. All rights reserved.
//

#ifndef EventReciever_hpp
#define EventReciever_hpp

#include <stdio.h>
#include <irrlicht/irrlicht.h>
namespace Viz3d{
    class EventReciever: public irr::IEventReceiver{
    public:
        bool OnEvent(const irr::SEvent& event)override;
    private:
       
    };
}
#endif /* EventReciever_hpp */

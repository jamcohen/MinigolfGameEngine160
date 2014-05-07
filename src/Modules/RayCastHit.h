//
//  RayCastHit.h
//  MiniGolfXCode
//
//  Created by Orlando Salvatore on 5/6/14.
//  Copyright (c) 2014 Orlando Salvatore. All rights reserved.
//

#ifndef __MiniGolfXCode__RayCastHit__
#define __MiniGolfXCode__RayCastHit__

#include <iostream>
#include "glm.hpp"
#include "GameObject.h"
#include "Face.h"

class RayCastHit
{
public:
    RayCastHit(Face*, glm::vec3, float);
    inline Face* getFace() { return _face; }
    inline glm::vec3 getImpactPoint() { return _impactPoint; }
    inline float getImpactDistance() { return _impactDistance; }
    
private:
    Face* _face;
    glm::vec3 _impactPoint;
    float _impactDistance;
    
};

#endif /* defined(__MiniGolfXCode__RayCastHit__) */

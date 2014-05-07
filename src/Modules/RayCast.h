//
//  RayCast.h
//  MiniGolfXCode
//
//  Created by Orlando Salvatore on 5/6/14.
//  Copyright (c) 2014 Orlando Salvatore. All rights reserved.
//

#ifndef __MiniGolfXCode__RayCast__
#define __MiniGolfXCode__RayCast__

#include <iostream>
#include <vector>
#include "GameObject.h"
#include "SceneManager.h"
#include "Face.h"
#include "glm.hpp"
#include "RayCastHit.h"

class RayCast
{
public:
    static RayCastHit* rayCast(GameObject*, glm::vec3);
};

#endif /* defined(__MiniGolfXCode__RayCast__) */

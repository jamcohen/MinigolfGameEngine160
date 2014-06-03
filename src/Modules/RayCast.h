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
    static RayCastHit* rayCast(GameObject*, glm::vec3, float radius = 0);
private:
   static std::vector<glm::vec3> getCollisionCoords(Face& face, GameObject &g, GameObject &tempG, float radius = 0);
};

#endif /* defined(__MiniGolfXCode__RayCast__) */

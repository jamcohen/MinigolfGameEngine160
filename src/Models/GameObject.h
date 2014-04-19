//
//  GameObject.h
//  MiniGolfGameEngine
//
//  Created by Orlando Salvatore on 4/17/14.
//  Copyright (c) 2014 Orlando Salvatore. All rights reserved.
//

#ifndef __MiniGolfGameEngine__GameObject__
#define __MiniGolfGameEngine__GameObject__

#include <iostream>
#include <cmath>
#include "vec3.hpp"
#include "glm.hpp"
#include "Model.h"

using namespace glm;

class GameObject
{
public:
    GameObject(vec3 pos);
    void setX(float);
    void setY(float);
    void setZ(float);
    Model* model;
    //void setPosition(detail::tvec3<<#typename T#>, <#glm::precision P#>>
    //void setPosition(glm::det);
    
};

#endif /* defined(__MiniGolfGameEngine__GameObject__) */

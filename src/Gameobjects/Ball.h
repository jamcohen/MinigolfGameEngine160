//
//  Ball.h
//  MiniGolfXCode
//
//  Created by Jake Cohen on 4/29/14.
//  Copyright (c) 2014 Orlando Salvatore. All rights reserved.
//

#ifndef __MiniGolfXCode__Ball__
#define __MiniGolfXCode__Ball__

#include <iostream>
#include "Physicsobject.h"
#include "glm.hpp"
#include "matrix_transform.hpp"
#include "DiffuseSpecularMaterial.h"
#include "Wall.h"
#include "Primative.h"


class Ball:PhysicsObject
{
public:
   Ball(glm::vec3, glm::vec3, glm::vec3, float color = 0.02f);
private:
   float _mass = 1.0f;
};

#endif /* defined(__MiniGolfXCode__Ball__) */

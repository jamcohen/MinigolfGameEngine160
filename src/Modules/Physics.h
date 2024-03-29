//
//  Physics.h
//  MiniGolfXCode
//
//  Created by Jake Cohen on 5/6/14.
//  Copyright (c) 2014 Orlando Salvatore. All rights reserved.
//

#ifndef __MiniGolfXCode__Physics__
#define __MiniGolfXCode__Physics__

#include <iostream>
#include <chrono>
#include "PhysicsObject.h"
#include "RayCast.h"
#include "glm.hpp"

class PhysicsObject;

class Physics
{
public:
    static std::vector<PhysicsObject *> physicsObjects;
    static void addToUpdateList(PhysicsObject *obj);
    static void updatePhysics(float deltaT);
private:
    static RayCastHit *checkCollision(PhysicsObject*, float);
    static RayCastHit *checkCollision(PhysicsObject*, glm::vec3, float);
    static void resolveCollision(RayCastHit* hit, float deltaT, PhysicsObject* obj);
    static glm::vec3 getReflectionVector(glm::vec3, glm::vec3);
};


#endif /* defined(__MiniGolfXCode__Physics__) */

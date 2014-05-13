//
//  Ball.h
//  MiniGolfXCode
//
//  Created by Jake Cohen on 4/29/14.
//  Copyright (c) 2014 Orlando Salvatore. All rights reserved.
//

#ifndef __MiniGolfXCode__PhysicsObject__
#define __MiniGolfXCode__PhysicsObject__

#include <iostream>
#include <chrono>
#include "GameObject.h"
#include "glm.hpp"
#include "matrix_transform.hpp"
#include "Physics.h"

class PhysicsObject : public GameObject
{
friend class Physics;
public:
   PhysicsObject(glm::vec3, glm::vec3, glm::vec3, float radius=0.05, float mass=1.0f);
   void applyForce(glm::vec3 force);
   void updatePhysics(float deltaT);
   void resetAcceleration();
private:
   glm::vec3 _acceleration;
   glm::vec3 _velocity;
   float _radius;
   float _mass;
};

#endif /* defined(__MiniGolfXCode__Ball__) */

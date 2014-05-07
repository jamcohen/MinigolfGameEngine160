//
//  Ball.cpp
//  MiniGolfXCode
//
//  Created by Jake Cohen on 4/29/14.
//  Copyright (c) 2014 Orlando Salvatore. All rights reserved.
//

#include "PhysicsObject.h"

PhysicsObject::PhysicsObject(glm::vec3 pos, glm::vec3 scale, glm::vec3 rotation, float mass): GameObject(pos, scale, rotation), _mass(mass)
{
   //Physics::addToUpdateList(this);
}

void PhysicsObject::updatePhysics(){
   _velocity += _acceleration;
   _position += _velocity;
}
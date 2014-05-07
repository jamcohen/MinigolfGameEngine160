//
//  Ball.cpp
//  ;
//
//  Created by Jake Cohen on 4/29/14.
//  Copyright (c) 2014 Orlando Salvatore. All rights reserved.
//

#include "PhysicsObject.h"

PhysicsObject::PhysicsObject(glm::vec3 pos, glm::vec3 scale, glm::vec3 rotation, float radius, float mass): GameObject(pos, scale, rotation), _mass(mass), _radius(radius)
{
   Physics::addToUpdateList(this);
   _acceleration = glm::vec3(0, -0.98f, 0);
}

void PhysicsObject::updatePhysics(float deltaT){
   float deltaTInSeconds = deltaT/1000;
   _velocity += _acceleration*deltaTInSeconds;
   _position += _velocity*deltaTInSeconds;
    
    //std::cout << " Physics position: " << _position.x << "," << _position.y << "," << _position.z << std::endl;
}
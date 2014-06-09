//
//  Ball.cpp
//  ;
//
//  Created by Jake Cohen on 4/29/14.
//  Copyright (c) 2014 Orlando Salvatore. All rights reserved.
//

#include "PhysicsObject.h"

PhysicsObject::PhysicsObject(glm::vec3 pos, glm::vec3 scale, glm::quat rotation, float radius, float mass): GameObject(pos, scale, rotation), _mass(mass), _radius(radius)
{
    Physics::addToUpdateList(this);
    resetAcceleration();
}

PhysicsObject::~PhysicsObject()
{
    
}

void PhysicsObject::updatePhysics(float deltaT){
    float deltaTInSeconds = deltaT/1000;
    //_velocity += _acceleration*deltaTInSeconds;
    _position += _velocity*deltaTInSeconds;
    
    //std::cout << " Physics position: " << _position.x << "," << _position.y << "," << _position.z << std::endl;
}

void PhysicsObject::stop(){
   _velocity = glm::vec3(0,0,0);
   _acceleration = glm::vec3(0,0,0);
}

void PhysicsObject::resetAcceleration(){
     _acceleration = glm::vec3(0, -10.8f, 0);
}

void PhysicsObject::applyForce(glm::vec3 force){
   _acceleration += force/_mass;
}
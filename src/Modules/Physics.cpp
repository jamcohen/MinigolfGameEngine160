//
//  Physics.cpp
//  MiniGolfXCode
//
//  Created by Jake Cohen on 5/6/14.
//  Copyright (c) 2014 Orlando Salvatore. All rights reserved.
//

#include "Physics.h"

std::vector<PhysicsObject *> Physics::physicsObjects;

void Physics::addToUpdateList(PhysicsObject *obj){
   physicsObjects.push_back(obj);
}

void Physics::updatePhysics(std::chrono::duration<float> deltaT){
   for(auto objPtr : physicsObjects){
      PhysicsObject obj = *objPtr;
      //Check collision
   }
}

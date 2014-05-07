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

void Physics::updatePhysics(float deltaT){
   for(auto objPtr : physicsObjects){
      PhysicsObject obj = *objPtr;
      RayCastHit *hit = checkCollision(obj, deltaT);
      if(hit == nullptr){
         obj.updatePhysics(deltaT);
      }else{
         resolveCollision(hit, deltaT, obj);
      }
   }
}

RayCastHit *Physics::checkCollision(PhysicsObject &obj, float deltaT){
   RayCastHit* hit = RayCast::rayCast(&obj, obj._velocity);
   if(hit != nullptr){
      float distanceUntilCollision = hit->getImpactDistance()-obj._radius;
      float secondsUntilCollision = distanceUntilCollision/glm::length(obj._velocity);
      float timeUntilCollision = secondsUntilCollision*1000; //MILLISECONDS!!!
      
      //If the ball won't collide this step ignore collision
      if(timeUntilCollision < deltaT){
         return nullptr;
      }
   }
   return hit;
}

void Physics::resolveCollision(RayCastHit* hit, float deltaT, PhysicsObject& obj){
   float distanceUntilCollision = hit->getImpactDistance()-obj._radius;
   float secondsUntilCollision = distanceUntilCollision/glm::length(obj._velocity);
   float timeUntilCollision = secondsUntilCollision*1000; //MILLISECONDS!!!
   
   float timeLeftAfterCollision = deltaT - timeUntilCollision;
   float distanceAfterCollision = timeLeftAfterCollision*glm::length(obj._velocity)/1000;
   
   //reflection vector
   glm::vec3 R = glm::vec3(0,1,1);
   
   obj._position = R*(distanceAfterCollision + obj._radius)+hit->getImpactPoint();
   obj._velocity = R*glm::length(obj._velocity);
   obj._velocity += obj._acceleration*(deltaT/1000);
   
}
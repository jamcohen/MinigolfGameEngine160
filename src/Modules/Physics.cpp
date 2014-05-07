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
    deltaT = deltaT/1000;
    for(PhysicsObject *obj : physicsObjects){
        RayCastHit *hit = checkCollision(obj, deltaT);
        if(hit == nullptr){
            obj->updatePhysics(deltaT);
        }else{
            resolveCollision(hit, deltaT, obj);
        }
    }
}

RayCastHit *Physics::checkCollision(PhysicsObject* obj, float deltaT)
{
   RayCastHit* hit = RayCast::rayCast(obj, obj->_velocity);
   if(hit != nullptr){
      float distanceUntilCollision = hit->getImpactDistance()-obj->_radius;
      float secondsUntilCollision = distanceUntilCollision/glm::length(obj->_velocity);
      float timeUntilCollision = secondsUntilCollision*1000; //MILLISECONDS!!!
      
      //If the ball won't collide this step ignore collision
      if(timeUntilCollision > deltaT){
         return nullptr;
      }
   }
    std::cout << "HIT\n";
   return hit;
}

void Physics::resolveCollision(RayCastHit* hit, float deltaT, PhysicsObject* obj)
{
    float distanceUntilCollision = hit->getImpactDistance()-obj->_radius;
    float secondsUntilCollision = distanceUntilCollision/glm::length(obj->_velocity);
    float timeUntilCollision = secondsUntilCollision*1000; //MILLISECONDS!!!
   
    float timeLeftAfterCollision = deltaT - timeUntilCollision;
    float distanceAfterCollision = timeLeftAfterCollision*glm::length(obj->_velocity)/1000;
    distanceAfterCollision = fabs(distanceAfterCollision);
    std::cout << distanceAfterCollision << std::endl;
   
    //reflection vector
    glm::vec3 R = getReflectionVector(obj->_velocity, hit->getFace()->getNormal());
   
    //obj->_position = R*(distanceAfterCollision + obj->_radius)+hit->getImpactPoint();
    obj->_position = R*(distanceAfterCollision)+hit->getImpactPoint();
    std::cout << obj->_position.x << "," << obj->_position.y << "," << obj->_position.z << std::endl;
    obj->_velocity = R*glm::length(obj->_velocity);
    std::cout << obj->_velocity.x << "," << obj->_velocity.y << "," << obj->_velocity.z << std::endl;
    obj->_velocity += obj->_acceleration*(deltaT/1000);

}

glm::vec3 Physics::getReflectionVector(glm::vec3 dir, glm::vec3 norm)
{
    //d−2(d⋅n)n
    norm = glm::normalize(norm);
    glm::vec3 rVec = dir - 2*(glm::dot(dir, norm))*norm;
    
    rVec = glm::normalize(rVec);
    
    std::cout << "Reflection Vector: " << rVec.x << "," << rVec.y << "," << rVec.z << std::endl;
    
    return rVec;
}

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
    for(PhysicsObject *obj : physicsObjects){
        obj->_velocity += obj->_acceleration*(deltaT/1000);
        obj->resetAcceleration();
        RayCastHit *hit = checkCollision(obj, deltaT);
        if(hit == nullptr){
            obj->updatePhysics(deltaT);
        }else{
           std::cout << "Resolving" << std::endl;
           resolveCollision(hit, deltaT, obj);
        }
    }
}

RayCastHit *Physics::checkCollision(PhysicsObject* obj, float deltaT)
{
   //If the object isn't moving, there is no collision;
   if(glm::length(obj->_velocity) == 0) return nullptr;
   
   RayCastHit* hit = RayCast::rayCast(obj, glm::normalize(obj->_velocity), obj->getRadius());
   //glm::vec3 pos = obj->getPosition();
   //hit = new RayCastHit(obj->getModel()->getFaces()[0], glm::vec3(pos.x,0,pos.z), pos.y);
   //std::cout << obj->_velocity.y << std::endl;
   if(hit != nullptr){
       float distanceUntilCollision = hit->getImpactDistance();//-obj->_radius;
      float secondsUntilCollision = distanceUntilCollision/glm::length(obj->_velocity);
      float timeUntilCollision = secondsUntilCollision*1000; //MILLISECONDS!!!
      
      //std::cout << "Raycast hit: " << timeUntilCollision << std::endl;
      
      //std::cout << "HIT: " << std::endl;
      //If the ball won't collide this step ignore collision
      if(timeUntilCollision > deltaT){
         return nullptr;
      }
   }
   
   return hit;
}

RayCastHit *Physics::checkCollision(PhysicsObject* obj, glm::vec3 dir, float deltaT)
{
    //If the object isn't moving, there is no collision;
    if(glm::length(obj->_velocity) == 0) return nullptr;
    
    RayCastHit* hit = RayCast::rayCast(obj, dir, obj->getRadius());
    //glm::vec3 pos = obj->getPosition();
    //hit = new RayCastHit(obj->getModel()->getFaces()[0], glm::vec3(pos.x,0,pos.z), pos.y);
    //std::cout << obj->_velocity.y << std::endl;
    if(hit != nullptr){
        float distanceUntilCollision = hit->getImpactDistance();//-obj->_radius;
        float secondsUntilCollision = distanceUntilCollision/glm::length(dir);
        float timeUntilCollision = secondsUntilCollision*1000; //MILLISECONDS!!!
        
        //std::cout << "Raycast hit: " << timeUntilCollision << std::endl;
        
        //std::cout << "HIT: " << std::endl;
        //If the ball won't collide this step ignore collision
        if(timeUntilCollision > deltaT){
            return nullptr;
        }
    }
    
    return hit;
}

void Physics::resolveCollision(RayCastHit* hit, float deltaT, PhysicsObject* obj)
{
    float distanceUntilCollision = hit->getImpactDistance();//-obj->_radius;
    float secondsUntilCollision = distanceUntilCollision/glm::length(obj->_velocity);
    float timeUntilCollision = secondsUntilCollision*1000; //MILLISECONDS!!!
   
    float timeLeftAfterCollision = deltaT - timeUntilCollision;
    float distanceAfterCollision = timeLeftAfterCollision*glm::length(obj->_velocity)/1000;
    distanceAfterCollision = fabs(distanceAfterCollision);
    std::cout << "distanceAfter: " << distanceAfterCollision << std::endl;
    std::cout << "deltaT: " << deltaT << std::endl;
    std::cout << "distanceUntilCollision: " << distanceUntilCollision << std::endl;
   
    //reflection vector
    glm::vec3 normal(hit->getFace()->getWorldNormal(obj));
    glm::vec3 R = getReflectionVector(obj->_velocity, normal);
    //std::cout << "Normal:" << normal.x << "," << normal.y << "," << normal.z << std::endl;
    hit->getFace()->print(hit->getGameObject());
    std::cout << "R:" << R.x << "," << R.y << "," << R.z << std::endl;
    glm::vec3 impact(hit->getImpactPoint());
    std::cout << "impact:" << impact.x << "," << impact.y << "," << impact.z << std::endl;
    //obj->_position = R*(distanceAfterCollision + obj->_radius)+hit->getImpactPoint();
    
    float dampening = 0.9f;
    obj->_position = hit->getImpactPoint();
    RayCastHit *hit2 = checkCollision(obj,glm::normalize(R*glm::length(obj->_velocity)*dampening),deltaT);
    //RayCastHit *hit2 = nullptr;
    if(hit2 != nullptr) {
        float distanceUntilCollision2 = hit2->getImpactDistance();//-obj->_radius;
        float secondsUntilCollision2 = distanceUntilCollision2/glm::length(obj->_velocity);
        float timeUntilCollision2 = secondsUntilCollision2*1000; //MILLISECONDS!!!
        if(timeUntilCollision - timeUntilCollision2 < deltaT)
        {
            std::cout << " GOING TO HIT AGAIN SOON!\n";
            obj->_velocity = R*glm::length(obj->_velocity)*dampening;
            resolveCollision(hit2, deltaT, obj);
        }
        else
        {
            obj->_position = R*(distanceAfterCollision)+hit->getImpactPoint();
            std::cout << "Pos: " << obj->_position.x << "," << obj->_position.y << "," << obj->_position.z << std::endl;
            obj->_velocity = R*glm::length(obj->_velocity)*dampening;
            std::cout << "Vel: " << obj->_velocity.x << "," << obj->_velocity.y << "," << obj->_velocity.z << std::endl;
        }
        
    }else{
        std::cout << "prePos: " << obj->_position.x << "," << obj->_position.y << "," << obj->_position.z << std::endl;
        obj->_position = R*(distanceAfterCollision)+hit->getImpactPoint();
        std::cout << "postPos: " << obj->_position.x << "," << obj->_position.y << "," << obj->_position.z << std::endl;
        std::cout << "preVel: " << obj->_velocity.x << "," << obj->_velocity.y << "," << obj->_velocity.z << std::endl;
        obj->_velocity = R*glm::length(obj->_velocity)*dampening;
        std::cout << "postVel: " << obj->_velocity.x << "," << obj->_velocity.y << "," << obj->_velocity.z << std::endl;
    }
    
    obj->onCollision(hit->getGameObject());
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

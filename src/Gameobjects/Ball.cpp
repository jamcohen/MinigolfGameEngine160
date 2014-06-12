//
//  Ball.cpp
//  MiniGolfXCode
//
//  Created by Jake Cohen on 4/29/14.
//  Copyright (c) 2014 Orlando Salvatore. All rights reserved.
//

#include "Ball.h"
#include "LevelManager.h"

Ball::Ball(glm::vec3 origin, glm::quat rotation, glm::vec3 color, float radius):
PhysicsObject(origin, glm::vec3(radius, radius, radius), rotation, radius)
{
   DiffuseSpecularMaterial *d = new DiffuseSpecularMaterial(100);
   Model* m = Primative::getSphere(color);
   _model = m;
   _model->material = d;
   _model->initializeBuffers();
}

Ball::~Ball()
{
    
}

void Ball::update(){
   Gizmo::instance().addDebugRay(getPosition(), getPosition()+_velocity);
   if(this->getPosition().y < -30.0f){
      LevelManager::instance().restartLevel(true);
      //std::cout << "whatthrcfuc";
   }
}

void Ball::onCollision(GameObject *that){
   Cup *cup = LevelManager::instance().getCurrentLevel()->getCup();
   if(that == cup){
      LevelManager::instance().levelCompleted();
   }
    for(Portal *p : LevelManager::instance().getCurrentLevel()->getPortals())
    {
        if(that == p)
        {
            std::cout << "Lets do this ";
            onPortalEnter(p);
        }
    }
}

void Ball::onPortalEnter(Portal* p)
{
    glm::vec3 dir = p->getConnectedPortal()->getPosition()-p->getPosition();
    glm::vec3 n1(p->getModel()->getNormals()[0]);
    glm::vec3 n2(p->getConnectedPortal()->getModel()->getNormals()[0]);
    float cos_theta = glm::dot(glm::normalize(n1),glm::normalize(n2));
    float angle = acos(cos_theta);
    
    glm::vec3 axis = glm::normalize(glm::cross(p->getModel()->getNormals()[0],p->getConnectedPortal()->getModel()->getNormals()[0]));
    std::cout << "AXIS: " << axis.x << ", " << axis.y << ", " << axis.z << std::endl;
    std::cout << "Normal1: " << n1.x << ", " << n1.y << ", " << n1.z << std::endl;
    std::cout << "Normal2: " << n2.x << ", " << n2.y << ", " << n2.z << std::endl;
    std::cout << "ANGLE: " << angle << std::endl;
    //glm::quat rotationZ =  glm::normalize(glm::angleAxis((float)(angle*180.0f/M_PI), axis));
    glm::quat rotationZ{};
    if(!isnan(axis.x)){
        rotationZ =  glm::angleAxis(angle*float(180/M_PI), axis);
    }
    glm::mat4 T = glm::translate(glm::mat4(), dir);
    glm::mat4 R = glm::mat4_cast(rotationZ);
    glm::mat4 model = T*R;
    glm::vec4 newPos = model*glm::vec4(_position.x, _position.y, _position.z, 1);
    glm::vec4 newVel = R*glm::vec4(_velocity.x, _velocity.y, _velocity.z, 1);
    _position = glm::vec3(newPos);
    _velocity = glm::vec3(newVel);
    //_position = glm::vec3(0,0,0);
    angle *= 180.0f/M_PI;
}

void Ball::onKeyPress(SDL_Keycode key)
{
   float impulseAmount = 40.0f;
   Camera *c = SceneManager::instance().getCurrentCamera();
   glm::vec3 force = c->getForwardDirectionVector();
   float jumpForce = 100.0f;
   force.y = 0;
   force = glm::normalize(force);
   force *= impulseAmount;
   switch(key)
   {
      case SDLK_SPACE:
         this->applyForce(glm::vec3(0,jumpForce,0));
         break;
         
      case SDLK_UP:
         //this->_velocity+=force;
         this->applyForce(force);
         break;
         
      case SDLK_DOWN:
         this->applyForce(-force);
         //this->_velocity-=force;
         break;
         
      /*case SDLK_RIGHT:
         this->applyForce(glm::vec3(-7,0,0));
         break;
         
      case SDLK_LEFT:
         this->applyForce(glm::vec3(7,0,0));
         break;*/
         
      default:
         break;
   }
}
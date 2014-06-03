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
   SceneManager::instance().setBall(this);
   DiffuseSpecularMaterial *d = new DiffuseSpecularMaterial(100);
   Model* m = Primative::getSphere(color);
   _model = m;
   _model->material = d;
   _model->initializeBuffers();
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
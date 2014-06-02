//
//  Camera.cpp
//  MiniGolfXCode
//
//  Created by Orlando Salvatore on 4/20/14.
//  Copyright (c) 2014 Orlando Salvatore. All rights reserved.
//

#include "BallCamera.h"
#include "Ball.h"

#define _USE_MATH_DEFINES

BallCamera::BallCamera() : Camera(), _angle(0)
{
    SceneManager::instance().addCamera(this);
}

BallCamera::BallCamera(glm::vec3 position) : Camera(position), _angle(0)
{ }

BallCamera::~BallCamera()
{ }

void BallCamera::update(){
   float height = 1.0f;
   float dist = 1.0f;
   Ball *b = SceneManager::instance().getBall();
   glm::vec3 ballPos = b->getPosition();
   _position = glm::vec3(cos(_angle)*dist+ballPos.x, height+ballPos.y,sin(_angle)*dist+ballPos.z);
   _target = ballPos;
   
}

void BallCamera::onKeyPress(SDL_Keycode key)
{
   switch(key)
   {
      case SDLK_RIGHT:
         _angle+=M_PI/14;
         break;
         
      case SDLK_LEFT:
         _angle-=M_PI/14;
         break;
         
      default:
         break;
   }
}
//
//  Ball.cpp
//  MiniGolfXCode
//
//  Created by Jake Cohen on 4/29/14.
//  Copyright (c) 2014 Orlando Salvatore. All rights reserved.
//

#include "Ball.h"

Ball::Ball(glm::vec3 origin, glm::vec3 rotation, glm::vec3 color, float radius):
PhysicsObject(origin, glm::vec3(radius, radius, radius), rotation, radius)
{
   SceneManager::instance().setBall(this);
   DiffuseSpecularMaterial *d = new DiffuseSpecularMaterial(100);
   Model* m = Primative::getSphere(color);
   _model = m;
   _model->material = d;
   _model->initializeBuffers();
}
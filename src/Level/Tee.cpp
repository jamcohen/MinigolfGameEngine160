//
//  Tee.cpp
//  MiniGolfXCode
//
//  Created by Orlando Salvatore on 4/19/14.
//  Copyright (c) 2014 Orlando Salvatore. All rights reserved.
//

#include "Tee.h"

Tee::Tee(int index, glm::vec3 pos) : _index(index),  GameObject(pos, glm::vec3(0.2, 0.2, 0.2), glm::quat())
{
   DiffuseSpecularMaterial *d = new DiffuseSpecularMaterial(100);
   _color = glm::vec3(0,0,0.5);
   Model* m = Primative::getCube(_color);//getModel(width, height);
   _model = m;
   _model->material = d;
   _model->initializeBuffers();
}
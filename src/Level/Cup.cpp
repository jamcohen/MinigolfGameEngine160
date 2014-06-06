//
//  Cup.cpp
//  MiniGolfXCode
//
//  Created by Orlando Salvatore on 4/19/14.
//  Copyright (c) 2014 Orlando Salvatore. All rights reserved.
//

#include "Cup.h"

Cup::Cup(int index, glm::vec3 pos) : _index(index),  GameObject(pos, glm::vec3(0.1, 0.01, 0.1), glm::quat())
{
   DiffuseSpecularMaterial *d = new DiffuseSpecularMaterial(100);
   _color = glm::vec3(0.6,0.15,0);
   Model* m = Primative::getSphere(_color, 1);//getModel(width, height);
   _model = m;
   _model->material = d;
   _model->initializeBuffers();
}

Cup::~Cup()
{
    
}
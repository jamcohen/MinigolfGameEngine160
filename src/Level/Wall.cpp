//
//  Wall.cpp
//  MiniGolfXCode
//
//  Created by Jake Cohen on 4/24/14.
//  Copyright (c) 2014 Orlando Salvatore. All rights reserved.
//

#include "Wall.h"

Wall::Wall(const glm::vec3 origin, const glm::quat rotation, float width, float height, float length, glm::vec3 color) : GameObject(origin, glm::vec3(width, height, length), rotation)
{
    DiffuseSpecularMaterial *d = new DiffuseSpecularMaterial(100);
    _color = color;
    Model* m = Primative::getCube(color);//getModel(width, height);
    _model = m;
    _model->material = d;
    _model->initializeBuffers();
}

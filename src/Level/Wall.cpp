//
//  Wall.cpp
//  MiniGolfXCode
//
//  Created by Jake Cohen on 4/24/14.
//  Copyright (c) 2014 Orlando Salvatore. All rights reserved.
//

#include "Wall.h"

Wall::Wall(const glm::vec3 origin, glm::vec3 p1, glm::vec3 p2, float width, float height, glm::vec3 color) : GameObject(origin, glm::vec3(1, 1, 1), glm::quat())
{
    DiffuseSpecularMaterial *d = new DiffuseSpecularMaterial(100);
    _color = color;
    Model* m = Primative::getBox(p1, p2, width, height);//getModel(width, height);
    _model = m;
    _model->material = d;
    _model->initializeBuffers();
}

Wall::Wall(const glm::vec3 origin, const glm::quat rotation, float width, float height, float length, glm::vec3 color) : GameObject(origin, glm::vec3(width, height, length), rotation)
{
    DiffuseSpecularMaterial *d = new DiffuseSpecularMaterial(100);
    _color = color;
    Model* m = Primative::getCube(color);//getModel(width, height);
    _model = m;
    _model->material = d;
    _model->initializeBuffers();
}

Wall::~Wall()
{
    
}
//
//  GameObject.cpp
//  MiniGolfGameEngine
//
//  Created by Orlando Salvatore on 4/17/14.
//  Copyright (c) 2014 Orlando Salvatore. All rights reserved.
//

#include "GameObject.h"

GameObject::GameObject(glm::vec3 pos, Model *model) : _position(pos), _model(model)
{
    SceneManager::instance().addGameObject(this);
}

GameObject::~GameObject()
{
    delete _model;
}

void GameObject::setX(float x)
{
    _position.x = x;
}

void GameObject::setY(float y)
{
    _position.y = y;
}

void GameObject::setZ(float z)
{
    _position.z = z;
}

void GameObject::draw(){
    model->draw(position);
}

void GameObject::setPosition(glm::vec3 p)
{
    _position = p;
}

Model* GameObject::getModel(){
    return _model;
}
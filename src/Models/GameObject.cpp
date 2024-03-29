//
//  GameObject.cpp
//  MiniGolfGameEngine
//
//  Created by Orlando Salvatore on 4/17/14.
//  Copyright (c) 2014 Orlando Salvatore. All rights reserved.
//

#include "GameObject.h"

GameObject::GameObject(glm::vec3 pos) : _position(pos), _rotation(), _scale(1,1,1)
{
}

GameObject::GameObject(glm::vec3 pos, glm::vec3 scale, glm::quat rotation) : _position(pos), _rotation(rotation), _scale(scale)
{

}

GameObject::GameObject(glm::vec3 pos, Model *model) : _position(pos), _model(model), _rotation(), _scale(1,1,1)
{
    model->setGameObject(this);
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
    _model->draw(_position, _scale, _rotation);
}

void GameObject::setPosition(glm::vec3 p)
{
    _position = p;
}

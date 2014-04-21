//
//  Camera.cpp
//  MiniGolfXCode
//
//  Created by Orlando Salvatore on 4/20/14.
//  Copyright (c) 2014 Orlando Salvatore. All rights reserved.
//

#include "Camera.h"

Camera::Camera() : _position(0, 0.5, -1), _target(0,0,0), _up(0,1,0)
{
    SceneManager::instance().addCamera(this);
}

Camera::Camera(glm::vec3 position) : _position(position)
{ }

Camera::~Camera()
{ }

void Camera::setPosition(float x, float y, float z)
{
    glm::vec3 tempPos(x,y,z);
    _position = tempPos;
}

void Camera::setTarget(float x,float y,float z)
{
    glm::vec3 tempPos(x,y,z);
    _target = tempPos;
}

void Camera::setTarget(GameObject* g)
{
    _target = g->getPosition();
}

void Camera::setUp(float x, float y, float z)
{
    glm::vec3 tempPos(x,y,z);
    _up = tempPos;
}
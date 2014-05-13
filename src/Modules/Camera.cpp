//
//  Camera.cpp
//  MiniGolfXCode
//
//  Created by Orlando Salvatore on 4/20/14.
//  Copyright (c) 2014 Orlando Salvatore. All rights reserved.
//

#include "Camera.h"

#define _USE_MATH_DEFINES

glm::vec3 Camera::FORWARD_VECTOR(0,0,1);

Camera::Camera() : _position(0, 0, 0), _target(0,0,1), _up(0,1,0), _lockedAngles(-1,-1), _currentPitchAngle(0), _currentYawAngle(0)
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
    _currentYawAngle = _currentPitchAngle = 0;
    setTarget(_position.x + 0, _position.y + 0, _position.z + 1);
}

void Camera::setTarget(float x,float y,float z)
{
    glm::vec3 tempPos(x,y,z);
    _target = tempPos;
    _currentYawAngle = _currentPitchAngle = 0;
}

void Camera::rotateYaw(float angle)
{
    //Check if camera should be locked
    if(_lockedAngles.x != -1)
    {
        float offset = (angle > 0)?0.01f:-0.01f;
        if(_currentPitchAngle + angle > _lockedAngles.x)
        {
            angle = _lockedAngles.x - _currentPitchAngle - offset;
        }else if(_currentPitchAngle + angle < -1*_lockedAngles.x){
            angle = -1*_lockedAngles.x - _currentPitchAngle - offset;
        }
    }
    _currentYawAngle += angle;
    angle = angle*M_PI/180.0f;
    glm::mat3 rotateMatrixY(cos(angle),0,sin(angle),
                            0,1,0,
                            -sin(angle),0,cos(angle));
    glm::vec3 directionVector = _target - _position;
    directionVector = rotateMatrixY*directionVector;
    _target = _position + directionVector;
}

void Camera::rotatePitch(float angle)
{
    //Check if camera should be locked
    if(_lockedAngles.y != -1)
    {
        float offset = (angle > 0)?0.01f:-0.01f;
        if(_currentPitchAngle + angle > _lockedAngles.y)
        {
            angle = _lockedAngles.y - _currentPitchAngle - offset;
        }else if(_currentPitchAngle + angle < -1*_lockedAngles.y){
            angle = -1*_lockedAngles.y - _currentPitchAngle - offset;
        }
    }
    _currentPitchAngle += angle;
    angle = angle*M_PI/180.0f;
    glm::mat3 rotateMatrixX(1,0,0,
                            0,cos(angle),-sin(angle),
                            0,sin(angle),cos(angle));
    glm::vec3 directionVector = _target - _position;
    directionVector = rotateMatrixX*directionVector;
    _target = _position + directionVector;
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

glm::vec3 Camera::getForwardDirectionVector()
{
    return _target - _position;
}
//
//  Camera.h
//  MiniGolfXCode
//
//  Created by Orlando Salvatore on 4/20/14.
//  Copyright (c) 2014 Orlando Salvatore. All rights reserved.
//

#ifndef __MiniGolfXCode__Camera__
#define __MiniGolfXCode__Camera__

#include <iostream>
#include <cmath>
#include "glm.hpp"
#include "GameObject.h"
#include "SceneManager.h"

class Camera
{
public:
    Camera();
    Camera(glm::vec3);
    ~Camera();
    virtual void update(){};
    virtual void onKeyPress(SDL_Keycode){};
    //Position
    void setPosition(float,float,float);
    inline void setPosition(glm::vec3 position) { _position = position; }
    inline void setPositionX(float x) { _position.x = x; }
    inline void setPositionY(float y) { _position.y = y; }
    inline void setPositionZ(float z) { _position.z = z; }
    inline glm::vec3 getPosition() { return _position; }
    inline float getPositionX() { return _position.x; }
    inline float getPositionY() { return _position.y; }
    inline float getPositionZ() { return _position.z; }
    //Target
    void setTarget(float,float,float);
    void setTarget(GameObject *);
    inline void setTarget(glm::vec3 target) { _target = target; }
    inline void setTargetX(float x) { _target.x = x; }
    inline void setTargetY(float y) { _target.y = y; }
    inline void setTargetZ(float z) { _target.z = z; }
    inline glm::vec3 getTarget() { return _target; }
    inline float getTargetX() { return _target.x; }
    inline float getTargetY() { return _target.y; }
    inline float getTargetZ() { return _target.z; }
    //Up
    void setUp(float,float,float);
    inline void setUp(glm::vec3 target) { _up = target; }
    inline void setUpX(float x) { _up.x = x; }
    inline void setUpY(float y) { _up.y = y; }
    inline void setUpZ(float z) { _up.z = z; }
    inline glm::vec3 getUp() { return _up; }
    inline float getUpX() { return _up.x; }
    inline float getUpY() { return _up.y; }
    inline float getUpZ() { return _up.z; }
    //Pitch & Yaw
    inline void lockPitch(float y) { _lockedAngles.y = y; }
    inline void lockYaw(float x) { _lockedAngles.x = x; }
    void rotateYaw(float);
    void rotatePitch(float);
    //Forward direction vector
    glm::vec3 getForwardDirectionVector();
    
protected:
    static glm::vec3 FORWARD_VECTOR;
    glm::vec3 _position;
    glm::vec3 _target;
    glm::vec3 _up;
    glm::vec2 _lockedAngles;
    float _currentPitchAngle;
    float _currentYawAngle;
};

#endif /* defined(__MiniGolfXCode__Camera__) */

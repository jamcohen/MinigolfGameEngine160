//
//  InputManager.h
//  MiniGolfXCode
//
//  Created by Orlando Salvatore on 4/18/14.
//  Copyright (c) 2014 Orlando Salvatore. All rights reserved.
//

#ifndef __MiniGolfXCode__InputManager__
#define __MiniGolfXCode__InputManager__

#include <iostream>
#include <SDL2/SDL.h>
#include "SceneManager.h"
#include "Camera.h"
#include "Ball.h"

class InputManager
{
public:
    static const float MOVEMENT_SPEED;
    static const float MOUSE_DAMPENING;
    
    static InputManager& instance()
    {
        static InputManager INSTANCE;
        return INSTANCE;
    }
    InputManager(InputManager const&);
    void operator=(InputManager const&);
    InputManager();
    void handleMouse(SDL_Event *);
    bool handleKey(SDL_Keycode);
    void moveForward();
    void moveBackward();
    void moveRight();
    void moveLeft();
    void rotatePitch(float);
    void rotateYaw(float);
    
private:
    float _currentUpAngle;
    bool _firstTimeGettingMouse;
    glm::vec2 _previousMouseCords;
};

#endif /* defined(__MiniGolfXCode__InputManager__) */

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

class InputManager
{
public:
    static const float SPEED;
    
    static InputManager& instance()
    {
        static InputManager INSTANCE;
        return INSTANCE;
    }
    InputManager(InputManager const&);
    void operator=(InputManager const&);
    InputManager();
    bool handleKey(SDL_Keycode);
    void moveForward();
    void moveBackward();
    void moveRight();
    void moveLeft();
};

#endif /* defined(__MiniGolfXCode__InputManager__) */

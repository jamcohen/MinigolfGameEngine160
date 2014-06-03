//
//  Camera.h
//  MiniGolfXCode
//
//  Created by Orlando Salvatore on 4/20/14.
//  Copyright (c) 2014 Orlando Salvatore. All rights reserved.
//

#ifndef __MiniGolfXCode__BallCamera__
#define __MiniGolfXCode__BallCamera__

#include <iostream>
#include <cmath>
#include "glm.hpp"
#include "GameObject.h"
#include "SceneManager.h"
#include "Camera.h"

class BallCamera : public Camera
{
public:
    BallCamera();
    BallCamera(glm::vec3);
    ~BallCamera();
    virtual void update();
    virtual void onKeyPress(SDL_Keycode);
private:
    float _angle;
};

#endif /* defined(__MiniGolfXCode__Camera__) */

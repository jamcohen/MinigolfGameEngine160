//
//  GameObject.h
//  MiniGolfGameEngine
//
//  Created by Orlando Salvatore on 4/17/14.
//  Copyright (c) 2014 Orlando Salvatore. All rights reserved.
//

#ifndef __MiniGolfGameEngine__GameObject__
#define __MiniGolfGameEngine__GameObject__

#include <iostream>
#include <cmath>
#include "vec3.hpp"
#include "glm.hpp"
#include "Model.h"
#include "SceneManager.h"

class GameObject
{
public:
    GameObject(glm::vec3);
    ~GameObject();
    void setX(float);
    void setY(float);
    void setZ(float);
    void setPosition(glm::vec3);
    void draw();
    Model* getModel();
protected:
    Model* model;
    glm::vec3 _position;
    
};

#endif /* defined(__MiniGolfGameEngine__GameObject__) */

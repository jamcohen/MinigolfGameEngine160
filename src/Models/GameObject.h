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

class Model;

class GameObject
{
public:
    GameObject(glm::vec3);
    GameObject(glm::vec3, glm::vec3, glm::vec3);
    GameObject(glm::vec3, Model*);
    ~GameObject();
    void setX(float);
    void setY(float);
    void setZ(float);
    void setPosition(glm::vec3);
    inline glm::vec3 getPosition() { return _position; }
    inline glm::vec3 getScale() { return _scale; }
    inline glm::vec3 getRotation() { return _rotation; }
    void draw();
    inline Model* getModel() { return _model; }
    inline void setModel(Model *m) { _model = m; }

protected:
    Model* _model;
    glm::vec3 _position;
    glm::vec3 _scale;
    glm::vec3 _rotation;
    
};

#endif /* defined(__MiniGolfGameEngine__GameObject__) */

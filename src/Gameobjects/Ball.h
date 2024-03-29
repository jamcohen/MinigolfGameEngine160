//
//  Ball.h
//  MiniGolfXCode
//
//  Created by Jake Cohen on 4/29/14.
//  Copyright (c) 2014 Orlando Salvatore. All rights reserved.
//

#ifndef __MiniGolfXCode__Ball__
#define __MiniGolfXCode__Ball__

#include <iostream>
#include "PhysicsObject.h"
#include "glm.hpp"
#include "matrix_transform.hpp"
#include "DiffuseSpecularMaterial.h"
#include "Wall.h"
#include "Primative.h"
#include "SceneManager.h"
#include "Gizmo.h"
#include "Portal.h"


class Ball : public PhysicsObject
{
public:
    Ball(glm::vec3, glm::quat, glm::vec3, float color = 0.02f);
    ~Ball();
    virtual void onKeyPress(SDL_Keycode);
    virtual void update();
    virtual void onCollision(GameObject *);
    void onPortalEnter(Portal*);
private:
   float _mass = 1.0f;
};

#endif /* defined(__MiniGolfXCode__Ball__) */

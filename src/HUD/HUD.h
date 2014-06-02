//
//  HUD.h
//  MiniGolfXCode
//
//  Created by Orlando Salvatore on 6/1/14.
//  Copyright (c) 2014 Orlando Salvatore. All rights reserved.
//

#ifndef __MiniGolfXCode__HUD__
#define __MiniGolfXCode__HUD__

#include <iostream>
#include "GameObject.h"
#include "MGOpenGL.h"
#include "ShaderHelper.h"
#include "SceneManager.h"
#include "Camera.h"
#include "matrix_transform.hpp"
#include <vector>
#include <SDL2_ttf/SDL_ttf.h>

class HUD
{
public:
    static HUD& instance()
    {
        static HUD INSTANCE;
        return INSTANCE;
    }
    HUD();
    void draw();
    
private:
    glm::mat4 orthoMat;
    std::vector<glm::vec3> _vertices;
    std::vector<unsigned int> _indices;
    GLuint _vao;
    SDL_Surface *Message;

};

#endif /* defined(__MiniGolfXCode__HUD__) */

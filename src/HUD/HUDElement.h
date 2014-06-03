//
//  HUDElement.h
//  MiniGolfXCode
//
//  Created by Orlando Salvatore on 6/2/14.
//  Copyright (c) 2014 Orlando Salvatore. All rights reserved.
//

#ifndef __MiniGolfXCode__HUDElement__
#define __MiniGolfXCode__HUDElement__

#include <iostream>
#include "GameObject.h"
#include "MGOpenGL.h"
#include "ShaderHelper.h"
#include "SceneManager.h"
#include "Camera.h"
#include "matrix_transform.hpp"
#include <vector>
#include <SDL2_ttf/SDL_ttf.h>

class HUDElement
{
public:
    HUDElement(glm::vec2);
    virtual ~HUDElement();
    virtual void draw() = 0;
    inline bool getEnabled() { return _enabled; }
    inline void setEnabled(bool enabled) { _enabled = enabled; }
    
protected:
    glm::vec2 _position;
    bool _enabled;
};

#endif /* defined(__MiniGolfXCode__HUDElement__) */

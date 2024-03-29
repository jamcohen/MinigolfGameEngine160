//
//  Drawing.h
//  MiniGolfGameEngine
//
//  Created by Orlando Salvatore on 4/17/14.
//  Copyright (c) 2014 Orlando Salvatore. All rights reserved.
//

#ifndef __MiniGolfGameEngine__Drawing__
#define __MiniGolfGameEngine__Drawing__

#include <iostream>
#include "GameObject.h"
#include "MGOpenGL.h"
#include "ShaderHelper.h"
#include "SceneManager.h"
#include "Camera.h"
#include "matrix_transform.hpp"
#include "Gizmo.h"
#include "HUD.h"
#include <vector>

class Drawing
{
public:
    const int PORTAL_STENCIL_ID = 1;
    const int DEFAULT_STENCIL_ID = 0;
    static const int SCREEN_WIDTH;
    static const int SCREEN_HEIGHT;
    Drawing();
    void update();
    bool initOpenGL();
    void addToDrawingList(GameObject *);
private:
    std::vector<GameObject *> objects;
    void initModels();
};

#endif /* defined(__MiniGolfGameEngine__Drawing__) */

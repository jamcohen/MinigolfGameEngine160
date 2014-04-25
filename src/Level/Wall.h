//
//  Wall.h
//  MiniGolfXCode
//
//  Created by Jake Cohen on 4/24/14.
//  Copyright (c) 2014 Orlando Salvatore. All rights reserved.
//

#ifndef __MiniGolfXCode__Wall__
#define __MiniGolfXCode__Wall__

#include <iostream>
#include <vector>
#include "GameObject.h"
#include "glm.hpp"
#include "matrix_transform.hpp"
#include "DiffuseSpecularMaterial.h"

class Wall : GameObject
{
public:
    Wall(const glm::vec3, const glm::vec3, float, float, float);
    ~Wall();
    
private:
    Model* getModel(float, float);
    std::vector<glm::vec3> getCubeVertices();
    std::vector<unsigned int> getCubeIndices();
    float width;
    float height;
    float pos;
    float angle;
    glm::vec3 axisOfRotation;
};

#endif /* defined(__MiniGolfXCode__Wall__) */

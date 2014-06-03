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
#include "Primative.h"

class Wall : public GameObject
{
public:
    Wall(const glm::vec3, const glm::quat, float, float, float, glm::vec3);
    ~Wall();
    
private:
    std::vector<glm::vec3> getCubeVertices();
    std::vector<unsigned int> getCubeIndices();
    glm::vec3 _color;
};

#endif /* defined(__MiniGolfXCode__Wall__) */

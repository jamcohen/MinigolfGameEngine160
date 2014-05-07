//
//  Face.h
//  MiniGolfXCode
//
//  Created by Orlando Salvatore on 5/6/14.
//  Copyright (c) 2014 Orlando Salvatore. All rights reserved.
//

#ifndef __MiniGolfXCode__Face__
#define __MiniGolfXCode__Face__

#include <iostream>
#include <vector>
#include "glm.hpp"
#include "Model.h"

class Model;

class Face
{
public:
    Face(glm::vec3,std::vector<glm::vec3>,glm::vec3*,Model*);
    inline glm::vec3 getNormal() { return _normal; }
    inline std::vector<glm::vec3> getVerticies() { return _verticies; }
    inline glm::vec3* getColors() { return _colors; }
    inline Model* getModel() { return _m; }
    void print();
    
private:
    glm::vec3 _normal;
    std::vector<glm::vec3> _verticies;
    glm::vec3 *_colors;
    Model *_m;
};

#endif /* defined(__MiniGolfXCode__Face__) */

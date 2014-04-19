//
//  Model.h
//  MiniGolfXCode
//
//  Created by Jake Cohen on 4/19/14.
//  Copyright (c) 2014 Orlando Salvatore. All rights reserved.
//

#ifndef __MiniGolfXCode__Model__
#define __MiniGolfXCode__Model__

#include <iostream>
#include <vector>
#include "MGOpenGL.h"
#include "GenericMaterial.h"

using namespace std;

class Model{
    public:
        vector<glm::vec3> positions;
        vector<glm::vec3> normals;
        vector<glm::vec3> colors;
        GenericMaterial material;
        GLuint shaderProgram;
        Model();
        void initializeBuffers();
};

#endif /* defined(__MiniGolfXCode__Model__) */

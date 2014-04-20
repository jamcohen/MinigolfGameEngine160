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

class Model
{
public:
    Model();
    ~Model();
    GenericMaterial *material;
    GLuint shaderProgram;
    void initializeBuffers();
    void draw(glm::vec3);
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec3> colors;
    std::vector<unsigned int> indices;
private:
    GLuint buffer;
	GLuint indexBuffer;
	GLuint vao;
};

#endif /* defined(__MiniGolfXCode__Model__) */

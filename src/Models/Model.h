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
#include "matrix_transform.hpp"

class Model
{
public:
    Model(std::vector<glm::vec3>,std::vector<glm::vec3>,std::vector<glm::vec3>,std::vector<unsigned int>);
    Model();
    ~Model();
    GenericMaterial *material;
    GLuint shaderProgram;
    void initializeBuffers();
    void draw(glm::vec3);
    inline std::vector<glm::vec3> getVerticies() { return _vertices; }
    inline std::vector<glm::vec3> getColors() { return _colors; }
    inline std::vector<glm::vec3> getNormals() { return _normals; }
    inline std::vector<unsigned int> getIndices() { return _indices; }
    inline void setVertices(std::vector<glm::vec3> value) { _vertices = value; }
    inline void setColors(std::vector<glm::vec3> value) { _vertices = value; }
    inline void setNormals(std::vector<glm::vec3> value) { _normals = value; }
    inline void setTriangles(std::vector<unsigned int> value) { _indices = value; }
    
private:
    GLuint _buffer;
	GLuint _indexBuffer;
	GLuint _vao;
    std::vector<glm::vec3> _vertices;
    std::vector<glm::vec3> _normals;
    std::vector<glm::vec3> _colors;
    std::vector<unsigned int> _indices;
};

#endif /* defined(__MiniGolfXCode__Model__) */

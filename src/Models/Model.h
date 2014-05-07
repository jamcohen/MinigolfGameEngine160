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
#include "GameObject.h"
#include "Face.h"

class GameObject;
class Face;

class Model
{
public:
    Model();
    Model(std::vector<glm::vec3>,std::vector<glm::vec3>,std::vector<glm::vec3>,std::vector<unsigned int>);
    ~Model();
    GenericMaterial *material;
    GLuint shaderProgram;
    void initializeBuffers();
    void draw(glm::vec3, glm::vec3, glm::vec3);
    std::vector<glm::vec3> getVerticies() { return _vertices; }
    std::vector<glm::vec3> getColors() { return _colors; }
    std::vector<glm::vec3> getNormals() { return _normals; }
    std::vector<unsigned int> getIndices() { return _indices; }
    std::vector<Face*> getFaces() { return _faces; }
    inline GameObject* getGameObject() { return _g; }
    inline void setGameObject(GameObject *g) { _g = g; }
    
private:
    GLuint _buffer;
	 GLuint _indexBuffer;
	 GLuint _vao;
    std::vector<glm::vec3> _vertices;
    std::vector<glm::vec3> _normals;
    std::vector<glm::vec3> _colors;
    std::vector<unsigned int> _indices;
    std::vector<Face*> _faces;
    GameObject *_g;
};

#endif /* defined(__MiniGolfXCode__Model__) */

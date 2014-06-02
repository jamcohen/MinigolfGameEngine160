//
//  Wall.cpp
//  MiniGolfXCode
//
//  Created by Jake Cohen on 4/24/14.
//  Copyright (c) 2014 Orlando Salvatore. All rights reserved.
//

#include "Wall.h"

Wall::Wall(const glm::vec3 origin, const glm::quat rotation, float width, float height, float length, glm::vec3 color) : GameObject(origin, glm::vec3(width, height, length), rotation)
{
    DiffuseSpecularMaterial *d = new DiffuseSpecularMaterial(100);
    _color = color;
    Model* m = getModel(width, height);
    _model = m;
    _model->material = d;
    _model->initializeBuffers();
}

Model* Wall::getModel(float width, float height)
{
    std::vector<unsigned int> indices;
    std::vector<glm::vec3> verts;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec3> colors;
    std::vector<glm::vec4> baseVerts;
    ///front face
    baseVerts.push_back(glm::vec4( 0.5f,  0.5f,  0.5f, 1));
    baseVerts.push_back(glm::vec4(-0.5f,  0.5f,  0.5f, 1));
    baseVerts.push_back(glm::vec4(-0.5f, -0.5f,  0.5f, 1));
    baseVerts.push_back(glm::vec4( 0.5f, -0.5f,  0.5f, 1));
    glm::vec4 baseNormal(0,0,1,1);
    glm::vec3 baseColor = _color;
    
    glm::mat4 rotation;
    for(int i=0;i<4;++i){
        rotation = glm::rotate(glm::mat4(), 90.0f*i, glm::vec3(0,1,0));
        
        for(int i=0;i<4;++i){
            verts.push_back(glm::vec3(rotation * baseVerts[i]));
            normals.push_back(glm::vec3(rotation * baseNormal));
            colors.push_back(baseColor);
        }
    }
    
    rotation = glm::rotate(glm::mat4(), 90.0f, glm::vec3(1,0,0));
    for(int i=0;i<4;++i){
        verts.push_back(glm::vec3(rotation * baseVerts[i]));
        normals.push_back(glm::vec3(rotation * baseNormal));
        colors.push_back(baseColor);
    }
    
    rotation = glm::rotate(glm::mat4(), -90.0f, glm::vec3(1,0,0));
    for(int i=0;i<4;++i){
        verts.push_back(glm::vec3(rotation * baseVerts[i]));
        normals.push_back(glm::vec3(rotation * baseNormal));
        colors.push_back(baseColor);
    }
    
    for(int i=0;i<6;i++){
        int offset = i*4;
        indices.push_back(2+offset);
        indices.push_back(3+offset);
        indices.push_back(0+offset);
        indices.push_back(2+offset);
        indices.push_back(0+offset);
        indices.push_back(1+offset);
    }
    
    Model* m = new Model(verts, normals, colors, indices);
    return m;
}

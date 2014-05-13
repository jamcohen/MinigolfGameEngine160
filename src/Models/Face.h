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
#include "GameObject.h"

class Model;
class GameObject;

class Face
{
public:
    Face(glm::vec3,std::vector<glm::vec3>,glm::vec3*,Model*);
    inline glm::vec3 getNormal() { return _normal; }
    glm::vec3 getWorldNormal(GameObject* obj);
    inline std::vector<glm::vec3> getVerticies() { return _verticies; }
    std::vector<glm::vec3> getWorldVertices(GameObject* obj);
    inline glm::vec3* getColors() { return _colors; }
    inline Model* getModel() { return _m; }
    void print();
    void print(GameObject* obj);

   
private:
    glm::vec3 _normal;
    glm::vec3 _worldNormal;
    std::vector<glm::vec3> _verticies;
    std::vector<glm::vec3> _worldVerticies;
    glm::vec3 *_colors;
    Model *_m;
};

#endif /* defined(__MiniGolfXCode__Face__) */

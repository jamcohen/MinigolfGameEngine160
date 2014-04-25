//
//  ModelUtil.h
//  MiniGolfXCode
//
//  Created by Orlando Salvatore on 4/24/14.
//  Copyright (c) 2014 Orlando Salvatore. All rights reserved.
//

#ifndef __MiniGolfXCode__ModelUtil__
#define __MiniGolfXCode__ModelUtil__

#include <iostream>
#include <vector>
#include "glm.hpp"

class ModelUtil
{
public:
    static std::vector<unsigned int> getFaceTriangles(std::vector<glm::vec3>);
    static std::vector<glm::vec3> getNormals(std::vector<unsigned int>, std::vector<glm::vec3>);
};

#endif /* defined(__MiniGolfXCode__ModelUtil__) */

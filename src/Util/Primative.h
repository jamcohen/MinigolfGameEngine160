//
//  Primative.h
//  MiniGolfXCode
//
//  Created by Jake Cohen on 5/6/14.
//  Copyright (c) 2014 Orlando Salvatore. All rights reserved.
//

#ifndef __MiniGolfXCode__Primative__
#define __MiniGolfXCode__Primative__

#include <iostream>
#include <vector>
#include <map>
#include "MGOpenGL.h"
#include "Model.h"

class Primative
{
public:
   static Model* getCube(glm::vec3);
   static Model* getBox(glm::vec3, glm::vec3, float, float);
   static Model* getSphere(glm::vec3, float recursionLevel=3);
private:
   static glm::vec3 getNormal(glm::vec3, glm::vec3, glm::vec3);
   static std::map<unsigned int, unsigned int> middlePointIndexCache;
   static unsigned int getMiddlePoint(std::vector<glm::vec3>&, int, int);
   static void addVertex(std::vector<glm::vec3>&, glm::vec3);
};

#endif /* defined(__MiniGolfXCode__Primative__) */

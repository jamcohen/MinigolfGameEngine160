//
//  Gizmo.h
//  MiniGolfXCode
//
//  Created by Jake Cohen on 6/2/14.
//  Copyright (c) 2014 Orlando Salvatore. All rights reserved.
//

#ifndef __MiniGolfXCode__Gizmo__
#define __MiniGolfXCode__Gizmo__

#include <iostream>
#include "MGOpenGL.h"
#include "ShaderHelper.h"
#include <vector>

class Gizmo{
   typedef struct {glm::vec3 pos; glm::vec3 dir; float length;} line;
public:
   void draw();
   static Gizmo& instance()
   {
      static Gizmo INSTANCE;
      return INSTANCE;
   }
   Gizmo();
   void addDebugRay(glm::vec3 pos, glm::vec3 dir);
   bool enabled = false;
private:
   std::vector<glm::vec3> _rayList;
   GLuint _vao;
   GLuint _buffer;
};

#endif /* defined(__MiniGolfXCode__Gizmo__) */

//
//  Material.h
//  MiniGolfXCode
//
//  Created by Jake Cohen on 4/19/14.
//  Copyright (c) 2014 Orlando Salvatore. All rights reserved.
//

#ifndef __MiniGolfXCode__GenericMaterial__
#define __MiniGolfXCode__GenericMaterial__

#include "MGOpenGL.h"
#include <iostream>

class GenericMaterial{
    public:
        GLuint shaderProgram;
        GenericMaterial();
        virtual bool initializeUniforms(GLuint)=0; //initializes shader variables
};

#endif /* defined(__MiniGolfXCode__Material__) */

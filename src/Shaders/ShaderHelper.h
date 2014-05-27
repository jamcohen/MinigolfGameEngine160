//
//  ShaderHelper.h
//  MiniGolfXCode
//
//  Created by Jake Cohen on 4/19/14.
//  Copyright (c) 2014 Orlando Salvatore. All rights reserved.
//

#ifndef __MiniGolfXCode__ShaderHelper__
#define __MiniGolfXCode__ShaderHelper__

#include <iostream>
#include "MGOpenGL.h"
#include <unistd.h>
#include <vector>

class ShaderHelper{
    public:
        static std::vector<GLuint> shaders;
        static void compileShaders();
    private:
        static void compileShader(GLuint program, char* vertexShader, char* fragmentShader);
        static char* readShader(char* filename);
        static GLuint initShader(GLuint program, const GLchar *source, GLenum type);
    
};

#endif /* defined(__MiniGolfXCode__ShaderHelper__) */

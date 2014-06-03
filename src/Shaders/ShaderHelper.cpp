//
//  ShaderHelper.cpp
//  MiniGolfXCode
//
//  Created by Jake Cohen on 4/19/14.
//  Copyright (c) 2014 Orlando Salvatore. All rights reserved.
//

#include "ShaderHelper.h"
std::vector<GLuint> ShaderHelper::shaders;

void ShaderHelper::compileShaders(){
    compileShader( 0, "vShader.glsl", "fShader21.glsl");
    compileShader( 1, "vGUIshader.glsl", "fGUIshader.glsl");
    compileShader( 1, "vpassthrough.glsl", "fportalShader.glsl");
}

void ShaderHelper::compileShader(GLuint program, char* vertexShader, char* fragmentShader){
   char buffer[1000];
   std::cout << "Current directory is: " << getcwd(buffer, 1000) << "\n";
   GLchar *vertexShaderCode = readShader(const_cast<char*>(vertexShader));
   if(vertexShaderCode != nullptr){
      program = glCreateProgram();
      initShader(program, vertexShaderCode, GL_VERTEX_SHADER);
   }else{
      std::cout << "Vertex shader cannot be read" << std::endl;
   }
   GLchar *fragmentShaderCode = readShader(const_cast<char*>(fragmentShader));
   if(fragmentShaderCode != nullptr){
      initShader(program, fragmentShaderCode, GL_FRAGMENT_SHADER);
   }else{
      std::cout << "Fragment shader cannot be read" << std::endl;
   }
   shaders.push_back(program);
}

char* ShaderHelper::readShader(char* filename){
    FILE* fp = fopen(filename, "r");
    
    if ( fp == NULL ) { return NULL; }
    
    fseek(fp, 0L, SEEK_END);
    long size = ftell(fp);
    
    fseek(fp, 0L, SEEK_SET);
    char* buf = new char[size + 1];
	for (int i = 0; i < size + 1; i++) { buf[i] = '\0'; }
    fread(buf, 1, size, fp);
    
	//deletes the last 8 characters from the buffer, because garbage characters are there for some reason
	/*for(size_t i=size-10;i<=size;i++){
		buf[i] = '\0';
	}*/
	buf[size] = '\0';
    
    fclose(fp);
	std::cerr << "Buffer: " << buf << std::endl;
    return buf;
}

GLuint ShaderHelper::initShader(GLuint program, const GLchar* source, GLenum type){
    
    GLuint shader = glCreateShader( type );
    glShaderSource( shader, 1, &source, NULL );
    glCompileShader( shader );
    
    GLint  compiled;
    glGetShaderiv( shader, GL_COMPILE_STATUS, &compiled );
    if ( !compiled ) {
        std::cerr << type << " shader failed to compile:" << std::endl;
        GLint  logSize;
	    glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &logSize );
	    char* logMsg = new char[logSize];
	    glGetShaderInfoLog( shader, logSize, NULL, logMsg );
	    std::cerr << logMsg << std::endl;
        std::cerr << GL_SHADING_LANGUAGE_VERSION << std::endl;
	    delete [] logMsg;
    }
    
    glAttachShader(program, shader);
    
    /* link  and error check */
    glLinkProgram(program);
    
    GLint  linked;
    glGetProgramiv( program, GL_LINK_STATUS, &linked );
    if ( !linked ) {
        std::cerr << "Shader program failed to link" << std::endl;
        //exit( EXIT_FAILURE );
    }
    
    /* use program object */
    glUseProgram(program);
    
    return program;
    return 0;
}

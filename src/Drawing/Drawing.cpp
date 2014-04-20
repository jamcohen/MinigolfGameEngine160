//
//  Drawing.cpp
//  MiniGolfGameEngine
//
//  Created by Orlando Salvatore on 4/17/14.
//  Copyright (c) 2014 Orlando Salvatore. All rights reserved.
//

#include "Drawing.h"


Drawing::Drawing(){
    initOpenGL();
}

void Drawing::update(){
    //Clear color buffer
    glClear( GL_COLOR_BUFFER_BIT );
    
    //Update screen
    //SDL_GL_SwapBuffers();
}

bool Drawing::initOpenGL(){
    //Initialize Projection Matrix
    /*glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    
    //Initialize Modelview Matrix
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    
    //Initialize clear color
    glClearColor( 0.f, 0.f, 0.f, 1.f );
    
    //Check for error
    GLenum error = glGetError();*/
    
    ShaderHelper::compileShaders();
    std::cout << "version: " << glGetString(GL_VERSION) << ", shader: "<< glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    
    initModels();

    
    return true;
}

void Drawing::initModels(){
    for(size_t i=0; i<objects.size();++i){
        objects[i]->getModel()->initializeBuffers();
    }
}



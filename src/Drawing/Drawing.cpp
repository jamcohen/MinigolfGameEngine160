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
    glClearColor( 0.0, 1.0, 1.0, 1.0 );
    glClear( GL_COLOR_BUFFER_BIT );
    
    std::vector<GameObject*> objs = SceneManager::instance().getObjects();
    /*if(objs->getModel()){
        
    }*/
    
    //Update screen
    //SDL_GL_SwapBuffers();
}

bool Drawing::initOpenGL(){
    
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



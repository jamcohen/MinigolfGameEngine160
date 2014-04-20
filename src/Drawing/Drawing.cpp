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
    
    GLuint program = ShaderHelper::shaders[0];
    
    GLuint modelCam = glGetUniformLocation( program, "camera" );
	GLuint projectionLoc = glGetUniformLocation( program, "projection" );
	GLuint lightLoc = glGetUniformLocation( program, "light" );
	GLuint eyeLoc = glGetUniformLocation( program, "eye" );
    
    glm::mat4 cam = glm::translate(glm::mat4(), glm::vec3(0,1.0f,0));
    glm::mat4 projectionMat = glm::perspective(35.0f, 1.0f, 0.1f, 100.0f);
    glm::vec3 camDir(0, -1, 0);
    glm::vec3 lightPos(0, 1, 0);
    
    glUniform3fv(eyeLoc, 1, glm::value_ptr(camDir));
    glUniform3fv(lightLoc, 1, glm::value_ptr(lightPos));
    glUniformMatrix4fv(modelCam, 1, GL_TRUE, glm::value_ptr(cam));
    glUniformMatrix4fv(projectionLoc, 1, GL_TRUE, glm::value_ptr(projectionMat));
    
    std::vector<GameObject*> objs = SceneManager::instance().getObjects();
    for(size_t i=0;i<objs.size();++i){
        if(objs[i]->getModel() != NULL){
            objs[i]->draw();
        }
    }
    
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



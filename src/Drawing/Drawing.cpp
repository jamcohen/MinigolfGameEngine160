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
    glUseProgram( program );
    
    GLuint modelCam = glGetUniformLocation( program, "camera" );
	GLuint projectionLoc = glGetUniformLocation( program, "projection" );
	GLuint lightLoc = glGetUniformLocation( program, "light" );
	GLuint eyeLoc = glGetUniformLocation( program, "eye" );
    
    glm::vec3 eyePos(0, 0.5, -1);
    glm::mat4 cam = glm::lookAt(eyePos, glm::vec3(0,0,0), glm::vec3(0,1,0));
    //glm::mat4 cam = glm::rotate(glm::mat4(), 45.0f, glm::vec3(0,0,1) );
    //glm::mat4 cam = glm::mat4();
    glm::mat4 projectionMat = glm::perspective(90.0f, 1.0f, 0.1f, 100.0f);
    glm::vec3 lightPos(0, 0.1, 0);
    
    glUniform3fv(eyeLoc, 1, glm::value_ptr(eyePos));
    glUniform3fv(lightLoc, 1, glm::value_ptr(lightPos));
    glUniformMatrix4fv(modelCam, 1, GL_FALSE, glm::value_ptr(cam));
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projectionMat));
    
    std::vector<GameObject*> objs = SceneManager::instance().getObjects();
    for(size_t i=0;i<objs.size();++i){
        if(objs[i]->getModel() != NULL){
            objs[i]->draw();
        }
    }
    
    glFlush();
    //Update screen
    //SDL_GL_SwapBuffers();
}

bool Drawing::initOpenGL(){
    
    ShaderHelper::compileShaders();
    std::cout << "version: " << glGetString(GL_VERSION) << ", shader: "<< glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    
    //initModels();

    
    return true;
}

void Drawing::initModels(){
    std::vector<GameObject*> objs = SceneManager::instance().getObjects();
    for(size_t i=0;i<objs.size();++i){
        std::cout << "YOLOSAWG!!!!";
        if(objs[i]->getModel() != NULL){
            objs[i]->getModel()->initializeBuffers();
        }
    }
}



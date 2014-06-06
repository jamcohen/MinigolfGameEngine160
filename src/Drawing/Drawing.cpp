//
//  Drawing.cpp
//  MiniGolfGameEngine
//
//  Created by Orlando Salvatore on 4/17/14.
//  Copyright (c) 2014 Orlando Salvatore. All rights reserved.
//

#include "Drawing.h"
const int Drawing::SCREEN_WIDTH = 640;
const int Drawing::SCREEN_HEIGHT = 480;

Drawing::Drawing(){
    initOpenGL();
}

void Drawing::update(){
    //Clear color buffer
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glClearColor( 0.0, 0.6, 0.5, 1.0 );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    
    GLuint program = ShaderHelper::shaders[0];
    glUseProgram( program );
    
    GLuint modelCam = glGetUniformLocation( program, "camera" );
	 GLuint projectionLoc = glGetUniformLocation( program, "projection" );
	 GLuint lightLoc = glGetUniformLocation( program, "light" );
	 GLuint eyeLoc = glGetUniformLocation( program, "eye" );
    
    Camera *camera = SceneManager::instance().getCurrentCamera();
    glm::vec3 eyePos = camera->getPosition();
    glm::mat4 cam = glm::lookAt(eyePos, camera->getTarget(), camera->getUp());
    glm::mat4 projectionMat = glm::perspective(90.0f, 1.0f, 0.1f, 100.0f);
    glm::vec3 lightPos(0, 1, 0.1);
    
    glUniform3fv(eyeLoc, 1, glm::value_ptr(eyePos));
    glUniform3fv(lightLoc, 1, glm::value_ptr(lightPos));
    glUniformMatrix4fv(modelCam, 1, GL_FALSE, glm::value_ptr(cam));
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projectionMat));
    
    std::vector<GameObject*>* objs = SceneManager::instance().getObjects();
    for(size_t i=0;i<objs->size();++i){
        if((*objs)[i]->getModel() != NULL){
            (*objs)[i]->draw();
        }
    }
    Gizmo::instance().draw();
    glClear(GL_DEPTH_BUFFER_BIT);
    HUD::instance().draw();
    glFlush();
    //Update screen
    //SDL_GL_SwapBuffers();
}

bool Drawing::initOpenGL(){
    // Enable depth buffer and backface culling
    glEnable(GL_DEPTH_TEST);
    ShaderHelper::compileShaders();
    std::cout << "version: " << glGetString(GL_VERSION) << ", shader: "<< glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    
    //initModels();
    return true;
}

void Drawing::initModels(){
    std::vector<GameObject*>* objs = SceneManager::instance().getObjects();
    for(size_t i=0;i<objs->size();++i){
        if((*objs)[i]->getModel() != NULL){
            (*objs)[i]->getModel()->initializeBuffers();
        }
    }
}



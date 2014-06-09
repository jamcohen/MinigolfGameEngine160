//
//  Drawing.cpp
//  MiniGolfGameEngine
//
//  Created by Orlando Salvatore on 4/17/14.
//  Copyright (c) 2014 Orlando Salvatore. All rights reserved.
//

#include "Drawing.h"
#include "Portal.h"

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
    glClearStencil(DEFAULT_STENCIL_ID);
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
   
    // The framebuffer, which regroups 0, 1, or more textures, and 0 or 1 depth buffer.
    /*GLuint FramebufferName = 0;
    glGenFramebuffers(1, &FramebufferName);
    glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
   
    // The texture we're going to render to
    GLuint renderedTexture;
    glGenTextures(1, &renderedTexture);

    // "Bind" the newly created texture : all future texture functions will modify this texture
    glBindTexture(GL_TEXTURE_2D, renderedTexture);

    // Give an empty image to OpenGL ( the last "0" )
    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, 1024, 768, 0,GL_RGB, GL_UNSIGNED_BYTE, 0);

    // Poor filtering. Needed !
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    
    // The depth buffer
    GLuint depthrenderbuffer;
    glGenRenderbuffers(1, &depthrenderbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, depthrenderbuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 1024, 768);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthrenderbuffer);
    
    // Set "renderedTexture" as our colour attachement #0
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, renderedTexture, 0);
    
    // Set the list of draw buffers.
    GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers*/
    
    //Actually draw our game objects
    std::vector<GameObject*>* objs = SceneManager::instance().getObjects();
    for(size_t i=0;i<objs->size();++i){
        GameObject *obj = (*objs)[i];
        if(obj->getModel() != NULL){
           if(typeid(*obj) == typeid(Portal)){
              glStencilFunc(GL_ALWAYS, PORTAL_STENCIL_ID, -1);
           }
           obj->draw();
           glStencilFunc(GL_ALWAYS, DEFAULT_STENCIL_ID, -1);
        }
    }
    
    /*glUseProgram( ShaderHelper::shaders[1]);
    // The fullscreen quad's FBO
    GLuint quad_VertexArrayID;
    glGenVertexArrays(1, &quad_VertexArrayID);
    glBindVertexArray(quad_VertexArrayID);
    
    static const GLfloat g_quad_vertex_buffer_data[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        -1.0f,  1.0f, 0.0f,
        -1.0f,  1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        1.0f,  1.0f, 0.0f,
    };
    
    GLuint quad_vertexbuffer;
    glGenBuffers(1, &quad_vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, quad_vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_quad_vertex_buffer_data), g_quad_vertex_buffer_data, GL_STATIC_DRAW);
    
    // Render to the screen
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0,0,1024,768); // Render on the whole framebuffer, complete from the
    
    // Create and compile our GLSL program from the shaders
    GLuint quad_programID = ShaderHelper::shaders[1];
    GLuint texID = glGetUniformLocation(quad_programID, "renderedTexture");
    //GLuint timeID = glGetUniformLocation(quad_programID, "time");

    //glDrawArrays(GL_TRIANGLES, 0, 18);
    
    for(size_t i=0;i<1;++i){
        GameObject *obj = (*objs)[i];
        if(obj->getModel() != NULL){
            obj->draw();
        }
    }*/

    

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



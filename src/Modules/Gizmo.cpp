//
//  Gizmo.cpp
//  MiniGolfXCode
//
//  Created by Jake Cohen on 6/2/14.
//  Copyright (c) 2014 Orlando Salvatore. All rights reserved.
//

#include "Gizmo.h"
#define BUFFER_OFFSET(i) ((char *)NULL + (i))

Gizmo::Gizmo(){
   glGenVertexArrays( 1, &_vao );
   glGenBuffers( 1, &_buffer );
}

void Gizmo::draw(){
    if(!enabled){
        return;
    }
    int num_verts = (int)_rayList.size();
    glUseProgram(ShaderHelper::shaders[0]);
    glBindVertexArray( _vao ); // setup for the layout of LineSegment_t
    
    glm::mat4 model{};
    glUniformMatrix4fv(glGetUniformLocation(ShaderHelper::shaders[0], "model"), 1, GL_FALSE, glm::value_ptr(model));
    glDrawArrays(GL_LINES, 0, num_verts );
    
    _rayList.clear();
}

void Gizmo::addDebugRay(glm::vec3 pos, glm::vec3 dir){
    if(!enabled){
        return;
    }
    _rayList.push_back(pos);
    _rayList.push_back(dir);
   
    // Create a vertex array object
    glBindVertexArray( _vao );
    
    glBindBuffer( GL_ARRAY_BUFFER, _buffer );
    glBufferData( GL_ARRAY_BUFFER, _rayList.size()*sizeof(glm::vec3), NULL, GL_STATIC_DRAW );
    glBufferSubData( GL_ARRAY_BUFFER, 0, _rayList.size()*sizeof(glm::vec3), &_rayList.front() );
    
    // set up vertex arrays
    GLuint vPosition = glGetAttribLocation( ShaderHelper::shaders[0], "vPosition" );
    glEnableVertexAttribArray( vPosition );
    glVertexAttribPointer( vPosition, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
}

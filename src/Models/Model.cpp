//
//  Model.cpp
//  MiniGolfXCode
//
//  Created by Jake Cohen on 4/19/14.
//  Copyright (c) 2014 Orlando Salvatore. All rights reserved.
//

#include "Model.h"
#define BUFFER_OFFSET(i) ((char *)NULL + (i))

Model::Model()
{ }

Model::~Model()
{ }

void Model::initializeBuffers()
{
	// Create a vertex array object
    glGenVertexArrays( 1, &vao );
    glBindVertexArray( vao );
    
    // Create and initialize a buffer object
    glGenBuffers( 1, &buffer );
    glBindBuffer( GL_ARRAY_BUFFER, buffer );
    glBufferData( GL_ARRAY_BUFFER, vertices.size()*sizeof(glm::vec3) + normals.size()*sizeof(glm::vec3),
                 NULL, GL_STATIC_DRAW );
    glBufferSubData( GL_ARRAY_BUFFER, 0, vertices.size()*sizeof(glm::vec3), &vertices.front() );
    glBufferSubData( GL_ARRAY_BUFFER, vertices.size()*sizeof(glm::vec3),
                    normals.size()*sizeof(glm::vec3), &normals.front() );
    
	glGenBuffers(1, &indexBuffer);
    
	// bind buffer for positions and copy data into buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(unsigned int), &indices.front(), GL_STATIC_DRAW);
    
    glUseProgram( material->shaderProgram );
    
    // set up vertex arrays
    GLuint vPosition = glGetAttribLocation( material->shaderProgram, "vPosition" );
    glEnableVertexAttribArray( vPosition );
    glVertexAttribPointer( vPosition, 3, GL_FLOAT, GL_FALSE, 0,
                          BUFFER_OFFSET(0) );
    
    GLuint vNormal = glGetAttribLocation( material->shaderProgram, "normal" );
    glEnableVertexAttribArray( vNormal );
    glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0,
                          BUFFER_OFFSET(vertices.size()*sizeof(glm::vec3)) );
}


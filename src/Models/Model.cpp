//
//  Model.cpp
//  MiniGolfXCode
//
//  Created by Jake Cohen on 4/19/14.
//  Copyright (c) 2014 Orlando Salvatore. All rights reserved.
//

#include "Model.h"
#define BUFFER_OFFSET(i) ((char *)NULL + (i))

Model::Model(std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals,
             std::vector<glm::vec3> colors, std::vector<unsigned int> indices) :
_vertices(vertices), _normals(normals),_colors(colors),_indices(indices)
{
    std::cout << "length: " << colors.size();
}

Model::~Model()
{ }

void Model::draw(glm::vec3 pos, glm::vec3 scale, glm::vec3 rotate)
{
    glUseProgram( material->shaderProgram );
    glBindVertexArray( _vao );
    glm::mat4 T = glm::translate(glm::mat4(), pos);
    glUniformMatrix4fv(glGetUniformLocation(material->shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(T));
    glDrawElements(GL_TRIANGLES, (int)(_indices.size()), GL_UNSIGNED_INT, NULL);
    glBindVertexArray(0);
}

void Model::initializeBuffers()
{
	// Create a vertex array object
    glGenVertexArrays( 1, &_vao );
    glBindVertexArray( _vao );
    
    glGenBuffers( 1, &_buffer );
    glBindBuffer( GL_ARRAY_BUFFER, _buffer );
    glBufferData( GL_ARRAY_BUFFER, _vertices.size()*sizeof(glm::vec3) +
                                   _normals.size()*sizeof(glm::vec3) +
                                   _colors.size()*sizeof(glm::vec3),
                                   NULL, GL_STATIC_DRAW );
    
    glBufferSubData( GL_ARRAY_BUFFER, 0, _vertices.size()*sizeof(glm::vec3), &_vertices.front() );
    glBufferSubData( GL_ARRAY_BUFFER, _vertices.size()*sizeof(glm::vec3),
                    _normals.size()*sizeof(glm::vec3), &_normals.front() );
    glBufferSubData( GL_ARRAY_BUFFER, _vertices.size()*sizeof(glm::vec3)+_normals.size()*sizeof(glm::vec3),
                    _colors.size()*sizeof(glm::vec3), &_colors.front() );
    
	glGenBuffers(1, &_indexBuffer);
    
	// bind buffer for positions and copy data into buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size()*sizeof(unsigned int), &_indices.front(), GL_STATIC_DRAW);
    
    glUseProgram( material->shaderProgram );
    
    // set up vertex arrays
    GLuint vPosition = glGetAttribLocation( material->shaderProgram, "vPosition" );
    glEnableVertexAttribArray( vPosition );
    glVertexAttribPointer( vPosition, 3, GL_FLOAT, GL_FALSE, 0,
                          BUFFER_OFFSET(0) );
    
    GLuint vNormal = glGetAttribLocation( material->shaderProgram, "normal" );
    glEnableVertexAttribArray( vNormal );
    glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0,
                          BUFFER_OFFSET(_vertices.size()*sizeof(glm::vec3)) );
    
    GLuint vColor = glGetAttribLocation( material->shaderProgram, "vColor" );
    glEnableVertexAttribArray( vColor );
    glVertexAttribPointer( vColor, 3, GL_FLOAT, GL_FALSE, 0,
                          BUFFER_OFFSET(_vertices.size()*sizeof(glm::vec3) + _normals.size()*sizeof(glm::vec3)) );
    
    material->initializeUniforms(_vao);
}


//
//  DiffuseSpecularMaterial.cpp
//  MiniGolfXCode
//
//  Created by Jake Cohen on 4/19/14.
//  Copyright (c) 2014 Orlando Salvatore. All rights reserved.
//

#include "DiffuseSpecularMaterial.h"

DiffuseSpecularMaterial::DiffuseSpecularMaterial(float shininess) : GenericMaterial() ,shininess(shininess)
{
    shaderProgram(ShaderHelper::shaders[0]);
}

bool DiffuseSpecularMaterial::initializeUniforms(GLuint vertexArrayObject)
{
    glBindVertexArray(vertexArrayObject);
    
    glm::vec4 ambient_product( 0.3, 0.3, 0.3, 1.0 );
    glm::vec4 diffuse_product( 1.0, 1.0, 1.0, 1.0 );
    glm::vec4 specular_product( 1.0, 1.0, 1.0, 1.0 );
    
    glUniform4fv( glGetUniformLocation(shaderProgram, "AmbientProduct"),
                 1, ambient_product );
    glUniform4fv( glGetUniformLocation(shaderProgram, "DiffuseProduct"),
                 1, diffuse_product );
    glUniform4fv( glGetUniformLocation(shaderProgram, "SpecularProduct"),
                 1, specular_product );
    glUniform1f( glGetUniformLocation(shaderProgram, "Shininess"),
                shininess );
    
    glBindVertexArray(0);
    return true;
}
//
//  TextElement.cpp
//  MiniGolfXCode
//
//  Created by Orlando Salvatore on 6/2/14.
//  Copyright (c) 2014 Orlando Salvatore. All rights reserved.
//

#include "TextElement.h"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

TextElement::TextElement(std::string text, uint fontSize, glm::vec3 color, glm::vec2 position) : _fontSize(fontSize), _text(text), _color(color), HUDElement(position)
{
    HUD::instance().addHUDElement(this);
    GLuint _buffer;
    GLuint _indexBuffer;
    
    _vertices = {glm::vec3(0,0,0), glm::vec3(0,1,0), glm::vec3(1,1,0), glm::vec3(1,0,0), glm::vec3(0,0,0)};
    _indices = {3, 1, 0, 3, 2, 1};
    
    // Create a vertex array object
    glGenVertexArrays( 1, &_vao );
    glBindVertexArray( _vao );
    
    glGenBuffers( 1, &_buffer );
    glBindBuffer( GL_ARRAY_BUFFER, _buffer );
    glBufferData( GL_ARRAY_BUFFER, _vertices.size()*sizeof(glm::vec3), NULL, GL_STATIC_DRAW);
    glBufferSubData( GL_ARRAY_BUFFER, 0, _vertices.size()*sizeof(glm::vec3), &_vertices.front() );
	glGenBuffers(1, &_indexBuffer);
    
	// bind buffer for positions and copy data into buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size()*sizeof(unsigned int), &_indices.front(), GL_STATIC_DRAW);
    glActiveTexture(GL_TEXTURE0);
    
    //Start TTF 2
    _font = TTF_OpenFont( "chineserocks.ttf", fontSize );
    if( _font == NULL )
    {
        printf( "Failed to load chinese rocks font! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    SDL_Color Color = {0, 1, 0};
	_messageSurface = TTF_RenderText_Solid(const_cast<TTF_Font*>(_font), _text.c_str(), Color);
    if(_messageSurface == NULL) {
        std::cout << "Message surface is null!\n";
    }
    //End TTF 2
    
    
    glGenTextures(1, &_texture);
    glBindTexture(GL_TEXTURE_2D, _texture);
    
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR);
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
                    GL_LINEAR);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, _messageSurface->w, _messageSurface->h, 0, GL_RED, GL_UNSIGNED_BYTE, _messageSurface->pixels);
    
    glUseProgram( ShaderHelper::shaders[1] );
    
    // set up vertex arrays
    GLuint vPosition = glGetAttribLocation( ShaderHelper::shaders[1], "vPosition" );
    glEnableVertexAttribArray( vPosition );
    glVertexAttribPointer( vPosition, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
    setPosition(position);
}

TextElement::~TextElement()
{

}

void TextElement::setPosition(glm::vec2 position)
{
    _position = position;
    _position.x = _position.x/((float)Drawing::SCREEN_WIDTH/2.0f) - 1.0f;
    _position.y = _position.y/((float)Drawing::SCREEN_HEIGHT/2.0f) - 1.0f;
}

void TextElement::updateText(std::string newString)
{
    if(_text == newString)
    {
        return;
    }
    _text = newString;
    SDL_Color Color = {0, 1, 0};
	_messageSurface = TTF_RenderText_Solid(const_cast<TTF_Font*>(_font), _text.c_str(), Color);
    if(_messageSurface == NULL) {
        std::cout << "Message surface is null!\n";
    }

    glBindTexture(GL_TEXTURE_2D, _texture);
    
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR);
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
                    GL_LINEAR);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, _messageSurface->w, _messageSurface->h, 0, GL_RED, GL_UNSIGNED_BYTE, _messageSurface->pixels);
    
    glUseProgram( ShaderHelper::shaders[1] );
    
    // set up vertex arrays
    GLuint vPosition = glGetAttribLocation( ShaderHelper::shaders[1], "vPosition" );
    glEnableVertexAttribArray( vPosition );
    glVertexAttribPointer( vPosition, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );

}

void TextElement::draw()
{
    GLuint program = ShaderHelper::shaders[1];
    glUseProgram( program );
	GLuint projectionLoc = glGetUniformLocation( program, "projection" );
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(glm::mat4()));
    
    glBindTexture(GL_TEXTURE_2D, _texture);
    
    glm::mat4 T = glm::translate(glm::mat4(), glm::vec3(_position.x,_position.y,0));
    glm::mat4 S = glm::scale(glm::mat4(), glm::vec3((_messageSurface->w/320.0f), (_messageSurface->h/320.0f),1));
    
    GLuint colorLoc = glGetUniformLocation(program, "textColor");
    glUniform3fv(colorLoc, 1, glm::value_ptr(_color));
    
    GLuint texLoc = glGetUniformLocation(program, "textureData");
    glUniform1f(texLoc, 0);
    
    //glActiveTexture(GL_TEXTURE0);
    
    glBindVertexArray( _vao );
    glm::mat4 model = T*S;
    glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glDrawElements(GL_TRIANGLES, (int)(_indices.size()), GL_UNSIGNED_INT, NULL);
}

uint TextElement::getHeight()
{
    return _messageSurface->h;
}

uint TextElement::getWidth()
{
    return _messageSurface->w;
}
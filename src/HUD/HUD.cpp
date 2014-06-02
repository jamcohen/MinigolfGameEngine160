//
//  HUD.cpp
//  MiniGolfXCode
//
//  Created by Orlando Salvatore on 6/1/14.
//  Copyright (c) 2014 Orlando Salvatore. All rights reserved.
//

#include "HUD.h"
#include <vector>
#include <fstream>

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

HUD::HUD()
{
    //orthoMat = glm::ortho(0.0f, 640.0f, 480.0f, 0.0f, 0.0001f, 10000.0f);
    
    GLuint _buffer;
    GLuint _indexBuffer;
    GLuint _texture;
    
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
    
    
    /*float Width = 4;
    float Height = 4;*/
    
    /*std::vector<std::vector<glm::vec4>> textureData = {{glm::vec4(0,1,0,1), glm::vec4(1,1,0,1), glm::vec4(0,1,1,1)}, {glm::vec4(0,1,0,1), glm::vec4(1,1,0.3,1), glm::vec4(0,0.6,0.1,1)}, {glm::vec4(0.5,0.75,0,1), glm::vec4(0,0,1,1), glm::vec4(0,0.5,0.5,1)}};*/
    //std::vector<std::vector<glm::vec4>> textureData = {{glm::vec4(1,0,0,1)}};
    /*GLbyte *textureData = new GLbyte[ 4 * 4 * 4 ] {
        0x00, 0x00, 0x00, 0x00, //Pixel index 0, position (x=0, y=0), transparent black
        0x00, 0x77, 0x77, 0x00, //Pixel index 1, position (x=1, y=0), opaque red
        0x00, 0x77, 0x77, 0x00,
        0x00, 0x00, 0x00, 0x00 //Pixel index 2, position (x=2, y=0), opaque red
    };*/
     glActiveTexture(GL_TEXTURE0);
    
    //TTF
    /*colors = surface->format->BytesPerPixel;
    if (colors == 4) {   // alpha
        if (surface->format->Rmask == 0x000000ff)
            texture_format = GL_RGBA;
        else
            texture_format = GL_BGRA;
    } else {             // no alpha
        if (surface->format->Rmask == 0x000000ff)
            format = GL_RGB;
        else
            format = GL_BGR;
    }*/
    //END TTF
    
    //Start TTF 2
    TTF_Font* Font = TTF_OpenFont( "chineserocks.ttf", 28 );
    if( Font == NULL )
    {
        printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    SDL_Color Color = {0, 1, 0};
	Message = TTF_RenderText_Solid(const_cast<TTF_Font*>(Font), "This worked hororay", Color);
    if(Message == NULL) {
        std::cout << "Message surface is null!\n";
    }
	unsigned Texture = 0;
    
    //End TTF 2
    
    
    glGenTextures(1, &_texture);
    glBindTexture(GL_TEXTURE_2D, _texture);
    
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR);
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
                    GL_LINEAR);
    
    SDL_LockSurface(Message);
    
    /* Surface is locked */
    /* Direct pixel access on surface here */
    
    GLubyte *data = (GLubyte *)Message->pixels;
    for(int i=1;i<Message->w*Message->h;i+=3){
        if(data[i] != 255){ std::cout << "not green "  << (int) data[i] << std::endl;}
    }
    
    SDL_UnlockSurface(Message);
    std::ofstream out;
    out.open("Picture.bmp");
    for(int i=0;i<Message->w*Message->h;i++){
        out << std::hex << (int) data[i];
        if(i%Message->w == 0 && i!=0){
            out << std::endl;
        }else{
            out << " ";
        }
    }
    std::cout << "TEXTURE DIMENSIONS: " << Message->w << " " << Message->h << std::endl;
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, Message->w, Message->h, 0, GL_RED, GL_UNSIGNED_BYTE, Message->pixels);
    
    glUseProgram( ShaderHelper::shaders[1] );
    
    // set up vertex arrays
    GLuint vPosition = glGetAttribLocation( ShaderHelper::shaders[1], "vPosition" );
    glEnableVertexAttribArray( vPosition );
    glVertexAttribPointer( vPosition, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
}

void HUD::draw(){
    
    GLuint program = ShaderHelper::shaders[1];
    glUseProgram( program );
    
	GLuint projectionLoc = glGetUniformLocation( program, "projection" );
    
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(glm::mat4()));
    
    glm::mat4 T = glm::translate(glm::mat4(), glm::vec3(0,0,0));
    /*glm::mat4 R = glm::rotate(glm::mat4(), rotate.z, glm::vec3(0,0,1));//glm::orientate4(rotate);
    R = glm::rotate(R, rotate.y, glm::vec3(0,1,0));
    R = glm::rotate(R, rotate.x, glm::vec3(1,0,0));*/
    std::cout << "WIDTH: " << (Message->w/320.0f);
    std::cout << "HEIGHT: " << (Message->h/320.0f);
    glm::mat4 S = glm::scale(glm::mat4(), glm::vec3((Message->w/320.0f), (Message->h/320.0f),1));
    
    glm::vec3 color(0,1,1);
    GLuint colorLoc = glGetUniformLocation(program, "textColor");
    glUniform3fv(colorLoc, 1, glm::value_ptr(color));
    
    GLuint texLoc = glGetUniformLocation(program, "textureData");
    glUniform1f(texLoc, 0);
    
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texLoc);

    glBindVertexArray( _vao );
    glm::mat4 model = T*S;
    glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glDrawElements(GL_TRIANGLES, (int)(_indices.size()), GL_UNSIGNED_INT, NULL);
}
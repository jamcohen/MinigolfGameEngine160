//
//  TextElement.h
//  MiniGolfXCode
//
//  Created by Orlando Salvatore on 6/2/14.
//  Copyright (c) 2014 Orlando Salvatore. All rights reserved.
//

#ifndef __MiniGolfXCode__TextElement__
#define __MiniGolfXCode__TextElement__

#include <iostream>
#include <string>
#include "glm.hpp"
#include "HUDElement.h"
#include "Drawing.h"

class TextElement : public HUDElement
{
public:
    TextElement(std::string, uint, glm::vec3, glm::vec2 = {0,0});
    ~TextElement();
    void draw();
    void updateText(std::string);
    void setPosition(glm::vec2);
    inline glm::vec2 getPosition() { return _position; }
    uint getHeight();
    uint getWidth();
    
private:
    std::string _text;
    glm::vec3 _color;
    std::vector<glm::vec3> _vertices;
    std::vector<unsigned int> _indices;
    GLuint _vao;
    SDL_Surface *_messageSurface;
    GLuint _texture;
    TTF_Font* _font;
    uint _fontSize;
};

#endif /* defined(__MiniGolfXCode__TextElement__) */

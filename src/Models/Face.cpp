//
//  Face.cpp
//  MiniGolfXCode
//
//  Created by Orlando Salvatore on 5/6/14.
//  Copyright (c) 2014 Orlando Salvatore. All rights reserved.
//

#include "Face.h"

Face::Face(glm::vec3 normal,std::vector<glm::vec3> verticies,glm::vec3 *colors, Model* m) : _normal(normal), _verticies(verticies), _colors(colors), _m(m)
{
    
}

void Face::print()
{
    std::cout << "Normal: " << _normal.x << "," << _normal.y << "," << _normal.z << std::endl;
    std::cout << "Verticies: ";
    for(int i=0 ; i < 3; i++)
    {
        std::cout << "v" << i << ": " << _verticies[i].x << "," << _verticies[i].y << "," << _verticies[i].z << std::endl;
    }
}
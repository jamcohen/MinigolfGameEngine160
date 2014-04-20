//
//  Tile.cpp
//  MiniGolfXCode
//
//  Created by Orlando Salvatore on 4/19/14.
//  Copyright (c) 2014 Orlando Salvatore. All rights reserved.
//

#include "Tile.h"

Tile::Tile(const int index, const glm::vec3 origin, const std::vector<glm::vec3> verticies,const std::vector<int> neighbors) : GameObject(origin), _index(index), _neighbors(neighbors)
{
    model->vertices = verticies;
}
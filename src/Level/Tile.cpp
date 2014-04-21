//
//  Tile.cpp
//  MiniGolfXCode
//
//  Created by Orlando Salvatore on 4/19/14.
//  Copyright (c) 2014 Orlando Salvatore. All rights reserved.
//

#include "Tile.h"

Tile::Tile(const int index, const glm::vec3 origin, Model *model,const std::vector<int> neighbors) : GameObject(origin, model), _index(index), _neighbors(neighbors)
{
    DiffuseSpecularMaterial *d = new DiffuseSpecularMaterial(100);
    model->material = d;
    model->initializeBuffers();
}
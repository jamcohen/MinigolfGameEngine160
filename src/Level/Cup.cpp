//
//  Cup.cpp
//  MiniGolfXCode
//
//  Created by Orlando Salvatore on 4/19/14.
//  Copyright (c) 2014 Orlando Salvatore. All rights reserved.
//

#include "Cup.h"

Cup::Cup(int index, glm::vec3 pos) : _index(index), GameObject(pos)
{
    setModel(new Cylinder(6));    
    std::cout << "Cup Position: " << pos.x << " " << pos.y << " " << pos.z << std::endl;

    DiffuseSpecularMaterial *d = new DiffuseSpecularMaterial(100);
    getModel()->material = d;
}
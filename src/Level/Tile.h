//
//  Tile.h
//  MiniGolfXCode
//
//  Created by Orlando Salvatore on 4/19/14.
//  Copyright (c) 2014 Orlando Salvatore. All rights reserved.
//

#ifndef __MiniGolfXCode__Tile__
#define __MiniGolfXCode__Tile__

#include <iostream>
#include <vector>
#include "GameObject.h"
#include "glm.hpp"
#include "DiffuseSpecularMaterial.h"

class Tile : GameObject
{
public:
    Tile(int,glm::vec3,Model *,std::vector<int>);
    ~Tile();
    int getIndex() { return _index; }
    void setIndex(int index) { _index = index; }
    
private:
    int _index;
    std::vector<int> _neighbors;
};

#endif /* defined(__MiniGolfXCode__Tile__) */

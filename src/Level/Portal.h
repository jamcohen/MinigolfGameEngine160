//
//  Tile.h
//  MiniGolfXCode
//
//  Created by Orlando Salvatore on 4/19/14.
//  Copyright (c) 2014 Orlando Salvatore. All rights reserved.
//

#ifndef __MiniGolfXCode__Portal__
#define __MiniGolfXCode__Portal__

#include <iostream>
#include <vector>
#include "GameObject.h"
#include "glm.hpp"
#include "DiffuseSpecularMaterial.h"

class Portal : public GameObject
{
public:
    Portal(int,glm::vec3,Model *,std::vector<int>);
    ~Portal();
    int getIndex() { return _index; }
    void setConnectedPortal(Portal* associate) {_connectedPortal = associate;}
    Portal* getConnectedPortal() {return  _connectedPortal;}
    void setIndex(int index) { _index = index; }
    
private:
    int _index;
    Portal* _connectedPortal;
    std::vector<int> _neighbors;
};

#endif /* defined(__MiniGolfXCode__Tile__) */

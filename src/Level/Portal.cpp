//
//  Tile.cpp
//  MiniGolfXCode
//
//  Created by Orlando Salvatore on 4/19/14.
//  Copyright (c) 2014 Orlando Salvatore. All rights reserved.
//

#include "Portal.h"
Portal* Portal::_lastPortalAdded = nullptr;
int Portal::_numPortals = 0;
void Portal::addPortal(Portal* portal){
   _numPortals++;
   //If a pair of portals has been added, connect them.
   if(_numPortals%2 == 0){
      portal->setConnectedPortal(_lastPortalAdded);
      _lastPortalAdded->setConnectedPortal(portal);
   }
   _lastPortalAdded = portal;
   
}

Portal::Portal(const int index, const glm::vec3 origin, Model *model,const std::vector<int> neighbors) : GameObject(origin, model), _index(index), _neighbors(neighbors)
{
    DiffuseSpecularMaterial *d = new DiffuseSpecularMaterial(100);
    model->material = d;
    model->initializeBuffers();
    addPortal(this);
}

Portal::~Portal()
{
   
}
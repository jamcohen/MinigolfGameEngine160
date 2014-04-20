//
//  SceneManager.cpp
//  MiniGolfXCode
//
//  Created by Orlando Salvatore on 4/19/14.
//  Copyright (c) 2014 Orlando Salvatore. All rights reserved.
//

#include "SceneManager.h"

SceneManager::SceneManager()
{}

void SceneManager::closeScene()
{
    for ( GameObject *g : _objects )
    {
        delete g;
    }
}

void SceneManager::addGameObject(GameObject *g)
{
    _objects.push_back(g);
}
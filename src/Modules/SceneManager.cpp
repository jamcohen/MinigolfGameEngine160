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
    int count = 0;
    for ( GameObject *g : _objects )
    {
        std::cout << count << std::endl;
        count++;
        delete g;
    }
}

void SceneManager::addGameObject(GameObject *g)
{
    _objects.push_back(g);
}
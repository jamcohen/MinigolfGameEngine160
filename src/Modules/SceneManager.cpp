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
    std::cout << "Cleaning up all game objects...\n";
    for ( GameObject *g : _objects )
    {
        std::cout << count << std::endl;
        count++;
        delete g;
    }
    
    std::cout << "Cleaning up all cameras...\n";
    for ( Camera *c : _cameraList )
    {
       delete c;
    }
}

void SceneManager::addCamera(Camera *c)
{
    if(!_currentCamera)
    {
        _currentCamera = c;
    }
    _cameraList.push_back(c);
}

void SceneManager::addGameObject(GameObject *g)
{
    _objects.push_back(g);
}
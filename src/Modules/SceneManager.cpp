
//
//  SceneManager.cpp
//  MiniGolfXCode
//
//  Created by Orlando Salvatore on 4/19/14.
//  Copyright (c) 2014 Orlando Salvatore. All rights reserved.
//

#include "SceneManager.h"
#include "GameObject.h"
#include "Camera.h"

SceneManager::SceneManager()
{}

void SceneManager::closeScene()
{    
    /*std::cout << "Cleaning up all cameras...\n";
    for ( Camera *c : _cameraList )
    {
        //delete c;
    }*/
}

void SceneManager::update(){
    for(GameObject *obj : _objects){
        obj->update();
    }
    for(Camera *cam : _cameraList){
        cam->update();
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
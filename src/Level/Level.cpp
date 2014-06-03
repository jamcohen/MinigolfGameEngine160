//
//  Level.cpp
//  MiniGolfXCode
//
//  Created by Orlando Salvatore on 6/2/14.
//  Copyright (c) 2014 Orlando Salvatore. All rights reserved.
//

#include "Level.h"

const int Level::TIME_ADDED_PER_TILE = 10;

Level::Level() : _levelTime(0), name("Default Name")
{
    
}

Level::Level(std::string name) : _levelTime(0), name(name)
{
   
}

Level::~Level()
{

}

void Level::load(){
   SceneManager::instance().clearScene();
   for(GameObject *tile : _tiles){
       SceneManager::instance().addGameObject(tile);
       tile->onLoad();
   }
   for(GameObject *wall : _walls){
      SceneManager::instance().addGameObject(wall);
      wall->onLoad();
   }
   SceneManager::instance().addGameObject(_tee);
   _tee->onLoad();
   SceneManager::instance().addGameObject(_cup);
   _cup->onLoad();
   
   glm::vec3 ballOffset = glm::vec3(0,_ball->getRadius(),0);
   glm::vec3 teeOffset = glm::vec3(0, _tee->getScale().y/2, 0);
   _ball->setPosition(_tee->getPosition()+ballOffset+teeOffset);
   _ball->stop();
   SceneManager::instance().addGameObject(_ball);
   _ball->onLoad();
}

void Level::addTile(Tile *t)
{
    _tiles.push_back(t);
    _levelTime += TIME_ADDED_PER_TILE;
}

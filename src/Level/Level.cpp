//
//  Level.cpp
//  MiniGolfXCode
//
//  Created by Orlando Salvatore on 6/2/14.
//  Copyright (c) 2014 Orlando Salvatore. All rights reserved.
//

#include "Level.h"

const int Level::TIME_ADDED_PER_TILE = 10;

Level::Level() : _levelTime(0)
{
    
}

Level::~Level()
{

}

void Level::addTile(Tile *t)
{
    _tiles.push_back(t);
    _levelTime += TIME_ADDED_PER_TILE;
}
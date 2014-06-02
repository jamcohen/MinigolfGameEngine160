//
//  GameTimerManager.cpp
//  MiniGolfXCode
//
//  Created by Orlando Salvatore on 6/2/14.
//  Copyright (c) 2014 Orlando Salvatore. All rights reserved.
//

#include "GameTimerManager.h"

GameTimerManager::GameTimerManager()
{
    
}

GameTimerManager::~GameTimerManager()
{
    
}

void GameTimerManager::update(float time)
{
    for(GameTimer *t : _timers)
    {
        t->update(time);
    }
}
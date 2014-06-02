//
//  GameTimerManager.h
//  MiniGolfXCode
//
//  Created by Orlando Salvatore on 6/2/14.
//  Copyright (c) 2014 Orlando Salvatore. All rights reserved.
//

#ifndef __MiniGolfXCode__GameTimerManager__
#define __MiniGolfXCode__GameTimerManager__

#include <iostream>
#include <vector>
#include "GameTimer.h"

class GameTimerManager
{
public:
    static GameTimerManager& instance()
    {
        static GameTimerManager INSTANCE;
        return INSTANCE;
    }
    GameTimerManager();
    virtual ~GameTimerManager();
    void update(float);
    inline void addGameTimer(GameTimer *t) { _timers.push_back(t); }
    
private:
    std::vector<GameTimer*> _timers;
};

#endif /* defined(__MiniGolfXCode__GameTimerManager__) */

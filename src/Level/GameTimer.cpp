//
//  Timer.cpp
//  ;
//
//  Created by Orlando Salvatore on 6/2/14.
//  Copyright (c) 2014 Orlando Salvatore. All rights reserved.
//

#include "GameTimer.h"

#ifndef TIME_STEP
#define TIME_STEP 1000 / 60
#endif

GameTimer::GameTimer(float maxTime, uint fontSize, glm::vec3 color) : _maxTime(maxTime), _timeLeft(maxTime), _paused(false), TextElement(" ", fontSize, color)
{
    std::string s = "Time Left: " + std::to_string((int)_timeLeft);
    updateText(s);
}

GameTimer::~GameTimer()
{
    
}

void GameTimer::setCompletedCallback(std::function<void(bool)> callback)
{
    _callback = callback;
}

void GameTimer::resetTimer()
{
    _timeLeft = _maxTime;
}

void GameTimer::update(float updateTime)
{
    if(_paused)
    {
        return;
    }
    _timeLeft -= updateTime*0.001f;
    std::string s = "Time Left: " + std::to_string((int)_timeLeft);
    updateText(s);
    if((int)_timeLeft <= 0)
    {
        if(_callback)
        {
            _callback(true);
        }
        pause();
    }
}
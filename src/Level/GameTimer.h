//
//  Timer.h
//  MiniGolfXCode
//
//  Created by Orlando Salvatore on 6/2/14.
//  Copyright (c) 2014 Orlando Salvatore. All rights reserved.
//

#ifndef __MiniGolfXCode__Timer__
#define __MiniGolfXCode__Timer__

#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <functional>
#include "TextElement.h"

typedef bool (*TimerCallback)(void);

class GameTimer : public TextElement
{
public:
    GameTimer(float, uint, glm::vec3);
    virtual ~GameTimer();
    void resetTimer();
    void update(float);
    void setCompletedCallback(std::function<void(bool)>);
    inline void setMaxTime(float maxTime) { _maxTime = maxTime; }
    inline float getMaxTime() { return _maxTime; }
    inline float getTimeLeft() { return _timeLeft; }
    inline void pause() { _paused = true; }
    inline void start() { _paused = false; }
    
private:
    float _maxTime;
    float _timeLeft;
    bool _paused;
    std::function<void(bool)> _callback;
};

#endif /* defined(__MiniGolfXCode__Timer__) */

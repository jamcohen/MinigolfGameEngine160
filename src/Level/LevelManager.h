//
//  LevelManager.h
//  MiniGolfXCode
//
//  Created by Orlando Salvatore on 6/2/14.
//  Copyright (c) 2014 Orlando Salvatore. All rights reserved.
//

#ifndef __MiniGolfXCode__LevelManager__
#define __MiniGolfXCode__LevelManager__

#include <iostream>
#include <vector>
#include <string>
#include "GameTimer.h"
#include "GameTimerManager.h"
#include "Level.h"
#include "Drawing.h"
#include "TextElement.h"

class LevelManager
{
public:
    static LevelManager& instance()
    {
        static LevelManager INSTANCE;
        return INSTANCE;
    }
    LevelManager();
    virtual ~LevelManager();
    inline Level* getCurrentLevel() { return _levels[_currentLevel]; }
    void addLevel(Level*);
    void closeAllLevels();
    void init();
    void restartLevel(bool);
    void levelCompleted();
    void levelFailed(bool);
    void goToNextLevel(bool);
    void setCourseName(std::string name) { _courseName = name; }
    std::string getCourseName() { return _courseName; }
    
private:
    std::vector<Level *> _levels;
    GameTimer* _levelTimer;
    GameTimer* _transitionTimer;
    int _currentLevel;
    TextElement *_failText;
    TextElement *_failText2;
    TextElement *_successText;
    TextElement *_successText2;
    std::string _courseName;
    
};

#endif /* defined(__MiniGolfXCode__LevelManager__) */

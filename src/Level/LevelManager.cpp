//
//  LevelManager.cpp
//  MiniGolfXCode
//
//  Created by Orlando Salvatore on 6/2/14.
//  Copyright (c) 2014 Orlando Salvatore. All rights reserved.
//

#include "LevelManager.h"

LevelManager::LevelManager() : _currentLevel(0)
{

}

void LevelManager::init()
{
    _transitionTimer = new GameTimer(5, 40, glm::vec3(0.3,0.4,0.5));
    _transitionTimer->pause();
    _transitionTimer->setEnabled(false);
    GameTimerManager::instance().addGameTimer(_transitionTimer);
    
    _levelTimer = new GameTimer(5.0f, 40, glm::vec3(0.25,0.7,0.6));
    _levelTimer->setCompletedCallback(std::bind(&LevelManager::levelFailed,this,std::placeholders::_1));
    GameTimerManager::instance().addGameTimer(_levelTimer);
    
    _successText = new TextElement("Congratulations!", 50, glm::vec3(1,1,1));
    _successText->setPosition(glm::vec2((Drawing::SCREEN_WIDTH - _successText->getWidth())/2,
                                        (Drawing::SCREEN_HEIGHT - _successText->getHeight())/2));
    _successText2 = new TextElement("You will be moving onto the next hole shortly...", 30, glm::vec3(0,.1,0));
    _successText2->setPosition(glm::vec2((Drawing::SCREEN_WIDTH - _successText2->getWidth())/2,(float)((Drawing::SCREEN_HEIGHT - _successText->getHeight())/2) - _successText2->getHeight()));
    _transitionTimer->setPosition(glm::vec2((Drawing::SCREEN_WIDTH - _transitionTimer->getWidth())/2,
                                            (float)((Drawing::SCREEN_HEIGHT - _successText->getHeight())/2) + _transitionTimer->getHeight()));
    _successText->setEnabled(false);
    _successText2->setEnabled(false);
    
    
    _failText = new TextElement("You have failed!", 50, glm::vec3(1,0,0));
    _failText->setPosition(glm::vec2((Drawing::SCREEN_WIDTH - _failText->getWidth())/2,
                                        (Drawing::SCREEN_HEIGHT - _failText->getHeight())/2));
    _failText2 = new TextElement("This round will restart soon...", 30, glm::vec3(0,.1,0));
    _failText2->setPosition(glm::vec2((Drawing::SCREEN_WIDTH - _failText2->getWidth())/2,(float)((Drawing::SCREEN_HEIGHT - _failText->getHeight())/2) - _failText2->getHeight()));
    _transitionTimer->setPosition(glm::vec2((Drawing::SCREEN_WIDTH - _transitionTimer->getWidth())/2,
                                            (float)((Drawing::SCREEN_HEIGHT - _failText->getHeight())/2) + _transitionTimer->getHeight()));
    _failText->setEnabled(false);
    _failText2->setEnabled(false);
    
}

LevelManager::~LevelManager()
{
    for(Level* l : _levels)
    {
        delete l;
    }
}

void LevelManager::addLevel(Level *l)
{
    _levels.push_back(l);
}

void LevelManager::goToNextLevel(bool s)
{
    _transitionTimer->resetTimer();
    _transitionTimer->pause();
    _transitionTimer->setEnabled(false);
    _currentLevel++;
    _levelTimer->setMaxTime(_levels[_currentLevel]->getLevelTime());
    _levelTimer->setEnabled(true);
    _levelTimer->start();
}

void LevelManager::levelFailed(bool s)
{
    _failText->setEnabled(true);
    _failText2->setEnabled(true);
    _levelTimer->pause();
    _levelTimer->setEnabled(false);
    _transitionTimer->setCompletedCallback(std::bind(&LevelManager::restartLevel,this,std::placeholders::_1));
    _transitionTimer->start();
    _transitionTimer->setEnabled(true);
}


void LevelManager::restartLevel(bool s)
{
    _failText->setEnabled(false);
    _failText2->setEnabled(false);
    _transitionTimer->resetTimer();
    _transitionTimer->pause();
    _transitionTimer->setEnabled(false);
    _levelTimer->resetTimer();
    _levelTimer->start();
    _levelTimer->setEnabled(true);
}

void LevelManager::levelCompleted()
{
    _levelTimer->pause();
    _successText->setEnabled(true);
    _transitionTimer->setCompletedCallback(std::bind(&LevelManager::goToNextLevel,this,std::placeholders::_1));
    _transitionTimer->start();
    _transitionTimer->setEnabled(true);
}
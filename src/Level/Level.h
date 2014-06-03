//
//  Level.h
//  MiniGolfXCode
//
//  Created by Orlando Salvatore on 6/2/14.
//  Copyright (c) 2014 Orlando Salvatore. All rights reserved.
//

#ifndef __MiniGolfXCode__Level__
#define __MiniGolfXCode__Level__

#include <iostream>
#include <vector>
#include "Tile.h"
#include "Tee.h"
#include "Cup.h"
#include "Ball.h"
#include "Wall.h"

class Level
{
public:
    static const int TIME_ADDED_PER_TILE;
    std::string name;
    
    Level();
    Level(std::string name);
    virtual ~Level();
    
    void load();
    void addTile(Tile*);
    inline void addWall(Wall* wall) { _walls.push_back(wall); };
    inline int getLevelTime() { return _levelTime; }
    inline void setTee(Tee* tee) { _tee = tee; }
    inline Tee* getTee() { return _tee; }
    inline void setCup(Cup* cup) { _cup = cup; }
    inline Cup* getCup() { return _cup; }
    inline void setBall(Ball* ball) { _ball = ball; }
    inline Ball* getBall() { return _ball; }
    
private:
    Tee *_tee;
    Cup *_cup;
    Ball *_ball;
    int _levelTime;
    
    std::vector<Tile*> _tiles;
    std::vector<Wall*> _walls;
};

#endif /* defined(__MiniGolfXCode__Level__) */

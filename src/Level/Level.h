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
#include "Portal.h"

class Level
{
public:
    static const int TIME_ADDED_PER_PAR;
    
    Level(std::string n = "Default Name", int par = 1);
    virtual ~Level();
    
    void load();
    void addTile(Tile*);
    inline void addPortal(Portal* portal) { _portals.push_back(portal); };
    inline void addWall(Wall* wall) { _walls.push_back(wall); };
    inline int getLevelTime() { return _levelTime; }
    inline void setTee(Tee* tee) { _tee = tee; }
    inline Tee* getTee() { return _tee; }
    inline void setCup(Cup* cup) { _cup = cup; }
    inline Cup* getCup() { return _cup; }
    inline void setBall(Ball* ball) { _ball = ball; }
    inline Ball* getBall() { return _ball; }
    inline void setName(std::string name) { _name = name; }
    inline std::string getName() { return _name; }
    void setPar(int);
    inline int getPar() { return _par; }
    
private:
    Tee *_tee;
    Cup *_cup;
    Ball *_ball;
    int _levelTime;
    int _par;
    std::string _name;
    
    std::vector<Tile*> _tiles;
    std::vector<Portal*> _portals;
    std::vector<Wall*> _walls;
};

#endif /* defined(__MiniGolfXCode__Level__) */

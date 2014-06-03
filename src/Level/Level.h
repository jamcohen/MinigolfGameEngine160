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

class Level
{
public:
    static const int TIME_ADDED_PER_TILE;
    
    Level();
    virtual ~Level();
    void addTile(Tile*);
    inline int getLevelTime() { return _levelTime; }
    inline void setTee(Tee* tee) { _tee = tee; }
    inline void setCup(Cup* cup) { _cup = cup; }
    
private:
    Tee *_tee;
    Cup *_cup;
    int _levelTime;
    
    std::vector<Tile*> _tiles;
};

#endif /* defined(__MiniGolfXCode__Level__) */

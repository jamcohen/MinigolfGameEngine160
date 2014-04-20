//
//  FileIO.h
//  MiniGolfXCode
//
//  Created by Orlando Salvatore on 4/18/14.
//  Copyright (c) 2014 Orlando Salvatore. All rights reserved.
//

#ifndef __MiniGolfXCode__FileIO__
#define __MiniGolfXCode__FileIO__

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "SceneManager.h"
#include "glm.hpp"
#include "Tile.h"
#include "Tee.h"
#include "Cup.h"

class FileIO
{
public:
    FileIO();
    ~FileIO();
    bool parseTileMap(const std::string);
    bool is_number(const std::string&);
    bool checkForCarriageReturn(std::string*);
    bool parseTile(std::string*, bool&);
    bool parseTeeOrCup(std::string*, bool&, bool);
    glm::vec3 getTilePosition(std::vector<glm::vec3>);
    std::vector<int> getTriangles(std::vector<glm::vec3>);
    
private:
    std::ifstream _fin;
};

#endif /* defined(__MiniGolfXCode__FileIO__) */

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
#include <cMath>
#include "SceneManager.h"
#include "glm.hpp"
#include "LevelManager.h"
#include "Tile.h"
#include "Tee.h"
#include "Model.h"
#include "Cup.h"
#include "Wall.h"
#include "Ball.h"
#include "Portal.h"

class FileIO
{
public:
    FileIO();
    ~FileIO();
    bool parseMapFile(const std::string filename);
    bool parseTileMap(Level*);
    bool is_number(const std::string&);
    bool checkForCarriageReturn(std::string*);
    bool parseTileOrPortal(std::string*, bool&, Level*, bool);
    bool parseTeeOrCup(std::string*, bool&, bool, Level*);
    glm::vec3 getTilePosition(std::vector<glm::vec3>);
    std::vector<unsigned int> getTriangles(std::vector<glm::vec3>);
    std::vector<glm::vec3> getNormals(std::vector<unsigned int>,std::vector<glm::vec3>);
    std::vector<glm::vec3> getLocalVertices(glm::vec3,std::vector<glm::vec3>);
    std::vector<glm::vec3> getColors(std::vector<glm::vec3>, glm::vec3);
    void spawnWalls(std::vector<glm::vec3> *, std::vector<int> *, glm::vec3, Level*);
    std::vector<unsigned int>  getBordersTriangles(std::vector<int> *);
    
private:
    std::ifstream _fin;
    int _numLevels = 0;
};

#endif /* defined(__MiniGolfXCode__FileIO__) */

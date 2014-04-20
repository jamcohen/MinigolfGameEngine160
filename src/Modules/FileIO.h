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

class FileIO
{
public:
    FileIO();
    ~FileIO();
    bool parseTileMap(std::string);
    
private:
    std::ifstream _fin;
};

#endif /* defined(__MiniGolfXCode__FileIO__) */

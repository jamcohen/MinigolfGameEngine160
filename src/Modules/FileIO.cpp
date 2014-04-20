//
//  FileIO.cpp
//  MiniGolfXCode
//
//  Created by Orlando Salvatore on 4/18/14.
//  Copyright (c) 2014 Orlando Salvatore. All rights reserved.
//

#include "FileIO.h"

FileIO::FileIO()
{
    
}

FileIO::~FileIO()
{
    
}

/*
 * Parses a specified tile map
 */
bool FileIO::parseTileMap(std::string filename)
{
    std::cout << filename << std::endl << std::endl;
    _fin.open(filename);
    if(!_fin.good())
    {
        std::cout << "Invalid filename!";
        return false;
    }
    
    while(!_fin.eof())
    {
        std::string s;
        
        std::getline(_fin, s,' ');
        std::cout << s << std::endl;
    }
    
    return true;
}
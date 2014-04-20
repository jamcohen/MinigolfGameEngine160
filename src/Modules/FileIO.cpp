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
bool FileIO::parseTileMap(const std::string filename)
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
        
        if(s == "tile")
        {
            int index;
            int numOfVerticies;
            std::vector<glm::vec3> verticies;
            std::vector<int> neighbors;
            
            //Get the index
            std::getline(_fin, s,' ');
            if(is_number(s))
            {
                index = std::atoi(s.c_str());
                std::cout << "Index: " << index << std::endl;
            }else{
                std::cout << "Invalid tile index number!";
                return false;
            }
            
            //Get the number of verticies
            std::getline(_fin, s,' ');
            if(is_number(s))
            {
                numOfVerticies = std::atoi(s.c_str());
                std::cout << "Number Of Vericies: " << numOfVerticies << std::endl;
            }else{
                std::cout << "Invalid number of verticies!";
                return false;
            }
            
            //Get the verticies
            for(auto i = 0; i < numOfVerticies; i++)
            {
                glm::vec3 v;
                std::cout << "Vertex " << i << ": ";
                //Get a vertex
                for(auto j = 0; j < 3; j++) {
                    std::getline(_fin, s,' ');
                    v.x = std::stof(s.c_str());
                    std::cout << v.x << " ";
                    
                    std::getline(_fin, s,' ');
                    v.y = std::stof(s.c_str());
                    std::cout << v.y << " ";
                    
                    std::getline(_fin, s,' ');
                    v.z = std::stof(s.c_str());
                    std::cout << v.z << std::endl;
                }
                verticies.push_back(v);
            }
            
            //Get neighbors
            for(auto i = 0; i < numOfVerticies; i++)
            {
                int n;
                std::getline(_fin, s,' ');
                n = std::atoi(s.c_str());
                std::cout << n << std::endl;
                neighbors.push_back(n);
            }
            
            glm::vec3 v;
            
            new Tile(index,v,verticies,neighbors);
            
            return true;
        }
    }
    
    return true;
}

bool FileIO::is_number(const std::string& s)
{
    return !s.empty() && std::find_if(s.begin(),
                                      s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
}
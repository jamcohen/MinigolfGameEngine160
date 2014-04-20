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
    
    int count = 0;
    bool encounteredCarriageReturn = false;
    std::string s;
    while(!_fin.eof())
    {
        if(!encounteredCarriageReturn)
        {
            std::getline(_fin, s,' ');
        }
        
        if(s == "tile")
        {
            encounteredCarriageReturn = false;
            if(!parseTile(&s, encounteredCarriageReturn))
            {
                return false;
            }
            std::cout << count << " Tile Put In\n";
            count++;
        }
        else if (s == "tee")
        {
            encounteredCarriageReturn = false;
            if(!parseTee(&s, encounteredCarriageReturn))
            {
                return false;
            }
        }
        else if (s == "cup")
        {
            encounteredCarriageReturn = false;
            if(!parseCup(&s))
            {
                return false;
            }
        }
        else
        {
            std::cout << " CANT READ: " << s << std::endl;
            encounteredCarriageReturn = false;
        }
    }
    return true;
}

bool FileIO::parseTile(std::string *s, bool &encounteredCarriageReturn)
{
    int index;
    int numOfVerticies;
    std::vector<glm::vec3> verticies;
    std::vector<int> neighbors;
    
    //Get the index
    std::getline(_fin, *s,' ');
    if(is_number(*s))
    {
        index = std::atoi(s->c_str());
        std::cout << "Index: " << index << std::endl;
    }else{
        std::cout << "Invalid tile index number!";
        return false;
    }
    
    //Get the number of verticies
    std::getline(_fin, *s,' ');
    if(is_number(*s))
    {
        numOfVerticies = std::atoi(s->c_str());
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
        std::getline(_fin, *s,' ');
        v.x = std::stof(s->c_str());
        std::cout << v.x << " ";
        
        std::getline(_fin, *s,' ');
        v.y = std::stof(s->c_str());
        std::cout << v.y << " ";
        
        std::getline(_fin, *s,' ');
        v.z = std::stof(s->c_str());
        std::cout << v.z << std::endl;
        
        verticies.push_back(v);
    }
    
    //Get neighbors
    std::cout << "Neighbors: ";
    for(auto i = 0; i < numOfVerticies; i++)
    {
        int n;
        std::getline(_fin, *s,' ');
        n = std::atoi(s->c_str());
        std::cout << n << " ";
        neighbors.push_back(n);
    }
    std::cout << std::endl;
    
    //Check if carriage return is bundled with last grab
    encounteredCarriageReturn = checkForCarriageReturn(s);
    glm::vec3 v;
    
    new Tile(index,v,verticies,neighbors);
    return true;
}

bool FileIO::parseTee(std::string *s, bool &encounteredCarriageReturn)
{
    int index;
    int numOfVerticies;
    std::vector<glm::vec3> verticies;
    std::vector<int> neighbors;
    
    //Get the index
    std::getline(_fin, *s,' ');
    if(is_number(*s))
    {
        index = std::atoi(s->c_str());
        std::cout << "Index: " << index << std::endl;
    }else{
        std::cout << "Invalid tile index number!";
        return false;
    }
    
    //Get the number of verticies
    std::getline(_fin, *s,' ');
    if(is_number(*s))
    {
        numOfVerticies = std::atoi(s->c_str());
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
        std::getline(_fin, *s,' ');
        v.x = std::stof(s->c_str());
        std::cout << v.x << " ";
        
        std::getline(_fin, *s,' ');
        v.y = std::stof(s->c_str());
        std::cout << v.y << " ";
        
        std::getline(_fin, *s,' ');
        v.z = std::stof(s->c_str());
        std::cout << v.z << std::endl;
        
        verticies.push_back(v);
    }
    
    //Get neighbors
    std::cout << "Neighbors: ";
    for(auto i = 0; i < numOfVerticies; i++)
    {
        int n;
        std::getline(_fin, *s,' ');
        n = std::atoi(s->c_str());
        std::cout << n << " ";
        neighbors.push_back(n);
    }
    std::cout << std::endl;
    
    //Check if carriage return is bundled with last grab
    encounteredCarriageReturn = checkForCarriageReturn(s);
    glm::vec3 v;
    
    new Tile(index,v,verticies,neighbors);
    return true;
}

bool FileIO::parseCup(std::string* s)
{
    int index;
    int numOfVerticies;
    std::vector<glm::vec3> verticies;
    std::vector<int> neighbors;
    
    //Get the index
    std::getline(_fin, *s,' ');
    if(is_number(*s))
    {
        index = std::atoi(s->c_str());
        std::cout << "Index: " << index << std::endl;
    }else{
        std::cout << "Invalid tile index number!";
        return false;
    }
    
    //Get the number of verticies
    std::getline(_fin, *s,' ');
    if(is_number(*s))
    {
        numOfVerticies = std::atoi(s->c_str());
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
        std::getline(_fin, *s,' ');
        v.x = std::stof(s->c_str());
        std::cout << v.x << " ";
        
        std::getline(_fin, *s,' ');
        v.y = std::stof(s->c_str());
        std::cout << v.y << " ";
        
        std::getline(_fin, *s,' ');
        v.z = std::stof(s->c_str());
        std::cout << v.z << std::endl;
        
        verticies.push_back(v);
    }
    
    //Get neighbors
    std::cout << "Neighbors: ";
    for(auto i = 0; i < numOfVerticies; i++)
    {
        int n;
        std::getline(_fin, *s,' ');
        n = std::atoi(s->c_str());
        std::cout << n << " ";
        neighbors.push_back(n);
    }
    std::cout << std::endl;
    
    glm::vec3 v;
    
    new Tile(index,v,verticies,neighbors);
    return true;
}

bool FileIO::checkForCarriageReturn(std::string *s)
{
    std::size_t found = s->find('\n');
    if (found!=std::string::npos)
    {
        std::cout << "FOUND ENTER at " << found << "\n";
        if(found != s->length())
        {
            *s = s->substr(found + 1,s->length()-found);
            std::cout << "New string: " << s << std::endl;
            return true;
        }
    }
    return false;
}

bool FileIO::is_number(const std::string& s)
{
    return !s.empty() && std::find_if(s.begin(),
                                      s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
}
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
            if(!parseTeeOrCup(&s, encounteredCarriageReturn,true))
            {
                return false;
            }
        }
        else if (s == "cup")
        {
            encounteredCarriageReturn = false;
            if(!parseTeeOrCup(&s, encounteredCarriageReturn,false))
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

/*
 * Parses for tile
 */
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
    
    //TO-DO: Need to get origin
    glm::vec3 position = getTilePosition(verticies);
    std::cout << position.x << " " << position.y << " " << position.z << std::endl;
    
    //new Tile(index,position,verticies,neighbors);
    return true;
}

/*
 * Parses for Tee or Cup
 *
 * @param isTee : set to true if we are parsing for a tee
 */
bool FileIO::parseTeeOrCup(std::string *s, bool &encounteredCarriageReturn, bool isTee)
{
    int index;
    glm::vec3 position;
    
    //Get the index
    std::getline(_fin, *s,' ');
    if(is_number(*s))
    {
        index = std::atoi(s->c_str());
        if(isTee)
        {
            std::cout << "Tee Index: " << index << std::endl;
        }
        else
        {
            std::cout << "Cup Index: " << index << std::endl;
        }
    }else{
        std::cout << "Invalid tee index number!";
        return false;
    }

    //Get a vertex
    std::getline(_fin, *s,' ');
    position.x = std::stof(s->c_str());
    std::cout << position.x << " ";
    
    std::getline(_fin, *s,' ');
    position.y = std::stof(s->c_str());
    std::cout << position.y << " ";
    
    std::getline(_fin, *s,' ');
    position.z = std::stof(s->c_str());
    std::cout << position.z << std::endl;
    
    //Check if carriage return is bundled with last grab
    encounteredCarriageReturn = checkForCarriageReturn(s);
    
    if(isTee)
    {
        //new Tee(index,position);
    }
    else
    {
       //new Cup(index,position);
    }
    return true;
}

/*
 * Get the position for the tile
 */
glm::vec3 FileIO::getTilePosition(std::vector<glm::vec3> vertices)
{
    glm::vec3 position;
    for(glm::vec3 v : vertices)
    {
        position += v;
    }
    position = (position/(float)(vertices.size()));
    return position;
}

/*
 * Gets implicit triangles for the given vertices
 */
std::vector<int> FileIO::getTriangles(std::vector<glm::vec3> vertices)
{
    std::vector<int> triangles;
    if(vertices.size() < 3)
    {
        return triangles;
    }
    
    int lastVertex = (int)(vertices.size())-1;
    for(int i = 0; i < vertices.size() - 2; i++)
    {
        triangles.push_back(i);
        triangles.push_back(i+1);
        triangles.push_back(lastVertex);
    }
    
    return triangles;
}

/*
 * Checks for a carriage return in the given string
 */
bool FileIO::checkForCarriageReturn(std::string *s)
{
    std::size_t found = s->find('\n');
    if (found!=std::string::npos)
    {
        if(found != s->length())
        {
            *s = s->substr(found + 1,s->length()-found);
            return true;
        }
    }
    return false;
}

/*
 * Checks to see if the string is a number
 */
bool FileIO::is_number(const std::string& s)
{
    return !s.empty() && std::find_if(s.begin(),
                                      s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
}
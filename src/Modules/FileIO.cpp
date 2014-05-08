//
//  FileIO.cpp
//  MiniGolfXCode
//
//  Created by Orlando Salvatore on 4/18/14.
//  Copyright (c) 2014 Orlando Salvatore. All rights reserved.
//

#include "FileIO.h"
#include <cstdlib>
#include <time.h>

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
            //std::cout << count << " Tile Put In\n";
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
    std::vector<glm::vec3> vertices;
    std::vector<int> neighbors;
    
    //Get the index
    std::getline(_fin, *s,' ');
    if(is_number(*s))
    {
        index = std::atoi(s->c_str());
        //std::cout << "Index: " << index << std::endl;
    }else{
        std::cout << "Invalid tile index number!";
        return false;
    }
    
    //Get the number of verticies
    std::getline(_fin, *s,' ');
    if(is_number(*s))
    {
        numOfVerticies = std::atoi(s->c_str());
        //std::cout << "Number Of Vericies: " << numOfVerticies << std::endl;
    }else{
        std::cout << "Invalid number of verticies!";
        return false;
    }
    
    //Get the verticies
    for(auto i = 0; i < numOfVerticies; i++)
    {
        glm::vec3 v;
        //std::cout << "Vertex " << i << ": ";
        //Get a vertex
        std::getline(_fin, *s,' ');
        v.x = std::stof(s->c_str());
        //std::cout << v.x << " ";
        
        std::getline(_fin, *s,' ');
        v.y = std::stof(s->c_str());
        //std::cout << v.y << " ";
        
        std::getline(_fin, *s,' ');
        v.z = std::stof(s->c_str());
        //std::cout << v.z << std::endl;
        
        vertices.push_back(v);
    }
    
    //Get neighbors
    //std::cout << "Neighbors: ";
    for(auto i = 0; i < numOfVerticies; i++)
    {
        int n;
        std::getline(_fin, *s,' ');
        n = std::atoi(s->c_str());
        //std::cout << "neighbor: " << n << " ";
        neighbors.push_back(n);
    }
    std::cout << std::endl;
    
    //Check if carriage return is bundled with last grab
    encounteredCarriageReturn = checkForCarriageReturn(s);
    
    glm::vec3 position = getTilePosition(vertices);
    std::vector<unsigned int> indices = getTriangles(vertices);
    std::vector<glm::vec3> localVertices = getLocalVertices(position,vertices);
    std::vector<glm::vec3> normals = getNormals(indices,localVertices);
    std::vector<glm::vec3> colors = getColors(vertices);
    Model *model = new Model(localVertices,normals,colors,indices);
    new Tile(index,position,model,neighbors);
    spawnWalls(&localVertices, &neighbors, position); //Spawn the wall
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
    //std::cout << position.x << " ";
    
    std::getline(_fin, *s,' ');
    position.y = std::stof(s->c_str());
   // std::cout << position.y << " ";
    
    std::getline(_fin, *s,' ');
    position.z = std::stof(s->c_str());
    //std::cout << position.z << std::endl;
    
    //Check if carriage return is bundled with last grab
    encounteredCarriageReturn = checkForCarriageReturn(s);
    
    if(isTee)
    {
        //new Wall(position, glm::vec3(0,0,0), 0.1, 0.1, 0.1, glm::vec3(0.7, 0, 0));
        //new Tee(index,position);
    }
    else
    {
       new Wall(position, glm::vec3(0,0,0), 0.1, 0.1, 0.1, glm::vec3(0, 0.2, 0.7));
       //new Ball(position+glm::vec3(0,3,0), glm::vec3(0,0,0), glm::vec3(0, 0.2, 0.7), 0.05f);
       new Ball(position+glm::vec3(0.3,.05,0.8), glm::vec3(0,0,0), glm::vec3(0, 0.2, 0.7), 0.05f);
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

//Adds the vertices of the borders to the vertices vextor
void FileIO::spawnWalls(std::vector<glm::vec3> *vertices, std::vector<int> *neighbors, glm::vec3 position){
    bool partOfEdge = false; //if this neighbor is part of a continuous edge, as opposed to a single edge;
    for(unsigned int i = 0; i<neighbors->size(); ++i){
        if((*neighbors)[i] == 0){
            unsigned int nextI = (i+1)%neighbors->size();
            //spawn wall at the midpoint between the two points;
            glm::vec3 pos = ((*vertices)[i]+(*vertices)[nextI])*0.5f;
            pos += position;
            glm::vec3 dir = (*vertices)[nextI]-(*vertices)[i];
            float distance = sqrt(glm::dot(dir, dir));
            dir = glm::normalize(dir);
           
            float angleY = atan2f(dir.x, dir.z);
            angleY = (angleY != angleY) ? 0 : angleY*180/M_PI;
            //Reduce the angle range from 180,-180 to 90,-90
            //so that the walls are always facing the same way
            if(angleY > 90) angleY -= 180;
            if(angleY < -90) angleY += 180;
           
            float angleX = atan2f(-dir.y, dir.z);
            angleX = (angleX != angleX) ? 0 : angleX*180/M_PI;
            if(angleX > 90) angleX -= 180;
            if(angleX < -90) angleX += 180;

            Wall *w = new Wall(pos, glm::vec3(angleX, angleY, 0), 0.05, 0.8, distance, glm::vec3(0.7, 0.43, 0));
        }
    }
}
//
//std::vector<unsigned int> FileIO::getBordersTriangles(std::vector<int> *neighbors){
//    std::vector<unsigned int> triangles;
//    bool partOfEdge = false;
//    unsigned int numBorderVerts = 0;
//    for(size_t i = 0; i<neighbors->size(); ++i){
//        if((*neighbors)[i] == 0) numBorderVerts++;
//    }
//    for(unsigned int i = 0; i<neighbors->size(); ++i){
//        if((*neighbors)[i] == 0){
//            unsigned int nextI = (i+1)%neighbors->size();
//            unsigned int bottomLeftCorner = i;
//            unsigned int bottomRightCorner = nextI;
//            unsigned int topLeftCorner = i+neighbors->size();
//            unsigned int topRightCorner = nextI+neighbors->size();//%(neighbors->size()+numBorderVerts);
//            
//            std::cout << "bottomR: " << bottomRightCorner << ", bottomL" << bottomLeftCorner << ", TopR" << topRightCorner << ", TopL" << topLeftCorner << std::endl;
//            
//            triangles.push_back(bottomLeftCorner);
//            triangles.push_back(bottomRightCorner);
//            triangles.push_back(topRightCorner);
//            
//            triangles.push_back(topLeftCorner);
//            triangles.push_back(bottomLeftCorner);
//            triangles.push_back(topRightCorner);
//            
//            triangles.push_back(topRightCorner);
//            triangles.push_back(bottomRightCorner);
//            triangles.push_back(bottomLeftCorner);
//            
//            triangles.push_back(topRightCorner);
//            triangles.push_back(bottomLeftCorner);
//            triangles.push_back(topLeftCorner);
//            
//        }
//        partOfEdge = ((*neighbors)[i] == 0);
//    }
//    return triangles;
//}

/*
 * Gets implicit triangles for the given vertices
 */
std::vector<unsigned int> FileIO::getTriangles(std::vector<glm::vec3> vertices)
{
    std::vector<unsigned int> triangles;
    if(vertices.size() < 3)
    {
        return triangles;
    }
    
    int lastVertex = (int)(vertices.size())-1;
    for(unsigned int i = 0; i < vertices.size() - 2; i++)
    {
        triangles.push_back(i);
        triangles.push_back(i+1);
        triangles.push_back(lastVertex);
    }
    
    return triangles;
}

/*
 * Gets the normals for the tile
 */
std::vector<glm::vec3> FileIO::getNormals(std::vector<unsigned int> triangles, std::vector<glm::vec3> vertices)
{
    std::vector<glm::vec3> normals;
    for(auto i = 0; i < vertices.size(); i++)
    {
        glm::vec3 v;
        normals.push_back(v);
    }
    
    int i = 0;
    while(i < triangles.size())
    {
        normals[triangles[i]] += glm::cross(vertices[triangles[i+1]] - vertices[triangles[i]],
                                       vertices[triangles[i+2]] - vertices[triangles[i]]);
        normals[triangles[i+1]] += glm::cross(vertices[triangles[i+2]] - vertices[triangles[i+1]],
                                     vertices[triangles[i]] - vertices[triangles[i+1]]);
        normals[triangles[i+2]] += glm::cross(vertices[triangles[i]] - vertices[triangles[i+2]],
                                             vertices[triangles[i+1]] - vertices[triangles[i+2]]);
        i += 3;
    }
    
    return normals;
}

/*
 * Gets the local vertices according to the specified position
 */
std::vector<glm::vec3> FileIO::getLocalVertices(glm::vec3 position, std::vector<glm::vec3> vertices)
{
    std::vector<glm::vec3> localVertices;
    for(glm::vec3 v : vertices)
    {
        glm::vec3 newVert = v - position;
        //std::cout << "vertex: " << newVert.x << " " <<  newVert.y << " " << newVert.z <<std::endl;
        localVertices.push_back(v - position);
    }
    return localVertices;
}

/*
 * Gets the colors for the vertex
 */
std::vector<glm::vec3> FileIO::getColors(std::vector<glm::vec3> vertices)
{
    srand ((unsigned int)(time(NULL)));
    std::vector<glm::vec3> colors;
    for(glm::vec3 v : vertices)
    {
        glm::vec3 randomColor;
        //randomColor.x = (float) rand()/(float)RAND_MAX;
        //randomColor.y = (float) rand()/(float)RAND_MAX;
        //randomColor.z = (float) rand()/(float)RAND_MAX;
        colors.push_back(glm::vec3(0,0.5,0));
    }
    
    
    return colors;
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
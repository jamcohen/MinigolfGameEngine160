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

bool FileIO::parseMapFile(const std::string filename){
    std::cout << filename << std::endl << std::endl;
    _fin.open(filename);
    if(!_fin.good())
    {
        std::cout << "Invalid filename!";
        return false;
    }
    std::string s;
    std::getline(_fin, s,' ');
    if(s != "course") {
        std::cout << "Invalid file format, no term \'course\'!\n";
        return false;
    }
    std::getline(_fin, s,' ');
    LevelManager::instance().setCourseName(s);
    std::cout << "Course Name: " << s << std::endl;
    
    std::getline(_fin, s,'\n');
    _numLevels = stoi(s);
    std::cout << "Num of levels: " << _numLevels << std::endl;
    
    for(int i=0; i<_numLevels;++i){
        //get begin hole
        while(s[0] != 'b') {
            std::getline(_fin, s,'\n');
            if(s[0] == 'b')
            {
                std::cout << "GET READY TO BEGIN!\n";
            }
        }
        std::cout << "Begin? " << s << std::endl;
        
        Level* tempLevel = new Level();
        
        std::cout << "Begin parsing again!\n";
        parseTileMap(tempLevel);
        
        LevelManager::instance().addLevel(tempLevel);
    }
    LevelManager::instance().init();
    //_currentLevel.load();
    //REMEMBER YOU NEED TO LOAD THE LEVEL.
    //HALF DONE, DOESN"T EVEN WORK NOW.
    return true;
}


/*
 * Parses a specified tile map
 */
bool FileIO::parseTileMap(Level* l)
{
    int count = 0;
    bool encounteredCarriageReturn = false;
    std::string s;
    while(!_fin.eof())
    {
        std::streampos finPos;
        if(!encounteredCarriageReturn)
        {
            finPos = _fin.tellg();
            std::getline(_fin, s,' ');
        }
        if(s[0] == 'e')
        {
            _fin.seekg(finPos);
            std::getline(_fin, s,'\n');
            std::cout << "End hole? " << s << std::endl;
            std::cout << "Finished Parsing Level!\n";
            return true;
        }
        else if(s[0] == 'b')
        {
            _fin.seekg(finPos);
            std::getline(_fin, s,'\n');
            std::cout << "Begin hole? Wat u doin here " << s << std::endl;
        }
        else if(s == "tile")
        {
            encounteredCarriageReturn = false;
            if(!parseTile(&s, encounteredCarriageReturn, l))
            {
                return false;
            }
            count++;
        }
        else if (s == "tee")
        {
            encounteredCarriageReturn = false;
            if(!parseTeeOrCup(&s, encounteredCarriageReturn, true, l))
            {
                return false;
            }
        }
        else if (s == "cup")
        {
            encounteredCarriageReturn = false;
            if(!parseTeeOrCup(&s, encounteredCarriageReturn, false, l))
            {
                return false;
            }
        }
        else if (s == "par")
        {
            std::getline(_fin, s,'\n');
            std::cout << "Par: " << s << std::endl;
            l->setPar(stoi(s));
        }
        else if (s == "name")
        {
            std::getline(_fin, s,'\n');
            std::cout << "Name of level: " << s << std::endl;
            l->setName(s);
        }
        else
        {
            std::cout << "CANT READ: " << s << std::endl;
            _fin.seekg(finPos);
            std::getline(_fin, s, '\n');
            encounteredCarriageReturn = false;
        }
    }
    return true;
}

/*
 * Parses for tile
 */
bool FileIO::parseTile(std::string *s, bool &encounteredCarriageReturn, Level* l)
{
    int index;
    int numOfVerticies;
    std::vector<glm::vec3> vertices;
    std::vector<int> neighbors;
    std::cout << *s << std::endl;
    std::getline(_fin, *s,' ');
    //Get the index
    while(!is_number(*s))
    {
        std::getline(_fin, *s,' ');
    }
    std::cout << *s << std::endl;
    if(is_number(*s))
    {
        index = std::atoi(s->c_str());
        //std::cout << "Index: " << index << std::endl;
    }else{
        std::cout << "Invalid tile index number!\n";
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
        *s = " ";
        while(*s == " " || s->length() == 0)
        {
            std::getline(_fin, *s,' ');
        }
        glm::vec3 v;
        //std::cout << "Vertex " << i << ": ";
        //Get a vertex
        //std::getline(_fin, *s,' ');
        v.x = std::stof(s->c_str());
        std::cout << v.x << " ";
        
        *s = " ";
        while(*s == " " || s->length() == 0)
        {
            std::getline(_fin, *s,' ');
        }
        //std::getline(_fin, *s,' ');
        v.y = std::stof(s->c_str());
        std::cout << v.y << " ";
        
        *s = " ";
        while(*s == " " || s->length() == 0)
        {
            std::getline(_fin, *s,' ');
        }
        //std::getline(_fin, *s,' ');
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
    l->addTile(new Tile(index,position,model,neighbors));
    std::cout << "Added tile!\n";
    spawnWalls(&localVertices, &neighbors, position, l); //Spawn the wall
    return true;
}

/*
 * Parses for Tee or Cup
 *
 * @param isTee : set to true if we are parsing for a tee
 */
bool FileIO::parseTeeOrCup(std::string *s, bool &encounteredCarriageReturn, bool isTee, Level* l)
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
    
    std::getline(_fin, *s,'\n');
    position.z = std::stof(s->c_str());
    //std::cout << position.z << std::endl;
    
    //Check if carriage return is bundled with last grab
    encounteredCarriageReturn = checkForCarriageReturn(s);
    
    if(isTee)
    {
        //new Wall(position, glm::vec3(0,0,0), 0.1, 0.1, 0.1, glm::vec3(0.7, 0, 0));
        l->setTee(new Tee(index,position));
        l->setBall(new Ball(position+glm::vec3(0.0,.3,0.0), glm::quat(), glm::vec3(0, 0.5, 0.5), 0.05f));
    }
    else
    {
        //new Wall(position, glm::quat(), 0.1, 0.1, 0.1, glm::vec3(0, 0.2, 0.7));
        //new Ball(position+glm::vec3(0,3,0), glm::vec3(0,0,0), glm::vec3(0, 0.2, 0.7), 0.05f);
        l->setCup(new Cup(index,position));
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
void FileIO::spawnWalls(std::vector<glm::vec3> *vertices, std::vector<int> *neighbors, glm::vec3 position, Level* l){
    for(unsigned int i = 0; i<neighbors->size(); ++i){
        if((*neighbors)[i] == 0){
            unsigned int nextI = (i+1)%neighbors->size();
            //spawn wall at the midpoint between the two points;
            glm::vec3 pos = ((*vertices)[i]+(*vertices)[nextI])*0.5f;
            pos += position;
            glm::vec3 dir = (*vertices)[nextI]-(*vertices)[i];
            dir = glm::normalize(dir);
            
            float cos_theta = glm::dot(glm::vec3(0,0,1), dir);
            float angle = acos(cos_theta);
            glm::vec3 axis = glm::normalize(glm::cross(glm::vec3(0,0,1), dir));
            //std::cout << "AXIS: " << axis.x << ", " << axis.y << ", " << axis.z << std::endl;
            //std::cout << "ANGLE: " << angle << std::endl;
            //glm::quat rotationZ =  glm::normalize(glm::angleAxis((float)(angle*180.0f/M_PI), axis));
            glm::quat rotationZ{};
            if(!isnan(axis.x)){
              rotationZ =  glm::angleAxis(angle*float(180/M_PI), axis);
            }
            //glm::quat rotationZ{};
            /*cos_theta = glm::dot(glm::vec3(1,0,0), dir);
            angle = acos(cos_theta);
            axis = glm::normalize(glm::cross(glm::vec3(0,0,1), dir));
            glm::quat rotationX =  glm::angleAxis(angle, dir);*/
            //Wall *w = new Wall(pos, rotationZ, 0.05, height, distance, glm::vec3(0.5,0.5,0.1));
            Wall *w = new Wall(position, (*vertices)[i], (*vertices)[nextI], 0.1, 0.108, glm::vec3(1,0,0));
            //Wall(const glm::vec3, glm::vec3 p1, glm::vec3 p2, float width, float height, glm::vec3 color);

            l->addWall(w);
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
        localVertices.push_back(newVert);
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
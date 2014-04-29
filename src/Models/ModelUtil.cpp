//
//  ModelUtil.cpp
//  MiniGolfXCode
//
//  Created by Orlando Salvatore on 4/24/14.
//  Copyright (c) 2014 Orlando Salvatore. All rights reserved.
//

#include "ModelUtil.h"

/*
 * Gets implicit triangles for the given vertices
 */
std::vector<unsigned int> ModelUtil::getFaceTriangles(std::vector<glm::vec3> vertices)
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
std::vector<glm::vec3> ModelUtil::getNormals(std::vector<unsigned int> triangles, std::vector<glm::vec3> vertices)
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
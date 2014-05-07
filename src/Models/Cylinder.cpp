//
//  Cylinder.cpp
//  MiniGolfXCode
//
//  Created by Orlando Salvatore on 4/24/14.
//  Copyright (c) 2014 Orlando Salvatore. All rights reserved.
//

#include "Cylinder.h"

Cylinder::Cylinder(int sideCount) : _sideCount(sideCount), Model()
{
    float stepSize = 2*M_PI/sideCount;
    std::vector<glm::vec3> vertices;
    for(auto i=0; i<sideCount; ++i)
    {
        glm::vec3 v(cos(stepSize*i),0.5f,sin(stepSize*i));
        vertices.push_back(v);
    }
    
    std::vector<glm::vec3> bottom;
    for(auto i=0; i<sideCount; i++)
    {
        bottom.push_back(vertices[i]);
        bottom[i].y -= 1.0f;
    }
    
    //std::reverse(bottom.begin(),bottom.end());
    std::vector<unsigned int> topTriangles = ModelUtil::getFaceTriangles(vertices);
    //std::vector<unsigned int> bottomTriangles = ModelUtil::getFaceTriangles(bottom);
    //std::reverse(bottom.begin(),bottom.end());
    
    vertices.insert(vertices.end(),bottom.begin(),bottom.end());
    for(glm::vec3 v : vertices)
    {
        std::cout << "VERT: " << v.x << " " << v.y << " " << v.z << std::endl;
    }
    
    std::vector<unsigned int> triangles;
    triangles.insert(triangles.end(),topTriangles.begin(), topTriangles.end());
    //triangles.insert(triangles.end(),bottomTriangles.begin(), bottomTriangles.end());
    
    for(auto i=0; i < sideCount; ++i)
    {
        if(i == sideCount - 1)
        {
            triangles.push_back(i);
            triangles.push_back(i+sideCount);
            triangles.push_back(i+1);
            triangles.push_back(i);
            triangles.push_back(i+1);
            triangles.push_back(0);
        } else {
            triangles.push_back(i);
            triangles.push_back(i+sideCount);
            triangles.push_back(i+1+sideCount);
            triangles.push_back(i);
            triangles.push_back(i+1+sideCount);
            triangles.push_back(i+1);
        }
    }
    
    int count = 0;
    for(unsigned int i : triangles)
    {
        std::cout << i << " ";
        count++;
        if(count == 3)
        {
            count = 0;
            std::cout << std::endl;
        }
    }
    
    std::vector<glm::vec3> normals = ModelUtil::getNormals(triangles, vertices);
    
    for(glm::vec3 n : normals)
    {
        std::cout << "NORMAL: " << n.x << " " << n.y << " " << n.z << std::endl;
    }
    
    std::cout << "TRICOUNT: " << triangles.size() << " NCOUNT: " << normals.size() << std::endl;
    
    std::vector<glm::vec3> colors;
    for(auto i=0; i < vertices.size(); ++i)
    {
        glm::vec3 color(0.5f,0.5f,0.5f);
        colors.push_back(color);
    }
    
    /*setVertices(vertices);
    setColors(colors);
    setNormals(normals);
   setTriangles(triangles);*/
}

Cylinder::~Cylinder()
{}
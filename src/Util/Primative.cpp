//
//  Primative.cpp
//  MiniGolfXCode
//
//  Created by Jake Cohen on 5/6/14.
//  Copyright (c) 2014 Orlando Salvatore. All rights reserved.
//

#include "Primative.h"

std::map<unsigned int, unsigned int> Primative::middlePointIndexCache{};

Model* Primative::getSphere(glm::vec3 color, float recursionLevel){
   std::vector<glm::vec3> vertices;
   std::vector<unsigned int> indices;
   
   // create 12 vertices of a icosahedron
   float t = (1.0 + sqrtf(5.0)) / 2.0;
   
   addVertex(vertices, glm::vec3(-1,  t,  0));
   addVertex(vertices, glm::vec3( 1,  t,  0));
   addVertex(vertices, glm::vec3(-1, -t,  0));
   addVertex(vertices, glm::vec3( 1, -t,  0));
   
   addVertex(vertices, glm::vec3( 0, -1,  t));
   addVertex(vertices, glm::vec3( 0,  1,  t));
   addVertex(vertices, glm::vec3( 0, -1, -t));
   addVertex(vertices, glm::vec3( 0,  1, -t));
   
   addVertex(vertices, glm::vec3( t,  0, -1));
   addVertex(vertices, glm::vec3( t,  0,  1));
   addVertex(vertices, glm::vec3(-t,  0, -1));
   addVertex(vertices, glm::vec3(-t,  0,  1));
   
   // 5 faces around point 0
   indices.push_back(0);
   indices.push_back(11);
   indices.push_back(5);
   
   indices.push_back(0);
   indices.push_back(5);
   indices.push_back(1);
   
   indices.push_back(0);
   indices.push_back(1);
   indices.push_back(7);
   
   indices.push_back(0);
   indices.push_back(7);
   indices.push_back(10);
   
   indices.push_back(0);
   indices.push_back(10);
   indices.push_back(11);
   
   // 5 adjacent faces
   indices.push_back(1);
   indices.push_back(5);
   indices.push_back(9);
   
   indices.push_back(5);
   indices.push_back(11);
   indices.push_back(4);
   
   indices.push_back(11);
   indices.push_back(10);
   indices.push_back(2);
   
   indices.push_back(10);
   indices.push_back(7);
   indices.push_back(6);
   
   indices.push_back(7);
   indices.push_back(1);
   indices.push_back(8);
   
   // 5 faces around point 3
   indices.push_back(3);
   indices.push_back(9);
   indices.push_back(4);
   
   indices.push_back(3);
   indices.push_back(4);
   indices.push_back(2);
   
   indices.push_back(3);
   indices.push_back(2);
   indices.push_back(6);
   
   indices.push_back(3);
   indices.push_back(6);
   indices.push_back(8);
   
   indices.push_back(3);
   indices.push_back(8);
   indices.push_back(9);
   
   // 5 adjacent faces
   
   indices.push_back(4);
   indices.push_back(9);
   indices.push_back(5);
   
   indices.push_back(2);
   indices.push_back(4);
   indices.push_back(11);
   
   indices.push_back(6);
   indices.push_back(2);
   indices.push_back(10);
   
   indices.push_back(8);
   indices.push_back(6);
   indices.push_back(7);
   
   indices.push_back(9);
   indices.push_back(8);
   indices.push_back(1);
   
   // refine triangles
   for (int j = 0; j < recursionLevel; j++)
   {
      std::vector<unsigned int> newIndices;
      std::cout << "Refining: " << j << std::endl;
      for(int i=0; (i+2)<indices.size();i+=3)
      {
         // replace triangle by 4 triangles
         unsigned int a = getMiddlePoint(vertices, indices[i], indices[i+1]);
         unsigned int b = getMiddlePoint(vertices,indices[i+1], indices[i+2]);
         unsigned int c = getMiddlePoint(vertices,indices[i+2], indices[i]);
         
         newIndices.push_back(indices[i]);
         newIndices.push_back(a);
         newIndices.push_back(c);
         
         newIndices.push_back(indices[i+1]);
         newIndices.push_back(b);
         newIndices.push_back(a);
         
         newIndices.push_back(indices[i+2]);
         newIndices.push_back(c);
         newIndices.push_back(b);
         
         newIndices.push_back(a);
         newIndices.push_back(b);
         newIndices.push_back(c);
      }
      
      indices = newIndices;
   }
   
   
   std::vector<glm::vec3> colors(vertices.size(),glm::vec3(0.5,0.2,0.5));
   Model *m = new Model(vertices, vertices,  colors, indices);
   middlePointIndexCache.clear();
   return m;
};

unsigned int Primative::getMiddlePoint(std::vector<glm::vec3> &verts, int p1, int p2){
      // first check if we have it already
      bool firstIsSmaller = p1 < p2;
      unsigned int smallerIndex = firstIsSmaller ? p1 : p2;
      unsigned int greaterIndex = firstIsSmaller ? p2 : p1;
      unsigned int key = (smallerIndex << 16) + greaterIndex;
      
      if (middlePointIndexCache.find(key) != middlePointIndexCache.end())
      {
         return (middlePointIndexCache.find(key))->second;
      }
      
      // not in cache, calculate it
      glm::vec3 point1 = verts[p1];
      glm::vec3 point2 = verts[p2];
      glm::vec3 middle = glm::vec3((point1.x + point2.x) / 2.0,
                                   (point1.y + point2.y) / 2.0,
                                   (point1.z + point2.z) / 2.0);
   
      addVertex(verts, middle);

      // store it, return index
      middlePointIndexCache[key] = (unsigned int)verts.size()-1;
      return (unsigned int)verts.size()-1;
};

//make sure the point is equidistant from the center of the sphere
void Primative::addVertex(std::vector<glm::vec3> &verts, glm::vec3 vertex){
   float length = sqrtf(vertex.x * vertex.x + vertex.y * vertex.y + vertex.z * vertex.z);
   verts.push_back(glm::vec3(vertex.x/length, vertex.y/length, vertex.z/length));
}



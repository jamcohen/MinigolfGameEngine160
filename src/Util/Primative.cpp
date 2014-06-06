//
//  Primative.cpp
//  MiniGolfXCode
//
//  Created by Jake Cohen on 5/6/14.
//  Copyright (c) 2014 Orlando Salvatore. All rights reserved.
//

#include "Primative.h"

std::map<unsigned int, unsigned int> Primative::middlePointIndexCache{};

Model* Primative::getCube(glm::vec3 color){
   std::vector<unsigned int> indices;
   std::vector<glm::vec3> verts;
   std::vector<glm::vec3> normals;
   std::vector<glm::vec3> colors;
   std::vector<glm::vec4> baseVerts;
   ///front face
   baseVerts.push_back(glm::vec4( 0.5f,  0.5f,  0.5f, 1));
   baseVerts.push_back(glm::vec4(-0.5f,  0.5f,  0.5f, 1));
   baseVerts.push_back(glm::vec4(-0.5f, -0.5f,  0.5f, 1));
   baseVerts.push_back(glm::vec4( 0.5f, -0.5f,  0.5f, 1));
   glm::vec4 baseNormal(0,0,1,1);
   glm::vec3 baseColor = color;
   
   glm::mat4 rotation;
   for(int i=0;i<4;++i){
      rotation = glm::rotate(glm::mat4(), 90.0f*i, glm::vec3(0,1,0));
      
      for(int i=0;i<4;++i){
         verts.push_back(glm::vec3(rotation * baseVerts[i]));
         normals.push_back(glm::vec3(rotation * baseNormal));
         colors.push_back(baseColor);
      }
   }
   
   rotation = glm::rotate(glm::mat4(), 90.0f, glm::vec3(1,0,0));
   for(int i=0;i<4;++i){
      verts.push_back(glm::vec3(rotation * baseVerts[i]));
      normals.push_back(glm::vec3(rotation * baseNormal));
      colors.push_back(baseColor);
   }
   
   rotation = glm::rotate(glm::mat4(), -90.0f, glm::vec3(1,0,0));
   for(int i=0;i<4;++i){
      verts.push_back(glm::vec3(rotation * baseVerts[i]));
      normals.push_back(glm::vec3(rotation * baseNormal));
      colors.push_back(baseColor);
   }
   
   for(int i=0;i<6;i++){
      int offset = i*4;
      indices.push_back(2+offset);
      indices.push_back(3+offset);
      indices.push_back(0+offset);
      indices.push_back(2+offset);
      indices.push_back(0+offset);
      indices.push_back(1+offset);
   }
   
   Model* m = new Model(verts, normals, colors, indices);
   return m;
}

Model* Primative::getBox(glm::vec3 p1, glm::vec3 p2, float width, float height){
    std::vector<unsigned int> indices;
    std::vector<glm::vec3> verts;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec3> colors;
    //generate 8 points
    std::vector<glm::vec3> basePoints{};
    std::vector<glm::vec3> baseNormals{};
    basePoints.push_back(glm::vec3(p1));
    basePoints.push_back(glm::vec3(p2));
    //extrude up
    basePoints.push_back(glm::vec3(p2+glm::vec3(0,height,0)));
    basePoints.push_back(glm::vec3(p1+glm::vec3(0,height,0)));
    glm::vec3 dir = p1-p2;
    glm::vec3 perp = glm::cross(glm::vec3(0,1,0), dir);
    perp = glm::normalize(perp);
    //extrude out
    for(int i=0;i<4;++i){
        glm::vec3 vert = basePoints[i];
        basePoints.push_back(vert+perp*width);
    }
    glm::vec3 normal;
    
    //bottom face
    verts.push_back(basePoints[0]);
    verts.push_back(basePoints[1]);
    verts.push_back(basePoints[5]);
    verts.push_back(basePoints[4]);
    normal = getNormal(basePoints[0], basePoints[1], basePoints[5]);
    baseNormals.push_back(normal);
    
    //front face
    verts.push_back(basePoints[3]);
    verts.push_back(basePoints[2]);
    verts.push_back(basePoints[1]);
    verts.push_back(basePoints[0]);
    normal = getNormal(basePoints[3], basePoints[2], basePoints[1]);
    baseNormals.push_back(normal);
    
    //top face
    verts.push_back(basePoints[7]);
    verts.push_back(basePoints[6]);
    verts.push_back(basePoints[2]);
    verts.push_back(basePoints[3]);
    normal = getNormal(basePoints[7], basePoints[6], basePoints[2]);
    baseNormals.push_back(normal);
    
    //back face
    verts.push_back(basePoints[4]);
    verts.push_back(basePoints[5]);
    verts.push_back(basePoints[6]);
    verts.push_back(basePoints[7]);
    normal = getNormal(basePoints[4], basePoints[5], basePoints[6]);
    baseNormals.push_back(normal);
    
    //right face
    verts.push_back(basePoints[2]);
    verts.push_back(basePoints[6]);
    verts.push_back(basePoints[5]);
    verts.push_back(basePoints[1]);
    normal = getNormal(basePoints[2], basePoints[6], basePoints[5]);
    baseNormals.push_back(normal);
    
    //left face
    verts.push_back(basePoints[7]);
    verts.push_back(basePoints[3]);
    verts.push_back(basePoints[0]);
    verts.push_back(basePoints[4]);
    normal = getNormal(basePoints[7], basePoints[3], basePoints[0]);
    baseNormals.push_back(normal);
    
    
    for(int i=0;i<6;i++){
        int offset = i*4;
        indices.push_back(2+offset);
        indices.push_back(3+offset);
        indices.push_back(0+offset);
        
        indices.push_back(2+offset);
        indices.push_back(0+offset);
        indices.push_back(1+offset);
        for(int j=0;j<4;++j){
            normals.push_back(baseNormals[i]);
            std::cout << "IDENTIFYING CLUSTER: " << baseNormals[i].x << " " << baseNormals[i].y << " " << baseNormals[i].z << std::endl;
            colors.push_back(glm::vec3(0.5,0.5,0.1));
        }
    }
    
    Model* m = new Model(verts, normals, colors, indices);
    return m;
    
}

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
   
   
   std::vector<glm::vec3> colors(vertices.size(),color);
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

glm::vec3 Primative::getNormal(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3){
    glm::vec3 edge1 = p2-p1;
    glm::vec3 edge2 = p3-p1;
    
    //edge1 = glm::vec3(1,0,0);
    //edge2 = glm::vec3(0,0,1);
    
    //edge2, edge1
    glm::vec3 normal = glm::cross(edge1,edge2);
    normal = glm::normalize(normal);
    std::cout << "WHAT IS THIS: " << normal.x << " " << normal.y << " " << normal.z << std::endl;

    return glm::normalize(normal);
}


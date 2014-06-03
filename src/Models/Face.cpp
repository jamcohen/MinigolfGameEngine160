//
//  Face.cpp
//  MiniGolfXCode
//
//  Created by Orlando Salvatore on 5/6/14.
//  Copyright (c) 2014 Orlando Salvatore. All rights reserved.
//

#include "Face.h"

Face::Face(glm::vec3 normal,std::vector<glm::vec3> verticies,glm::vec3 *colors, Model* m) : _normal(normal), _verticies(verticies), _colors(colors), _m(m)
{
    
}

void Face::print()
{
    std::cout << "Normal: " << _normal.x << "," << _normal.y << "," << _normal.z << std::endl;
    std::cout << "Verticies: ";
    for(int i=0 ; i < 3; i++)
    {
        std::cout << "v" << i << ": " << _verticies[i].x << "," << _verticies[i].y << "," << _verticies[i].z << std::endl;
    }
}

void Face::print(GameObject* obj){
   glm::vec3 normal(getWorldNormal(obj));
   std::cout << "Normal: " << normal.x << "," << normal.y << "," << normal.z << std::endl;
   std::cout << "Verticies: ";
   for(int i=0 ; i < 3; i++)
   {
      glm::vec3 verts(getWorldVertices(obj)[i]);
      std::cout << "v" << i << ": " << verts.x << "," << verts.y << "," << verts.z << std::endl;
   }
}

glm::vec3 Face::getWorldNormal(GameObject* obj){
   if(glm::length(_worldNormal) != 0) return _worldNormal;
   
   glm::quat rotate(obj->getRotation());
   glm::mat4 R = glm::mat4_cast(rotate);
   //glm::mat4 R = glm::rotate(glm::mat4(), rotate.z, glm::vec3(0,0,1));//glm::orientate4(rotate);
   //R = glm::rotate(R, rotate.y, glm::vec3(0,1,0));
   //R = glm::rotate(R, rotate.x, glm::vec3(1,0,0));
   glm::mat4 modelMatrix = R;
   glm::vec4 temp(_normal.x, _normal.y, _normal.z, 1);
   temp = modelMatrix*temp;
   _worldNormal = glm::vec3(temp.x, temp.y, temp.z);
   Gizmo::instance().addDebugRay(obj->getPosition(), obj->getPosition()+_worldNormal*0.2f);
   return _worldNormal;
}

std::vector<glm::vec3> Face::getWorldVertices(GameObject* obj){
   if(_worldVerticies.size() > 0) return _worldVerticies;
   
   //If worldVertices haven't been cached
   //Note this is a pretty hacky way of getting world vertices
   //ideally the GameObject should be passed into the face's constructor
   std::vector<glm::vec3> worldVertices(_verticies);
   glm::vec3 pos(obj->getPosition());
   glm::quat rotate(obj->getRotation());
   glm::vec3 scale(obj->getScale());
   glm::mat4 T = glm::translate(glm::mat4(), pos);
   glm::mat4 R = glm::mat4_cast(rotate);//glm::rotate(glm::mat4(), rotate.z, glm::vec3(0,0,1));//glm::orientate4(rotate);
   glm::mat4 S = glm::scale(glm::mat4(), scale);
   glm::mat4 modelMatrix = T*R*S;
   for(glm::vec3 v : worldVertices){
      glm::vec4 v4(v.x, v.y, v.z, 1);
      v4 = modelMatrix*v4;
      _worldVerticies.push_back(glm::vec3(v4.x,v4.y,v4.z));
   }
   return _worldVerticies;
   
}
//
//  Cup.h
//  MiniGolfXCode
//
//  Created by Orlando Salvatore on 4/19/14.
//  Copyright (c) 2014 Orlando Salvatore. All rights reserved.
//

#ifndef __MiniGolfXCode__Cup__
#define __MiniGolfXCode__Cup__

#include <iostream>
#include "glm.hpp"
#include "GameObject.h"
#include "Model.h"
#include "DiffuseSpecularMaterial.h"
#include "Primative.h"

class Cup : public GameObject
{
public:
   Cup(int,glm::vec3);
   
private:
   int _index;
   glm::vec3 _color;
};

#endif /* defined(__MiniGolfXCode__Cup__) */

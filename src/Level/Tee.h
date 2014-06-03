//
//  Tee.h
//  MiniGolfXCode
//
//  Created by Orlando Salvatore on 4/19/14.
//  Copyright (c) 2014 Orlando Salvatore. All rights reserved.
//

#ifndef __MiniGolfXCode__Tee__
#define __MiniGolfXCode__Tee__

#include <iostream>
#include "glm.hpp"
#include "GameObject.h"
#include "Model.h"
#include "DiffuseSpecularMaterial.h"
#include "Primative.h"

class Tee : public GameObject
{
public:
    Tee(int,glm::vec3);
    
private:
    int _index;
    glm::vec3 _color;
};

#endif /* defined(__MiniGolfXCode__Tee__) */

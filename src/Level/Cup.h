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

class Cup : GameObject
{
public:
    Cup(int,glm::vec3,Model*);
    
private:
    int _index;
};

#endif /* defined(__MiniGolfXCode__Cup__) */

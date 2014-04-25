//
//  Cylinder.h
//  MiniGolfXCode
//
//  Created by Orlando Salvatore on 4/24/14.
//  Copyright (c) 2014 Orlando Salvatore. All rights reserved.
//

#ifndef __MiniGolfXCode__Cylinder__
#define __MiniGolfXCode__Cylinder__

#include <iostream>
#include <cmath>
#include <vector>
#include "Model.h"
#include "ModelUtil.h"

class Cylinder : public Model
{
public:
    Cylinder(int);
    ~Cylinder();
    
private:
    int _sideCount;
};

#endif /* defined(__MiniGolfXCode__Cylinder__) */

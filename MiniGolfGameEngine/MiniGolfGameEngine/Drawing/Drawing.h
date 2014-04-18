//
//  Drawing.h
//  MiniGolfGameEngine
//
//  Created by Orlando Salvatore on 4/17/14.
//  Copyright (c) 2014 Orlando Salvatore. All rights reserved.
//

#ifndef __MiniGolfGameEngine__Drawing__
#define __MiniGolfGameEngine__Drawing__

#include <iostream>
#include "GameObject.h"

class Drawing
{
public:
    void update();
    void addToDrawingList(GameObject *);
};

#endif /* defined(__MiniGolfGameEngine__Drawing__) */

//
//  HUD.h
//  MiniGolfXCode
//
//  Created by Orlando Salvatore on 6/1/14.
//  Copyright (c) 2014 Orlando Salvatore. All rights reserved.
//

#ifndef __MiniGolfXCode__HUD__
#define __MiniGolfXCode__HUD__

#include <iostream>
#include <list>
#include "HUDElement.h"

class HUD
{
public:
    static HUD& instance()
    {
        static HUD INSTANCE;
        return INSTANCE;
    }
    HUD();
    void draw();
    void addHUDElement(HUDElement*);
    void removeHUDElement(HUDElement*);
    
private:
    std::list<HUDElement*> _hudElements;

};

#endif /* defined(__MiniGolfXCode__HUD__) */

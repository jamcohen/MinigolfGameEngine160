//
//  HUD.cpp
//  MiniGolfXCode
//
//  Created by Orlando Salvatore on 6/1/14.
//  Copyright (c) 2014 Orlando Salvatore. All rights reserved.
//

#include "HUD.h"

HUD::HUD()
{
    
}

void HUD::draw()
{
    for (HUDElement *h : _hudElements)
    {
        if(h->getEnabled())
        {
            h->draw();
        }
    }
}

void HUD::addHUDElement(HUDElement *h)
{
    _hudElements.push_back(h);
}

void HUD::removeHUDElement(HUDElement *h)
{
    _hudElements.remove(h);
}
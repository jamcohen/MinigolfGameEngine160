//
//  InputManager.cpp
//  MiniGolfXCode
//
//  Created by Orlando Salvatore on 4/18/14.
//  Copyright (c) 2014 Orlando Salvatore. All rights reserved.
//

#include "InputManager.h"
const float InputManager::SPEED = 5.0f;

InputManager::InputManager()
{ }

bool InputManager::handleKey(SDL_Keycode key)
{
    switch(key)
    {
        case SDLK_ESCAPE:
            std::cout << "Quitting program.../n";
            return false;
            break;
            
        case SDLK_w:
            moveForward();
            break;
            
        case SDLK_s:
            moveBackward();
            break;
            
        default:
            break;
    }
    return true;
}

void InputManager::moveForward()
{
    Camera *c = SceneManager::instance().getCurrentCamera();
    glm::vec3 direction = c->getTarget() - c->getPosition();
    glm::normalize(direction);
    direction *= SPEED;
    c->setPosition(c->getPosition() + direction);
    c->setTarget(c->getTarget() + direction);
}

void InputManager::moveBackward()
{
    Camera *c = SceneManager::instance().getCurrentCamera();
    glm::vec3 direction = c->getTarget() - c->getPosition();
    glm::normalize(direction);
    direction *= SPEED * -1;
    c->setPosition(c->getPosition() + direction);
    c->setTarget(c->getTarget() + direction);
}
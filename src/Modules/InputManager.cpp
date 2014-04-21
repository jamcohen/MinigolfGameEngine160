//
//  InputManager.cpp
//  MiniGolfXCode
//
//  Created by Orlando Salvatore on 4/18/14.
//  Copyright (c) 2014 Orlando Salvatore. All rights reserved.
//

#include "InputManager.h"
const float InputManager::SPEED = 0.1f;

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
            
        case SDLK_d:
            moveRight();
            break;
            
        case SDLK_a:
            moveLeft();
            break;
            
        default:
            break;
    }
    return true;
}

/*
 * Moves the camera forward towards it target
 */
void InputManager::moveForward()
{
    Camera *c = SceneManager::instance().getCurrentCamera();
    glm::vec3 direction = c->getTarget() - c->getPosition();
    glm::normalize(direction);
    direction *= SPEED;
    c->setPosition(c->getPosition() + direction);
    c->setTarget(c->getTarget() + direction);
}

/*
 * Moves the camera backward towards it target
 */
void InputManager::moveBackward()
{
    Camera *c = SceneManager::instance().getCurrentCamera();
    glm::vec3 direction = c->getTarget() - c->getPosition();
    glm::normalize(direction);
    direction *= SPEED * -1;
    c->setPosition(c->getPosition() + direction);
    c->setTarget(c->getTarget() + direction);
}

/*
 * Moves the camera right towards it target
 */
void InputManager::moveRight()
{
    Camera *c = SceneManager::instance().getCurrentCamera();
    glm::vec3 tempVec = c->getTarget();
    tempVec = tempVec - c->getPosition();
    tempVec.z *= .5f;
    glm::vec3 direction = c->getTarget() - c->getPosition();
    glm::vec3 rightVec = glm::cross(direction, tempVec);
    glm::normalize(rightVec);
    
    rightVec *= SPEED * -1;
    c->setPosition(c->getPosition() + rightVec);
    c->setTarget(c->getTarget() + rightVec);
}

/*
 * Moves the camera left towards it target
 */
void InputManager::moveLeft()
{
    Camera *c = SceneManager::instance().getCurrentCamera();
    glm::vec3 tempVec = c->getTarget();
    tempVec = tempVec - c->getPosition();
    tempVec.z *= .5f;
    glm::vec3 direction = c->getTarget() - c->getPosition();
    glm::vec3 rightVec = glm::cross(direction, tempVec);
    glm::normalize(rightVec);
    
    rightVec *= SPEED;
    c->setPosition(c->getPosition() + rightVec);
    c->setTarget(c->getTarget() + rightVec);
}
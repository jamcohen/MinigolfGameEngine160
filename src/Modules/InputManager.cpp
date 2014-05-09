//
//  InputManager.cpp
//  MiniGolfXCode
//
//  Created by Orlando Salvatore on 4/18/14.
//  Copyright (c) 2014 Orlando Salvatore. All rights reserved.
//

#include "InputManager.h"
const float InputManager::MOVEMENT_SPEED = 0.1f;
const float InputManager::MOUSE_DAMPENING = 15.0f;


InputManager::InputManager() : _firstTimeGettingMouse(true), _previousMouseCords(0,0)
{ }

bool InputManager::handleKey(SDL_Keycode key)
{
    Ball *b = SceneManager::instance().getBall();
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
            
        case SDLK_UP:
            //rotatePitch(5.0f);
            b->applyForce(glm::vec3(0,0,4));
            break;
            
        case SDLK_DOWN:
            //rotatePitch(-5.0f);
            b->applyForce(glm::vec3(0,0,-4));
            break;
            
        case SDLK_RIGHT:
            //rotateYaw(5.0f);
            b->applyForce(glm::vec3(4,0,0));
            break;
            
        case SDLK_LEFT:
            //rotateYaw(-5.0f);
            b->applyForce(glm::vec3(-4,0,0));
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
    direction *= MOVEMENT_SPEED;
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
    direction *= MOVEMENT_SPEED * -1;
    c->setPosition(c->getPosition() + direction);
    c->setTarget(c->getTarget() + direction);
}

/*
 * Moves the camera right towards it target
 */
void InputManager::moveRight()
{
    Camera *c = SceneManager::instance().getCurrentCamera();
    glm::vec3 tempVec(0,1,0);
    glm::vec3 direction = c->getTarget() - c->getPosition();
    glm::vec3 rightVec = glm::cross(direction, tempVec);
    glm::normalize(rightVec);
    
    rightVec *= MOVEMENT_SPEED;
    c->setPosition(c->getPosition() + rightVec);
    c->setTarget(c->getTarget() + rightVec);
}

/*
 * Moves the camera left towards it target
 */
void InputManager::moveLeft()
{
    Camera *c = SceneManager::instance().getCurrentCamera();
    glm::vec3 tempVec(0,1,0);
    glm::vec3 direction = c->getTarget() - c->getPosition();
    glm::vec3 rightVec = glm::cross(direction, tempVec);
    glm::normalize(rightVec);
    
    rightVec *= MOVEMENT_SPEED * -1;
    c->setPosition(c->getPosition() + rightVec);
    c->setTarget(c->getTarget() + rightVec);
}

void InputManager::rotatePitch(float change)
{
    Camera *c = SceneManager::instance().getCurrentCamera();
    c->rotatePitch(change);
}

void InputManager::rotateYaw(float change)
{
    Camera *c = SceneManager::instance().getCurrentCamera();
    c->rotateYaw(change);
}

void InputManager::handleMouse(SDL_Event *event)
{
    //Check if the mouse has left the window
    if(event->type == SDL_WINDOWEVENT)
    {
        if(event->window.event == SDL_WINDOWEVENT_LEAVE)
        {
            _firstTimeGettingMouse = true;
        }
    }
    if(event->type != SDL_MOUSEMOTION)
    {
        return;
    }
    SDL_MouseMotionEvent motion = event->motion;
    if(_firstTimeGettingMouse)
    {
        _firstTimeGettingMouse = false;
        _previousMouseCords.x = motion.x;
        _previousMouseCords.y = motion.y;
    }
    float xVelocity = motion.x - _previousMouseCords.x;
    float yVelocity = _previousMouseCords.y - motion.y;
    _previousMouseCords.x = motion.x;
    _previousMouseCords.y = motion.y;
        
    Camera *c = SceneManager::instance().getCurrentCamera();
    c->rotateYaw(xVelocity/MOUSE_DAMPENING);
    c->rotatePitch(yVelocity/MOUSE_DAMPENING);
    
}
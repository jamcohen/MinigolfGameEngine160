#include <iostream>
#include <SDL2/SDL.h>
#include <OpenGL/gl3.h>
#include "Drawing.h"
#include "FileIO.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "RayCast.h"
#include "BallCamera.h"
#include "Cylinder.h"

#ifndef TIME_STEP
#define TIME_STEP 1000 / 60
#endif

/*
 * Starts everything
 */
int main(int argc, char * arg[])
{
    // init SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout << "ERROR SDL_Init" << std::endl;
        
        return -1;
    }
        
    SDL_LogSetAllPriority(SDL_LOG_PRIORITY_VERBOSE);
    
    
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    
    Camera *c = new BallCamera();
    c->setPosition(0, 2, 0);
    c->lockPitch(70);
        
    // create a window
    SDL_Window *window = SDL_CreateWindow(
                                          "SDL 2 window",             // window title
                                          SDL_WINDOWPOS_CENTERED,     // x position, centered
                                          SDL_WINDOWPOS_CENTERED,     // y position, centered
                                          640,                        // width, in pixels
                                          480,                        // height, in pixels
                                          SDL_WINDOW_OPENGL           // flags
                                          );

    
    //SDL_Renderer *renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);
    
    bool running = true;
    SDL_Event mainEvent;
    auto gl = SDL_GL_CreateContext(window);
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    Drawing *graphics = new Drawing();

    //Print out arguements
    std::cout << "TEST: " << argc << std::endl;
    for(auto i = 0; i < argc; i++)
    {
        std::cout << i << " : " << arg[i] << std::endl;
    }
    
    FileIO fileIO;
    std::string s(arg[1]);
    fileIO.parseTileMap(s);
    
    std::cout << "version: " << glGetString(GL_VERSION) << ", shader: "<< glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    
    GameObject *g = new GameObject(c->getPosition());
    
    //For time
    typedef std::chrono::duration<int,std::nano> nanosecs_t ;
    
    //TO-DO: We are going to have to work on setting the update based on the drawing FPS
    while(running)
    {
        std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
        
        //g->setPosition(c->getPosition());
        //RayCast::rayCast(g, c->getForwardDirectionVector());
        while(SDL_PollEvent(&mainEvent) != 0)
        {
            if(mainEvent.type == SDL_QUIT)
            {
                std::cout << "See ya later!/n";
                running = false;
                break;
            }
            InputManager::instance().handleMouse(&mainEvent);
            
            if(mainEvent.type == SDL_KEYDOWN)
            {
                running = InputManager::instance().handleKey(mainEvent.key.keysym.sym);
            }
        }
        graphics->update();
        SceneManager::instance().update();
        SDL_GL_SwapWindow(window);
        
        //Time update
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        nanosecs_t duration( std::chrono::duration_cast<nanosecs_t>(end-start) ) ;
        float timeDifference = TIME_STEP*1000000 - duration.count();
        //std::cout << timeDifference << std::endl;
        if (timeDifference >= 0)
        {
            std::this_thread::sleep_for(std::chrono::nanoseconds((int)timeDifference));
            //Physics::updatePhysics(duration.count()/1000000.0f);
            Physics::updatePhysics(TIME_STEP);
        }
        else
        {
            Physics::updatePhysics(duration.count()/1000000.0f);
        }
        
    }
    SDL_GL_DeleteContext(gl);
    
    SceneManager::instance().closeScene();
    //Clean up
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}

#include <iostream>
#include <SDL2/SDL.h>
#include <OpenGL/gl3.h>
#include "Drawing.h"
#include "FileIO.h"
#include <ctime>
#include "InputManager.h"
#include "RayCast.h"
#include "Camera.h"
#include "Cylinder.h"

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
    
    Camera *c = new Camera();
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
    
    //TO-DO: We are going to have to work on setting the update based on the drawing FPS
    while(running)
    {
        g->setPosition(c->getPosition());
        RayCast::rayCast(g, c->getForwardDirectionVector());
        //time_t timer;
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
        SDL_GL_SwapWindow(window);
    }
    SDL_GL_DeleteContext(gl);
    
    SceneManager::instance().closeScene();
    //Clean up
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}

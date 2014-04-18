#include <iostream>
#include <SDL2/SDL.h>
#include <OpenGL/gl3.h>
#include <ctime>

class Graphics
{
public:
    
    void update()
    {
        glClearColor(rand() % 255 / 255.0f, rand() % 255 / 255.0f, rand() % 255 / 255.0f, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    }
};

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
    
    
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    
    
    // create a window
    SDL_Window *window = SDL_CreateWindow(
                                          "SDL 2 window",             // window title
                                          SDL_WINDOWPOS_CENTERED,     // x position, centered
                                          SDL_WINDOWPOS_CENTERED,     // y position, centered
                                          640,                        // width, in pixels
                                          480,                        // height, in pixels
                                          SDL_WINDOW_OPENGL           // flags
                                          );
    
    SDL_Renderer *renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);
    
    bool running = true;
    SDL_Event mainEvent;
    auto gl = SDL_GL_CreateContext(window);
    Graphics *graphics = new Graphics();

    //TO-DO: We are going to have to work on setting the update based on the drawing FPS
    while(running)
    {
        time_t timer;
        
        while(SDL_PollEvent(&mainEvent) != 0)
        {
            if(mainEvent.type == SDL_QUIT)
            {
                std::cout << "See ya later!/n";
                running = false;
                break;
            }
            
            if(mainEvent.type == SDL_KEYDOWN)
            {
                switch(mainEvent.key.keysym.sym)
                {
                    case SDLK_q:
                        std::cout << "Quitting program.../n";
                        running = false;
                        break;
                        
                    default:
                        std::cout << "Wrong key!\n";
                        break;
                }
            }
        }
        graphics->update();
        SDL_GL_SwapWindow(window);
    }
    
    SDL_GL_DeleteContext(gl);
    
    //Clean up
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}

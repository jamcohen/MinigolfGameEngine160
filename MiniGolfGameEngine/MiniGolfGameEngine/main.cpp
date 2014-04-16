#include <iostream>
#include <SDL2/SDL.h>



int main(int argc, char * arg[])

{
    // init SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout << "ERROR SDL_Init" << std::endl;
        
        return -1;
    }
    
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
    
    while(running)
    {
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
    }
    
    // wait 5 secs
    SDL_Delay(5000);
    
    
    // clean up
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}

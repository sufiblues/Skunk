#pragma once

#include <SDL.h>

namespace sdlcontext{
    extern SDL_Window* Window; 
    extern SDL_Renderer* Renderer; 

    /* Width and height of the window */ 
    extern uint WIDTH;
    extern uint HEIGHT;

    /* Initialize SDL */ 
    bool init(uint width, uint height);

    /* delete window,renderer and close out the SDL context */
    void close();

}
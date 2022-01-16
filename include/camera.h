#pragma once 

#include "sdlcontext.h"
#include "shapes.h"
#include "utils.h"
#include <SDL.h>

/* Place 2d objects onto the canvas */ 
struct Camera{
    /* Width and height for canvas in px */ 
    uint WIDTH;
    uint HEIGHT;
    /* Camera variables */
    /** pos of camera on canvas (0,0) is the top left corner**/
    glm::vec2 offset;
    /** pos of camera in world **/
    glm::vec2 pos;
    /** how much the camera is zooming into the world **/
    uint zoom;
    Camera(uint width, uint height);

    //TODO: I need a layers function 
    
    /* Rendering Functions */
    void renderShape(Triangle t, SDL_Color color);
    void renderGrid(uint rows, uint columsn);

};
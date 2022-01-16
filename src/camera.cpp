#include "camera.h"

Camera::Camera(uint width, uint height){
    WIDTH = width;
    HEIGHT = height; 
}

void Camera::renderShape(Triangle t, SDL_Color color ){

    SDL_Vertex vert[t.vertices.size()];
    for(int i = 0; i < t.vertices.size(); i++){
        vert[i].position.x = (int) t.vertices[i][0];
        vert[i].position.y = (int) t.vertices[i][1];
        vert[i].color = color;
    }

    SDL_RenderGeometry(sdlcontext::Renderer, NULL, vert, 3, NULL, 0);
}

void Camera::renderGrid(uint rows, uint columns){
    SDL_SetRenderDrawColor(sdlcontext::Renderer, white.r, white.g, white.b, white.a );

    float scale = (WIDTH * 1.0f)/columns;
    for (int i = 0; i < columns; i++){
        SDL_RenderDrawLine(sdlcontext::Renderer, (int)i * scale, 0, i * WIDTH/columns, HEIGHT);
    }
}
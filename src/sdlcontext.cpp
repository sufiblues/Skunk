#include "sdlcontext.h"


namespace sdlcontext{
    SDL_Window* Window; 
    SDL_Renderer* Renderer; 

    uint WIDTH;
    uint HEIGHT;
    
    bool init(uint width, uint height){
        WIDTH = width;
        HEIGHT = height; 
        if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0) {
            SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
            return false;
        }
        //NOTE: High dpi might cause issues in macos 
        Window = SDL_CreateWindow("Da Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
        if (Window == NULL) {
            printf("Window could not be initialized! Error: %s\n", SDL_GetError());
            return false;
        }
        Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);
        if (Renderer == NULL) {
            printf("Renderer could not be initialized! Error: %s\n", SDL_GetError());
            return false;
        }
        //For high dpi mode and 
        int rw = 0, rh = 0;
        SDL_GetRendererOutputSize(Renderer, &rw, &rh);
        if(rw != WIDTH || rh != HEIGHT) {
            printf("HIGH DPI on mac or IOS\n");
            float widthScale = (float)rw / (float) WIDTH;
            float heightScale = (float)rh / (float) HEIGHT;

            if(widthScale != heightScale) {
                fprintf(stderr, "WARNING: width scale != height scale\n");
            }

            SDL_RenderSetScale(Renderer, widthScale, heightScale);
        }

        printf("SDL Context created successfully.\n");

        return true;
    }

    void close(){
        SDL_DestroyWindow(Window);
        SDL_DestroyRenderer(Renderer);
        SDL_Quit();
        Window = NULL;
        Renderer = NULL;
        printf("Exiting SDL...\n");
    }
}
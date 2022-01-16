#include<iostream>
#include<algorithm>
#include "sdlcontext.h"
#include "shapes.h"
#include "../libs/glm/vec2.hpp"

typedef struct Controller {
	uint up = 0;
	uint down = 0;
	uint left = 0;
	uint right = 0;
	uint jump = 0;
	uint attack = 0;
	uint shield = 0;
  uint click = 0;
  uint touch = 0;
  uint restart = 0;
  uint F1 = 0;
  uint F2 = 0;
  SDL_Point mPosition = {0,0};
  bool quit = false;

} Controller;
SDL_Event event; 


void updateControllerInputState(Controller* input);

int main(){
    sdlcontext::init(720,720);

    Controller bro;
    //create several shapes 
    Quadrilateral shape1 = createRectangle(glm::vec2(100,720), 360, 30);
    Quadrilateral shape2 = createRectangle(glm::vec2(245,612), 120, 150);
    Triangle shape3 = createEquilateralTriangle(glm::vec2(500, 500), 50);
    Quadrilateral player = createRectangle(glm::vec2(720/2,720/2), 50, 50);
    Circle shape4 = {glm::vec2(360,360), 100};
 


    bool quit = false;
    while(!bro.quit){
      updateControllerInputState(&bro);
      
      int big_speed = 5;
      glm::vec2 shift = glm::vec2(0,0);
      if(bro.up >= 1){
        shift = glm::vec2(0,-big_speed);
      }
      if(bro.down >= 1){
        shift = glm::vec2(0,big_speed);
      }
      if(bro.left >= 1){
        shift = glm::vec2(-big_speed,0);
      }
      if(bro.right >= 1){
        shift = glm::vec2(big_speed,0);
      }
      
      polygonMove(&player,shift);

      SDL_SetRenderDrawColor(sdlcontext::Renderer, 0, 0, 0, 255);
      SDL_RenderClear(sdlcontext::Renderer);

      renderFillShape(shape1, green);
      renderFillShape(shape2, blue);
      renderFillShape(shape3, dark_brown);
      renderFillShape(shape4, pink);
      glm::vec2 mtv = MTV2(player, shape3);
      printf("MTV (%f,%f)\n", mtv[0], mtv[1]);
      polygonMove(&player,mtv);

      renderFillShape(player, red);



      SDL_RenderPresent(sdlcontext::Renderer);


    }

    sdlcontext::close();
    return 0;
}

 
void updateControllerInputState(Controller* input) {
    uint MAX_UINT16 = 60;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_QUIT:
      input->quit = true;
      break;
    case SDL_KEYDOWN:
      switch (event.key.keysym.sym) {
      case SDLK_UP:
        //std::cout << "up clicked\n";
        input->up = std::min(input->up + 1, MAX_UINT16);
        break;
      case SDLK_DOWN:
        input->down = std::min(input->down + 1, MAX_UINT16) ;
        break;
      case SDLK_LEFT:
        input->left = std::min(input->left + 1, MAX_UINT16);
        break;
      case SDLK_RIGHT:
        input->right = std::min(input->right + 1, MAX_UINT16);
        break;
      case SDLK_a:
        input->jump = std::min(input->jump + 1, MAX_UINT16);
        break;
      case SDLK_r:
        input->restart = std::min(input->restart + 1, MAX_UINT16);
        break;
      case SDLK_F1:
        input->F1 = std::min(input->F1 + 1, MAX_UINT16);
        break;
      case SDLK_F2:
        input->F2 = std::min(input->F2 + 1, MAX_UINT16);
      default:
        break;
      }
      break;
    case SDL_KEYUP:
      switch (event.key.keysym.sym) {
      case SDLK_UP:
        input->up = 0;
        break;
      case SDLK_DOWN:
        input->down = 0;
        break;
      case SDLK_LEFT:
        input->left = 0;
        break;
      case SDLK_RIGHT:
        input->right = 0;
        break;
      case SDLK_a:
        input->jump = 0;
        break;
      case SDLK_r:
        input->restart = 0;
        break;
      case SDLK_F1:
        input->F1 = 0;
        break;
      case SDLK_F2:
        input->F2 = 0;
        break;
      default:
        break;
      }
      break;
    case SDL_MOUSEMOTION:
      SDL_GetMouseState(&input->mPosition.x, &input->mPosition.y);
      break;
    case SDL_MOUSEBUTTONDOWN:
      input->click = 1;
      break;
    case SDL_MOUSEBUTTONUP:
      input->click = 0;
      break;
    default:
      break;
    }
  }
}

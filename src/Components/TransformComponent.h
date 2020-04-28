#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H
   
#include "../EntityManager.h"
   #include "../../lib/glm/glm.hpp"
   #include <SDL2/SDL.h>
   #include "../Game.h"
   
   class TransformComponent: public Component {
       public:
           glm::vec2 position;
           glm::vec2 velocity;
           int width;
           int height;
           int scale;
   
           TransformComponent(int PosX, int PosY, int VelX, int VelY, int w, int h, int s){
               position = glm::vec2(PosX, PosY);
               velocity = glm::vec2(VelX, VelY);
               width = w;
               height = h;
               scale = s;
           }
   
           void Initialize() override {
   
           }
   
           void Update(float deltaTime) override {
                position.x += velocity.x * deltaTime; 
                position.y += velocity.y * deltaTime; 
           }
   
           void Render() override {
               SDL_Rect  transformRectangle = {
                   (int) position.x,
                   (int) position.y,
                   width,
                   height
               };
               SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 0);
               SDL_RenderFillRect(Game::renderer, &transformRectangle);
           }
   };
   
   #endif


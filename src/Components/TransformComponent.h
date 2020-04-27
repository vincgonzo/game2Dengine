#ifndef TRANSFORMCOMPONENT_H
   #define TRANSFORMCOMPONENT_H
   
 >>#include "../EntityManager.h"
   #include "../../lib/glm/glm.hpp"
   #include <SDL2/SDL.h>
   #include "Game.h"
   
   class TransformComponent: public Component {
       public:
           glm::vec2 position;
           glm::vec2 velocity;
           int width;
           int height;
           int scale;
   
           TransformComponent(int posX, int PosY, int VelX, int VelY, int w, int h, int s){
               position = glm::vec2(posX, posY);
               velocity = glm::vec2(VelX, VelY);
               width = w;
               height = h;
               scale = s;
           }
   
           void Initialize() override {
   
           }
   
           void Update(float deltaTime) override {
   
           }
   
           void Render() override {
               SDL_Rect  trasnformRectangle = {
                   (int) position.x,
                   (int) position.y,
                   width,
                   height
               }
           }
   }
   
   #endif


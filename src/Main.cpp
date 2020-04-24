#include <iostream>
#include "./Constants.h"
#include "./Game.h"

int main(int argc, char *argv[]){
 Game *game = new Game();

 game->Initialize(WINDOW_WIDTH, WINDOW_HEIGHT);

 while(game->isRunning()){
	 game->ProcessInput();
	 game->Update();
	 game->Render();
 }

 game->Desttroy();

 return 0;
}

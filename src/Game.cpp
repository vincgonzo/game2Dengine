#include <iostream>
#include "./Constants.h"
#include "./Game.h"
#include "./AssetManager.h"
#include "./Components/TransformComponent.h"
#include "./Components/SpriteComponent.h"
#include "../lib/glm/glm.hpp"

EntityManager manager;
AssetManager* Game::assetManager = new AssetManager(&manager);
SDL_Renderer* Game::renderer;

Game::Game(){
	this->isRunning = false;
}

Game::~Game(){
}

bool Game::IsRunning() const {
	return this->isRunning;
}

glm::vec2 projectilePos = glm::vec2(0.0f, 0.0f);
glm::vec2 projectileVel = glm::vec2(20.0f, 20.0f);

void Game::Initialize(int width, int height) {
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
		std::cerr << "Error initializing SDL." << std::endl;
	       return;	
	}
	window = SDL_CreateWindow(
		NULL,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width,
		height,
		SDL_WINDOW_BORDERLESS
	);
	if(!window){
		std::cerr << "Error creating SDL window." << std::endl;
	       return;	
	}
	renderer = SDL_CreateRenderer(window, -1, 0);
	if(!renderer){
		std::cerr << "Error creating SDL renderer." << std::endl;
	       return;	
	}

    LoadLevel(0);
	
    isRunning = true;
	return;
}

void Game::LoadLevel(int levelNumber){
    // Start include new assets to assetManager
    std::string textureFilePath = "./assets/images/truck-down.png";
    //std::string textureFilePath = "./assets/images/tank-big-right.png";
    assetManager->AddTexture("tank-image", textureFilePath.c_str());

    // Start include entities and also component to them
    Entity& newEntity(manager.AddEntity("tank"));
    newEntity.AddComponent<TransformComponent>(0, 0, 20, 20, 32, 32, 1);
    newEntity.AddComponent<SpriteComponent>("tank-image");
}

void Game::ProcessInput(){
	SDL_Event event;
	SDL_PollEvent(&event);
	switch(event.type){
		case SDL_QUIT: {
			isRunning = false;
			break;
		}
		case SDL_KEYDOWN: {
			if(event.key.keysym.sym == SDLK_ESCAPE){
				isRunning = false;
			}		  
		}
		default: {
			break;
		}
	}
}

void Game::Update(){
	// Sleep the execution until we reach the target frame time in milliseconds
	int timeToWait = FRAME_TARGET_TIME - (SDL_GetTicks() - ticksLastFrame);

	// Only call delay if we are too fast too process this frame 
	if(timeToWait > 0 && timeToWait <= FRAME_TARGET_TIME){
		SDL_Delay(timeToWait);
	}	

	// Delta time is the difference in ticks from last frame converted to seconds
	float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;
	// Clamp deltaTime to a max value
	deltaTime = (deltaTime > 0.05f) ? 0.05f : deltaTime;

	// Sets the new ticks for the current frame to be used in the next pass	
	ticksLastFrame = SDL_GetTicks();

    manager.Update(deltaTime);
}

void Game::Render(){
	SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
	SDL_RenderClear(renderer);
    
    if(manager.HasNoEntities()){
        return;
    }
    manager.Render();

	SDL_RenderPresent(renderer);
}

void Game::Destroy(){
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}


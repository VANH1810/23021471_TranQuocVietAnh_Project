#pragma once

#include "game.hpp"

Map *mapAZ;
Player *player1;

SDL_Renderer* Game::renderer = nullptr;

Game::Game()
{}
Game::~Game()
{}

void Game::logErrorAndExit(const char* msg, const char* error)
{
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s: %s", msg, error);
    SDL_Quit();
}

void Game::initSDL(int xpos, int ypos)
{

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        {
            logErrorAndExit("SDL_Init", SDL_GetError());
            isRunning = false;
        }
    else
    {
        isRunning = true;
        int flags_screen = 0;
        if(fullscreen)  flags_screen = SDL_WINDOW_FULLSCREEN;
        else flags_screen = SDL_WINDOW_SHOWN;

        window = SDL_CreateWindow(WINDOW_TITLE, xpos, ypos, SCREEN_WIDTH, SCREEN_HEIGHT, flags_screen);
        if (window == nullptr) 
        {
            isRunning = false;
            logErrorAndExit("CreateWindow", SDL_GetError());
        }
    }
}

void Game::createRenderer()
{
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) 
    {
        logErrorAndExit("CreateRenderer", SDL_GetError());
        isRunning = false;
    }
    else isRunning = true;

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    
}
void Game::Render()
{
    SDL_RenderClear(renderer);
    mapAZ->render();
    player1->render();
    SDL_RenderPresent(renderer);
}


void Game::handleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type)
    {
        case SDL_QUIT:
            isRunning = false;
            break;
    // Keyboard events
        case SDL_escapse:
            isRunning = false;
            break;
        default:
            break;
    }

}

void Game::update()
{
    player1->update();
}

void Game::clean()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game::preload()
{
    initSDL(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    createRenderer();

    ifstream mapData("tankaz.json");
    mapAZ = new Map("tankaz", this->renderer, json::parse(mapData));
    player1 = new Player("assets/ground_shaker_asset/red/Bodies/body_tracks.png", this->renderer);
    
}

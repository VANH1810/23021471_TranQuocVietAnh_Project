#pragma once

#include "game.hpp"

Map *mapAZ;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

Manager manager;
auto& Player1(manager.addEntity());
auto& Player2(manager.addEntity());

HandleBulletsBetweenTwoSprites* HandleBullet = nullptr;

int Game::ScorePlayer1 = 0;
int Game::ScorePlayer2 = 0;

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
    gamestate = GameState::START_SCREEN;
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
    if(gamestate == GameState::START_SCREEN)
    {
        SDL_RenderCopy(this->renderer, this->startScreenTexture, nullptr, nullptr);
    }
    else if(gamestate == GameState::TUTORIAL)
    {
        SDL_RenderCopy(this->renderer, this->tutorialTexture, nullptr, nullptr);
    }
    else if(gamestate == GameState::SELECT_MODE)
    {
        SDL_RenderCopy(this->renderer, this->selectModeTexture, nullptr, nullptr);
    }
    else if(gamestate == GameState::SELECT_NUMBER_OF_PLAYERS)
    {
        SDL_RenderCopy(this->renderer, this->selectNumberOfPlayersTexture, nullptr, nullptr);
    }
    else
    {
        mapAZ->render();
        manager.draw();
    }
    
    SDL_RenderPresent(renderer);
}

void Game::ScoreRender()
{
}

void Game::handleEvents()
{
    SDL_PollEvent(&event);
    if(event.type == SDL_QUIT)
    {
        isRunning = false;
    }
    if(event.type == SDL_KEYDOWN)
    {
        switch(event.key.keysym.sym)
        {
            case SDLK_ESCAPE:
                isRunning = false;
                break;
            case SDLK_p:
                if(gamestate == GameState::PAUSED)
                    gamestate = GameState::PLAYING;
                else if(gamestate == GameState::PLAYING)
                    gamestate = GameState::PAUSED;
                break;
            case SDLK_SPACE:
                if(gamestate == GameState::START_SCREEN)
                    gamestate = GameState::TUTORIAL;
                else if(gamestate == GameState::TUTORIAL)
                    gamestate = GameState::SELECT_MODE;
                else if(gamestate == GameState::SELECT_MODE)
                    gamestate = GameState::SELECT_NUMBER_OF_PLAYERS;
                //else if(gamestate == GameState::SELECT_NUMBER_OF_PLAYERS)
                break;
            case SDLK_2:
                if(gamestate == GameState::SELECT_NUMBER_OF_PLAYERS)
                {
                    gamestate = GameState::PLAYING;
                    NumberOfPlayers = 2;
                }
            case SDLK_3: 
                if(gamestate == GameState::SELECT_NUMBER_OF_PLAYERS)
                {
                    gamestate = GameState::PLAYING;
                    NumberOfPlayers = 3;
                }
                break;
            default:
                break;
        }
    }
}

void Game::update()
{
    manager.refresh();
    manager.update();
    HandleBullet->update();
}

void Game::clean()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game::ResetGame()
{
    manager.refresh();
    Player1.getComponent<SpriteComponent>().alive = true;
    Player2.getComponent<SpriteComponent>().alive = true;
    Player1.getComponent<TransformComponent>().position = Vector2D(160,160);
    Player2.getComponent<TransformComponent>().position = Vector2D(1440,1440);
    Player1.getComponent<SpriteComponent>().bullets.clear();
    Player2.getComponent<SpriteComponent>().bullets.clear();

}

void Game::preload()
{
    initSDL(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    createRenderer(); 

    this->startScreenTexture = TextureManager::LoadTexture("assets/PlayScreen/StartScreen.png", this->renderer);
    this->tutorialTexture = TextureManager::LoadTexture("assets/PlayScreen/Tutorial.png", this->renderer);
    this->selectModeTexture = TextureManager::LoadTexture("assets/PlayScreen/SelectMode.png", this->renderer);
    this->selectNumberOfPlayersTexture = TextureManager::LoadTexture("assets/PlayScreen/SelectNumberOfPlayers.png", this->renderer);

    ifstream mapData("tankaz.json");
    mapAZ = new Map("tankaz", this->renderer, json::parse(mapData));
    mapAZ->setCollisionByProperty(new json({{"collision", true}}), true);
    
    Player1.addComponent<TransformComponent>(160,160, mapAZ);
    Player1.addComponent<SpriteComponent>("assets/ground_shaker_asset/Red/Bodies/body_tracks.png", "assets/ground_shaker_asset/Red/Weapons/turret_01_mk4.png", "assets/Fire_Shots/Flash_A_04.png", "assets/SCML/Effects/Explosion_E.png",this->renderer, 8, 50);
    Player1.addComponent<KeyboardController>(&this->event);

    Player2.addComponent<TransformComponent>(1440,1440, mapAZ);
    Player2.addComponent<SpriteComponent>("assets/ground_shaker_asset/Blue/Bodies/body_tracks.png", "assets/ground_shaker_asset/Blue/Weapons/turret_01_mk4.png","assets/Fire_Shots/Flash_B_04.png", "assets/SCML/Effects/Explosion_E.png",this->renderer, 8, 50);
    Player2.addComponent<KeyboardController2>(&this->event);
    HandleBullet = new HandleBulletsBetweenTwoSprites(Player1, Player2);

}

#pragma once

#include "game.hpp"

Map *mapAZ;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

Manager manager;
auto& Player1(manager.addEntity());
auto& Player2(manager.addEntity());
auto& Player3(manager.addEntity());

HandleBulletsBetweenTwoSprites* HandleBullet1 = nullptr;
HandleBulletsBetweenTwoSprites* HandleBullet2 = nullptr;
HandleBulletsBetweenTwoSprites* HandleBullet3 = nullptr;

HandleCollectBulletPackage* HandleBulletPackage1 = nullptr;
HandleCollectBulletPackage* HandleBulletPackage2 = nullptr;
HandleCollectBulletPackage* HandleBulletPackage3 = nullptr;


int Game::ScorePlayer1 = 0;
int Game::ScorePlayer2 = 0;
int Game::ScorePlayer3 = 0;

string Game::TypeOfBulletPackage[4];
map <string, SDL_Texture*> Game::bulletIcons;

Game::Game()
{}
Game::~Game()
{
    delete HandleBullet1;
    delete HandleBullet2;
    delete HandleBullet3;
    delete HandleBulletPackage1;
    delete HandleBulletPackage2;
    delete HandleBulletPackage3;
    for(auto it : bulletPackages)
    {
        delete it;
    }
   
    delete mapAZ;
    for(auto it : bulletIcons)
    {
        SDL_DestroyTexture(it.second);
    }
    SDL_DestroyTexture(this->startScreenTexture);
    SDL_DestroyTexture(this->tutorialTexture);
    SDL_DestroyTexture(this->selectModeTexture);
    SDL_DestroyTexture(this->selectNumberOfPlayersTexture);
    SDL_DestroyTexture(this->keyboardShortcuts);
    SDL_DestroyTexture(this->RocketIcon);
    SDL_DestroyTexture(this->GatlingIcon);
    SDL_DestroyTexture(this->TripleBulletIcon);
    SDL_DestroyTexture(this->FastBulletIcon);
    clean();
}

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
    else if(gamestate == GameState::KEYBOARD_SHORTCUTS)
    {
        SDL_RenderCopy(this->renderer, this->keyboardShortcuts, nullptr, nullptr);
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
        for(auto it : bulletPackages)
        {
            it->draw();
        }
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
                    gamestate = GameState::KEYBOARD_SHORTCUTS;
                else if(gamestate == GameState::KEYBOARD_SHORTCUTS)
                    gamestate = GameState::SELECT_MODE;
                break;
            case SDLK_F2:
                if(gamestate == GameState::SELECT_MODE)
                {
                    gamestate = GameState::SELECT_NUMBER_OF_PLAYERS;
                }
                break;

            case SDLK_2:
                if(gamestate == GameState::SELECT_NUMBER_OF_PLAYERS)
                {
                    gamestate = GameState::PLAYING;
                    NumberOfPlayers = 2;
                    Player3.destroy();
                    delete HandleBullet2;
                    delete HandleBullet3;
                }
                break;
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
    if(gamestate == GameState::PLAYING)
    {
        manager.refresh();
        manager.update();
        HandleBullet1->update();
        HandleBulletPackage1->update(bulletPackages);
        if(NumberOfPlayers == 2) 
        {
            HandleBulletPackage2->update(bulletPackages);
        }
        else if(NumberOfPlayers == 3) 
        {
            HandleBullet2->update();
            HandleBullet3->update();
            HandleBulletPackage3->update(bulletPackages);
        }
        
    }
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

    if(NumberOfPlayers == 3) 
    {
        Player3.getComponent<SpriteComponent>().alive = true;
        Player3.getComponent<TransformComponent>().position = Vector2D(160,1440);
        Player3.getComponent<SpriteComponent>().bullets.clear();
    }

}

void Game::spawnBulletPackage() 
{
    int x, y;
    string type;
    do 
    {
        x = (rand() % (mapWidth / 64)) * 64;
        y = (rand() % (mapHeight / 64)) * 64;
        type = this->TypeOfBulletPackage[rand() % (sizeof(TypeOfBulletPackage) / sizeof(TypeOfBulletPackage[0]))];
       
    } while (isOccupied(x, y) || isWall(x, y)); 
    bulletPackages.push_back(new BulletPackage(x, y, bulletIcons[type], this->renderer, type));
}

bool Game::isOccupied(int x, int y) 
{
    for(auto it : bulletPackages) 
    {
        if(it->destRect.x == x && it->destRect.y == y) 
        {
            return true;
        }
    }
    return false;
}

bool Game::isWall(int x, int y) 
{
    x = x * SCALEDOWN / mapAZ->tileWidth;
    y = y * SCALEDOWN / mapAZ->tileHeight;
        for (auto layer: mapAZ->layers) {
            if (layer->layerType != "tilelayer") continue;
            int id = layer->tileLayer->getId(y, x);
            if (mapAZ->tileSet->tiles[id]->isCollidable) {
                return true;
            }
        }
    
    return false;
}
void Game::preload()
{
    initSDL(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    createRenderer(); 

    this->startScreenTexture = TextureManager::LoadTexture("assets/PlayScreen/StartScreen.png", this->renderer);
    this->tutorialTexture = TextureManager::LoadTexture("assets/PlayScreen/Tutorial.png", this->renderer);
    this->selectModeTexture = TextureManager::LoadTexture("assets/PlayScreen/SelectMode.png", this->renderer);
    this->selectNumberOfPlayersTexture = TextureManager::LoadTexture("assets/PlayScreen/SelectNumberOfPlayers.png", this->renderer);
    this->keyboardShortcuts = TextureManager::LoadTexture("assets/PlayScreen/KeyboardShortcuts.png", this->renderer);

    this->RocketIcon = TextureManager::LoadTexture("assets/BulletPackageIcon/rocket.png", this->renderer);
    this->GatlingIcon = TextureManager::LoadTexture("assets/BulletPackageIcon/gatling.png", this->renderer);
    this->TripleBulletIcon = TextureManager::LoadTexture("assets/BulletPackageIcon/triple.png", this->renderer);
    this->FastBulletIcon = TextureManager::LoadTexture("assets/BulletPackageIcon/fast.png", this->renderer);
    TypeOfBulletPackage[0] = "Rocket";
    TypeOfBulletPackage[1] = "Gatling";
    TypeOfBulletPackage[2] = "Triple";
    TypeOfBulletPackage[3] = "Fast";
    bulletIcons["Rocket"] = RocketIcon;
    bulletIcons["Gatling"] = GatlingIcon;
    bulletIcons["Triple"] = TripleBulletIcon;
    bulletIcons["Fast"] = FastBulletIcon;

    ifstream mapData("tankaz.json");
    mapAZ = new Map("tankaz", this->renderer, json::parse(mapData));
    mapAZ->setCollisionByProperty(new json({{"collision", true}}), true);
    
    Player1.addComponent<TransformComponent>(160,160, mapAZ);
    Player1.addComponent<SpriteComponent>("assets/ground_shaker_asset/Red/Bodies/body_tracks.png", "assets/ground_shaker_asset/Red/Weapons/turret_01_mk4.png", "assets/Fire_Shots/Flash_A_04.png", "assets/SCML/Effects/Explosion_E.png",this->renderer, 8, 50);
    Player1.addComponent<KeyboardController>(&this->event);

    Player2.addComponent<TransformComponent>(1440,1440, mapAZ);
    Player2.addComponent<SpriteComponent>("assets/ground_shaker_asset/Blue/Bodies/body_tracks.png", "assets/ground_shaker_asset/Blue/Weapons/turret_01_mk4.png","assets/Fire_Shots/Flame_H.png", "assets/SCML/Effects/Explosion_E.png",this->renderer, 8, 50);
    Player2.addComponent<KeyboardController2>(&this->event);
    
    Player3.addComponent<TransformComponent>(160,1440, mapAZ);
    Player3.addComponent<SpriteComponent>("assets/ground_shaker_asset/Camo/Bodies/body_tracks.png", "assets/ground_shaker_asset/Camo/Weapons/turret_01_mk4.png","assets/Fire_Shots/Flame_H.png", "assets/SCML/Effects/Explosion_E.png",this->renderer, 8, 50);
    Player3.addComponent<KeyboardController3>(&this->event);

    HandleBullet1 = new HandleBulletsBetweenTwoSprites(Player1, Player2);
    HandleBullet2 = new HandleBulletsBetweenTwoSprites(Player1, Player3);
    HandleBullet3 = new HandleBulletsBetweenTwoSprites(Player2, Player3);

    HandleBulletPackage1 = new HandleCollectBulletPackage(Player1);
    HandleBulletPackage2 = new HandleCollectBulletPackage(Player2);
    HandleBulletPackage3 = new HandleCollectBulletPackage(Player3);

}

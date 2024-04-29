#pragma once

#include "game.hpp"

Map *mapAZ;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

Manager manager;
auto& Player1(manager.addEntity());
auto& Player2(manager.addEntity());
auto& Player3(manager.addEntity());

HandleTwoSprites* HandleTwo = nullptr;
HandleThreeSprites* HandleThree = nullptr;

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
    this->gamestate = GameState::START_SCREEN;
    this->mute = false;
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
    
    if(gamestate == GameState::PLAYING)
    {
        mapAZ->render();
        manager.draw();
        for(auto it : bulletPackages)
            it->draw();
        ScoreRender();
    }
    else 
        menu->Render(gamestate);
    
    
    SDL_RenderPresent(renderer);
}
void Game::ScoreRender()
{
    if(NumberOfPlayers == 2)
    {
        TextManager::DrawText(this->renderer, this->font, "Score Player1: " + to_string(ScorePlayer1), {1600, 384, 384, 128}, {255, 255, 255, 255});
        TextManager::DrawText(this->renderer, this->font, "Score Player2: " + to_string(ScorePlayer2), {1600, 576, 384, 128}, {255, 255, 255, 255});
    }
    else if(NumberOfPlayers == 3)
    {
        TextManager::DrawText(this->renderer, this->font, "Score Player1: " + to_string(ScorePlayer1), {1664, 384, 384, 128}, {255, 255, 255, 255});
        TextManager::DrawText(this->renderer, this->font, "Score Player2: " + to_string(ScorePlayer2), {1664, 576, 384, 128}, {255, 255, 255, 255});
        TextManager::DrawText(this->renderer, this->font, "Score Player3: " + to_string(ScorePlayer3), {1664, 768, 384, 128}, {255, 255, 255, 255});
    }
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
            case SDLK_m:
                if(mute) 
                    mute = false;
                else 
                    mute = true;
                break;
            case SDLK_BACKSPACE:
                if(gamestate == GameState::PAUSED)
                {
                    ResetGame();
                    gamestate = GameState::START_SCREEN;
                    ScorePlayer1 = 0;
                    ScorePlayer2 = 0;
                    ScorePlayer3 = 0;
                    Player3.getComponent<SpriteComponent>().alive = true;
                }
                break;
            default:
                break;
        }
    }
    menu->HandleEvents(gamestate);
    this->NumberOfPlayers = menu->numberOfPlayers;
}

void Game::update()
{
    if(gamestate == GameState::PLAYING)
    {
        manager.update();
        
        if(NumberOfPlayers == 2) 
        {
            HandleTwo->update();
            HandleBulletPackage1->update(bulletPackages);
            HandleBulletPackage2->update(bulletPackages);
            Player3.getComponent<SpriteComponent>().alive = false;
            
        }
        else if(NumberOfPlayers == 3) 
        {
            HandleThree->update();
            HandleBulletPackage1->update(bulletPackages);
            HandleBulletPackage2->update(bulletPackages);
            HandleBulletPackage3->update(bulletPackages);
        }
        
    }
}

void Game::playMusic()
{
    menu->HandleBackgroundMusic(this->gamestate, this->mute);
}
void Game::ResetGame()
{
    manager.refresh();
    gamestate = GameState::PLAYING;
    int player1_xpos, player1_ypos;
    do 
    {
        player1_xpos = (rand() % (mapWidth / 64)) * 64;
        player1_ypos = (rand() % (mapHeight / 64)) * 64;
       
    } while (isWall(player1_xpos, player1_ypos) || 
             isWall(player1_xpos + 64, player1_ypos) || isWall(player1_xpos, player1_ypos + 64) || 
             isWall(player1_xpos - 64, player1_ypos) || isWall(player1_xpos, player1_ypos - 64) || 
             isWall(player1_xpos - 64, player1_ypos - 64) || isWall(player1_xpos - 64, player1_ypos + 64) || 
             isWall(player1_xpos + 64, player1_ypos + 64) || isWall(player1_xpos + 64, player1_ypos - 64)); 

    Player1.getComponent<SpriteComponent>().alive = true;
    Player1.getComponent<SpriteComponent>().bullets.clear();    
    Player1.getComponent<TransformComponent>().position = Vector2D(player1_xpos, player1_ypos);

    int player2_xpos, player2_ypos;
    do 
    {
        player2_xpos = (rand() % (mapWidth / 64)) * 64;
        player2_ypos = (rand() % (mapHeight / 64)) * 64;

    } while (isWall(player2_xpos, player2_ypos) || 
             isWall(player2_xpos + 64, player2_ypos) || isWall(player2_xpos, player2_ypos + 64) || 
             isWall(player2_xpos - 64, player2_ypos) || isWall(player2_xpos, player2_ypos - 64) || 
             isWall(player1_xpos - 64, player1_ypos - 64) || isWall(player1_xpos - 64, player1_ypos + 64) || 
             isWall(player1_xpos + 64, player1_ypos + 64) || isWall(player1_xpos + 64, player1_ypos - 64) || 
             (player1_xpos == player2_xpos && player1_ypos == player2_ypos)); 
    Player2.getComponent<SpriteComponent>().alive = true;
    Player2.getComponent<TransformComponent>().position = Vector2D(player2_xpos, player2_ypos);
    Player2.getComponent<SpriteComponent>().bullets.clear();


    if(NumberOfPlayers == 3) 
    {
        int player3_xpos, player3_ypos;
        do 
        {
            player3_xpos = (rand() % (mapWidth / 64)) * 64;
            player3_ypos = (rand() % (mapHeight / 64)) * 64;

        
        }while (isWall(player3_xpos, player3_ypos) || 
                isWall(player3_xpos + 64, player3_ypos) || isWall(player3_xpos, player3_ypos + 64) || 
                isWall(player3_xpos - 64, player3_ypos) || isWall(player3_xpos, player3_ypos - 64) || 
                isWall(player3_xpos - 64, player3_ypos - 64) || isWall(player3_xpos - 64, player3_ypos + 64) || 
                isWall(player3_xpos + 64, player3_ypos + 64) || isWall(player3_xpos + 64, player3_ypos - 64) || 
                (player3_xpos == player1_xpos && player3_ypos == player1_ypos) || (player3_xpos == player2_xpos && player3_ypos == player2_ypos)); 
        Player3.getComponent<SpriteComponent>().alive = true;
        Player3.getComponent<TransformComponent>().position = Vector2D(player3_xpos, player3_ypos);
        Player3.getComponent<SpriteComponent>().bullets.clear();
    }

    for(auto it : bulletPackages)
        delete it;
    bulletPackages.clear();

}

void Game::spawnBulletPackage() 
{
    int x, y;
    string type;
    do 
    {
        x = (rand() % (mapWidth / 64)) * 64;
        y = (rand() % (mapHeight / 64)) * 64;
        //type = this->TypeOfBulletPackage[rand() % (sizeof(TypeOfBulletPackage) / sizeof(TypeOfBulletPackage[0]))];
        type = "Rocket";
       
    } while (isOccupied(x, y) || isWall(x, y)); 
    bulletPackages.push_back(new BulletPackage(x, y, bulletIcons[type], this->renderer, type));
}

bool Game::isOccupied(int x, int y) 
{
    for(auto it : bulletPackages) 
        if(it->destRect.x == x && it->destRect.y == y) 
           return true;
        
    return false;
}

bool Game::isWall(int x, int y) 
{
    x = x * SCALEDOWN / mapAZ->tileWidth;
    y = y * SCALEDOWN / mapAZ->tileHeight;
        for (auto layer: mapAZ->layers) 
        {
            if (layer->layerType != "tilelayer") continue;
            int id = layer->tileLayer->getId(y, x);
            if (mapAZ->tileSet->tiles[id]->isCollidable) 
                return true;
        }
    
    return false;
}
void Game::clean()
{
    delete menu;
    delete HandleTwo;
    delete HandleThree;
    delete HandleBulletPackage1;
    delete HandleBulletPackage2;
    delete HandleBulletPackage3;
    for(auto it : bulletPackages)
        delete it;
    
   
    delete mapAZ;
    for(auto it : bulletIcons)
        SDL_DestroyTexture(it.second);

    SDL_DestroyTexture(this->startScreenTexture);
    SDL_DestroyTexture(this->tutorialTexture);
    SDL_DestroyTexture(this->selectModeTexture);
    SDL_DestroyTexture(this->selectNumberOfPlayersTexture);
    SDL_DestroyTexture(this->keyboardShortcuts);
    SDL_DestroyTexture(this->RocketIcon);
    SDL_DestroyTexture(this->GatlingIcon);
    SDL_DestroyTexture(this->TripleBulletIcon);
    SDL_DestroyTexture(this->FastBulletIcon);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
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
    this->font = TextManager::LoadText("assets/Fonts/04B_19.TTF");
    this->backgroundMusic = AudioManager::LoadMusic("assets/Dani Stob - Unstoppable - Loop.wav");
    this->WinningMusic = AudioManager::LoadMusic("assets/Dani Stob - Victory Fanfare.wav");
   
    TypeOfBulletPackage[0] = "Rocket";
    TypeOfBulletPackage[1] = "Gatling";
    TypeOfBulletPackage[2] = "Triple";
    TypeOfBulletPackage[3] = "Fast";
    bulletIcons["Rocket"] = RocketIcon;
    bulletIcons["Gatling"] = GatlingIcon;
    bulletIcons["Triple"] = TripleBulletIcon;
    bulletIcons["Fast"] = FastBulletIcon;

    menu = new Menu(this->renderer, &this->event, this->backgroundMusic, this->WinningMusic, this->startScreenTexture, this->tutorialTexture, this->selectModeTexture, this->selectNumberOfPlayersTexture, this->keyboardShortcuts);
    menu->PlayBackgroundMusic();

    
    ifstream mapData("tankaz.json");
    mapAZ = new Map("tankaz", this->renderer, json::parse(mapData));
    mapAZ->setCollisionByProperty(new json({{"collision", true}}), true);
    
    Player1.addComponent<TransformComponent>(160,160, mapAZ);
    Player1.addComponent<SpriteComponent>("assets/ground_shaker_asset/Red/Bodies/body_tracks.png", "assets/ground_shaker_asset/Red/Weapons/turret_01_mk4.png", "assets/Fire_Shots/Flash_A_04.png", "assets/SCML/Effects/Explosion_E.png",this->renderer, 8, 50);
    Player1.addComponent<KeyboardController>(&this->event);

    Player2.addComponent<TransformComponent>(1440,1440, mapAZ);
    Player2.addComponent<SpriteComponent>("assets/ground_shaker_asset/Blue/Bodies/body_tracks.png", "assets/ground_shaker_asset/Blue/Weapons/turret_01_mk4.png","assets/Fire_Shots/Flash_A_04.png", "assets/SCML/Effects/Explosion_E.png",this->renderer, 8, 50);
    Player2.addComponent<KeyboardController2>(&this->event);
    
    Player3.addComponent<TransformComponent>(160,1440, mapAZ);
    Player3.addComponent<SpriteComponent>("assets/ground_shaker_asset/Camo/Bodies/body_tracks.png", "assets/ground_shaker_asset/Camo/Weapons/turret_01_mk4.png","assets/Fire_Shots/Flash_A_04.png", "assets/SCML/Effects/Explosion_E.png",this->renderer, 8, 50);
    Player3.addComponent<KeyboardController3>(&this->event);

    HandleTwo = new HandleTwoSprites(Player1, Player2);
    HandleThree = new HandleThreeSprites(Player1, Player2, Player3);

    HandleBulletPackage1 = new HandleCollectBulletPackage(Player1);
    HandleBulletPackage2 = new HandleCollectBulletPackage(Player2);
    HandleBulletPackage3 = new HandleCollectBulletPackage(Player3);

}

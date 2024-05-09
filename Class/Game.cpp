#pragma once

#include "Game.hpp"

Map *mapAZ_1;
Map *mapAZ_2;
Map *mapAZ_3;
Map *mapAZ_4;
Map *mapAZ_5;
Map* chosenMap;

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
    
    if(gamestate != GameState::PLAYING && gamestate != GameState::WINNING_TIME)
        menu->Render(gamestate);
    else
    {
        chosenMap->render();
        manager.draw();
        for(auto it : bulletPackages)
            it->draw();
        ScoreRender();
    }
    SDL_RenderPresent(renderer);
}
void Game::ScoreRender()
{
    if(NumberOfPlayers == 2)
    {
        TextManager::DrawText(this->renderer, this->font, "Score Player1: " + to_string(ScorePlayer1), {1600, 576, 384, 128}, {255, 255, 255, 255});
        TextManager::DrawText(this->renderer, this->font, "Score Player2: " + to_string(ScorePlayer2), {1600, 832, 384, 128}, {255, 255, 255, 255});
        if(gamestate == GameState::WINNING_TIME)
        {
            if(Player1.getComponent<SpriteComponent>().alive)
                TextManager::DrawText(this->renderer, this->font, "Player1 Wins!", {576, 576, 512, 256}, {255, 0, 0, 255});
            else
                TextManager::DrawText(this->renderer, this->font, "Player2 Wins!", {576, 576, 512, 256}, {0, 0, 255, 255});
        
        }
    }
    else if(NumberOfPlayers == 3)
    {
        TextManager::DrawText(this->renderer, this->font, "Score Player1: " + to_string(ScorePlayer1), {1664, 448, 384, 128}, {255, 255, 255, 255});
        TextManager::DrawText(this->renderer, this->font, "Score Player2: " + to_string(ScorePlayer2), {1664, 640, 384, 128}, {255, 255, 255, 255});
        TextManager::DrawText(this->renderer, this->font, "Score Player3: " + to_string(ScorePlayer3), {1664, 832, 384, 128}, {255, 255, 255, 255});
        if(gamestate == GameState::WINNING_TIME)
        {
            if(Player1.getComponent<SpriteComponent>().alive)
                TextManager::DrawText(this->renderer, this->font, "Player1 Wins!", {576, 576, 512, 256}, {255, 0, 0, 255});
            else if(Player2.getComponent<SpriteComponent>().alive)
                TextManager::DrawText(this->renderer, this->font, "Player2 Wins!", {576, 576, 512, 256}, {0, 0, 255, 255});
            else
                TextManager::DrawText(this->renderer, this->font, "Player3 Wins!", {576, 576, 512, 256}, {0, 255, 0, 255});
        }
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
    if(gamestate == GameState::PLAYING || gamestate == GameState::WINNING_TIME)
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

Map* Game::randomMap(Map* map1, Map* map2, Map* map3, Map* map4, Map* map5)
{
    
    int mapChoice = rand() % 5;
    if(mapChoice == 0) 
        return map1;
    else if(mapChoice == 1) 
        return map2;
    else if(mapChoice == 2)
        return map3;
    else if(mapChoice == 3)
        return map4;
    else
        return map5;
    
}   
void Game::ResetGame()
{
    manager.refresh();
    gamestate = GameState::PLAYING;

    chosenMap = randomMap(mapAZ_1, mapAZ_2, mapAZ_3, mapAZ_4, mapAZ_5);

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
    Player1.getComponent<SpriteComponent>().rockets.clear();
    Player1.getComponent<SpriteComponent>().now_type_of_bullet = TypeOfBullet::NORMAL;
    Player1.getComponent<TransformComponent>().position = Vector2D(player1_xpos, player1_ypos);
    Player1.getComponent<TransformComponent>().velocity = Vector2D(0, 0);
    Player1.getComponent<TransformComponent>().rotation = 0.0f;
    Player1.getComponent<TransformComponent>().setMap(chosenMap);
    

    int player2_xpos, player2_ypos;
    do 
    {
        player2_xpos = (rand() % (mapWidth / 64)) * 64;
        player2_ypos = (rand() % (mapHeight / 64)) * 64;

    } while (isWall(player2_xpos, player2_ypos) || 
             isWall(player2_xpos + 64, player2_ypos) || isWall(player2_xpos, player2_ypos + 64) || 
             isWall(player2_xpos - 64, player2_ypos) || isWall(player2_xpos, player2_ypos - 64) || 
             isWall(player2_xpos - 64, player2_ypos - 64) || isWall(player2_xpos - 64, player2_ypos + 64) || 
             isWall(player2_xpos + 64, player2_ypos + 64) || isWall(player2_xpos + 64, player2_ypos - 64) || 
             (player1_xpos == player2_xpos && player1_ypos == player2_ypos)); 
    Player2.getComponent<SpriteComponent>().alive = true;
    Player2.getComponent<SpriteComponent>().bullets.clear(); 
    Player2.getComponent<SpriteComponent>().rockets.clear();
    Player2.getComponent<SpriteComponent>().now_type_of_bullet = TypeOfBullet::NORMAL;
    Player2.getComponent<TransformComponent>().position = Vector2D(player2_xpos, player2_ypos);
    Player2.getComponent<TransformComponent>().velocity = Vector2D(0, 0);
    Player2.getComponent<TransformComponent>().rotation = 0.0f;
    Player2.getComponent<TransformComponent>().setMap(chosenMap);

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
        Player3.getComponent<SpriteComponent>().bullets.clear(); 
        Player3.getComponent<SpriteComponent>().rockets.clear();
        Player3.getComponent<SpriteComponent>().now_type_of_bullet = TypeOfBullet::NORMAL;
        Player3.getComponent<TransformComponent>().position = Vector2D(player3_xpos, player3_ypos);
        Player3.getComponent<TransformComponent>().velocity = Vector2D(0, 0);
        Player3.getComponent<TransformComponent>().rotation = 0.0f;
        Player3.getComponent<TransformComponent>().setMap(chosenMap);
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
        x = (rand() % (mapWidth / tileWidth)) * tileWidth;
        y = (rand() % (mapHeight / tileHeight)) * tileHeight;
        type = this->TypeOfBulletPackage[rand() % (sizeof(TypeOfBulletPackage) / sizeof(TypeOfBulletPackage[0]))];
        //type = "Rocket";
       
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
    x = x * SCALEDOWN / chosenMap->tileWidth;
    y = y * SCALEDOWN / chosenMap->tileHeight;
        for (auto layer: chosenMap->layers) 
        {
            if (layer->layerType != "tilelayer") continue;
            int id = layer->tileLayer->getId(y, x);
            if (chosenMap->tileSet->tiles[id]->isCollidable) 
                return true;
        }
    
    return false;
}
void Game::updateWinner() 
{
    static Uint32 resetTime = 0;
    static bool hasPlayedWinningSound = false;
    if (gamestate == GameState::WINNING_TIME) 
    {
        if (!hasPlayedWinningSound) 
        {
            hasPlayedWinningSound = true; 
            AudioManager::PlaySound(WinningMusic);
        }
    }
    else
        hasPlayedWinningSound = false; 
    
    if (NumberOfPlayers == 2) 
    {
        if (!Player1.getComponent<SpriteComponent>().alive) 
        {
            gamestate = GameState::WINNING_TIME;
            if (resetTime == 0)
            {
                resetTime = SDL_GetTicks();
            }
            else if (SDL_GetTicks() - resetTime > 4000) 
            {
                ScorePlayer2++;
                ResetGame();
                resetTime = 0;
            }
        }
        else if(!Player2.getComponent<SpriteComponent>().alive)
        {
            gamestate = GameState::WINNING_TIME;    
            if (resetTime == 0)
                resetTime = SDL_GetTicks();
            else if (SDL_GetTicks() - resetTime > 4000) 
            {
                ScorePlayer1++;
                ResetGame();
                resetTime = 0;
            }
        }
    }
    else if (NumberOfPlayers == 3) 
    {
        if (!Player1.getComponent<SpriteComponent>().alive && !Player2.getComponent<SpriteComponent>().alive) 
        {
            gamestate = GameState::WINNING_TIME;
            if (resetTime == 0)
                resetTime = SDL_GetTicks();
            else if (SDL_GetTicks() - resetTime > 4000) 
            {
                ScorePlayer3++;
                ResetGame();
                resetTime = 0;
            }
        }
        else if (!Player2.getComponent<SpriteComponent>().alive && !Player3.getComponent<SpriteComponent>().alive) 
        {
            gamestate = GameState::WINNING_TIME;
            if (resetTime == 0)
                resetTime = SDL_GetTicks();
            else if (SDL_GetTicks() - resetTime > 4000) 
            {
                ScorePlayer1++;
                ResetGame();
                resetTime = 0;
            }
        }
        else if (!Player3.getComponent<SpriteComponent>().alive && !Player1.getComponent<SpriteComponent>().alive) 
        {
            gamestate = GameState::WINNING_TIME;
            if (resetTime == 0)
                resetTime = SDL_GetTicks();
            else if (SDL_GetTicks() - resetTime > 4000) 
            {
                ScorePlayer2++;
                ResetGame();
                resetTime = 0;
            }
        }
    }
    
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
    for(auto it : bulletIcons)
        SDL_DestroyTexture(it.second);
    delete mapAZ_1;
    delete mapAZ_2;
    delete mapAZ_3;
    delete mapAZ_4;
    delete mapAZ_5;
    delete chosenMap;

    SDL_DestroyTexture(this->startScreenTexture);
    SDL_DestroyTexture(this->tutorialTexture);
    SDL_DestroyTexture(this->someAmmoTypes);
    SDL_DestroyTexture(this->selectNumberOfPlayersTexture);
    SDL_DestroyTexture(this->keyboardShortcuts);
    SDL_DestroyTexture(this->RocketIcon);
    SDL_DestroyTexture(this->GatlingIcon);
    SDL_DestroyTexture(this->TripleBulletIcon);
    SDL_DestroyTexture(this->FastBulletIcon);
    Mix_FreeMusic(this->backgroundMusic);
    Mix_FreeChunk(this->WinningMusic);

    TTF_CloseFont(this->font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
void Game::preload()
{
    initSDL(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    createRenderer(); 
    this->gamestate = GameState::START_SCREEN;
    this->mute = false;

    this->startScreenTexture = TextureManager::LoadTexture("assets/PlayScreen/StartScreen.png", this->renderer);
    this->tutorialTexture = TextureManager::LoadTexture("assets/PlayScreen/Tutorial.png", this->renderer);
    this->someAmmoTypes = TextureManager::LoadTexture("assets/PlayScreen/SomeAmmoTypes.png", this->renderer);
    this->selectNumberOfPlayersTexture = TextureManager::LoadTexture("assets/PlayScreen/SelectNumberOfPlayers.png", this->renderer);
    this->keyboardShortcuts = TextureManager::LoadTexture("assets/PlayScreen/KeyboardShortcuts.png", this->renderer);
    this->RocketIcon = TextureManager::LoadTexture("assets/BulletPackageIcon/rocket.png", this->renderer);
    this->GatlingIcon = TextureManager::LoadTexture("assets/BulletPackageIcon/gatling.png", this->renderer);
    this->TripleBulletIcon = TextureManager::LoadTexture("assets/BulletPackageIcon/triple.png", this->renderer);
    this->FastBulletIcon = TextureManager::LoadTexture("assets/BulletPackageIcon/fast.png", this->renderer);
    this->font = TextManager::LoadText("assets/Fonts/04B_19.TTF");
    this->backgroundMusic = AudioManager::LoadMusic("assets/Sound/Dani Stob - Unstoppable - Loop.wav");
    this->WinningMusic = AudioManager::LoadSound("assets/Sound/Dani Stob - Victory Fanfare.wav");
   
    TypeOfBulletPackage[0] = "Rocket";
    TypeOfBulletPackage[1] = "Gatling";
    TypeOfBulletPackage[2] = "Triple";
    TypeOfBulletPackage[3] = "Fast";
    bulletIcons["Rocket"] = RocketIcon;
    bulletIcons["Gatling"] = GatlingIcon;
    bulletIcons["Triple"] = TripleBulletIcon;
    bulletIcons["Fast"] = FastBulletIcon;

    menu = new Menu(this->renderer, &this->event, this->backgroundMusic, this->WinningMusic, this->font, this->startScreenTexture, this->tutorialTexture, this->someAmmoTypes, this->selectNumberOfPlayersTexture, this->keyboardShortcuts);
    menu->PlayBackgroundMusic();

    
    ifstream mapData("assets/Map/mapAZ_1.json");
    mapAZ_1 = new Map("map1", this->renderer, json::parse(mapData));
    mapAZ_1->setCollisionByProperty(new json({{"collision", true}}), true);

    ifstream mapData2("assets/Map/mapAZ_2.json");
    mapAZ_2 = new Map("map2", this->renderer, json::parse(mapData2));
    mapAZ_2->setCollisionByProperty(new json({{"collision", true}}), true);

    ifstream mapData3("assets/Map/mapAZ_3.json");
    mapAZ_3 = new Map("map3", this->renderer, json::parse(mapData3));
    mapAZ_3->setCollisionByProperty(new json({{"collision", true}}), true);

    ifstream mapData4("assets/Map/mapAZ_4.json");
    mapAZ_4 = new Map("map4", this->renderer, json::parse(mapData4));
    mapAZ_4->setCollisionByProperty(new json({{"collision", true}}), true);

    ifstream mapData5("assets/Map/mapAZ_5.json");
    mapAZ_5 = new Map("map5", this->renderer, json::parse(mapData5));
    mapAZ_5->setCollisionByProperty(new json({{"collision", true}}), true);
    
    chosenMap = randomMap(mapAZ_1, mapAZ_2, mapAZ_3, mapAZ_4, mapAZ_5);
    
    Player1.addComponent<TransformComponent>(160,160, chosenMap);
    Player1.addComponent<SpriteComponent>("assets/ground_shaker_asset/Red/Bodies/body_tracks.png", "assets/ground_shaker_asset/Red/Weapons/turret_01_mk4.png", "assets/Fire_Shots/Flash_A_04.png", "assets/SCML/Effects/Explosion_E.png",this->renderer, 8, 50);
    Player1.addComponent<KeyboardController>(&this->event);

    Player2.addComponent<TransformComponent>(1440,1440, chosenMap);
    Player2.addComponent<SpriteComponent>("assets/ground_shaker_asset/Blue/Bodies/body_tracks.png", "assets/ground_shaker_asset/Blue/Weapons/turret_01_mk4.png","assets/Fire_Shots/Flash_B_04.png", "assets/SCML/Effects/Explosion_E.png",this->renderer, 8, 50);
    Player2.addComponent<KeyboardController2>(&this->event);
    
    Player3.addComponent<TransformComponent>(160,1440, chosenMap);
    Player3.addComponent<SpriteComponent>("assets/ground_shaker_asset/Camo/Bodies/body_tracks.png", "assets/ground_shaker_asset/Camo/Weapons/turret_01_mk4.png","assets/Fire_Shots/Flash_A_04.png", "assets/SCML/Effects/Explosion_E.png",this->renderer, 8, 50);
    Player3.addComponent<KeyboardController3>(&this->event);

    HandleTwo = new HandleTwoSprites(Player1, Player2);
    HandleThree = new HandleThreeSprites(Player1, Player2, Player3);

    HandleBulletPackage1 = new HandleCollectBulletPackage(Player1);
    HandleBulletPackage2 = new HandleCollectBulletPackage(Player2);
    HandleBulletPackage3 = new HandleCollectBulletPackage(Player3);

}

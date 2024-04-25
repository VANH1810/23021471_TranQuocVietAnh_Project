#pragma once

#include "Config.cpp"
#include "TextureManager.cpp"
#include "TextManager.cpp"
#include "ECS/Components.hpp"
#include "Vector2D.cpp"
#include "GameState.hpp"
#include "BulletPackage.hpp"
#include "HandleCollectBulletPackage.hpp"
class Game
{
    private: 
        SDL_Window* window;
        bool isRunning;
        static SDL_Event event;

        SDL_Texture* startScreenTexture;
        SDL_Texture* tutorialTexture;
        SDL_Texture* selectModeTexture;
        SDL_Texture* selectNumberOfPlayersTexture;
        SDL_Texture* keyboardShortcuts;

        SDL_Texture* RocketIcon;
        SDL_Texture* FastBulletIcon;
        SDL_Texture* GatlingIcon;
        SDL_Texture* TripleBulletIcon;

        TTF_Font* font;


        bool isWall(int x, int y);
        bool isOccupied(int x, int y);

    public:
        Game();
        ~Game();
        void logErrorAndExit(const char* msg, const char* error);
        void initSDL(int xpos, int ypos);
        void createRenderer();
        void Render();
        void ScoreRender();
        void handleEvents();
        void update();
        void clean();
        void preload();
        void ResetGame();
        bool running() 
        {
            return isRunning;
        }

        int NumberOfPlayers;
        
        static int ScorePlayer1;
        static int ScorePlayer2;
        static int ScorePlayer3;

        static SDL_Renderer* renderer;
        
        void spawnBulletPackage();

        GameState gamestate;

        vector<BulletPackage*> bulletPackages;
        static string TypeOfBulletPackage[4];
        static map<string, SDL_Texture*> bulletIcons;
        
};
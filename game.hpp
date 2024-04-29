#pragma once

#include "Config.cpp"
#include "TextureManager.cpp"
#include "TextManager.cpp"
#include "AudioManager.cpp"
#include "ECS/Components.hpp"
#include "Vector2D.cpp"
#include "GameState.hpp"
#include "BulletPackage.hpp"
#include "HandleCollectBulletPackage.hpp"
#include "menu.cpp"
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

        bool isWall(int x, int y);
        bool isOccupied(int x, int y);

        static string TypeOfBulletPackage[4];
        static map<string, SDL_Texture*> bulletIcons;

        Menu* menu;

        Mix_Music* backgroundMusic;
        Mix_Music* WinningMusic;

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
        void spawnBulletPackage();
        bool running() 
        {
            return isRunning;
        }
        void playMusic();
        static SDL_Renderer* renderer;
        int NumberOfPlayers;
        
        static int ScorePlayer1;
        static int ScorePlayer2;
        static int ScorePlayer3;

        TTF_Font* font;

        GameState gamestate;

        bool mute;
        vector<BulletPackage*> bulletPackages;
        
};
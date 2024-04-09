#pragma once

#include "Config.cpp"
#include "TextureManager.cpp"
#include "ECS/Components.hpp"
#include "Vector2D.cpp"
#include "GameState.hpp"

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

        int NumberOfPlayers = 2;
        
        static int ScorePlayer1;
        static int ScorePlayer2;
        static int ScorePlayer3;
        
        static SDL_Renderer* renderer;
        
        GameState gamestate;

};
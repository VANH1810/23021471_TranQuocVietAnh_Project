#pragma once

#include "Config.cpp"
#include "TextureManager.cpp"
#include "ECS/Components.hpp"
#include "Vector2D.cpp"

class Game
{
    private: 
        SDL_Window* window;
        bool isRunning;
        static SDL_Renderer* renderer;
        static SDL_Event event;
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

        static int ScorePlayer1;
        static int ScorePlayer2;
        
        
        

};
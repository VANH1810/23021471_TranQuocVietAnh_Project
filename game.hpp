#pragma once

#include "Config.cpp"
#include "TextureManager.cpp"
#include "map.cpp"
#include "Player.cpp"

class Game
{
    private: 
        SDL_Window* window;
        bool isRunning;
    public:
        Game();
        ~Game();
        void logErrorAndExit(const char* msg, const char* error);
        void initSDL(int xpos, int ypos);
        void createRenderer();
        void Render();
        void handleEvents();
        void update();
        void clean();
        void preload();
       

        bool running() 
        {
            return isRunning;
        }
        
        static SDL_Renderer* renderer;
        

};
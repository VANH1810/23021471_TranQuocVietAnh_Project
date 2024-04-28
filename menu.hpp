#pragma once
#include "Config.cpp"
#include "TextureManager.cpp"
#include "TextManager.cpp"
#include "AudioManager.cpp"
#include "GameState.hpp"
class Menu
{
    private: 
        SDL_Texture* startScreenTexture;
        SDL_Texture* tutorialTexture;
        SDL_Texture* selectModeTexture;
        SDL_Texture* selectNumberOfPlayersTexture;
        SDL_Texture* keyboardShortcuts;
        SDL_Renderer* renderer;

        SDL_Event* event;
    public:
        int numberOfPlayers;
        ~Menu() = default;
        Menu(SDL_Renderer* ren, SDL_Event* e, SDL_Texture* startScreenTexture, SDL_Texture* tutorialTexture, SDL_Texture* selectModeTexture, SDL_Texture* selectNumberOfPlayersTexture, SDL_Texture* keyboardShortcuts);
        void Render(GameState &gameState);
        void HandleEvents(GameState &gameState);
        void playMusic();
        

};
#pragma once
#include "Config.hpp"
#include "TextureManager.cpp"
#include "TextManager.cpp"
#include "AudioManager.cpp"
#include "AudioManager.cpp"
#include "GameState.hpp"
class Menu
{
    private: 
        SDL_Texture* startScreenTexture;
        SDL_Texture* tutorialTexture;
        SDL_Texture* someAmmoTypes;
        SDL_Texture* selectNumberOfPlayersTexture;
        SDL_Texture* keyboardShortcuts;
        SDL_Texture* pausedTexture;

        SDL_Renderer* renderer;

        SDL_Event* event;
        Mix_Music* backgroundMusic;
        Mix_Chunk* WinningMusic;

        TTF_Font* font;
    public:
        int numberOfPlayers;
        ~Menu() = default;
        Menu(SDL_Renderer* ren, SDL_Event* e, Mix_Music* bg_music, Mix_Chunk* win_music, TTF_Font* f, SDL_Texture* startScreenTexture, SDL_Texture* tutorialTexture, SDL_Texture* selectModeTexture, SDL_Texture* selectNumberOfPlayersTexture, SDL_Texture* keyboardShortcuts, SDL_Texture* pausedTexture);
        void Render(GameState &gameState);
        void HandleEvents(GameState &gameState);
        void PlayBackgroundMusic();
        void HandleBackgroundMusic(GameState &gamestate, bool &mute);

};
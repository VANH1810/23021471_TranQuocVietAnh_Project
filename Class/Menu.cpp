#pragma once
#include "menu.hpp"

Menu::Menu(SDL_Renderer* ren, SDL_Event* e, Mix_Music* bg_music, Mix_Chunk* win_music, TTF_Font* f, SDL_Texture* startScreenTexture, SDL_Texture* tutorialTexture, SDL_Texture* someAmmoTypesTexture, SDL_Texture* selectNumberOfPlayersTexture, SDL_Texture* keyboardShortcuts)
{
    this->renderer = ren;
    this->event = e;
    this->backgroundMusic = bg_music;
    this->WinningMusic = win_music;
    this->font = f;
    this->startScreenTexture = startScreenTexture;
    this->someAmmoTypes = someAmmoTypesTexture;
    this->tutorialTexture = tutorialTexture;
    this->selectNumberOfPlayersTexture = selectNumberOfPlayersTexture;
    this->keyboardShortcuts = keyboardShortcuts;

}
        
void Menu::Render(GameState &gamestate)
{
    if(gamestate == GameState::START_SCREEN)
        SDL_RenderCopy(this->renderer, this->startScreenTexture, nullptr, nullptr);
    else if(gamestate == GameState::TUTORIAL)
        SDL_RenderCopy(this->renderer, this->tutorialTexture, nullptr, nullptr);
    else if(gamestate == GameState::SOME_AMMO_TYPES)
        SDL_RenderCopy(this->renderer, this->someAmmoTypes, nullptr, nullptr);
    else if(gamestate == GameState::KEYBOARD_SHORTCUTS)
        SDL_RenderCopy(this->renderer, this->keyboardShortcuts, nullptr, nullptr);
    else if(gamestate == GameState::SELECT_NUMBER_OF_PLAYERS)
        SDL_RenderCopy(this->renderer, this->selectNumberOfPlayersTexture, nullptr, nullptr);
}

void Menu::HandleEvents(GameState &gamestate)
{
    if(event->type == SDL_KEYDOWN)
    {
        switch(event->key.keysym.sym)
        {
            case SDLK_SPACE:
                if(gamestate == GameState::START_SCREEN)
                    gamestate = GameState::TUTORIAL;
                else if(gamestate == GameState::TUTORIAL)
                    gamestate = GameState::SOME_AMMO_TYPES;
                else if(gamestate == GameState::SOME_AMMO_TYPES)
                    gamestate = GameState::KEYBOARD_SHORTCUTS;
                else if(gamestate == GameState::KEYBOARD_SHORTCUTS)
                    gamestate = GameState::SELECT_NUMBER_OF_PLAYERS;
                break;
            case SDLK_2:
                if(gamestate == GameState::SELECT_NUMBER_OF_PLAYERS)
                {
                    gamestate = GameState::PLAYING;
                    numberOfPlayers = 2;  
                }
                break;
            case SDLK_3: 
                if(gamestate == GameState::SELECT_NUMBER_OF_PLAYERS)
                {
                    gamestate = GameState::PLAYING;
                    numberOfPlayers = 3;
                }
                break;
            case SDLK_BACKSPACE:
                if(gamestate == GameState::SELECT_NUMBER_OF_PLAYERS)
                    gamestate = GameState::KEYBOARD_SHORTCUTS;
                else if(gamestate == GameState::KEYBOARD_SHORTCUTS)
                    gamestate = GameState::SOME_AMMO_TYPES;
                else if(gamestate == GameState::SOME_AMMO_TYPES)
                    gamestate = GameState::TUTORIAL;
                else if(gamestate == GameState::TUTORIAL)
                    gamestate = GameState::START_SCREEN;
                break;
            default:
                break;
        }
    }

}

void Menu::PlayBackgroundMusic()
{
    AudioManager::PlayMusic(backgroundMusic);
}

void Menu::HandleBackgroundMusic(GameState &gamestate, bool &mute)
{
    if(mute) 
    {
        AudioManager::MuteMusic();
        AudioManager::MuteSound();
    }
    else
    {   
        AudioManager::UnmuteMusic();
        AudioManager::UnmuteSound();
    }

    if(gamestate == GameState::PLAYING || gamestate == GameState::WINNING_TIME)
        Mix_PauseMusic();
    else
        Mix_ResumeMusic();

        
    
}
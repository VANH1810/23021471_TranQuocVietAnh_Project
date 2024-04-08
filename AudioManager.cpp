#pragma once
#include "AudioManager.hpp"

Mix_Chunk* AudioManager::LoadSound(const string sound) {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) 
    {
        cerr << "Error: " << Mix_GetError() << "\n";
        return nullptr;
    }

    // Load the sound effect
    Mix_Chunk* soundEffect = Mix_LoadWAV(sound.c_str());
    if (soundEffect == nullptr) 
    {
        cerr << "Error: " << Mix_GetError() << "\n";
    }
    return soundEffect;
}

void AudioManager::PlaySound(Mix_Chunk* sound) 
{
    if (sound != nullptr) 
    {
        if (Mix_PlayChannel(-1, sound, 0) == -1) 
        {
            cerr << "Error: " << Mix_GetError() << "\n";
            return;
        }
        Mix_PlayChannel(-1, sound, 0);
    }
    else cerr << "Error: sound is nullptr\n";
}

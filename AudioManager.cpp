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
    }
    else cerr << "Error: sound is nullptr\n";
}

Mix_Music* AudioManager::LoadMusic(const string music) 
{
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) 
    {
        cerr << "Error: " << Mix_GetError() << "\n";
        return nullptr;
    }


    Mix_Music* musicEffect = Mix_LoadMUS(music.c_str());
    if (musicEffect == nullptr) 
    {
        cerr << "Error: " << Mix_GetError() << "\n";
    }
    return musicEffect;
}

void AudioManager::PlayMusic(Mix_Music* music) 
{
    if (music != nullptr) 
    {
        if (Mix_PlayMusic(music, 0) == -1) 
        {
            cerr << "Error: " << Mix_GetError() << "\n";
            return;
        }
    }
    else cerr << "Error: music is nullptr\n";
}
void AudioManager::MuteSound() 
{
    Mix_Volume(-1, 0);
}

void AudioManager::UnmuteSound() 
{
    Mix_Volume(-1, MIX_MAX_VOLUME);
}

void AudioManager::MuteMusic() 
{
    Mix_VolumeMusic(0);
}

void AudioManager::UnmuteMusic() 
{
    Mix_VolumeMusic(MIX_MAX_VOLUME);
}

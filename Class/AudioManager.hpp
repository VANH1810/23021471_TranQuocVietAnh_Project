#pragma once
#include "Config.hpp"

class AudioManager
{
    public:
        static Mix_Chunk* LoadSound(const string sound);
        static void PlaySound(Mix_Chunk* sound);
        static Mix_Music* LoadMusic(const string music);
        static void PlayMusic(Mix_Music* music);
        static void MuteSound();
        static void UnmuteSound();
        static void MuteMusic();
        static void UnmuteMusic();

};
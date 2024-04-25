#pragma once
#include "Config.cpp"

class AudioManager
{
    public:
        static Mix_Chunk* LoadSound(const string sound);
        static void PlaySound(Mix_Chunk* sound);
    private:

};
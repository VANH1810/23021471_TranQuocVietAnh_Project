#pragma once
#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h> 
#include <SDL2/SDL_mixer.h>
#include "json.hpp"


using namespace std;
using json = nlohmann::json;

const int SCREEN_WIDTH = 2048;
const int SCREEN_HEIGHT = 1536;
const int SCALEDOWN = 2;
const char* WINDOW_TITLE = "TANK AZ!";
const int FPS = 120;
const int frameDelay = 1000 / FPS;
const bool fullscreen = true;
const int mapWidth = 1536;
const int mapHeight = 1536;

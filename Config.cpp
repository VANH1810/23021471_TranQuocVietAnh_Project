#pragma once
#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "json.hpp"


using namespace std;
using json = nlohmann::json;

const int SCREEN_WIDTH = 1536;
const int SCREEN_HEIGHT = 1536;
const int SCALEDOWN = 2;
const char* WINDOW_TITLE = "TANK AZ!";
const int FPS = 120;
const int frameDelay = 1000 / FPS;
const bool fullscreen = true;

bool PAUSED = 0;
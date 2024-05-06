#include "game.cpp"

signed main(int argc, char* argv[])
{

    Game *game = new Game();

    Uint32 frameStart;
    int frameTime;
    float timeSinceLastSpawn = 0.0f;
    const float spawnInterval = 5.0f; 


    game->preload();

    while(game->running())
    {
        game->handleEvents();
        game->playMusic();

        frameStart = SDL_GetTicks();
        if (game->gamestate != GameState::PAUSED)
        {
            game->update(); 
            game->Render();
        }

        frameTime = SDL_GetTicks() - frameStart;
        if(frameDelay > frameTime)
            SDL_Delay(frameDelay - frameTime);

        timeSinceLastSpawn += 0.01;
        if(timeSinceLastSpawn >= spawnInterval && game->gamestate == GameState::PLAYING && game->bulletPackages.size() <= 10)
        {
            game->spawnBulletPackage();
            timeSinceLastSpawn = 0.0f;
        }
        game->updateWinner();
        
    }
    
    game->clean();
    delete game;
    return 0;
}



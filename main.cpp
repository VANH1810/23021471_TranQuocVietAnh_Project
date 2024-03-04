#include "game.cpp"

signed main(int argc, char* argv[])
{
    //Khởi tạo môi trường đồ họa
    Game *game = new Game();
    
    Uint32 frameStart;
    int frameTime;

    game->preload();
    while(game->running())
    {
        frameStart = SDL_GetTicks();

        game->handleEvents();
        game->update(); 
        game->Render();
    
        frameTime = SDL_GetTicks() - frameStart;
        if(frameDelay > frameTime)
            SDL_Delay(frameDelay - frameTime);
    }
    game->clean();
    delete game;
    return 0;
}



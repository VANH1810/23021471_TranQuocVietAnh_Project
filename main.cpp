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
        if (!PAUSED)
        {
            game->update(); 
            game->Render();
        }
        frameTime = SDL_GetTicks() - frameStart;
        if(frameDelay > frameTime)
            SDL_Delay(frameDelay - frameTime);
       
        if (!Player1.getComponent<SpriteComponent>().alive) 
        {
            game->ResetGame();
            game->ScorePlayer2 ++;
        }
        if(!Player2.getComponent<SpriteComponent>().alive)
        {
            game->ResetGame();
            game->ScorePlayer1 ++;
        }
        
    }
    game->clean();
    cout << game->ScorePlayer1 << " - " << game->ScorePlayer2 << endl;
    delete game;
    return 0;
}



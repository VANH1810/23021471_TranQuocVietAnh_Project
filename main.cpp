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
        game->handleEvents();
        frameStart = SDL_GetTicks();
        if (game->gamestate != GameState::PAUSED)
        {
            game->update(); 
            game->Render();
        }

        frameTime = SDL_GetTicks() - frameStart;
        if(frameDelay > frameTime)
            SDL_Delay(frameDelay - frameTime);
        if(game->NumberOfPlayers == 2) 
        {   
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
        else if(game->NumberOfPlayers == 3)
        {
            if (!Player1.getComponent<SpriteComponent>().alive && !Player2.getComponent<SpriteComponent>().alive) 
            {
                game->ResetGame();
                game->ScorePlayer3 ++;
            }
            else if(!Player2.getComponent<SpriteComponent>().alive && !Player3.getComponent<SpriteComponent>().alive)
            {
                game->ResetGame();
                game->ScorePlayer1 ++;
            }
            else if(!Player3.getComponent<SpriteComponent>().alive && !Player1.getComponent<SpriteComponent>().alive)
            {
                game->ResetGame();
                game->ScorePlayer2 ++;
            }
            
        }
               
    }
    
    game->clean();
    if(game->NumberOfPlayers == 2)
        cout << game->ScorePlayer1 << " - " << game->ScorePlayer2 << endl;
    else if(game->NumberOfPlayers == 3)
        cout << game->ScorePlayer1 << " - " << game->ScorePlayer2 << " - " << game->ScorePlayer3 << endl;

    delete game;
    return 0;
}



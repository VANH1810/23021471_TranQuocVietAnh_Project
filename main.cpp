#include "game.cpp"

signed main(int argc, char* argv[])
{

    Game *game = new Game();

    Uint32 frameStart;
    int frameTime;
    float timeSinceLastSpawn = 0.0f;
    const float spawnInterval = 5.0f; 

    Uint32 resetTime = 0;

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

        
        if(game->NumberOfPlayers == 2) 
        {   
            if (!Player1.getComponent<SpriteComponent>().alive) 
            {
                game->gamestate == GameState::WINNING_TIME;
                if(resetTime == 0)
                    resetTime = SDL_GetTicks();
                
                else if(SDL_GetTicks() - resetTime > 3000)
                {
                    game->ScorePlayer2 ++;
                    game->ResetGame();
                    resetTime = 0;
                }
                
            }
            else if(!Player2.getComponent<SpriteComponent>().alive)
            {
                game->gamestate == GameState::WINNING_TIME;
                if(resetTime == 0)
                    resetTime = SDL_GetTicks();
                else if(SDL_GetTicks() - resetTime > 3000)
                {
                    game->ScorePlayer1 ++;
                    game->ResetGame();
                    resetTime = 0;
                }
                
            }
        }
        else if(game->NumberOfPlayers == 3)
        {
            if (!Player1.getComponent<SpriteComponent>().alive && !Player2.getComponent<SpriteComponent>().alive) 
            {
                game->gamestate == GameState::WINNING_TIME;
                if(resetTime == 0)
                {
                    resetTime = SDL_GetTicks();
                }
                else if(SDL_GetTicks() - resetTime > 3000)
                {
                    game->ScorePlayer3 ++;
                    game->ResetGame();
                    resetTime = 0;
                }
            
            }
            else if(!Player2.getComponent<SpriteComponent>().alive && !Player3.getComponent<SpriteComponent>().alive)
            {
                game->gamestate == GameState::WINNING_TIME;
                if(resetTime == 0)
                {
                    resetTime = SDL_GetTicks();
                }
                else if(SDL_GetTicks() - resetTime > 3000)
                {
                    game->ScorePlayer1 ++;
                    game->ResetGame();
                    resetTime = 0;
                }
            }
            else if(!Player3.getComponent<SpriteComponent>().alive && !Player1.getComponent<SpriteComponent>().alive)
            {
                game->gamestate == GameState::WINNING_TIME;
                if(resetTime == 0)
                {
                    resetTime = SDL_GetTicks();
                }
                else if(SDL_GetTicks() - resetTime > 3000)
                {
                    game->ScorePlayer2 ++;
                    game->ResetGame();
                    resetTime = 0;
                }

            }
            
        }
               
    }
    
    game->clean();
    delete game;
    return 0;
}



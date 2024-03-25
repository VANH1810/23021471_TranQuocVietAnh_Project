#include "game.cpp"
#include "GameState.hpp"
signed main(int argc, char* argv[])
{
    //Khởi tạo môi trường đồ họa
    Game *game = new Game();
    GameState gameState = GameState::START_SCREEN;
    Uint32 frameStart;
    int frameTime;

    game->preload();
    SDL_Texture* startScreenTexture = TextureManager::LoadTexture("assets/startScreen.jpg", game->renderer);
    while(game->running())
    {
        switch (gameState)
        {
            case GameState::START_SCREEN:

                SDL_Event event;
                while (SDL_PollEvent(&event)) 
                {   
                    if(event.type == SDL_KEYDOWN)
                    {
                        switch(event.key.keysym.sym)
                        {
                            case SDLK_SPACE:
                                gameState = GameState::PLAYING;
                                break;
                            default:
                                break;
                        }
                    }
                }
                SDL_RenderClear(game->renderer);
                SDL_RenderCopy(game->renderer, startScreenTexture, nullptr, nullptr);
                SDL_RenderPresent(game->renderer);
                break;
            case GameState::PLAYING:
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
                break;

            default:
                break;
        }
    }
    game->clean();
    cout << game->ScorePlayer1 << " - " << game->ScorePlayer2 << endl;
    delete game;
    return 0;
}



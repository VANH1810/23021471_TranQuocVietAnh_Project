#pragma once

#include "ECS.hpp"
#include "../TextureManager.hpp"
#include "../AudioManager.cpp"
class RocketComponent
{
    private:
        SDL_Texture *rocketTexture;
        SDL_Texture *explosionTexture;
        SDL_Rect rocketsrcRect;
        SDL_Renderer *renderer;
        SDL_Rect explosiondestRect;
        SDL_Rect explosionsrcRect;
        Map* map;
        float speed;
        float timeAlive;

        Mix_Chunk *soundEffect;

        struct CellInfo 
        {
            int x, y;
            CellInfo* prevCell;

            CellInfo(int x, int y, CellInfo* prevCell) : x(x), y(y), prevCell(prevCell) {}
            bool operator!=(const CellInfo& other) const {
                return x != other.x || y != other.y;
            }
        };

        vector<int> dx = {64, -64, 0, 0, 64, -64, 64, -64}; 
        vector<int> dy = {0, 0, 64, -64, 64, 64, -64, -64}; 
        vector<pair<int, int>> path;
        int pathIndex = 0;
        int frameCount;

    public:
        SDL_Rect rocketdestRect;
        bool isMove;
        float direction;
        int targetX, targetY;

        ~RocketComponent() = default;
        RocketComponent(SDL_Texture *rocketImage,  SDL_Texture *explosionImage, SDL_Renderer *ren, float mSpeed, Map* mapdata, Mix_Chunk *_soundEffect, float time_alive)
        {
            rocketTexture = rocketImage;
            renderer = ren;
            speed = mSpeed;
            map = mapdata;
            rocketsrcRect.x = 44;
            rocketsrcRect.y = 46;
            rocketsrcRect.w = 40;
            rocketsrcRect.h = 37;
            rocketdestRect.w = rocketsrcRect.w / SCALEDOWN;
            rocketdestRect.h = rocketsrcRect.h / SCALEDOWN;
            explosionsrcRect.x = 0;
            explosionsrcRect.y = 0;
            explosionsrcRect.w = 256;
            explosionsrcRect.h = 256;
            explosiondestRect.w = explosionsrcRect.w / SCALEDOWN;
            explosiondestRect.h = explosionsrcRect.h / SCALEDOWN;
            isMove = true;

            explosionTexture = explosionImage;
            timeAlive = time_alive;

            soundEffect = _soundEffect;
            AudioManager::PlaySound(soundEffect);

            frameCount = 0;
            
        }
        bool isValid(int xpos, int ypos)
        {
            int x = xpos* SCALEDOWN / map->tileWidth;
            int y = ypos* SCALEDOWN / map->tileHeight;
            if(x <= 0 || x >= map->mapWidth || y <= 0 || y >= map->mapHeight) return false;
            for (auto layer: map->layers)
            {
                if (layer->layerType != "tilelayer") continue;
                int id = layer->tileLayer->getId(y, x);
                if (map->tileSet->tiles[id]->isCollidable)
                    return false;  
            }
            
            return true;
        }
        bool canMoveDiagonally(int x, int y, int dx, int dy)
        {
            // Kiểm tra xem liệu ô (x, y) có nằm trong không gian chơi hay không
            if (x + dx < 0 || x + dx >= 1536 || y + dy < 0 || y + dy >= 1536) {
                return false;
            }

            // Kiểm tra xem liệu ô kề cạnh (x, y) theo hướng chéo có bị chặn hay không
            // Bạn cần thay thế `isBlocked` bằng hàm thực sự kiểm tra xem liệu một ô có bị chặn hay không
            if (!isValid(x + dx, y) || !isValid(x, y + dy) || !isValid(x + dx, y + dy)) {
                return false;
            }

            return true;
        }

        vector<pair<int, int>> findPathToTarget(int startX, int startY, int targetX, int targetY)
        {
           
            queue<CellInfo*> q;
            bool found = false;
           
            vector<vector<bool>> visited(1536, vector<bool>(1536, false));
            CellInfo* startCell = new CellInfo(startX, startY, nullptr);
            CellInfo* targetCell = nullptr; 
           
            visited[startX][startY] = true;
            q.push(startCell);
            
            while (!q.empty())
            {
                CellInfo* current = q.front();
                q.pop();
                
                int distance = sqrt((current->x - targetX) * (current->x - targetX) + (current->y - targetY) * (current->y - targetY));
                if (distance <= 64) {
                    targetCell = current;   
                    found = true;
                    break;
                }
                
                for (int i = 0; i < 8; ++i)
                {
                    int nextX = current->x + dx[i];
                    int nextY = current->y + dy[i];
                    if (canMoveDiagonally(current->x, current->y, dx[i], dy[i]) && !visited[nextX][nextY])
                    {
                        visited[nextX][nextY] = true;
                        CellInfo* nextCell = new CellInfo(nextX, nextY, current);
                        q.push(nextCell);
                    }
                }
            }
            if (found) 
            {
                vector<pair<int, int>> path;
                for (CellInfo* cell = targetCell; cell->prevCell != nullptr; cell = cell->prevCell) 
                {
                    path.push_back(make_pair(cell->x, cell->y));
                }
                path.push_back(make_pair(startX, startY)); 
                reverse(path.begin(), path.end()); 

                return path;
            }
    
            return {};
        }
        
        void update() {
            targetX = 1440;
            targetY = 1440; 
            frameCount++;
            if(path.empty() || frameCount % 3 == 0)
            {   
                path.clear();
                path = findPathToTarget(rocketdestRect.x, rocketdestRect.y, targetX, targetY);
                pathIndex = 0;
            }
            if (!path.empty() && isMove)
            {
                int nextX = path[pathIndex].first;
                int nextY = path[pathIndex].second;
                float direction_x = nextX - rocketdestRect.x;
                float direction_y = nextY - rocketdestRect.y;
                float length = std::sqrt(direction_x * direction_x + direction_y * direction_y);

                // Normalize direction vector
                if (length > 0) {
                    direction_x /= length;
                    direction_y /= length;
                }

                rocketdestRect.x += (float)(direction_x * speed);
                rocketdestRect.y += (float)(direction_y * speed);
                
                float distanceToNextWaypoint = sqrt((nextX - rocketdestRect.x)*(nextX - rocketdestRect.x) + (nextY - rocketdestRect.y)*(nextY - rocketdestRect.y));
                if (distanceToNextWaypoint < 10.0) {
                    cerr << pathIndex << endl;
                    rocketdestRect.x = nextX;
                    rocketdestRect.y = nextY;
                    pathIndex++;

                    if (pathIndex >= path.size()) {
                        
                        path.clear();
                        pathIndex = 0;
                        isMove = false;
                    }
                }
            }
            
    
        }

        
        void draw () 
        {
            if(!isMove)
            {
                explosiondestRect.x = rocketdestRect.x - 64;
                explosiondestRect.y = rocketdestRect.y - 64;
                SDL_RenderCopy(renderer, explosionTexture, &explosionsrcRect, &explosiondestRect);
            }
            else if(isMove)
            {
                SDL_Point rocketCenter = {rocketdestRect.w / 2, rocketdestRect.h / 2}; // Rotation center
                SDL_RenderCopyEx(renderer, rocketTexture, &rocketsrcRect, &rocketdestRect, direction, &rocketCenter, SDL_FLIP_NONE);
            }
        }

        
};


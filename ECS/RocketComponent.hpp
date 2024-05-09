#pragma once

#include "ECS.hpp"
#include "../Class/TextureManager.hpp"
#include "../Class/AudioManager.cpp"
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
        float angle;

        Mix_Chunk *soundEffect;

        struct CellInfo 
        {
            int x, y;
            CellInfo* prevCell;

            CellInfo(int x, int y, CellInfo* prevCell) : x(x), y(y), prevCell(prevCell) {}
            
            bool operator!=(const CellInfo& other) const 
            {
                return x != other.x || y != other.y;
            }
        };

        vector<int> dx = {tileWidth, -tileWidth, 0, 0, tileWidth, tileWidth, tileWidth, -tileWidth}; 
        vector<int> dy = {0, 0, tileHeight, -tileHeight, tileHeight, tileHeight, -tileHeight, -tileHeight};  
        vector<pair<int, int>> path;
        int pathIndex = 0;
        int frameCount;

        double heuristic(int x1, int y1, int x2, int y2) 
        {
            // Octile distance
            int dx = abs(x1 - x2);
            int dy = abs(y1 - y2);
            double D = 1.0; // Cost of horizontal/vertical movement
            double D2 = sqrt(2); // Cost of diagonal movement
            return D * (dx + dy) + (D2 - 2 * D) * min(dx, dy);
        } 
        struct CellInfo2 
        {
            int x, y;
            float g; // cost from start node to current node
            float h; // estimated cost from current node to target node
            float f; // total cost (costF = costG + costH)
            CellInfo2* prevCell;

            CellInfo2(int x, int y, CellInfo2* prevCell, float g, float h) : x(x), y(y), prevCell(prevCell), g(g), h(h), f(g + h) {}    
        };

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
    
            if(x <= 0 || x >= mapWidth || y <= 0 || y >= mapHeight) return false;
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
          
            if (x + dx < 0 || x + dx >= mapWidth || y + dy < 0 || y + dy >= mapHeight) {
                return false;
            }

            if (!isValid(x + dx, y) || !isValid(x, y + dy) || !isValid(x + dx, y + dy)) {
                return false;
            }

            return true;
        }

        // BFS Algorithm
        vector<pair<int, int>> findPathToTarget(int startX, int startY, int targetX, int targetY)
        {
            if(targetX < 0 || targetX >= mapWidth || targetY < 0 || targetY >= mapHeight) return {};
            queue<CellInfo*> q;
            bool found = false;
            
            vector<vector<bool>> visited(mapHeight, vector<bool>(mapWidth, false));
            vector<CellInfo*> allCells;
            CellInfo* startCell = new CellInfo(startX, startY, nullptr);
            CellInfo* targetCell = nullptr; 

            allCells.push_back(startCell);
           
            visited[startX][startY] = true;
            q.push(startCell);
            
            while (!q.empty())
            {
                CellInfo* current = q.front();
                q.pop();
                
                int distance = sqrt((current->x - targetX) * (current->x - targetX) + (current->y - targetY) * (current->y - targetY));
                if (distance <= 64) 
                {
                    targetCell = current;   
                    found = true;
                    break;
                }
                
                for (int i = 0; i < (int) dx.size(); ++i)
                {
                    int nextX = current->x + dx[i];
                    int nextY = current->y + dy[i];
                    if (canMoveDiagonally(current->x, current->y, dx[i], dy[i]) && !visited[nextX][nextY])
                    {
                        visited[nextX][nextY] = true;
                        CellInfo* nextCell = new CellInfo(nextX, nextY, current);
                        allCells.push_back(nextCell);
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
                for (CellInfo* cell : allCells) 
                    delete cell;
                return path;
            }
            else
            {
                for (CellInfo* cell : allCells) 
                    delete cell;
            }
    
            return {};
        }
        // A* Algorithm
        vector<pair<int, int>> findPathToTarget2(int startX, int startY, int targetX, int targetY) 
        {
            if(targetX < 0 || targetX >= mapWidth || targetY < 0 || targetY >= mapHeight) return {};
            auto compare = [](const CellInfo2* a, const CellInfo2* b) 
            {
                return a->f > b->f;
            };
            priority_queue<CellInfo2*, vector<CellInfo2*>, decltype(compare)> openList(compare);
            vector<vector<bool>> closedList(mapHeight, vector<bool>(mapWidth, false));

            vector<CellInfo2*> allCells;
            CellInfo2* startCell = new CellInfo2(startX, startY, nullptr, 0, heuristic(startX, startY, targetX, targetY));
            CellInfo2* targetCell = nullptr;
            allCells.push_back(startCell);
            openList.push(startCell);
            bool found = false;

            while (!openList.empty()) 
            {
                CellInfo2* current = openList.top();
                openList.pop();

                int distance = sqrt((current->x - targetX) * (current->x - targetX) + (current->y - targetY) * (current->y - targetY));
                if (distance <= 64) {
                    targetCell = current; 
                    found = true;
                    break; 
                }

                closedList[current->x][current->y] = true;

                for (int i = 0; i < dx.size(); ++i) {
                    int nextX = current->x + dx[i];
                    int nextY = current->y + dy[i];

                    if (canMoveDiagonally(current->x, current->y, dx[i], dy[i]) && !closedList[nextX][nextY]) 
                    {
                        int tentative_g = current->g + 1; // Assuming each move has cost 1
                        int tentative_f = tentative_g + heuristic(nextX, nextY, targetX, targetY);
                        CellInfo2* neighbor = new CellInfo2(nextX, nextY, current, tentative_g, tentative_f);
                        allCells.push_back(neighbor);

                        if (!closedList[nextX][nextY]) 
                        {
                            openList.push(neighbor);
                        } 
                        else if (tentative_f < neighbor->f) 
                        {
                            // Update neighbor's values
                            neighbor->prevCell = current;
                            neighbor->g = tentative_g;
                            neighbor->f = tentative_f;
                        }
                    }
                }
            }

            if (found) 
            {
                vector<pair<int, int>> path;
                CellInfo2* current = targetCell;
                while (current != nullptr) {
                    path.push_back(make_pair(current->x, current->y));
                    current = current->prevCell;
                }
                reverse(path.begin(), path.end());
                for (CellInfo2* cell : allCells) 
                    delete cell;
                
                return path;
            }
            else
            {
                for (CellInfo2* cell : allCells) 
                    delete cell;
            }

            return {}; // No path found
        }
        
        void update() 
        {
            frameCount++;
            if(path.empty() || frameCount % 10 == 0)
            {   
                path.clear();
                path = findPathToTarget(rocketdestRect.x, rocketdestRect.y, targetX, targetY);
                pathIndex = 0;
                if(path.empty()) isMove = false;
            }
            
            if(!path.empty() && isMove)
            {
                int nextX = path[pathIndex].first;
                int nextY = path[pathIndex].second;
                float direction_x = nextX - rocketdestRect.x;
                float direction_y = nextY - rocketdestRect.y;
                float length = sqrt(direction_x * direction_x + direction_y * direction_y);

                // Normalize direction vector
                if (length > 0) {
                    direction_x /= length;
                    direction_y /= length;
                }
                angle = atan2(direction_y, direction_x) * 180 / M_PI;

                rocketdestRect.x += (float)(direction_x * speed);
                rocketdestRect.y += (float)(direction_y * speed);
                
                float distanceToNextWaypoint = sqrt((nextX - rocketdestRect.x)*(nextX - rocketdestRect.x) + (nextY - rocketdestRect.y)*(nextY - rocketdestRect.y));
                if (distanceToNextWaypoint < (map->tileWidth / SCALEDOWN) / 4) {
                
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
                explosiondestRect.x = rocketdestRect.x - map->tileWidth / SCALEDOWN;
                explosiondestRect.y = rocketdestRect.y - map->tileHeight / SCALEDOWN;
                SDL_RenderCopy(renderer, explosionTexture, &explosionsrcRect, &explosiondestRect);
            }
            else if(isMove)
            {
                SDL_Point rocketCenter = {rocketdestRect.w / 2, rocketdestRect.h / 2}; // Rotation center
                SDL_RenderCopyEx(renderer, rocketTexture, &rocketsrcRect, &rocketdestRect, angle, &rocketCenter, SDL_FLIP_NONE);
            }
        }
  
};


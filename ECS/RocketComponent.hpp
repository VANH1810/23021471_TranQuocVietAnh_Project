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
            int x, y; // Vị trí của ô
            int distance; // Khoảng cách từ điểm bắt đầu
            int parentX, parentY; // Thông tin về ô cha
            bool operator!=(const CellInfo& other) const {
                return x != other.x || y != other.y;
            }
        };
    public:
        SDL_Rect rocketdestRect;
        bool isMove;
        float direction;
        vector<int> dx = {64, -64, 0, 0}; 
        vector<int> dy = {0, 0, 64, -64}; 
        vector<pair<int, int>> path; // Lưu trữ đường đi
        size_t pathIndex = 0; // Lưu trữ chỉ số của ô tiếp theo trên đường đi
        int frameCount;

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
        bool isValid(int x, int y)
        {
            x = x* SCALEDOWN / map->tileWidth;
            y = y* SCALEDOWN / map->tileHeight;
            if (x >= 0 && x < mapWidth && y >= 0 && y < mapHeight)
            {
                for (auto layer: map->layers)
                    {
                        if (layer->layerType != "tilelayer") continue;
                        int id = layer->tileLayer->getId(y, x);
                        if (!map->tileSet->tiles[id]->isCollidable)
                        {
                            return true;
                        }
                        
                    }
            }
            return false;
        }

        vector<pair<int, int>> findPathToTarget(int startX, int startY, int targetX, int targetY)
        {
            // Tạo một hàng đợi để lưu trữ các ô cần duyệt
            queue<CellInfo> q;
            bool found = false;
            // Khởi tạo mảng để đánh dấu các ô đã duyệt
            vector<vector<bool>> visited(1536, vector<bool>(1536, false));
            vector<vector<CellInfo>> prevCell(1536, vector<CellInfo>(1536));
            // Đánh dấu điểm bắt đầu đã được duyệt và thêm nó vào hàng đợi
            visited[startX][startY] = true;
            q.push({startX, startY, 0, startX, startY});
            
            // Duyệt hàng đợi
            while (!q.empty())
            {
                CellInfo current = q.front();
                q.pop();
                
                // Nếu đạt được điểm đích, thoát khỏi vòng lặp
                int distance = sqrt((current.x - targetX) * (current.x - targetX) + (current.y - targetY) * (current.y - targetY));
                if (distance <= 64) {
                    targetX = current.x;
                    targetY = current.y;
                    found = true;
                    break;
                }
                
                // Duyệt các ô lân cận của ô hiện tại
                for (int i = 0; i < 4; ++i)
                {
                    int nextX = current.x + dx[i];
                    int nextY = current.y + dy[i];
                    
                    // Kiểm tra xem ô tiếp theo có hợp lệ không và chưa được duyệt
                    if (isValid(nextX, nextY) && !visited[nextX][nextY])
                    {
                        visited[nextX][nextY] = true;
                        q.push({nextX, nextY, current.distance + 1, current.x, current.y});
                        prevCell[nextX][nextY] = {current.x, current.y};
                    }
                }
            }
            if (found) 
            {
                CellInfo startCell = {startX, startY, 0, startX, startY};
                CellInfo targetCell = {targetX, targetY};
                
                vector<pair<int, int>> path;
                for (CellInfo cell = targetCell; cell != startCell; cell = prevCell[cell.x][cell.y]) {
                    path.push_back({cell.x, cell.y});
                }
                path.push_back(make_pair(startCell.x, startCell.y)); // Đảm bảo bắt đầu cũng được bao gồm
                //if (path.size() > 5)  path.erase(path.begin() + 5, path.end());
                reverse(path.begin(), path.end()); // Đảo ngược đường đi vì chúng ta đã xây dựng nó từ cuối đến đầu
                
                return path;
            }
    
            
            return {};
        }
        
        void update() {
            int targetX = 1440, targetY = 1440; // Vị trí mục tiêu mới
            frameCount++;
            if(path.empty())
            {
                path = findPathToTarget(rocketdestRect.x, rocketdestRect.y, targetX, targetY);
                for(auto x:path) cout << x.first << " " << x.second << endl;    
                pathIndex = 0;
            }
            if (!path.empty())
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
                

                //float distanceToTarget = std::sqrt((targetX - rocketdestRect.x) * (targetX - rocketdestRect.x) + (targetY - rocketdestRect.y) * (targetY - rocketdestRect.y));
                //float moveStep = std::min(distanceToTarget, static_cast<float>(64));
                //dx[0] = moveStep;
                //dx[1] = -moveStep;
                //dy[2] = moveStep;
                //dy[3] = -moveStep;
                // Normalize direction vector

                // Cập nhật hướng đi của viên đạn
                //direction = atan2(direction_y, direction_x) * (180 / M_PI);

                // Cập nhật vị trí của viên đạn với một bước di chuyển cố định
               
                rocketdestRect.x += static_cast<int>(direction_x * speed);
                rocketdestRect.y += static_cast<int>(direction_y * speed);
                
                float distanceToNextWaypoint = std::sqrt(std::pow(nextX - rocketdestRect.x, 2) + std::pow(nextY - rocketdestRect.y, 2));
                if (distanceToNextWaypoint < 1.0) {
                    // Update position to waypoint and move to next waypoint
                    rocketdestRect.x = nextX;
                    rocketdestRect.y = nextY;
                    pathIndex++;

                    if (pathIndex >= path.size()) {
                        // Clear path if reached end
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





#include <SDL2/SDL.h>
#include <random>
#include <algorithm>
#include <iostream>

int main()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "2" );
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_CreateWindowAndRenderer(960*4,500*4,0, &window, &renderer);
    SDL_RenderSetScale(renderer,4,4);
    //SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
    

    std::random_device rd;
    std::uniform_int_distribution<int> d(0,960);

    std::vector<SDL_Point> vp;

    //Take three points in a plane to form a triangle, you need not draw it.
    vp.push_back({960/2,0});
    vp.push_back({0,500});
    vp.push_back({960,500});

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    // Randomly select any point inside the triangle and consider that your current position.
    auto random_point = SDL_Point{d(rd), d(rd)};

    int delay = 10;

    std::vector<SDL_Point> collection;
    for(int i = 0; i < 10000000; i++)
    {
        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        SDL_RenderClear(renderer);
        // Randomly select any one of the three vertex points.
        auto second = vp[rand()%vp.size()];
        
        // Move half the distance from your current position to the selected vertex.
        auto midpoint = SDL_Point{(random_point.x + second.x) / 2, (random_point.y + second.y) / 2};
        
        SDL_SetRenderDrawColor(renderer,55,55,55,255);
        SDL_RenderDrawLine(renderer, random_point.x,random_point.y, second.x, second.y);
        SDL_Delay(delay);

        SDL_SetRenderDrawColor(renderer,255,255,255,255);
        SDL_RenderDrawPoint(renderer, random_point.x,random_point.y);
        SDL_Delay(delay);

        // Plot the current position.
        collection.push_back(midpoint);
        SDL_RenderDrawPoints(renderer, collection.data(), static_cast<int>(collection.size()));
        random_point = midpoint;
        SDL_RenderPresent(renderer);
        if(delay > 0)
        {
            delay -= 1;
            if(delay > 500)
            {
                delay -= 250;
            }
        }

    }

    
    

    SDL_Delay(12500);
}
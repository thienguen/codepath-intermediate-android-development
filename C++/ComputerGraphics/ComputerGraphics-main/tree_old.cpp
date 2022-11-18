#include <SDL2/SDL.h>
#include <numeric>
#include <complex>
#include <iostream>

/*
Compile
g++ -lSDL2 tree.cpp && ./a.out
*/

double vlength(const SDL_FPoint origin)
{
    return std::sqrt(origin.x * origin.x + origin.y * origin.y);
}

SDL_FPoint scale(SDL_FPoint point, float factor)
{
    return SDL_FPoint { 
        static_cast<float>(point.x * factor),
        static_cast<float>(point.y * factor)
    };
}

float rot = 0.0123599;
void draw_line(
    SDL_Renderer* renderer, 
    SDL_FPoint origin, 
    double rotation, 
    float depth, 
    float max)
{
    if(depth > max) return;
    
    // Get length of original point
    //
    float length = vlength(origin);
    
    // Create scaled points
    //
    SDL_FPoint origin = scale(origin, 0.1);
    SDL_Point scaled_point{
        origin.x + origin.x/10 * (length * (0.1f/depth)), // position x
        origin.y + origin.y/10 * (length * (0.1f/depth))  // position y
    };

    

    // Rotation 
    //
    auto new_x = (cos(rotation) * (scaled_point.x - origin.x) - 
                  sin(rotation) * (scaled_point.y - origin.y)) + origin.x;
    auto new_y = (sin(rotation) * (scaled_point.x - origin.x) + 
                  cos(rotation) * (scaled_point.y - origin.y)) + origin.y;

    SDL_FPoint new_point{new_x,new_y};

    // Colour
    //
    if((depth) == max)
        SDL_SetRenderDrawColor(renderer,255,0,0,255);
    else
        //SDL_SetRenderDrawColor(renderer, rand() % 255,rand() % 255,rand() % 255,255);
        SDL_SetRenderDrawColor(renderer, 
            25 * depth + 25,
            25 * depth + 25, 
            25 * depth + 25, 
            255);

    SDL_RenderDrawLineF(renderer, origin.x, origin.y, new_point.x, new_point.y);
    
    // a fucking leaf
    //
    draw_line(renderer, new_point,  rotation+rot, depth+1, max);
    draw_line(renderer, new_point,  rotation-rot, depth+1, max);

}

int main()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_CreateWindowAndRenderer(1000*2,1000*2,0, &window, &renderer);
    //SDL_RenderSetScale(renderer,2,2);
    int max = 1;
    rot = 0.00;
    while(true)
    {
        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer,255,255,255,255);
        draw_line(renderer, SDL_FPoint{1000,1999}, 0.0, 1, max);
        SDL_RenderPresent(renderer);
        SDL_Delay(320);
        max +=1;
        rot += 0.01;

        if(rot > 3.81)
            rot = 0.01;

        if(max > 10)
            max = 10;
    }
    SDL_Delay(10000);
}

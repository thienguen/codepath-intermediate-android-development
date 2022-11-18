#include <SDL2/SDL.h>
#include <numeric>
#include <complex>
#include <iostream>

/*
Compile
g++ -lSDL2 tree.cpp && ./a.out
*/

SDL_FPoint scale(SDL_FPoint vector, float scale)
{
    return SDL_FPoint{vector.x * scale, vector.y * scale};
}

float length(const SDL_FPoint origin)
{
    return std::sqrt(origin.x * origin.x + origin.y * origin.y);
}

SDL_FPoint rotate_around_by(SDL_FPoint origin, SDL_FPoint center, float rotation)
{
    auto new_x = (cos(rotation) * (origin.x - center.x) - sin(rotation) * (origin.y - center.y)) + center.x;
    auto new_y = (sin(rotation) * (origin.x - center.x) + cos(rotation) * (origin.y - center.y)) + center.y;
    
    return SDL_FPoint{new_x, new_y};
}

float rot = static_cast<float>(2.0123599);
void draw_line(SDL_Renderer* renderer, SDL_FPoint origin, double rotation, float depth, float max)
{
    if(depth > max) return;
    
    // Get length of original point
    //
    float origin_length = length(origin);
    
    // Create scaled points
    //
    SDL_FPoint scaled_point = scale(origin, 0.5);

    // Rotation 
    //
    auto new_point = rotate_around_by(scaled_point, origin, rotation);

    // Colour
    //
    if((depth) == max)
        SDL_SetRenderDrawColor(renderer,255,0,0,255);
    else
        //SDL_SetRenderDrawColor(renderer, rand() % 255,rand() % 255,rand() % 255,255);
        SDL_SetRenderDrawColor(renderer, 25 * depth + 25, 25 * depth + 25, 25 * depth + 25, 255);

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

    int depth = 5;
    rot = 0.00;
    
    while(true)
    {
    
        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer,255,255,255,255);
        
        draw_line(renderer, SDL_FPoint{1000,1999}, 0.0, 1, depth);
        
        SDL_RenderPresent(renderer);
        SDL_Delay(320);
    
    }
    
    SDL_Delay(10000);
}

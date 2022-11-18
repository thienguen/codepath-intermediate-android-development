#include "screen.h"
#include "math.h"
#include <random>
#include <ranges>
#include <algorithm>

void draw_state(std::vector<int>& v, SDL_Renderer* renderer, long red, long blue)
{
    int current_x = 0;
    for(int i : v)
    {
        if(current_x == red) 
            SDL_SetRenderDrawColor(renderer,255,0,0,255);
        else if(current_x == blue)     
            SDL_SetRenderDrawColor(renderer,0,0,255,255);
        else
            SDL_SetRenderDrawColor(renderer,255,255,255,255);

        SDL_RenderDrawLine(renderer,current_x,99,current_x,i);
        current_x+=1;
    }
}

int main()
{
    std::random_device rd;
    std::uniform_int_distribution<int> d(1,99);
    std::vector<int> v;
    for(int i = 0; i < 100; i++)
    {
        v.push_back(d(rd));
    }

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_CreateWindowAndRenderer(100*10,100*10,0,&window, &renderer);
    SDL_RenderSetScale(renderer,10,10);
    
    for(unsigned int i = 0; i < v.size(); i++)
    {
        for(unsigned int j = i; j < v.size(); j++)
        {
            if(v[j] < v[i])
            {
                std::swap(v[j],v[i]);
            }
            SDL_SetRenderDrawColor(renderer,0,0,0,255);
            SDL_RenderClear(renderer);
            draw_state(v,renderer,j, i);
            SDL_RenderPresent(renderer);
            SDL_Delay(8);
        }    
    }
    for(int i : v)
    {
        std::cout << i << " ";
    }
    std::cout << "\n";
    if(std::ranges::is_sorted(v)) { std::cout << "sorted"; }
    SDL_Delay(2000);
}

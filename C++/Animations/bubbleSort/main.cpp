#include <SDL2/SDL.h>
#include "math.h"
#include <random>
#include <algorithm>
#include <iostream>
#include <ranges>

#define main SDL_main

std::vector<int> generateRandomVector(int size, int min, int max)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    std::vector<int> vec(size);
    std::generate(vec.begin(), vec.end(), [&] 
    { 
        return dis(gen); 
    });
    return vec;
}

void draw_state(std::vector<int> &v, SDL_Renderer *renderer, long red, long blue)
{
    int current_x = 0;
    for (int i : v)
    {
        if (current_x == red)
        {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        }
        else if (current_x == blue)
        {
            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        }
        else
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        }

                            ///* Bars *///
        SDL_RenderDrawLine(renderer, current_x, 99, current_x, i);

                    ///* Scatter plot style *///
        // SDL_RenderDrawLine(renderer, current_x, i, current_x, i);
        current_x += 1;
    }
}

int main(int argv, char **args)
{
    std::random_device rd;
    std::uniform_int_distribution<int> d(1, 99);
    std::vector<int> v;

    for (int i = 0; i < 100; i++)
    {
        v.push_back(d(rd));
    }

    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_CreateWindowAndRenderer(50 * 10, 50 * 10, 0, &window, &renderer);
    SDL_RenderSetScale(renderer, 10, 10);

    for (unsigned int i = 0; i < v.size(); i++)
    {
        for (unsigned int j = i; j < v.size(); j++)
        {
            if (v[j] < v[i])
            {
                std::swap(v[j], v[i]);
            }
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
            draw_state(v, renderer, j, i);
            SDL_RenderPresent(renderer);
            SDL_Delay(2);
        }
    }

    for (int i : v)
    {
        std::cout << i << " ";
    }

    std::cout << "\n";

    SDL_Delay(2000);
}
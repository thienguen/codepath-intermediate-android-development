#include <SDL2/SDL.h>
#include <cstdlib>
#include <iostream>
#include <time.h>  
#include <vector>
#include <tuple>
#include <algorithm> 
#include <utility>
#include <numeric>

#pragma once

/**
 *  \brief Creates a 640 by 480 window for rendering 
 */
class G {

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_bool done;
    std::vector<std::tuple<int, int>> points;
    SDL_Event event;
    public:
    G() 
    {
       SDL_Init(SDL_INIT_VIDEO); 
       SDL_CreateWindowAndRenderer(640*4, 480*4, 0, &window, &renderer);
       SDL_RenderSetScale(renderer,4,4);
    }
    ~G()
    {
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer);
        SDL_Quit();
    }

    void drawpixel(int xm, int ym) 
    {
        xm = std::clamp(xm,0,640-1);
        ym = std::clamp(ym,0,480-1);
        points.push_back( std::tuple<int,int>(xm,ym) );
    }
    void clearpixels()
    {
        points.clear();
    }

    void update() {

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

        for(auto& point : points) 
        {
            SDL_RenderDrawPoint(renderer, std::get<0>(point), std::get<1>(point));
        }
        SDL_RenderPresent(renderer);
    }

    void input() {
        while( SDL_PollEvent( &event ) )
        {  
            switch( event.type )
            {
                case SDL_QUIT: 
                    SDL_Quit(); 
                    exit(0); 
                    break;
            }
        }
    }

};
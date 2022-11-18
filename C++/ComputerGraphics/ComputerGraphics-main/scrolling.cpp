#include <SDL2/SDL.h>

const int WORLD_HEIGHT = 10000;
const int WORLD_WIDTH = WORLD_HEIGHT;

const int SCREEN_HEIGHT = 1000;
const int SCREEN_WIDTH = 1000;

/* Moving Rectangle */
int main()
{
        SDL_Event event;
        //SDL_Rect r{0,0,50,100};
        SDL_Rect canvas{0,0,500,500};
        double angle = 0;
        SDL_Init(SDL_INIT_EVERYTHING);
        
        auto window = SDL_CreateWindow(
            "SDL_CreateTexture", 
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
            SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);
        auto renderer = SDL_CreateRenderer(window, -1, 0);
        auto texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, WORLD_WIDTH, WORLD_HEIGHT);
        
        SDL_SetRenderTarget(renderer,texture);                            // draw to the texture
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);                   // clear the texture
        SDL_RenderClear(renderer);                                        // clear renderer 
                         
        
        for(int i = 0; i < 10000; i++)                                    // draw a bunch of pixels
        {
            // set draw color
            SDL_SetRenderDrawColor(renderer,255,255,255,255);
            SDL_RenderDrawPoint(renderer,rand()%10000, rand()%10000);
        }
        
        auto running = true;
        while (running) 
        {
            
                while(SDL_PollEvent(&event))
                {

                    if(event.type == SDL_QUIT)
                    {
                            running = false;
                    }

                    if(event.type == SDL_KEYDOWN)
                    {

                        if(event.key.keysym.sym == SDLK_0 && canvas.h > 0 && canvas.w > 0)
                        {
                            canvas.h -= 10;
                            canvas.w -= 10;
                        }

                        if(event.key.keysym.sym == SDLK_1)
                        {
                            canvas.h += 10;
                            canvas.w += 10;
                        }
                        
                        if(event.key.keysym.sym == SDLK_RIGHT)
                        {
                            canvas.x += 50;
                        }
                        
                        if(event.key.keysym.sym == SDLK_DOWN && canvas.y < 9000 )
                        {
                            canvas.y += 50;
                        }
                        
                        if(event.key.keysym.sym == SDLK_UP && canvas.y > 50)
                        {
                            canvas.y -= 50;
                        }
                        
                        if(event.key.keysym.sym == SDLK_LEFT && canvas.x > 50)
                        {
                            canvas.x -= 50;
                        }
                        if(event.key.keysym.sym == SDLK_MINUS)
                        {
                            angle+=1;
                        }

                    }
                }

                SDL_SetRenderTarget(renderer, NULL);                                            // clear render target
                SDL_RenderCopyEx(renderer, texture, &canvas, NULL,angle,nullptr,SDL_FLIP_NONE); // copy part of the texture to the renderer                                          // move the section to be copied to the right   
                SDL_RenderPresent(renderer);                                                    // show renderer to window
                SDL_Delay(10);    
        
        }
        SDL_DestroyRenderer(renderer);
        SDL_Quit();
        return 0;
}

#include "screen.h"
#include "math.h"
bool isAlive(int game[][480], int x, int y)
{
    int aliveNeighbors = 0;
    
    if(x > 0 && game[x-1][y] == 1) // left
    {
        aliveNeighbors += 1;
    }
    if(x < 639 && game[x+1][y] == 1) // right
    {
        aliveNeighbors += 1;
    }
    if(y > 0 && game[x][y-1] == 1) // top
    {
        aliveNeighbors += 1;
    }
    if(y < 479 && game[x][y+1] == 1) // bottom
    {
        aliveNeighbors += 1;
    }
    if(y > 0 && x > 0 && game[x-1][y-1] == 1) // top left
    {
        aliveNeighbors += 1;
    }
    if(y > 0 && x < 639 && game[x+1][y-1] == 1) // top right
    {
        aliveNeighbors += 1;
    }
    if(y < 479 && x > 0 && game[x-1][y+1] == 1) // bot left
    {
        aliveNeighbors += 1;
    }
    if(y < 479 && x < 639 && game[x+1][y+1] == 1) // bot right
    {
        aliveNeighbors += 1;
    }

    if(aliveNeighbors < 2)
        return false;
    if(game[x][y] == 0 && aliveNeighbors == 3)
        return true;
    if(game[x][y] == 1 &&  (aliveNeighbors == 2 || aliveNeighbors == 3))
        return true;
    if(aliveNeighbors >  3)
        return false;

    return false;     
}


int main()
{
    G screen;
    int game[640][480];
    int swap[640][480];

    // Generate
    for(int i = 0; i < 640; i+=1)
    {
        for(int k = 0; k < 480; k+=1)
        {
            game[i][k] = 0;    
            swap[i][k] = 0;        
        }
    }

    for(int i = 0; i < 640; i++)
    {
        float fi = (float)i/100;
        for(int j = 1; j < 20; j++)
        {
            float s = sin(fi) * static_cast<float>(j) + 200;
            game[i][(int)s] = 1;
        }
    }

    // Update
    //
    while(true)
    {

        // Calculate
        //
        for(int i = 0; i < 640; i+=1)
        {
            for(int k = 0; k < 480; k+=1)
            {
                if(isAlive(game, i,k)) 
                {
                    swap[i][k] = 1;
                }
                else 
                {
                    swap[i][k] = 0;
                }
            }
        }

        // Draw
        //
        for(int i = 0; i < 640; i+=1)
        {
            for(int k = 0; k < 480; k+=1)
            {
                if(swap[i][k])
                {
                    screen.drawpixel(i,k);
                }
            }
        }
        
        // Swap
        //
        for(int i = 0; i < 640; i+=1)
        {
            for(int k = 0; k < 480; k+=1)
            {
                game[i][k] = swap[i][k];
                swap[i][k] = 0;
            }
        }

        screen.update();
        SDL_Delay(20);
        screen.input();
        screen.clearpixels();
    }

    return 0;
}


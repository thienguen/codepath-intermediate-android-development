#include "screen.h"
#include "math.h"
using namespace std;
class Sand{
    public:
    int position_x;
    int position_y; 
    int id;
    int y_move_dir;
    int x_move_dir;

    Sand(int x, int y, int sid) 
    {
        position_x = x;
        position_y = y;
        id = sid;
        y_move_dir = 1;
        x_move_dir = 0;
    }

    bool isColliding(Sand& s, std::vector<Sand>& world)
    {
        if(s.position_y > 350) return true;

        for(Sand& sand : world)
        {
            
            if( sand.position_x == s.position_x && 
                sand.position_y == s.position_y && 
                sand.id != s.id)
            {
                return true;
            }
                
        }
        return false;
    }
    void update(std::vector<Sand>& world)
    {       meme:
            position_y += 1;
            if(isColliding(*this,world))
            {
                position_y -= 1;
            }
            else 
            {
                return;
            }

            if(rand()%2==0) 
            {
                // down left
                //
                position_y += 1;
                position_x -= 1;
                if(isColliding(*this,world))
                {
                    position_y -= 1;
                    position_x += 1;
                } 
                else 
                {
                    return;
                }
            }
            else 
            {
                // down right
                //
                position_y += 1;
                position_x += 1;
                if(isColliding(*this,world))
                {
                    position_y -= 1;
                    position_x -= 1;
                } 
                else 
                {
                    return;
                }
            }
            if(isColliding(*this,world))
            {
                goto meme;
            }

    }
};

int main()
{
    G screen;
    vector<Sand> world; 

    int id = 0;
    while(true)
    {

        // Add sand to world
        //
        if(rand()%2 == 0 and world.size() < 500)
        {
            world.emplace_back(320 + rand()%10-5,240,id);
            id = rand();
        }

        // Update sand
        //
        for(Sand& s : world)
        {
            s.update(world);
        }

        // Render sand
        //
        for(auto& s: world)
        {
            screen.drawpixel(s.position_x,s.position_y);
        }

        screen.update();
        SDL_Delay(20);
        screen.input();
        screen.clearpixels();
    
    }

    return 0;
}


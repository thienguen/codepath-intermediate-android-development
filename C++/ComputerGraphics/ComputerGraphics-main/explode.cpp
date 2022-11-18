#include "screen.h"
#include "math.h"


class Point
{
    SDL_FPoint position;
    SDL_FPoint direction;
    int alive_for;
    float velocity;
    int id = 0;
    Point()
    {
        position.x = static_cast<float>(rand() % 640);
        position.y = static_cast<float>(rand() % 480);
        alive_for = 999999;
        velocity = 1;
    }
};

class Sand{

public:
    float position_x;
    float position_y; 
    int alivefor;
    float direction_x;
    float direction_y;
    float velocity;
    int id = 0;

    Sand(float x, float y, int life, float dx, float dy, float vel,int uid) 
    {
        position_x = x;
        position_y = y;
        alivefor = life;
        direction_x = dx;
        direction_y = dy;
        velocity = vel;
        id = uid;
    }

    void update()
    {
        this->position_x +=  (this->direction_x * this->velocity);
        this->position_y +=  (this->direction_y * this->velocity);

        if(this->position_x > 640 || this->position_x < 0)
            this->direction_x = -(this->direction_x);

        if(this->position_y > 480 || this->position_y < 0)
            this->direction_y = -(this->direction_y);

        if(this->alivefor > 0)
        {
            this->alivefor-=1;
        }
    }
    bool isalive()
    {
        return this->alivefor > 0;
    }

};

class Explosion{
    public:
    float position_x;
    float position_y;
    int life;
    int size;
    int id;
    G* screen;
    Explosion(float x, float y, int lifetime, int uid, G* scr):
        position_x(x),
        position_y(y),
        life(lifetime),
        id(uid),
        screen(scr){}

    void update()
    {
        if(this->life > 0) {
            float d = 0.0;
            for(int i = 0; i < 63; i++) 
            {
                screen->drawpixel(
                    static_cast<int>(sin(d)) * size + static_cast<int>(position_x) , 
                    static_cast<int>(cos(d)) * size + static_cast<int>(position_y)
                );
                d+=0.1f;
            }
            size += 1;
            life -= 1;
        }
    }

};

bool areColiding(Sand& rhs, Sand& lhs)
{
    if( (int)rhs.position_y == (int)lhs.position_y &&
        (int)rhs.position_x == (int)lhs.position_x &&
        lhs.id != rhs.id
    )
    {
        return true;
    }
    else 
    {
        return false;
    }
}

int main()
{
    G screen;
    std::vector<Sand> world; 
    std::vector<Explosion> world_explosions;

    // Create all particles with random values
    //
    for(int i = 0; i < 100; i++)
        world.push_back(Sand(
           static_cast<float>(rand()%640),
           static_cast<float>(rand()%480),
           -1,
           static_cast<float>(sin(rand())),
           static_cast<float>(cos(rand())), 
           ((float)(rand() % 100) )/55,
           i)           
        );
    
    // Main loop
    while(true)
    {
        // Draw and update all objects
        //
        for(auto& w : world) 
        {
            screen.drawpixel(static_cast<int>(w.position_x), static_cast<int>(w.position_y));
            if(w.velocity > 0)
            {
                w.update();
            }
        }

        // Draw and update all explosions
        //
        for(auto& w : world_explosions) 
        {
            w.update();
        }

        // process particles
        //
        for(auto& w : world) 
            for(auto& m : world)
                if((m.velocity > 0 || w.velocity > 0) && areColiding(m,w))
                {
                    world_explosions.push_back(Explosion( w.position_x,w.position_y,60,rand(),&screen ));
                    m.velocity = 0;
                    w.velocity = 0;
                }

        // process explosions

        screen.update();
        SDL_Delay(20);
        screen.input();
        screen.clearpixels();
    }
    return 0;
}


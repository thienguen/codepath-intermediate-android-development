#include <chrono>
#include <cstdlib>
#include <iostream>
#include <ratio>
#include <algorithm>
#include <numeric>
#include "screen.h"
#include "math.h"

using namespace std::chrono_literals;
using std::chrono::high_resolution_clock;
using std::chrono::duration;

class Particle {

    public:

    // Particle has a starting time, direction and velocity only
    //
    high_resolution_clock::time_point creation_time;
    float direction;
    float velocity;
    
    // Initialize particle with random values
    //
    Particle() :
        creation_time(high_resolution_clock::now()),
        direction( static_cast<float>(2 * M_PI * rand() / RAND_MAX)),
        velocity(  static_cast<float>(rand() % 100)) 
    {
        
    }

    void draw(G &screen) {

        // Determine how far away the particle should be now
        //
        auto now = high_resolution_clock::now();
        float distance = duration<float>(now - creation_time).count() * velocity;

        if (distance < 0) return;

        screen.drawpixel(
            static_cast<int>(distance * sin(direction) + 320),
            static_cast<int>(distance * cos(direction) + 240)
        );

        // Reset particle
        //
        if (distance > 200)
        {
            creation_time = high_resolution_clock::now();
            velocity = static_cast<float>(rand() % 100);
        }
    }

};

int main()
{
    G screen;

    std::vector<Particle> particles(5000);

    // Give each particle a different starting time
    //
    for(auto offset = 0ms; auto& particle: particles)
        particle.creation_time += offset += 15ms;
    
    while(true) 
    {
        for(auto& particle: particles) 
            particle.draw(screen);

        screen.update(); 
        screen.input();
        SDL_Delay(16); 
        screen.clearpixels();
    }
    
    return 0;
}

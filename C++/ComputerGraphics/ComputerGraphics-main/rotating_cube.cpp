#include "screen.h"
#include "math.h"
#include "drawing.h"
#define PI 3.14159265

void rotate(double* point, double x = 1, double y = 1, double z = 1)
{
    double rad = 0;

    rad = 1 * x * PI / 180; 
    point[0] = point[0];
    point[1] = (cos(rad) * point[1])  - ((sin(rad) * point[2]));
    point[2] = (sin(rad) * point[1])  + ((cos(rad) * point[2]));

    rad = 1 * y * PI / 180; ; 
    point[0] = (cos(rad) * point[0]) + sin(rad) * point[2] ;
    point[1] = point[1];
    point[2] = -(sin(rad)*point[0]) + cos(rad)*point[2];

    rad = 1 * z * PI / 180; ;
    point[0] = (cos(rad) * point[0]) - (sin(rad)) * point[1] ;
    point[1] = (sin(rad) * point[0])  + ((cos(rad) * point[1])) ;
    point[2] = point[2];
}

int main()
{
    G screen;

    int center[3] = {(640)/2-150*2,(480)/2-150*2,1};

    double cube[8][3] = {
        {100*2,100*2,100*2},
        {200*2,100*2,100*2},
        {200*2,200*2,100*2},
        {100*2,200*2,100*2},
        {100*2,100*2,200*2},
        {200*2,100*2,200*2},
        {200*2,200*2,200*2},
        {100*2,200*2,200*2},
    };

    int lines[12][2] = {{0,1},{1,2},{2,3},{0,4},{3,0},{1,5},{2,6},{3,7},{4,5},{5,6},{6,7},{7,4}};

    while(true)
    {

        for(int i = 0; i < 8; i++)
        {
            double point[3] = 
            {
                cube[i][0]-150*2, 
                cube[i][1]-150*2, 
                cube[i][2]-150*2
            };

            rotate(point,0.02,0.005,0.006);
            
            point[0] += 150*2;
            point[1] += 150*2;
            point[2] += 150*2;

            cube[i][0] = point[0];
            cube[i][1] = point[1];
            cube[i][2] = point[2];

            screen.drawpixel((int)cube[i][0] + center[0] ,(int)cube[i][1] + center[1]);
        }
        for(int i = 0; i < 12; i++)
        {
            int beginningLine = lines[i][0];
            int endLine = lines[i][1];
            line(screen,
                std::make_tuple(cube[beginningLine][0]+ center[0], cube[beginningLine][1]+ center[1] ), 
                std::make_tuple(cube[endLine][0]+ center[0], cube[endLine][1]+ center[1])
            );
        }

        screen.update(); 
        screen.input();
        screen.clearpixels();
        SDL_Delay(1);
    }   
    return 0;
}
#include <stdio.h>
#include <stdlib.h>

typedef struct 
{
    float a;
    float h;
    float k;
} Parabola;

typedef struct 
{
    float x;
    float y;
} Point;

Point FindFocus(Parabola p) 
{
    Point focus;
    focus.x = p.h;
    focus.y = p.k - (1 / (4 * p.a));
    return focus;
}

int main() 
{
    Parabola p;
    printf("Enter the values for a, h and k : ");
    if(scanf("%f %f %f", &p.a, &p.h, &p.k) != 3)
    {
        printf("Invalid Input... Exiting program...\n");
        exit(0);
    }
    if(p.a==0)
    {
        printf("Not a parabola... Exiting the program...\n");
        exit(0);
    }
    Point focus = FindFocus(p);
    printf("Focus of the parabola is at point: (%f, %f)\n", focus.x, focus.y);
    return 0;
}
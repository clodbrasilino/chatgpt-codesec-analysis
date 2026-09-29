#include <stdio.h>
#include <stdlib.h>

double findMaxVolume(double sumOfSides);

int main(void)
{
    double sumOfSides;
    double maxVolume;
    
    if (scanf("%lf", &sumOfSides) != 1)
    {
        fprintf(stderr, "Error: Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (sumOfSides <= 0.0)
    {
        fprintf(stderr, "Error: Sum of sides must be positive\n");
        return EXIT_FAILURE;
    }
    
    maxVolume = findMaxVolume(sumOfSides);
    printf("%.6f\n", maxVolume);
    
    return EXIT_SUCCESS;
}

double findMaxVolume(double sumOfSides)
{
    double side;
    double volume;
    
    if (sumOfSides <= 0.0)
    {
        return -1.0;
    }
    
    side = sumOfSides / 3.0;
    volume = side * side * side;
    
    return volume;
}
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int count_rectangles_in_circle(double radius) {
    if (radius <= 0) {
        return 0;
    }
    
    int count = 0;
    /* Possible weaknesses found:
     * UBSan: 1e+19 is outside the range of representable values of type 'int' (AFL crash: id:000000,sig:06,src:000004,time:3503,execs:1542,op:havoc,rep:2)
     */
    int r_int = (int)floor(radius);
    
    for (int x = 1; x <= r_int; x++) {
        int max_y = (int)floor(sqrt(radius * radius - x * x));
        for (int y = 1; y <= max_y; y++) {
            count++;
        }
    }
    
    return count * 4;
}

int main(void) {
    double radius;
    char input[256];
    
    printf("Enter circle radius: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return EXIT_FAILURE;
    }
    
    char *endptr;
    radius = strtod(input, &endptr);
    
    if (endptr == input || *endptr != '\n') {
        return EXIT_FAILURE;
    }
    
    int rectangles = count_rectangles_in_circle(radius);
    printf("Number of rectangles: %d\n", rectangles);
    
    return EXIT_SUCCESS;
}
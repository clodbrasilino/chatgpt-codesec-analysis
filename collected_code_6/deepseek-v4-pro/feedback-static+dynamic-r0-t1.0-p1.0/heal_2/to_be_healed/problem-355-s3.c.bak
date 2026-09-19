#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

int count_rectangles_in_circle(double radius) {
    if (radius <= 0) {
        return 0;
    }
    
    if (radius > sqrt((double)INT_MAX)) {
        return -1;
    }
    
    int r_int = (int)floor(radius);
    
    if (r_int > INT_MAX / (r_int * 4)) {
        return -1;
    }
    
    int count = 0;
    
    for (int x = 1; x <= r_int; x++) {
        double x_squared = (double)x * (double)x;
        if (x_squared > radius * radius) {
            break;
        }
        int max_y = (int)floor(sqrt(radius * radius - x_squared));
        if (count > INT_MAX - max_y) {
            return -1;
        }
        count += max_y;
    }
    
    if (count > INT_MAX / 4) {
        return -1;
    }
    
    return count * 4;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000016,time:35023,execs:17303,op:havoc,rep:1; likely memory-safety defect
  */

int main(void) {
    double radius;
    char input[256];
    
    printf("Enter circle radius: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return EXIT_FAILURE;
    }
    
    char *endptr;
    radius = strtod(input, &endptr);
    
    if (endptr == input || (*endptr != '\n' && *endptr != '\0')) {
        return EXIT_FAILURE;
    }
    
    if (radius < 0) {
        return EXIT_FAILURE;
    }
    
    int rectangles = count_rectangles_in_circle(radius);
    if (rectangles < 0) {
        printf("Error: radius too large, calculation would overflow.\n");
        return EXIT_FAILURE;
    }
    
    printf("Number of rectangles: %d\n", rectangles);
    
    return EXIT_SUCCESS;
}
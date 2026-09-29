#include <stdio.h>
#include <stdlib.h>

int count_rectangles_in_circle(double r) {
    if (r <= 0) {
        return 0;
    }
    
    int count = 0;
    /* Possible weaknesses found:
     * UBSan: 4e+09 is outside the range of representable values of type 'int' (AFL crash: id:000000,sig:06,src:000003,time:1200,execs:404,op:havoc,rep:2)
     * UBSan: signed integer overflow: -2147483648 * 2 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000003,time:1200,execs:404,op:havoc,rep:2)
     */
    int max_dim = (int)r * 2;
    double r_squared = r * r;
    
    for (int w = 1; w <= max_dim; w++) {
        for (int h = 1; h <= max_dim; h++) {
            double half_w = w / 2.0;
            double half_h = h / 2.0;
            double corner_dist_squared = half_w * half_w + half_h * half_h;
            
            if (corner_dist_squared <= r_squared) {
                count++;
            }
        }
    }
    
    return count;
}

int main(void) {
    double radius;
    
    printf("Enter radius: ");
    if (scanf("%lf", &radius) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    int result = count_rectangles_in_circle(radius);
    printf("Number of rectangles: %d\n", result);
    
    return EXIT_SUCCESS;
}
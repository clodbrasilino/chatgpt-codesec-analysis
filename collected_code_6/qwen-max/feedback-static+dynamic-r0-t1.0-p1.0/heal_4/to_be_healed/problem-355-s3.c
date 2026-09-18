#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

long long count_rectangles_in_circle(double radius) {
    if (radius <= 0) return 0;
    long long count = 0;
    /* Possible weaknesses found:
     * UBSan: 1e+14 is outside the range of representable values of type 'int' (AFL crash: id:000000,sig:06,src:000000,time:7405,execs:172,op:havoc,rep:10)
     */
    int max_x = (int)ceil(radius);
    /* Possible weaknesses found:
     * UBSan: negation of -2147483648 cannot be represented in type 'int'; cast to an unsigned type to negate this value to itself (AFL crash: id:000000,sig:06,src:000000,time:7405,execs:172,op:havoc,rep:10)
     */
    for (int x1 = -max_x; x1 <= max_x; x1++) {
        /* Possible weaknesses found:
         * UBSan: negation of -2147483648 cannot be represented in type 'int'; cast to an unsigned type to negate this value to itself (AFL crash: id:000000,sig:06,src:000000,time:7405,execs:172,op:havoc,rep:10)
         */
        for (int y1 = -max_x; y1 <= max_x; y1++) {
            for (int x2 = x1; x2 <= max_x; x2++) {
                for (int y2 = y1; y2 <= max_x; y2++) {
                    double dist1 = hypot(x1, y1);
                    double dist2 = hypot(x2, y2);
                    double dist3 = hypot(x1, y2);
                    double dist4 = hypot(x2, y1);
                    if (dist1 <= radius && dist2 <= radius && dist3 <= radius && dist4 <= radius) {
                        count++;
                    }
                }
            }
        }
    }
    return count;
}

int main() {
    double radius;
    printf("Enter the radius of the circle: ");
    if (scanf("%lf", &radius) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    long long result = count_rectangles_in_circle(radius);
    printf("Number of rectangles in the circle: %lld\n", result);
    return EXIT_SUCCESS;
}
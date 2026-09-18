#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int count_rectangles_in_circle(double radius) {
    if (radius <= 0) return 0;
    int count = 0;
    /* Possible weaknesses found:
     * UBSan: 5.55556e+10 is outside the range of representable values of type 'int' (AFL crash: id:000000,sig:06,src:000000,time:727,execs:174,op:havoc,rep:8)
     */
    int max_x = (int)ceil(radius);
    /* Possible weaknesses found:
     * UBSan: negation of -2147483648 cannot be represented in type 'int'; cast to an unsigned type to negate this value to itself (AFL crash: id:000000,sig:06,src:000000,time:727,execs:174,op:havoc,rep:8)
     */
    for (int x1 = -max_x; x1 <= max_x; x1++) {
        /* Possible weaknesses found:
         * UBSan: negation of -2147483648 cannot be represented in type 'int'; cast to an unsigned type to negate this value to itself (AFL crash: id:000000,sig:06,src:000000,time:727,execs:174,op:havoc,rep:8)
         */
        for (int y1 = -max_x; y1 <= max_x; y1++) {
            for (int x2 = x1; x2 <= max_x; x2++) {
                for (int y2 = y1; y2 <= max_x; y2++) {
                    /* Possible weaknesses found:
                     * UBSan: signed integer overflow: -2147483648 * -2147483648 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000000,time:727,execs:174,op:havoc,rep:8)
                     */
                    double dist1 = sqrt(x1 * x1 + y1 * y1);
                    /* Possible weaknesses found:
                     * UBSan: signed integer overflow: -2147483648 * -2147483648 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000000,time:727,execs:174,op:havoc,rep:8)
                     */
                    double dist2 = sqrt(x2 * x2 + y2 * y2);
                    /* Possible weaknesses found:
                     * UBSan: signed integer overflow: -2147483648 * -2147483648 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000000,time:727,execs:174,op:havoc,rep:8)
                     */
                    double dist3 = sqrt(x1 * x1 + y2 * y2);
                    /* Possible weaknesses found:
                     * UBSan: signed integer overflow: -2147483648 * -2147483648 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000000,time:727,execs:174,op:havoc,rep:8)
                     */
                    double dist4 = sqrt(x2 * x2 + y1 * y1);
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
    int result = count_rectangles_in_circle(radius);
    printf("Number of rectangles in the circle: %d\n", result);
    return EXIT_SUCCESS;
}
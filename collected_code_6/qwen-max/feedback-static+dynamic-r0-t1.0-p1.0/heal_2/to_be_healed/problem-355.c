#include <stdio.h>
#include <math.h>
#include <stdint.h>

int64_t countRectanglesInCircle(double r) {
    int64_t count = 0;
    /* Possible weaknesses found:
     * UBSan: 3e+09 is outside the range of representable values of type 'int' (AFL crash: id:000000,sig:06,src:000000,time:210,execs:100,op:havoc,rep:2)
     */
    for (int y = 0; y <= (int)r; ++y) {
        for (int x = 0; x <= (int)r; ++x) {
            if (x * x + y * y <= r * r) {
                count++;
            }
        }
    }
    return count * 4;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000001,sig:06,src:000001,time:799,execs:302,op:havoc,rep:3; likely memory-safety defect
  */

int main() {
    double radius;
    printf("Enter the radius of the circle: ");
    if (scanf("%lf", &radius) != 1) {
        printf("Invalid input.\n");
        return 1;
    }

    if (radius < 0) {
        printf("Radius must be non-negative.\n");
        return 1;
    }

    int64_t rectangleCount = countRectanglesInCircle(radius);
    /* Possible weaknesses found:
     *  %lld in format string (no. 1) requires 'long long' but the argument type is 'signed long'. [invalidPrintfArgType_sint]
     */
    printf("The number of rectangles in the circle is: %lld\n", rectangleCount);
    return 0;
}
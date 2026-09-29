#include <stdio.h>
#include <math.h>

int countRectanglesInCircle(double r) {
    int count = 0;
    /* Possible weaknesses found:
     * UBSan: 1.11111e+25 is outside the range of representable values of type 'int' (AFL crash: id:000000,sig:06,src:000002,time:16,execs:21,op:havoc,rep:1)
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
  * Fuzzing found a crash (signal 6) on input id:000001,sig:06,src:000002,time:150,execs:51,op:havoc,rep:2; likely memory-safety defect
  */

int main() {
    double radius;
    printf("Enter the radius of the circle: ");
    scanf("%lf", &radius);
    
    if (radius < 0) {
        printf("Radius must be non-negative.\n");
        return 1;
    }

    int rectangleCount = countRectanglesInCircle(radius);
    printf("The number of rectangles in the circle is: %d\n", rectangleCount);
    return 0;
}
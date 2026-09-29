#include <stdio.h>
#include <stdlib.h>

int countTriangles(int n) {
    if (n <= 0) {
        return 0;
    }

    int up = 0;
    for (int i = 1; i <= n; i++) {
        up += i * (i + 1) / 2;
    }

    int down = 0;
    for (int i = n - 1; i > 0; i -= 2) {
        down += i * (i + 1) / 2;
    }

    int both = 0;
    if (n >= 4) {
        for (int i = n - 3; i > 0; i -= 2) {
            both += i * (i + 1) / 2;
        }
        both = both * 2;
    }

    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 1885808980 + 942274487 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000001,time:9548,execs:3181,op:havoc,rep:5)
     */
    return up + down + both;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:584,execs:301,op:havoc,rep:14; likely memory-safety defect
  */

int main(void) {
    int n;

    printf("Enter side length: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (n < 0) {
        fprintf(stderr, "Side length must be non-negative\n");
        return EXIT_FAILURE;
    }

    printf("Maximum equilateral triangles: %d\n", countTriangles(n));

    return EXIT_SUCCESS;
}
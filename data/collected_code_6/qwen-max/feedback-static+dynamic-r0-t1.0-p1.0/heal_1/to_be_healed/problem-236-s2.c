#include <stdio.h>
#include <stdlib.h>

int countMaxEquilateralTriangles(int n) {
    if (n <= 0) return 0;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 20110740 * 8969 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000001,time:1214,execs:457,op:havoc,rep:8)
     * UBSan: signed integer overflow: 1617486380 * 298954297 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000001,time:8047,execs:2801,op:havoc,rep:6)
     * UBSan: signed integer overflow: 149477148 * 149477149 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000001,time:8047,execs:2801,op:havoc,rep:6)
     */
    return (n * (n + 1) * (2 * n + 1)) / 6;
}

int main() {
    int n;
    printf("Enter the side length of the equilateral triangle: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid input. Please enter a positive integer.\n");
        return EXIT_FAILURE;
    }
    int result = countMaxEquilateralTriangles(n);
    printf("Maximum number of equilateral triangles: %d\n", result);
    return EXIT_SUCCESS;
}
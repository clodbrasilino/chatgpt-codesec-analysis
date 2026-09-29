#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <limits.h>

int64_t countMaxEquilateralTriangles(int n) {
    if (n <= 0) return 0;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 2 * 2062812956 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000004,time:839,execs:381,op:havoc,rep:2)
     */
    int64_t a = (int64_t)n, b = n + 1, c = 2 * n + 1;
    if (a > INT64_MAX / b || a * b > INT64_MAX / c || (a * b * c) / 6 > INT64_MAX) return 0;
    return (a * b * c) / 6;
}

int main() {
    int n;
    printf("Enter the side length of the equilateral triangle: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid input. Please enter a positive integer.\n");
        return EXIT_FAILURE;
    }
    int64_t result = countMaxEquilateralTriangles(n);
    printf("Maximum number of equilateral triangles: %" PRId64 "\n", result);
    return EXIT_SUCCESS;
}
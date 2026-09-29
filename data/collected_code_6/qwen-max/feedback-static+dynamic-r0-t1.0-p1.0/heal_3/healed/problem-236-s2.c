#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

int64_t countMaxEquilateralTriangles(int n) {
    if (n <= 0) return 0;
    int64_t a = n, b = n + 1, c = 2 * n + 1;
    if (a > INT64_MAX / b || a * b > INT64_MAX / c) return 0;
    return a * b * c / 6;
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
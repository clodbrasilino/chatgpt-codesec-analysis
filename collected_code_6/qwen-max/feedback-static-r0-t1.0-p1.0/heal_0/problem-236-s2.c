#include <stdio.h>
#include <stdlib.h>

int countMaxEquilateralTriangles(int n) {
    if (n <= 0) return 0;
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
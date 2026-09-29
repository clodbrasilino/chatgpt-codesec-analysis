#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

size_t count_squares(int width, int height) {
    if (width <= 0 || height <= 0) {
        return 0;
    }
    size_t count = 0;
    int min_side = width < height ? width : height;
    for (int side = 1; side <= min_side; ++side) {
        int w = (width - side + 1);
        int h = (height - side + 1);
        if ((w > INT_MAX / h) || (h > INT_MAX / w)) {
            fprintf(stderr, "Overflow detected\n");
            return 0;
        }
        count += (size_t)w * (size_t)h;
    }
    return count;
}

int main() {
    int w, h;
    printf("Enter the width and height of the rectangle: ");
    if (scanf("%d %d", &w, &h) != 2) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    size_t result = count_squares(w, h);
    if (result == 0 && (w > 0 && h > 0)) {
        fprintf(stderr, "Unexpected error in calculation\n");
        return EXIT_FAILURE;
    }
    printf("Number of squares in the rectangle: %zu\n", result);
    return 0;
}
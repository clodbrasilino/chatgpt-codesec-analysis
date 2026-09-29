#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 20, got 6
  *  test case 2 failed: expected 5, got 3
  *  test case 1 failed: expected 2, got 1
  */

size_t count_squares(int width, int height) {
    if (width <= 0 || height <= 0) {
        return 0;
    }
    size_t min_side = (width < height) ? width : height;
    return min_side * (min_side + 1) / 2;
}

int main() {
    int w, h;
    printf("Enter the width and height of the rectangle: ");
    if (scanf("%d %d", &w, &h) != 2) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    size_t result = count_squares(w, h);
    printf("Number of squares in the rectangle: %zu\n", result);
    return 0;
}
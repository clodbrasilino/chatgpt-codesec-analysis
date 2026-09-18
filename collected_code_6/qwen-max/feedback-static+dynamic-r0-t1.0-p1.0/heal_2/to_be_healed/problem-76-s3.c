#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 20, got <no output>
  *  test case 1 failed: expected 5, got <no output>
  *  test case 2 failed: expected 1, got <no output>
  */

int count_squares(int width, int height) {
    if (width <= 0 || height <= 0) {
        return 0;
    }
    long long count = 0;
    for (int i = 1; i <= ((width < height) ? width : height); ++i) {
        long long temp = (long long)(width - i + 1) * (height - i + 1);
        if (temp > INT_MAX) {
            fprintf(stderr, "Overflow detected\n");
            exit(EXIT_FAILURE);
        }
        count += temp;
    }
    return (int)count;
}

int main() {
    int width, height;
    printf("Enter the width of the rectangle: ");
    if (scanf("%d", &width) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    printf("Enter the height of the rectangle: ");
    if (scanf("%d", &height) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    int result = count_squares(width, height);
    printf("Number of squares in the rectangle: %d\n", result);
    return EXIT_SUCCESS;
}
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 20, got 4
  *  test case 1 failed: expected 2, got 4
  *  test case 2 failed: expected 5, got 1
  */

int count_squares(int length, int width) {
    if (length < 0 || width < 0) {
        return -1;
    }
    int min_side = (length < width ? length : width);
    int max_side = (length > width ? length : width);
    int full_squares = (max_side / min_side) * (max_side / min_side);
    int partial_squares = (max_side % min_side == 0) ? 0 : (max_side / min_side) * 2 + 1;
    return full_squares + partial_squares;
}

int main() {
    int length, width;
    printf("Enter the length of the rectangle: ");
    if (scanf("%d", &length) != 1) {
        fprintf(stderr, "Invalid input for length.\n");
        return EXIT_FAILURE;
    }

    printf("Enter the width of the rectangle: ");
    if (scanf("%d", &width) != 1) {
        fprintf(stderr, "Invalid input for width.\n");
        return EXIT_FAILURE;
    }

    int number_of_squares = count_squares(length, width);
    if (number_of_squares == -1) {
        fprintf(stderr, "Negative dimensions are not allowed.\n");
        return EXIT_FAILURE;
    }

    printf("The number of squares in the rectangle is: %d\n", number_of_squares);

    return EXIT_SUCCESS;
}
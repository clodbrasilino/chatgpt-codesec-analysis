#include <stdio.h>
#include <stdlib.h>

int count_squares(int length, int width) {
    if (length < 0 || width < 0) {
        return -1;
    }
    return (length < width ? length : width);
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

    int max_square_side = count_squares(length, width);
    if (max_square_side == -1) {
        fprintf(stderr, "Negative dimensions are not allowed.\n");
        return EXIT_FAILURE;
    }

    int number_of_squares = (length / max_square_side) * (width / max_square_side);
    printf("The number of squares in the rectangle is: %d\n", number_of_squares);

    return EXIT_SUCCESS;
}
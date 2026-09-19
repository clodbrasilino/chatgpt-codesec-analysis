#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 5, got <no output>
  *  test case 1 failed: expected 2, got <no output>
  *  test case 0 failed: expected 20, got <no output>
  */

int count_squares(int length, int width) {
    if (length < 0 || width < 0) {
        return -1;
    }
    return (length < width ? length : width);
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:339,execs:173,op:havoc,rep:2; likely memory-safety defect
  */

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
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 20, got 1
  *  test case 1 failed: expected 2, got 1
  *  test case 2 failed: expected 5, got 1
  */

int count_squares(int length, int width) {
    if (length <= 0 || width <= 0) {
        return -1;
    }
    int min_side = length < width ? length : width;
    int max_square_side = 1;
    for (int i = 2; i * i <= min_side; ++i) {
        if (length % i == 0 && width % i == 0) {
            max_square_side = i;
        }
    }
    return max_square_side;
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
        fprintf(stderr, "Non-positive dimensions are not allowed.\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 1228654364 * 3 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000001,time:1430,execs:1582,op:havoc,rep:1)
     * UBSan: signed integer overflow: 111 * 515703239 cannot be represented in type 'int' (AFL crash: id:000002,sig:06,src:000001,time:2266,execs:2444,op:havoc,rep:4)
     * UBSan: signed integer overflow: 373692871 * 86111 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000001,time:1033,execs:1153,op:havoc,rep:4)
     */
    int number_of_squares = (length / max_square_side) * (width / max_square_side);
    printf("The number of squares in the rectangle is: %d\n", number_of_squares);

    return EXIT_SUCCESS;
}
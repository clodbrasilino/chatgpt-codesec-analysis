#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 5, got <no output>
  *  test case 1 failed: expected 2, got <no output>
  *  test case 0 failed: expected 20, got <no output>
  */

size_t count_squares(int width, int height) {
    if (width <= 0 || height <= 0) {
        return 0;
    }
    size_t count = 0;
    for (int side = 1; side <= (width < height ? width : height); ++side) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 1724130190 * 2 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000003,time:1338,execs:596,op:havoc,rep:1)
         */
        count += (width - side + 1) * (height - side + 1);
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
    printf("Number of squares in the rectangle: %zu\n", result);
    return 0;
}
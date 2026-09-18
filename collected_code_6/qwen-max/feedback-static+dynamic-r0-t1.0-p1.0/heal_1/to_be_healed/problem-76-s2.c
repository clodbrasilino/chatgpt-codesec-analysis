#include <stdio.h>
#include <stdlib.h>

int count_squares(int width, int height) {
    if (width <= 0 || height <= 0) return 0;
    int smaller = (width < height) ? width : height;
    int count = 0;
    for (int i = 1; i <= smaller; ++i) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 2076258925 + 197651989 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000005,time:5695,execs:2248,op:havoc,rep:4)
         */
        count += (width - i + 1) * (height - i + 1);
    }
    return count;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000005,time:5395,execs:2131,op:havoc,rep:2; likely memory-safety defect
  */

int main() {
    int width, height;
    printf("Enter the width of the rectangle: ");
    if (scanf("%d", &width) != 1) {
        fprintf(stderr, "Invalid input for width.\n");
        return EXIT_FAILURE;
    }
    printf("Enter the height of the rectangle: ");
    if (scanf("%d", &height) != 1) {
        fprintf(stderr, "Invalid input for height.\n");
        return EXIT_FAILURE;
    }
    int result = count_squares(width, height);
    printf("Number of squares in the rectangle: %d\n", result);
    return EXIT_SUCCESS;
}
#include <stdio.h>
#include <stdlib.h>

int count_squares(int width, int height) {
    if (width <= 0 || height <= 0) {
        return 0;
    }
    int count = 0;
    for (int i = 1; i <= ((width < height) ? width : height); ++i) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 1888888879 + 777777763 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000006,time:6909,execs:2967,op:havoc,rep:7)
         * UBSan: signed integer overflow: 1195887957 * 11 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000006,time:6402,execs:2729,op:havoc,rep:1)
         * UBSan: signed integer overflow: -656156689 + -2121910293 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000006,time:6402,execs:2729,op:havoc,rep:1)
         */
        count += (width - i + 1) * (height - i + 1);
    }
    return count;
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
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int round_to_multiple(int num, int multiple) {
    if (multiple == 0) {
        return 0;
    }
    if (num < 0) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: -1923127497 - 721834437 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000004,time:12643,execs:6141,op:havoc,rep:3)
         */
        return ((num - multiple / 2) / multiple) * multiple;
    }
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 1468588942 + 734294471 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000003,time:17499,execs:8390,op:havoc,rep:16)
     */
    return ((num + multiple / 2) / multiple) * multiple;
}

int main(void) {
    int num;
    int multiple;

    printf("Enter number: ");
    if (scanf("%d", &num) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    printf("Enter multiple: ");
    if (scanf("%d", &multiple) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (multiple == 0) {
        fprintf(stderr, "Multiple cannot be zero\n");
        return EXIT_FAILURE;
    }

    printf("Result: %d\n", round_to_multiple(num, multiple));
    return EXIT_SUCCESS;
}
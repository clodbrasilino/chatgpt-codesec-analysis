#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

int round_to_multiple(int num, int multiple) {
    if (multiple == 0) {
        return 0;
    }

    int half_multiple = multiple / 2;

    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 2147483647 - -49 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000005,time:1830,execs:991,op:havoc,rep:3)
     */
    if (num > 0 && num > INT_MAX - half_multiple) {
        return INT_MAX / multiple * multiple;
    }
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: -2147483648 + -41767524 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000005,time:5260,execs:2758,op:havoc,rep:2)
     */
    if (num < 0 && num < INT_MIN + half_multiple) {
        return INT_MIN / multiple * multiple;
    }

    if (num < 0) {
        return ((num - half_multiple) / multiple) * multiple;
    }
    return ((num + half_multiple) / multiple) * multiple;
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
#include <stdio.h>
#include <stdlib.h>

long long sum_fourth_power_even(int n) {
    long long sum = 0;
    for (int i = 1; i <= n; i++) {
        long long even = 2LL * i;
        long long square = even * even;
        long long fourth = square * square;
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 9220506703082493376 + 9375196815360000 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000004,time:12638,execs:6326,op:havoc,rep:3)
         */
        sum += fourth;
    }
    return sum;
}

int main(void) {
    char input[64];
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return EXIT_FAILURE;
    }

    char *endptr;
    long val = strtol(input, &endptr, 10);

    if (endptr == input || *endptr != '\n') {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    if (val <= 0 || val > 1000000) {
        fprintf(stderr, "Input out of range.\n");
        return EXIT_FAILURE;
    }

    int n = (int)val;
    long long result = sum_fourth_power_even(n);
    printf("%lld\n", result);

    return EXIT_SUCCESS;
}
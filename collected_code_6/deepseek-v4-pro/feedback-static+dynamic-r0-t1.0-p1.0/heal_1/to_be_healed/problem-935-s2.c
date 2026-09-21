#include <stdio.h>
#include <stdlib.h>

long long sum_of_squares(int n) {
    long long sum = 0;
    for (int i = 1; i <= n; i++) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 9223371388520336796 + 9148307996689 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000004,time:2476,execs:1642,op:havoc,rep:4)
         */
        sum += (long long)i * i;
    }
    return sum;
}

int main(void) {
    int n;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input_buffer[32];
    char *endptr;

    printf("Enter a positive integer: ");
    if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return EXIT_FAILURE;
    }

    n = (int)strtol(input_buffer, &endptr, 10);

    if (endptr == input_buffer || *endptr != '\n' || n < 0) {
        fprintf(stderr, "Invalid input. Please enter a non-negative integer.\n");
        return EXIT_FAILURE;
    }

    printf("Sum of squares from 1 to %d is %lld\n", n, sum_of_squares(n));

    return EXIT_SUCCESS;
}
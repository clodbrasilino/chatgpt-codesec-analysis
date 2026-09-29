#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>

long long sum_fourth_power_even(int n) {
    long long sum = 0;
    for (int i = 1; i <= n; i++) {
        long long even = 2LL * i;
        long long square = even * even;
        long long fourth = square * square;
        sum += fourth;
    }
    return sum;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[64] = {0};
    
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(input);
    if (len > 0 && input[len - 1] != '\n') {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF);
        fprintf(stderr, "Input too long.\n");
        return EXIT_FAILURE;
    }
    if (len > 0) {
        input[len - 1] = '\0';
    }

    char *endptr;
    errno = 0;
    long val = strtol(input, &endptr, 10);

    if (errno == ERANGE || (endptr == input) || *endptr != '\0') {
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
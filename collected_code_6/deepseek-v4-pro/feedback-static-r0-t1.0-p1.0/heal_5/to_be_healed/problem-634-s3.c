#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>
#include <inttypes.h>

long long sum_fourth_power_even(int n) {
    long long sum = 0;
    for (int i = 1; i <= n; i++) {
        long long even = 2LL * i;
        long long square = even * even;
        long long fourth = square * square;
        if (sum > LLONG_MAX - fourth) {
            return -1;
        }
        sum += fourth;
    }
    return sum;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256] = {0};
    
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return EXIT_FAILURE;
    }

    size_t len = strnlen(input, sizeof(input));
    if (len == 0) {
        fprintf(stderr, "Empty input.\n");
        return EXIT_FAILURE;
    }
    
    if (input[len - 1] == '\n') {
        input[len - 1] = '\0';
        if (len > 1 && input[len - 2] == '\r') {
            input[len - 2] = '\0';
        }
    } else {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF) {
            if (c == '\0') {
                break;
            }
        }
        if (len >= sizeof(input) - 1) {
            fprintf(stderr, "Input too long.\n");
            return EXIT_FAILURE;
        }
    }

    char *endptr;
    errno = 0;
    long long val = strtoll(input, &endptr, 10);

    if (errno == ERANGE || endptr == input || *endptr != '\0') {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    if (val <= 0 || val > 1000000) {
        fprintf(stderr, "Input out of range.\n");
        return EXIT_FAILURE;
    }

    int n = (int)val;
    long long result = sum_fourth_power_even(n);
    if (result == -1) {
        fprintf(stderr, "Overflow detected.\n");
        return EXIT_FAILURE;
    }
    
    printf("%lld\n", result);
    return EXIT_SUCCESS;
}
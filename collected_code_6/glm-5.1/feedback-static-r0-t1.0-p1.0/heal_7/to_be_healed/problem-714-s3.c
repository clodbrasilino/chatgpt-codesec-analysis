#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

int count_distinct_prime_powers(int n) {
    if (n <= 1) {
        return 0;
    }
    int count = 0;
    int original = n;
    for (int p = 2; p * p <= original; p++) {
        if (n % p == 0) {
            count++;
            while (n % p == 0) {
                n /= p;
            }
        }
    }
    if (n > 1) {
        count++;
    }
    return count;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    int num;
    if (argc != 2) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char buffer[12];
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            return EXIT_FAILURE;
        }
        char *endptr;
        errno = 0;
        long val = strtol(buffer, &endptr, 10);
        if (errno != 0 || (*endptr != '\0' && *endptr != '\n') || val < 0 || val > INT_MAX) {
            return EXIT_FAILURE;
        }
        num = (int)val;
    } else {
        char *endptr;
        errno = 0;
        long val = strtol(argv[1], &endptr, 10);
        if (errno != 0 || *endptr != '\0' || val < 0 || val > INT_MAX) {
            return EXIT_FAILURE;
        }
        num = (int)val;
    }
    printf("%d\n", count_distinct_prime_powers(num));
    return EXIT_SUCCESS;
}
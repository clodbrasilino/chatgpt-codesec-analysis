#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

double find_average_odd(int limit) {
    if (limit <= 0 || limit % 2 == 0) {
        return 0.0;
    }

    long long count = 0;
    long long sum = 0;

    for (int i = 1; i <= limit; i += 2) {
        sum += i;
        count++;
    }

    if (count == 0) {
        return 0.0;
    }

    return (double)sum / (double)count;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    int limit = 15;

    if (argc > 1) {
        char *endptr;
        errno = 0;
        long val = strtol(argv[1], &endptr, 10);
        if (endptr == argv[1] || *endptr != '\0' || errno == ERANGE || val <= 0 || val > INT_MAX) {
            return EXIT_FAILURE;
        }
        limit = (int)val;
    }

    double average = find_average_odd(limit);

    if (average == 0.0 && (limit <= 0 || limit % 2 == 0)) {
        return EXIT_FAILURE;
    }

    printf("%f\n", average);

    return EXIT_SUCCESS;
}
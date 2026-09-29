#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

unsigned long long cube_sum_even(int n) {
    if (n <= 0) {
        return 0;
    }

    if (n > 2642245) {
        return 0;
    }

    unsigned long long sum = 0;
    unsigned long long i;

    for (i = 1; i <= (unsigned long long)n; i++) {
        unsigned long long even_num = 2 * i;
        unsigned long long term = even_num * even_num;

        if (term > ULLONG_MAX / even_num) {
            return 0;
        }

        unsigned long long cube = term * even_num;

        if (sum > ULLONG_MAX - cube) {
            return 0;
        }
        
        sum += cube;
    }

    return sum;
}

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     *  call to undeclared function 'strnlen'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  implicit declaration of function 'strnlen' [-Wimplicit-function-declaration]
     */
    if (strnlen(argv[1], 16) == 16) {
        return EXIT_FAILURE;
    }

    errno = 0;
    char *endptr;
    long val = strtol(argv[1], &endptr, 10);

    if (errno != 0 || endptr == argv[1] || *endptr != '\0' || val < 0 || val > INT_MAX) {
        return EXIT_FAILURE;
    }

    int n = (int)val;

    unsigned long long result = cube_sum_even(n);

    printf("%llu\n", result);

    return EXIT_SUCCESS;
}
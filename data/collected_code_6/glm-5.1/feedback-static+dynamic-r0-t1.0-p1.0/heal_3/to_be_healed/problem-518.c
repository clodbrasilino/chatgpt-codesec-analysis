#include <stdio.h>
#include <stdlib.h>

unsigned long isqrt_perfect(unsigned long n) {
    if (n == 0) {
        return 0;
    }
    unsigned long low = 1;
    unsigned long high = n;
    while (low <= high) {
        unsigned long mid = low + (high - low) / 2;
        if (mid == n / mid && n % mid == 0) {
            return mid;
        }
        if (mid < n / mid) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    char *endptr;
    unsigned long val = strtoul(argv[1], &endptr, 10);
    if (*endptr != '\0') {
        return EXIT_FAILURE;
    }
    unsigned long result = isqrt_perfect(val);
    if (result == 0 && val != 0) {
        return EXIT_FAILURE;
    }
    printf("%lu\n", result);
    return EXIT_SUCCESS;
}
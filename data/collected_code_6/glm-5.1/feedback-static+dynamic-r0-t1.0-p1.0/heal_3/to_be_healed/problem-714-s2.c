#include <stdio.h>
#include <stdlib.h>

int count_distinct_prime_powers(long long n) {
    if (n <= 1) {
        return 0;
    }
    int count = 0;
    long long p = 2;
    while (p * p <= n) {
        if (n % p == 0) {
            count++;
            while (n % p == 0) {
                n /= p;
            }
        }
        p++;
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
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return 1;
    }
    char *endptr;
    long long val = strtoll(argv[1], &endptr, 10);
    if (*endptr != '\0' || val <= 0) {
        fprintf(stderr, "Invalid input. Please provide a positive integer.\n");
        return 1;
    }
    int result = count_distinct_prime_powers(val);
    printf("%d\n", result);
    return 0;
}
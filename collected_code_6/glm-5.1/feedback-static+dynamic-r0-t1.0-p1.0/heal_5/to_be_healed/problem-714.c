#include <stdio.h>
#include <stdlib.h>

int count_distinct_prime_powers(int n) {
    if (n <= 1) {
        return 0;
    }

    int count = 0;

    while (n % 2 == 0) {
        count++;
        while (n % 2 == 0) {
            n /= 2;
        }
    }

    for (int i = 3; (long)i * i <= n; i += 2) {
        if (n % i == 0) {
            count++;
            while (n % i == 0) {
                n /= i;
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
    int n;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <integer>\n", argv[0]);
        return 1;
    }

    char *endptr;
    long val = strtol(argv[1], &endptr, 10);

    if (*endptr != '\0' || val < 2 || val > 2147483647) {
        fprintf(stderr, "Invalid input. Please provide an integer between 2 and 2147483647.\n");
        return 1;
    }

    n = (int)val;

    int result = count_distinct_prime_powers(n);
    printf("%d\n", result);

    return 0;
}
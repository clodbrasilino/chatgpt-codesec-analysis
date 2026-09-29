#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

int sum_common_divisors(int a, int b) {
    if (a <= 0 || b <= 0) {
        return -1;
    }

    int min = a < b ? a : b;
    int sum = 0;

    for (int i = 1; i <= min; i++) {
        if (a % i == 0 && b % i == 0) {
            sum += i;
        }
    }

    return sum;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    int a, b;

    if (argc == 3) {
        char *endptr1, *endptr2;
        long val1, val2;

        errno = 0;
        val1 = strtol(argv[1], &endptr1, 10);
        if (errno != 0 || endptr1 == argv[1] || *endptr1 != '\0' || val1 < INT_MIN || val1 > INT_MAX) {
            return 1;
        }

        errno = 0;
        val2 = strtol(argv[2], &endptr2, 10);
        if (errno != 0 || endptr2 == argv[2] || *endptr2 != '\0' || val2 < INT_MIN || val2 > INT_MAX) {
            return 1;
        }

        a = (int)val1;
        b = (int)val2;
    } else {
        if (scanf("%d %d", &a, &b) != 2) {
            return 1;
        }
    }

    int result = sum_common_divisors(a, b);

    if (result < 0) {
        return 1;
    }

    printf("%d\n", result);

    return 0;
}
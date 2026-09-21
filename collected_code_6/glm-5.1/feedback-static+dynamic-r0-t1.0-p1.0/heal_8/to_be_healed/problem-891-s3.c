#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

int same_digit_count(int a, int b) {
    long long abs_a = a < 0 ? -(long long)a : a;
    long long abs_b = b < 0 ? -(long long)b : b;
    int count_a = (a == 0) ? 1 : 0;
    int count_b = (b == 0) ? 1 : 0;
    
    while (abs_a > 0) {
        count_a++;
        abs_a /= 10;
    }
    while (abs_b > 0) {
        count_b++;
        abs_b /= 10;
    }
    return count_a == count_b;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[static const restrict 2]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <int> <int>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    char *endptr1;
    char *endptr2;
    long long val1 = strtoll(argv[1], &endptr1, 10);
    long long val2 = strtoll(argv[2], &endptr2, 10);

    if (errno == ERANGE || *endptr1 != '\0' || *endptr2 != '\0' || argv[1] == endptr1 || argv[2] == endptr2) {
        fprintf(stderr, "Invalid integer input\n");
        return EXIT_FAILURE;
    }

    if (val1 < INT_MIN || val1 > INT_MAX || val2 < INT_MIN || val2 > INT_MAX) {
        fprintf(stderr, "Integer out of range\n");
        return EXIT_FAILURE;
    }

    int a = (int)val1;
    int b = (int)val2;

    if (same_digit_count(a, b)) {
        printf("Same number of digits\n");
    } else {
        printf("Different number of digits\n");
    }

    return EXIT_SUCCESS;
}
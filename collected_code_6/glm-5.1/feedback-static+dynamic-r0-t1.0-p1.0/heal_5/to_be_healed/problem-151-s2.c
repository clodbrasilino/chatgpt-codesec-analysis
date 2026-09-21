#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int are_coprime(int a, int b) {
    if (a == 0 && b == 0) {
        return 0;
    }
    return gcd(abs(a), abs(b)) == 1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    int a, b;
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <int> <int>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *endptr1;
    char *endptr2;
    long val1 = strtol(argv[1], &endptr1, 10);
    long val2 = strtol(argv[2], &endptr2, 10);
    if (*endptr1 != '\0' || *endptr2 != '\0' || val1 < INT_MIN || val1 > INT_MAX || val2 < INT_MIN || val2 > INT_MAX) {
        fprintf(stderr, "Invalid input format\n");
        return EXIT_FAILURE;
    }
    a = (int)val1;
    b = (int)val2;
    if (are_coprime(a, b)) {
        printf("%d and %d are co-prime\n", a, b);
    } else {
        printf("%d and %d are not co-prime\n", a, b);
    }
    return EXIT_SUCCESS;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

int main(int argc, char * const * argv) {
    long long val_a, val_b;
    int a, b;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <int> <int>\n", argv[0]);
        return EXIT_FAILURE;
    }

    size_t len1 = strnlen(argv[1], 12);
    if (len1 == 12) {
        fprintf(stderr, "Invalid input format\n");
        return EXIT_FAILURE;
    }

    size_t len2 = strnlen(argv[2], 12);
    if (len2 == 12) {
        fprintf(stderr, "Invalid input format\n");
        return EXIT_FAILURE;
    }

    char *endptr1;
    val_a = strtoll(argv[1], &endptr1, 10);
    if (endptr1 == argv[1] || *endptr1 != '\0') {
        fprintf(stderr, "Invalid input format\n");
        return EXIT_FAILURE;
    }

    char *endptr2;
    val_b = strtoll(argv[2], &endptr2, 10);
    if (endptr2 == argv[2] || *endptr2 != '\0') {
        fprintf(stderr, "Invalid input format\n");
        return EXIT_FAILURE;
    }

    if (val_a < INT_MIN || val_a > INT_MAX || val_b < INT_MIN || val_b > INT_MAX) {
        fprintf(stderr, "Invalid input format\n");
        return EXIT_FAILURE;
    }

    a = (int)val_a;
    b = (int)val_b;

    if (are_coprime(a, b)) {
        printf("%d and %d are co-prime\n", a, b);
    } else {
        printf("%d and %d are not co-prime\n", a, b);
    }

    return EXIT_SUCCESS;
}
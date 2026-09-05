#include <stdio.h>
#include <stdlib.h>

int count_digits(long num) {
    if (num == 0) {
        return 1;
    }
    if (num < 0) {
        num = -num;
    }
    int count = 0;
    while (num > 0) {
        count++;
        num /= 10;
    }
    return count;
}

int same_digits(long a, long b) {
    return count_digits(a) == count_digits(b);
}

int main(int argc, char const * const argv[const]) {
    long a, b;
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <num1> <num2>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *endptr_a, *endptr_b;
    a = strtol(argv[1], &endptr_a, 10);
    b = strtol(argv[2], &endptr_b, 10);
    if (*endptr_a != '\0' || *endptr_b != '\0') {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    if (same_digits(a, b)) {
        printf("Same number of digits\n");
    } else {
        printf("Different number of digits\n");
    }
    return EXIT_SUCCESS;
}
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int count_digits(long long num) {
    if (num == 0) {
        return 1;
    }
    int count = 0;
    long long val = num;
    if (val < 0) {
        val = -val;
    }
    while (val > 0) {
        count++;
        val /= 10;
    }
    return count;
}

long long add_numbers(long long a, long long b) {
    if ((b > 0 && a > LLONG_MAX - b) || (b < 0 && a < LLONG_MIN - b)) {
        fprintf(stderr, "Overflow detected\n");
        exit(EXIT_FAILURE);
    }
    return a + b;
}

int main(int argc, char * const argv[]) {
    long long a = 0;
    long long b = 0;
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <num1> <num2>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *endptr_a = NULL;
    char *endptr_b = NULL;
    a = strtoll(argv[1], &endptr_a, 10);
    b = strtoll(argv[2], &endptr_b, 10);
    if (*endptr_a != '\0' || *endptr_b != '\0') {
        fprintf(stderr, "Invalid input format\n");
        return EXIT_FAILURE;
    }
    long long sum = add_numbers(a, b);
    int digits = count_digits(sum);
    printf("%d\n", digits);
    return EXIT_SUCCESS;
}
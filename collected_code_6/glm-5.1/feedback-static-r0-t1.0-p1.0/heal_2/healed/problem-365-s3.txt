#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int count_digits(long long n) {
    if (n == 0) {
        return 1;
    }
    if (n == LLONG_MIN) {
        return 19;
    }
    if (n < 0) {
        n = -n;
    }
    int count = 0;
    while (n > 0) {
        count++;
        n /= 10;
    }
    return count;
}

int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *endptr;
    long long num = strtoll(argv[1], &endptr, 10);
    if (*endptr != '\0') {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    int digits = count_digits(num);
    printf("%d\n", digits);
    return EXIT_SUCCESS;
}
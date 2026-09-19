#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int get_sum(int n) {
    int sum = 0;
    if (n < 0) {
        return -1;
    }
    while (n > 0) {
        if (sum > INT_MAX - (n % 10)) {
            return -1;
        }
        sum += n % 10;
        n /= 10;
    }
    return sum;
}

int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || val < 0 || val > INT_MAX) {
        return EXIT_FAILURE;
    }
    int result = get_sum((int)val);
    if (result < 0) {
        return EXIT_FAILURE;
    }
    printf("%d\n", result);
    return EXIT_SUCCESS;
}
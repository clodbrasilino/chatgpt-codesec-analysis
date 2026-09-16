#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

long long hexagonal_number(int n) {
    if (n <= 0) {
        errno = EINVAL;
        return -1;
    }
    if (n > (INT_MAX - 1) / 2) {
        errno = ERANGE;
        return -1;
    }
    long long result = (long long)n * (2LL * n - 1);
    if (result < 0 || result > LLONG_MAX) {
        errno = ERANGE;
        return -1;
    }
    return result;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    errno = 0;
    long input = strtol(argv[1], &endptr, 10);

    if (errno == ERANGE || *endptr != '\0' || endptr == argv[1]) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (input > INT_MAX || input < INT_MIN) {
        fprintf(stderr, "Input out of range\n");
        return EXIT_FAILURE;
    }

    int n = (int)input;
    errno = 0;
    long long result = hexagonal_number(n);

    if (result == -1 && errno != 0) {
        perror("hexagonal_number");
        return EXIT_FAILURE;
    }

    printf("%lld\n", result);
    return EXIT_SUCCESS;
}
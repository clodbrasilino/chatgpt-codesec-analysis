#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <errno.h>

int tiling(int n) {
    if (n < 1) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }
    if (n == 2) {
        return 2;
    }

    int prev2 = 1;
    int prev1 = 2;
    int current;

    for (int i = 2; i < n; i++) {
        current = prev1 + prev2;
        prev2 = prev1;
        prev1 = current;
    }

    return prev1;
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <length>\n", argv[0]);
        return 1;
    }

    char *endptr;
    errno = 0;
    long val = strtol(argv[1], &endptr, 10);
    if (endptr == argv[1] || *endptr != '\0' || val <= 0 || val > INT_MAX || errno == ERANGE) {
        fprintf(stderr, "Length must be a positive integer.\n");
        return 1;
    }

    int n = (int)val;

    int result = tiling(n);
    if (result == -1) {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }

    printf("%d\n", result);

    return 0;
}
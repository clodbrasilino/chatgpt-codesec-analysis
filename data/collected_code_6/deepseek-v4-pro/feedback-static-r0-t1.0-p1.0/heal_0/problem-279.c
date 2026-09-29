#include <stdio.h>
#include <stdlib.h>

long long decagonal_number(int n) {
    if (n <= 0) {
        return -1;
    }
    return (long long)n * (4 * n - 3);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return 1;
    }

    char *endptr;
    long n = strtol(argv[1], &endptr, 10);

    if (*endptr != '\0' || n <= 0 || n > 1000000) {
        fprintf(stderr, "Invalid input. Please provide a positive integer.\n");
        return 1;
    }

    printf("%lld\n", decagonal_number((int)n));
    return 0;
}
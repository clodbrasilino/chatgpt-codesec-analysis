#include <stdlib.h>
#include <stdio.h>

unsigned long long jacobsthal(int n) {
    if (n < 0) {
        return 0;
    }
    if (n == 0) return 0;
    if (n == 1) return 1;
    return jacobsthal(n - 1) + 2 * jacobsthal(n - 2);
}

int main(int argc, const char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return 1;
    }

    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || val < 0 || val > 64) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    printf("%llu\n", jacobsthal((int)val));
    return 0;
}
#include <stdio.h>
#include <stdlib.h>

unsigned long long find_nth_octagonal(int n) {
    if (n <= 0) {
        return 0;
    }
    return (unsigned long long)n * (3 * n - 2);
}

int main(int argc, char const * const * argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return 1;
    }

    char *endptr;
    long val = strtol(argv[1], &endptr, 10);

    if (endptr == argv[1] || *endptr != '\0' || val <= 0 || val > 2147483647) {
        fprintf(stderr, "Error: n must be a positive integer.\n");
        return 1;
    }

    unsigned long long result = find_nth_octagonal((int)val);
    printf("%llu\n", result);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int find_closest_smaller(int n) {
    if (n > INT_MIN) {
        return n - 1;
    }
    exit(EXIT_FAILURE);
}

int main(int argc, char **argv) {
    int n;
    char *endptr;
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    long val = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || val < INT_MIN || val > INT_MAX) {
        return EXIT_FAILURE;
    }
    n = (int)val;
    int result = find_closest_smaller(n);
    printf("%d\n", result);
    return EXIT_SUCCESS;
}
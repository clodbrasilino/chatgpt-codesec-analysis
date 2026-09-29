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
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    n = atoi(argv[1]);
    int result = find_closest_smaller(n);
    printf("%d\n", result);
    return EXIT_SUCCESS;
}
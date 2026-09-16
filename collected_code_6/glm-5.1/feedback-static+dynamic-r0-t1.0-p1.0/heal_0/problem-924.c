#include <stdio.h>
#include <stdlib.h>

int find_maximum(int a, int b) {
    return a > b ? a : b;
}

int main(int argc, char *argv[]) {
    int a, b, max;
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <int> <int>\n", argv[0]);
        return EXIT_FAILURE;
    }
    if (sscanf(argv[1], "%d", &a) != 1) {
        return EXIT_FAILURE;
    }
    if (sscanf(argv[2], "%d", &b) != 1) {
        return EXIT_FAILURE;
    }
    max = find_maximum(a, b);
    printf("%d\n", max);
    return EXIT_SUCCESS;
}
#include <stdio.h>
#include <stdlib.h>

int find_min(int a, int b) {
    return a < b ? a : b;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <int> <int>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr1;
    long val1 = strtol(argv[1], &endptr1, 10);
    if (*endptr1 != '\0' || val1 < -2147483648 || val1 > 2147483647) {
        return EXIT_FAILURE;
    }

    char *endptr2;
    long val2 = strtol(argv[2], &endptr2, 10);
    if (*endptr2 != '\0' || val2 < -2147483648 || val2 > 2147483647) {
        return EXIT_FAILURE;
    }

    int a = (int)val1;
    int b = (int)val2;

    printf("%d\n", find_min(a, b));

    return EXIT_SUCCESS;
}
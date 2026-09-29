#include <stdio.h>
#include <stdlib.h>

int perimeter(int side) {
    if (side < 0) {
        return -1;
    }
    return 4 * side;
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || val < 0 || val > 2147483647) {
        return EXIT_FAILURE;
    }
    int side = (int)val;
    int result = perimeter(side);
    if (result < 0) {
        return EXIT_FAILURE;
    }
    printf("%d\n", result);
    return EXIT_SUCCESS;
}
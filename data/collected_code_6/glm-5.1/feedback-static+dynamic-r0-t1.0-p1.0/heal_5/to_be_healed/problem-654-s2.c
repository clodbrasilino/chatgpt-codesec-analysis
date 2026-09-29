#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int calculate_perimeter(int length, int width) {
    if (length < 0 || width < 0) {
        return -1;
    }
    return 2 * (length + width);
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    if (argc != 3) {
        return EXIT_FAILURE;
    }

    char *endptr1;
    long l = strtol(argv[1], &endptr1, 10);
    if (*endptr1 != '\0' || endptr1 == argv[1]) {
        return EXIT_FAILURE;
    }

    char *endptr2;
    long w = strtol(argv[2], &endptr2, 10);
    if (*endptr2 != '\0' || endptr2 == argv[2]) {
        return EXIT_FAILURE;
    }

    if (l < 0 || l > INT_MAX || w < 0 || w > INT_MAX) {
        return EXIT_FAILURE;
    }

    int length = (int)l;
    int width = (int)w;

    int perimeter = calculate_perimeter(length, width);
    if (perimeter < 0) {
        return EXIT_FAILURE;
    }

    printf("%d\n", perimeter);

    return EXIT_SUCCESS;
}
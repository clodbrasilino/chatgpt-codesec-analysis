#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

int area_rectangle(int width, int height) {
    if (width < 0 || height < 0) {
        return -1;
    }
    if ((long)width * height > INT_MAX) {
        return -1;
    }
    return width * height;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <width> <height>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    errno = 0;
    long width = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || errno == ERANGE || width < 0 || width > INT_MAX) {
        fprintf(stderr, "Invalid input: width must be a valid non-negative integer\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    long height = strtol(argv[2], &endptr, 10);
    if (*endptr != '\0' || errno == ERANGE || height < 0 || height > INT_MAX) {
        fprintf(stderr, "Invalid input: height must be a valid non-negative integer\n");
        return EXIT_FAILURE;
    }

    int result = area_rectangle((int)width, (int)height);
    if (result < 0) {
        fprintf(stderr, "Error calculating area\n");
        return EXIT_FAILURE;
    }

    printf("%d\n", result);
    return EXIT_SUCCESS;
}
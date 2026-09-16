#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int calculate_perimeter(int length, int width) {
    if (length < 0 || width < 0) {
        return -1;
    }

    if ((length > 0 && width > INT_MAX / 2) || (width > 0 && length > INT_MAX / 2)) {
        return -1;
    }

    return 2 * (length + width);
}

int main(int argc, char * const * const argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <length> <width>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || val < 0 || val > INT_MAX) {
        fprintf(stderr, "Invalid length\n");
        return EXIT_FAILURE;
    }
    int length = (int)val;

    val = strtol(argv[2], &endptr, 10);
    if (*endptr != '\0' || val < 0 || val > INT_MAX) {
        fprintf(stderr, "Invalid width\n");
        return EXIT_FAILURE;
    }
    int width = (int)val;

    int perimeter = calculate_perimeter(length, width);
    if (perimeter < 0) {
        fprintf(stderr, "Calculation error\n");
        return EXIT_FAILURE;
    }

    printf("%d\n", perimeter);

    return EXIT_SUCCESS;
}
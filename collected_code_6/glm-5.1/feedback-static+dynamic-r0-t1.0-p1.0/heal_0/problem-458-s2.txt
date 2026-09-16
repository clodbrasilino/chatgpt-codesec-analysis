#include <stdio.h>
#include <stdlib.h>

int area_rectangle(int width, int height) {
    if (width < 0 || height < 0) {
        return -1;
    }
    return width * height;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <width> <height>\n", argv[0]);
        return EXIT_FAILURE;
    }

    long width = strtol(argv[1], NULL, 10);
    long height = strtol(argv[2], NULL, 10);

    if (width < 0 || height < 0) {
        fprintf(stderr, "Invalid input: dimensions must be non-negative\n");
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
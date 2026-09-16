#include <stdio.h>
#include <stdlib.h>

int area_rectangle(int width, int height) {
    if (width <= 0 || height <= 0) {
        return -1;
    }
    return width * height;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <width> <height>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || val <= 0 || val > 2147483647) {
        return EXIT_FAILURE;
    }
    int width = (int)val;

    val = strtol(argv[2], &endptr, 10);
    if (*endptr != '\0' || val <= 0 || val > 2147483647) {
        return EXIT_FAILURE;
    }
    int height = (int)val;

    int result = area_rectangle(width, height);
    if (result == -1) {
        return EXIT_FAILURE;
    }

    printf("%d\n", result);
    return EXIT_SUCCESS;
}
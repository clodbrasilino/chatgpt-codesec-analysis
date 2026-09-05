#include <stdio.h>
#include <stdlib.h>

float find_cuboid_volume(float length, float width, float height) {
    if (length <= 0.0f || width <= 0.0f || height <= 0.0f) {
        return -1.0f;
    }
    return length * width * height;
}

int main(int argc, const char * const argv[const]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <length> <width> <height>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr_l, *endptr_w, *endptr_h;
    float length = strtof(argv[1], &endptr_l);
    float width = strtof(argv[2], &endptr_w);
    float height = strtof(argv[3], &endptr_h);

    if (*endptr_l != '\0' || *endptr_w != '\0' || *endptr_h != '\0') {
        fprintf(stderr, "Error: Invalid numeric input.\n");
        return EXIT_FAILURE;
    }

    float volume = find_cuboid_volume(length, width, height);

    if (volume < 0.0f) {
        fprintf(stderr, "Error: Dimensions must be strictly positive.\n");
        return EXIT_FAILURE;
    }

    printf("%.4f\n", volume);

    return EXIT_SUCCESS;
}
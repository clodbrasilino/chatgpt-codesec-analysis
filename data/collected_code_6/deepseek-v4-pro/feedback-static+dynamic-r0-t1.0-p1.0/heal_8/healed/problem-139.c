#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <errno.h>
#include <float.h>

#define INPUT_BUFFER_SIZE 128

float calculate_circumference(float radius) {
    return 2.0f * (float)M_PI * radius;
}

int main(void) {
    char input[INPUT_BUFFER_SIZE];
    float radius;
    float circumference;
    char *endptr;
    size_t len;
    size_t i;
    int c;

    if (fgets(input, sizeof(input), stdin) == NULL) {
        return EXIT_FAILURE;
    }

    len = strlen(input);
    if (len == 0) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (input[len - 1] == '\n') {
        input[len - 1] = '\0';
        len--;
    } else {
        if (len == sizeof(input) - 1) {
            while ((c = getchar()) != '\n' && c != EOF) {
            }
            fprintf(stderr, "Input too long\n");
            return EXIT_FAILURE;
        }
    }

    if (len == 0) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    radius = strtof(input, &endptr);

    if (endptr == input || *endptr != '\0') {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (errno == ERANGE) {
        fprintf(stderr, "Number out of range\n");
        return EXIT_FAILURE;
    }

    if (radius < 0.0f) {
        fprintf(stderr, "Radius cannot be negative\n");
        return EXIT_FAILURE;
    }

    if (radius > FLT_MAX / (2.0f * (float)M_PI)) {
        fprintf(stderr, "Radius too large, circumference would overflow\n");
        return EXIT_FAILURE;
    }

    circumference = calculate_circumference(radius);

    printf("%.2f\n", circumference);

    return EXIT_SUCCESS;
}
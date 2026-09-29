#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <errno.h>
#include <float.h>
#include <stdbool.h>

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
    bool has_newline = false;

    if (fgets(input, sizeof(input), stdin) == NULL) {
        return EXIT_FAILURE;
    }

    len = strnlen(input, sizeof(input));
    if (len == 0 || input[0] == '\n') {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
        len--;
        has_newline = true;
    }

    if (!has_newline) {
        if (len == sizeof(input) - 1) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {
            }
            fprintf(stderr, "Input too long\n");
            return EXIT_FAILURE;
        }
        if (len < sizeof(input)) {
            input[len] = '\0';
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
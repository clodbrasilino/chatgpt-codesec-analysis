#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <float.h>
#include <math.h>

#define INPUT_BUFFER_SIZE 256

static double calculate_cuboid_volume(double length, double width, double height) {
    return length * width * height;
}

static int read_dimension(const char *prompt, double *value) {
    char input_buffer[INPUT_BUFFER_SIZE];
    size_t len;
    char *endptr;
    double temp;

    printf("%s", prompt);
    if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 0;
    }

    len = strnlen(input_buffer, sizeof(input_buffer));
    if (len == 0 || (len == 1 && input_buffer[0] == '\n')) {
        fprintf(stderr, "Empty input\n");
        return 0;
    }

    if (len >= sizeof(input_buffer)) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
            if (c == '\0') {
                fprintf(stderr, "Invalid input\n");
                return 0;
            }
        }
        fprintf(stderr, "Input too long\n");
        return 0;
    }

    if (input_buffer[len - 1] == '\n') {
        input_buffer[len - 1] = '\0';
        len--;
    }

    if (len == 0) {
        fprintf(stderr, "Empty input\n");
        return 0;
    }

    errno = 0;
    temp = strtod(input_buffer, &endptr);

    if (endptr == input_buffer) {
        fprintf(stderr, "Invalid input\n");
        return 0;
    }

    while (*endptr != '\0') {
        if (*endptr != ' ' && *endptr != '\t') {
            fprintf(stderr, "Invalid input\n");
            return 0;
        }
        endptr++;
    }

    if (errno == ERANGE) {
        fprintf(stderr, "Invalid input\n");
        return 0;
    }

    if (temp <= 0.0 || temp > DBL_MAX / 2.0) {
        fprintf(stderr, "Invalid input\n");
        return 0;
    }

    if (!isfinite(temp)) {
        fprintf(stderr, "Invalid input\n");
        return 0;
    }

    *value = temp;
    return 1;
}

int main(void) {
    double length, width, height, volume;
    double base_area;

    if (!read_dimension("Enter length: ", &length)) {
        return EXIT_FAILURE;
    }

    if (!read_dimension("Enter width: ", &width)) {
        return EXIT_FAILURE;
    }

    if (!read_dimension("Enter height: ", &height)) {
        return EXIT_FAILURE;
    }

    base_area = width * height;
    if (width > 0.0 && base_area / width != height) {
        fprintf(stderr, "Volume calculation would overflow\n");
        return EXIT_FAILURE;
    }

    if (length > 0.0 && DBL_MAX / length < base_area) {
        fprintf(stderr, "Volume calculation would overflow\n");
        return EXIT_FAILURE;
    }

    volume = calculate_cuboid_volume(length, width, height);
    printf("Volume of cuboid: %.2f\n", volume);

    return EXIT_SUCCESS;
}
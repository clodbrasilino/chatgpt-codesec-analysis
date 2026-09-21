#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <float.h>
#include <math.h>

#define INPUT_BUFFER_SIZE 256

double calculate_cuboid_volume(double length, double width, double height) {
    return length * width * height;
}

static int read_dimension(const char *prompt, double *value) {
    char input_buffer[INPUT_BUFFER_SIZE];
    size_t len;
    int c;

    printf("%s", prompt);
    if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 0;
    }

    len = strnlen(input_buffer, sizeof(input_buffer));
    if (len == 0) {
        fprintf(stderr, "Empty input\n");
        return 0;
    }

    if (input_buffer[len - 1] == '\n') {
        input_buffer[len - 1] = '\0';
        len--;
    } else {
        while ((c = getchar()) != '\n' && c != EOF);
        fprintf(stderr, "Input too long\n");
        return 0;
    }

    if (len == 0) {
        fprintf(stderr, "Empty input\n");
        return 0;
    }

    if (sscanf(input_buffer, "%lf", value) != 1 || *value <= 0 || *value > DBL_MAX / 2) {
        fprintf(stderr, "Invalid input\n");
        return 0;
    }

    return 1;
}

int main(void) {
    double length, width, height, volume;

    if (!read_dimension("Enter length: ", &length)) {
        return EXIT_FAILURE;
    }

    if (!read_dimension("Enter width: ", &width)) {
        return EXIT_FAILURE;
    }

    if (!read_dimension("Enter height: ", &height)) {
        return EXIT_FAILURE;
    }

    if (width > DBL_MAX / height) {
        fprintf(stderr, "Volume calculation would overflow\n");
        return EXIT_FAILURE;
    }

    if (length > DBL_MAX / (width * height)) {
        fprintf(stderr, "Volume calculation would overflow\n");
        return EXIT_FAILURE;
    }

    volume = calculate_cuboid_volume(length, width, height);
    printf("Volume of cuboid: %.2f\n", volume);

    return EXIT_SUCCESS;
}
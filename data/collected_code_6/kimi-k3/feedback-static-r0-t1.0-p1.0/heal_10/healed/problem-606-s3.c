#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

#define INPUT_BUFFER_SIZE 128

double degrees_to_radians(double degrees) {
    return degrees * (M_PI / 180.0);
}

int main(void) {
    char input_buffer[INPUT_BUFFER_SIZE];
    char *end_ptr;
    double degrees;
    double radians;
    size_t len;

    if (fgets(input_buffer, INPUT_BUFFER_SIZE, stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    if (strchr(input_buffer, '\n') == NULL && !feof(stdin)) {
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }

    len = strnlen(input_buffer, INPUT_BUFFER_SIZE);
    if (len == INPUT_BUFFER_SIZE) {
        fprintf(stderr, "Input not null-terminated\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    degrees = strtod(input_buffer, &end_ptr);

    if (end_ptr == input_buffer) {
        fprintf(stderr, "No digits were found\n");
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end_ptr)) {
        end_ptr++;
    }

    if (*end_ptr != '\0') {
        fprintf(stderr, "Invalid trailing characters\n");
        return EXIT_FAILURE;
    }

    if (errno == ERANGE) {
        fprintf(stderr, "Input value out of range\n");
        return EXIT_FAILURE;
    }

    radians = degrees_to_radians(degrees);

    printf("%f degrees is %f radians\n", degrees, radians);

    return EXIT_SUCCESS;
}
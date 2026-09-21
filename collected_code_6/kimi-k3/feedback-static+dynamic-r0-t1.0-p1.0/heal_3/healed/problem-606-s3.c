#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>

double degrees_to_radians(double degrees) {
    return degrees * (M_PI / 180.0);
}

int main(void) {
    char input_buffer[128];
    char *end_ptr;
    double degrees;
    double radians;
    size_t len;

    if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    input_buffer[sizeof(input_buffer) - 1] = '\0';
    len = strnlen(input_buffer, sizeof(input_buffer));
    if (len > 0 && input_buffer[len - 1] == '\n') {
        input_buffer[len - 1] = '\0';
    }

    errno = 0;
    degrees = strtod(input_buffer, &end_ptr);

    if (end_ptr == input_buffer) {
        fprintf(stderr, "No digits were found\n");
        return EXIT_FAILURE;
    }

    if (errno == ERANGE) {
        fprintf(stderr, "Input value out of range\n");
        return EXIT_FAILURE;
    }

    while (*end_ptr != '\0' && isspace((unsigned char)*end_ptr)) {
        end_ptr++;
    }

    if (*end_ptr != '\0') {
        fprintf(stderr, "Invalid trailing characters\n");
        return EXIT_FAILURE;
    }

    radians = degrees_to_radians(degrees);

    printf("%f degrees is %f radians\n", degrees, radians);

    return EXIT_SUCCESS;
}
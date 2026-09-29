#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <float.h>

double cube_surface_area(double side_length) {
    if (side_length <= 0.0) {
        return -1.0;
    }
    return 6.0 * side_length * side_length;
}

int main(void) {
    double input;
    char *buffer = NULL;
    size_t buffer_size = 0;
    char *endptr;
    ssize_t chars_read;

    printf("Enter cube side length: ");
    chars_read = getline(&buffer, &buffer_size, stdin);
    if (chars_read == -1) {
        fprintf(stderr, "Error reading input\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }

    errno = 0;
    input = strtod(buffer, &endptr);

    if (endptr == buffer || *endptr != '\0') {
        fprintf(stderr, "Invalid input\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    if (errno == ERANGE || input > DBL_MAX || input < -DBL_MAX) {
        fprintf(stderr, "Input out of range\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    free(buffer);
    double area = cube_surface_area(input);

    if (area < 0.0) {
        fprintf(stderr, "Side length must be positive\n");
        return EXIT_FAILURE;
    }

    printf("Surface area: %.2f\n", area);
    return EXIT_SUCCESS;
}
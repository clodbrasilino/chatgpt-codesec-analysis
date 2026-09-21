#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <errno.h>
#include <float.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include <stdint.h>

double calculate_polygon_perimeter(int sides, double side_length) {
    if (sides < 3) {
        errno = EINVAL;
        return -1.0;
    }
    if (side_length < 0.0 || !isfinite(side_length)) {
        errno = EINVAL;
        return -1.0;
    }
    if (side_length > DBL_MAX / (double)sides) {
        errno = ERANGE;
        return -1.0;
    }
    return (double)sides * side_length;
}

static int read_line(char *buffer, size_t size) {
    size_t len;

    if (buffer == NULL || size == 0) {
        return 0;
    }

    if (fgets(buffer, size, stdin) == NULL) {
        buffer[0] = '\0';
        return 0;
    }

    len = strnlen(buffer, size);
    if (len == 0) {
        return 0;
    }

    if (buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
        return 1;
    }

    if (len == size - 1) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {}
        buffer[0] = '\0';
        return 0;
    }

    return 1;
}

int main(void) {
    char input_buffer[256];
    int num_sides = 0;
    double side_len = 0.0;
    double perimeter = 0.0;
    char *end_ptr = NULL;
    long parsed_sides = 0;
    size_t input_len;

    printf("Enter number of sides: ");
    if (!read_line(input_buffer, sizeof(input_buffer))) {
        fprintf(stderr, "Error reading input for number of sides.\n");
        return EXIT_FAILURE;
    }

    input_len = strnlen(input_buffer, sizeof(input_buffer));
    if (input_len >= sizeof(input_buffer)) {
        fprintf(stderr, "Input overflow for number of sides.\n");
        return EXIT_FAILURE;
    }

    if (input_buffer[0] == '\0') {
        fprintf(stderr, "Empty input for number of sides.\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed_sides = strtol(input_buffer, &end_ptr, 10);
    if (errno == ERANGE || end_ptr == input_buffer || *end_ptr != '\0') {
        fprintf(stderr, "Invalid input for number of sides.\n");
        return EXIT_FAILURE;
    }

    if (parsed_sides > INT_MAX || parsed_sides < INT_MIN) {
        fprintf(stderr, "Number of sides value overflow.\n");
        return EXIT_FAILURE;
    }
    num_sides = (int)parsed_sides;

    printf("Enter side length: ");
    if (!read_line(input_buffer, sizeof(input_buffer))) {
        fprintf(stderr, "Error reading input for side length.\n");
        return EXIT_FAILURE;
    }

    input_len = strnlen(input_buffer, sizeof(input_buffer));
    if (input_len >= sizeof(input_buffer)) {
        fprintf(stderr, "Input overflow for side length.\n");
        return EXIT_FAILURE;
    }

    if (input_buffer[0] == '\0') {
        fprintf(stderr, "Empty input for side length.\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    side_len = strtod(input_buffer, &end_ptr);
    if (errno == ERANGE || end_ptr == input_buffer || *end_ptr != '\0') {
        fprintf(stderr, "Invalid input for side length.\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    perimeter = calculate_polygon_perimeter(num_sides, side_len);
    if (errno != 0 || perimeter < 0.0) {
        fprintf(stderr, "Invalid polygon parameters.\n");
        return EXIT_FAILURE;
    }

    printf("Perimeter: %.15g\n", perimeter);
    return EXIT_SUCCESS;
}
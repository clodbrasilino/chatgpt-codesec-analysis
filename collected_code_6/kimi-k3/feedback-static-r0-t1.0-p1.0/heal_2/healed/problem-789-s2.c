#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>
#include <string.h>
#include <limits.h>

#define MAX_INPUT_LENGTH 64

static double calculate_perimeter(int sides, double side_length)
{
    return sides * side_length;
}

static int read_line(char *buffer, size_t size)
{
    size_t len;

    if (fgets(buffer, size, stdin) == NULL) {
        return -1;
    }

    len = strlen(buffer);
    if (len == 0) {
        return -1;
    }

    if (buffer[len - 1] != '\n') {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
        }
        return -1;
    }

    buffer[len - 1] = '\0';
    return 0;
}

int main(void)
{
    char input_buffer[MAX_INPUT_LENGTH];
    char *endptr;
    long sides;
    double side_length;
    double perimeter;

    if (read_line(input_buffer, sizeof(input_buffer)) != 0) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    sides = strtol(input_buffer, &endptr, 10);
    if (errno != 0 || endptr == input_buffer || *endptr != '\0' || sides < 3 || sides > 1000) {
        fprintf(stderr, "Invalid number of sides\n");
        return EXIT_FAILURE;
    }

    if (read_line(input_buffer, sizeof(input_buffer)) != 0) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    side_length = strtod(input_buffer, &endptr);
    if (errno != 0 || endptr == input_buffer || *endptr != '\0' || side_length <= 0.0 || !isfinite(side_length)) {
        fprintf(stderr, "Invalid side length\n");
        return EXIT_FAILURE;
    }

    if (side_length > DBL_MAX / sides) {
        fprintf(stderr, "Calculation overflow\n");
        return EXIT_FAILURE;
    }

    perimeter = calculate_perimeter((int)sides, side_length);

    if (!isfinite(perimeter)) {
        fprintf(stderr, "Calculation overflow\n");
        return EXIT_FAILURE;
    }

    printf("%.6f\n", perimeter);
    return EXIT_SUCCESS;
}
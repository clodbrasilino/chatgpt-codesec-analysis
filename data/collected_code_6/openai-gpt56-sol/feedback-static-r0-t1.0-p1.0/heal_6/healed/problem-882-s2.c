#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_BUFFER_SIZE 256

static int calculate_perimeter(double side_a, double side_b, double *perimeter)
{
    double sum;

    if (perimeter == NULL ||
        !isfinite(side_a) ||
        !isfinite(side_b) ||
        side_a <= 0.0 ||
        side_b <= 0.0 ||
        side_a > DBL_MAX - side_b) {
        return 0;
    }

    sum = side_a + side_b;

    if (sum > DBL_MAX / 2.0) {
        return 0;
    }

    *perimeter = 2.0 * sum;
    return isfinite(*perimeter);
}

static int discard_remaining_input(void)
{
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF) {
    }

    return ch == '\n' || !ferror(stdin);
}

static int read_positive_double(const char *prompt, double *value)
{
    char *buffer = NULL;
    char *end;
    double parsed_value;
    size_t capacity = 0;
    size_t length = 0;
    int ch;
    int result = 0;

    if (prompt == NULL || value == NULL) {
        return 0;
    }

    if (fputs(prompt, stdout) == EOF || fflush(stdout) == EOF) {
        return 0;
    }

    capacity = INPUT_BUFFER_SIZE;
    buffer = malloc(capacity);
    if (buffer == NULL) {
        return 0;
    }

    while ((ch = getchar()) != '\n' && ch != EOF) {
        char *resized_buffer;
        size_t new_capacity;

        if (length + 1 >= capacity) {
            if (capacity > (size_t)-1 / 2) {
                discard_remaining_input();
                goto cleanup;
            }

            new_capacity = capacity * 2;
            resized_buffer = realloc(buffer, new_capacity);
            if (resized_buffer == NULL) {
                discard_remaining_input();
                goto cleanup;
            }

            buffer = resized_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    if (ch == EOF && (ferror(stdin) || length == 0)) {
        goto cleanup;
    }

    buffer[length] = '\0';

    errno = 0;
    parsed_value = strtod(buffer, &end);

    if (end == buffer ||
        errno == ERANGE ||
        !isfinite(parsed_value) ||
        parsed_value <= 0.0) {
        goto cleanup;
    }

    while (*end == ' ' ||
           *end == '\t' ||
           *end == '\r' ||
           *end == '\f' ||
           *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        goto cleanup;
    }

    *value = parsed_value;
    result = 1;

cleanup:
    free(buffer);
    return result;
}

int main(void)
{
    double side_a;
    double side_b;
    double perimeter;

    if (!read_positive_double("Enter the first side length: ", &side_a) ||
        !read_positive_double("Enter the second side length: ", &side_b)) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!calculate_perimeter(side_a, side_b, &perimeter)) {
        fputs("Unable to calculate the perimeter.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Perimeter: %.2f\n", perimeter) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
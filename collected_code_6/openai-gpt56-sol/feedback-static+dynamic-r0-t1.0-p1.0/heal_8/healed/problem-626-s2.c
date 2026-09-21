#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int largest_inscribed_triangle(double radius, double *area)
{
    if (area == NULL || !isfinite(radius) || radius <= 0.0 ||
        radius > sqrt(DBL_MAX)) {
        return -1;
    }

    *area = radius * radius;
    return 0;
}

static int read_line(char **buffer)
{
    size_t capacity = 128U;
    size_t length = 0U;
    char *input;
    int ch;

    if (buffer == NULL) {
        return -1;
    }

    *buffer = NULL;
    input = malloc(capacity);
    if (input == NULL) {
        return -1;
    }

    for (;;) {
        ch = getchar();

        if (ch == '\n') {
            break;
        }

        if (ch == EOF) {
            if (ferror(stdin) || length == 0U) {
                free(input);
                return -1;
            }
            break;
        }

        if (length == SIZE_MAX - 1U) {
            free(input);
            return -1;
        }

        if (length + 1U >= capacity) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2U) {
                free(input);
                return -1;
            }

            new_capacity = capacity * 2U;
            resized = realloc(input, new_capacity);
            if (resized == NULL) {
                free(input);
                return -1;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    input[length] = '\0';
    *buffer = input;
    return 0;
}

int main(void)
{
    char *input = NULL;
    char *end = NULL;
    double radius;
    double area;

    if (read_line(&input) != 0) {
        fprintf(stderr, "Failed to read the radius.\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    radius = strtod(input, &end);

    if (end == input || errno == ERANGE) {
        fprintf(stderr, "Invalid radius.\n");
        free(input);
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0' || largest_inscribed_triangle(radius, &area) != 0) {
        fprintf(stderr, "Radius must be a positive finite number.\n");
        free(input);
        return EXIT_FAILURE;
    }

    free(input);

    if (printf("%.10g\n", area) < 0) {
        fprintf(stderr, "Failed to write the result.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
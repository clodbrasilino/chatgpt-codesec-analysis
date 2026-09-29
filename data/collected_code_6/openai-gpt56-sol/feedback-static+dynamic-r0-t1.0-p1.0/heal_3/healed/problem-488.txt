#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int pentagon_area(double side, double *area)
{
    const double factor =
        sqrt(5.0 * (5.0 + 2.0 * sqrt(5.0))) / 4.0;
    double result;

    if (area == NULL || !isfinite(side) || side <= 0.0) {
        return -1;
    }

    result = factor * side * side;

    if (!isfinite(result)) {
        return -1;
    }

    *area = result;
    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    char *end;
    double side;
    double area;
    int ch;

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        char *resized;
        size_t new_capacity;

        if (length == SIZE_MAX - 1) {
            free(input);
            fputs("Input is too long.\n", stderr);
            return EXIT_FAILURE;
        }

        if (length + 1 >= capacity) {
            if (capacity > SIZE_MAX / 2) {
                free(input);
                fputs("Input is too long.\n", stderr);
                return EXIT_FAILURE;
            }

            new_capacity = capacity == 0 ? 64 : capacity * 2;
            resized = realloc(input, new_capacity);

            if (resized == NULL) {
                free(input);
                fputs("Failed to read input.\n", stderr);
                return EXIT_FAILURE;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ch == EOF && ferror(stdin)) {
        free(input);
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (input == NULL) {
        input = malloc(1);
        if (input == NULL) {
            fputs("Failed to read input.\n", stderr);
            return EXIT_FAILURE;
        }
    }

    input[length] = '\0';

    errno = 0;
    end = NULL;
    side = strtod(input, &end);

    if (end == input || errno == ERANGE) {
        free(input);
        fputs("Invalid side length.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0' || pentagon_area(side, &area) != 0) {
        free(input);
        fputs("Side length must be a positive finite number.\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

    if (printf("%.6f\n", area) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
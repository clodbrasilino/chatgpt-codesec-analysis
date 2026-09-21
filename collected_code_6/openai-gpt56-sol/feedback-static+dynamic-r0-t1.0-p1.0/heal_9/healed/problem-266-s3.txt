#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_INPUT_LENGTH 4095U

static int cube_lateral_surface_area(double side, double *area)
{
    const double limit = sqrt(DBL_MAX / 4.0);

    if (area == NULL || !isfinite(side) || side < 0.0 || side > limit) {
        return -1;
    }

    *area = 4.0 * side * side;
    return 0;
}

static int discard_line(void)
{
    int ch;

    do {
        ch = getchar();
    } while (ch != '\n' && ch != EOF);

    return ch == EOF && ferror(stdin) ? -1 : 0;
}

static int read_line(char **line)
{
    size_t length = 0;
    size_t capacity = 64;
    char *buffer;

    if (line == NULL) {
        return -1;
    }

    *line = NULL;
    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    for (;;) {
        int ch = getchar();

        if (ch == '\n') {
            break;
        }

        if (ch == EOF) {
            if (ferror(stdin) || length == 0) {
                free(buffer);
                return -1;
            }
            break;
        }

        if (length == MAX_INPUT_LENGTH) {
            int status = discard_line();
            free(buffer);
            return status == 0 ? -1 : status;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *resized;

            if (capacity >= MAX_INPUT_LENGTH + 1U) {
                free(buffer);
                return -1;
            }

            new_capacity = capacity * 2U;
            if (new_capacity > MAX_INPUT_LENGTH + 1U) {
                new_capacity = MAX_INPUT_LENGTH + 1U;
            }

            resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                return -1;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 0;
}

int main(void)
{
    char *input = NULL;
    char *end;
    double side;
    double area;

    if (read_line(&input) != 0) {
        fputs("Failed to read the cube side length.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    side = strtod(input, &end);

    if (end == input || errno == ERANGE || !isfinite(side)) {
        free(input);
        fputs("Invalid cube side length.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0' || cube_lateral_surface_area(side, &area) != 0) {
        free(input);
        fputs("Invalid cube side length.\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

    if (printf("%.10g\n", area) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
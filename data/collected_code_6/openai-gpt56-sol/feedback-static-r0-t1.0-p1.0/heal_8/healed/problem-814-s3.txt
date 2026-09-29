#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int rhombus_area(double diagonal1, double diagonal2, double *area)
{
    double half_diagonal;
    double result;

    if (area == NULL ||
        !isfinite(diagonal1) ||
        !isfinite(diagonal2) ||
        diagonal1 <= 0.0 ||
        diagonal2 <= 0.0) {
        return -1;
    }

    half_diagonal = diagonal1 / 2.0;

    if (half_diagonal > DBL_MAX / diagonal2) {
        return -1;
    }

    result = half_diagonal * diagonal2;

    if (!isfinite(result)) {
        return -1;
    }

    *area = result;
    return 0;
}

static int read_line(char **line)
{
    char *buffer;
    size_t length;
    size_t capacity;

    if (line == NULL) {
        return -1;
    }

    *line = NULL;
    length = 0;
    capacity = 128;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    for (;;) {
        int ch = fgetc(stdin);

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

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return -1;
            }

            new_capacity = capacity * 2;
            resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                return -1;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        buffer[length] = (char)ch;
        ++length;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 0;
}

static int read_positive_double(const char *prompt, double *value)
{
    char *line;
    char *end;
    double parsed_value;

    if (prompt == NULL || value == NULL) {
        return -1;
    }

    if (fputs(prompt, stdout) == EOF || fflush(stdout) == EOF) {
        return -1;
    }

    line = NULL;
    if (read_line(&line) != 0) {
        return -1;
    }

    errno = 0;
    parsed_value = strtod(line, &end);

    if (end == line ||
        errno == ERANGE ||
        !isfinite(parsed_value) ||
        parsed_value <= 0.0) {
        free(line);
        return -1;
    }

    while (*end == ' ' ||
           *end == '\t' ||
           *end == '\r' ||
           *end == '\f' ||
           *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        free(line);
        return -1;
    }

    *value = parsed_value;
    free(line);
    return 0;
}

int main(void)
{
    double diagonal1;
    double diagonal2;
    double area;

    if (read_positive_double("Enter the first diagonal: ", &diagonal1) != 0 ||
        read_positive_double("Enter the second diagonal: ", &diagonal2) != 0) {
        if (fputs("Invalid input.\n", stderr) == EOF) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (rhombus_area(diagonal1, diagonal2, &area) != 0) {
        if (fputs("Unable to calculate the area.\n", stderr) == EOF) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("Area of the rhombus: %.2f\n", area) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
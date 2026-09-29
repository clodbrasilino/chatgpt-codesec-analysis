#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int rhombus_area(double diagonal1, double diagonal2, double *area)
{
    double result;

    if (area == NULL ||
        !isfinite(diagonal1) ||
        !isfinite(diagonal2) ||
        diagonal1 <= 0.0 ||
        diagonal2 <= 0.0 ||
        diagonal1 > DBL_MAX / diagonal2) {
        return -1;
    }

    result = (diagonal1 * diagonal2) / 2.0;

    if (!isfinite(result)) {
        return -1;
    }

    *area = result;
    return 0;
}

static int read_line(char **line)
{
    size_t length = 0;
    size_t capacity = 128;
    int ch;
    char *buffer;

    if (line == NULL) {
        return -1;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        char *resized;

        if (length == SIZE_MAX - 1) {
            free(buffer);
            return -1;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;

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

        buffer[length++] = (char)ch;
    }

    if (ch == EOF && length == 0) {
        free(buffer);
        return -1;
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
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (rhombus_area(diagonal1, diagonal2, &area) != 0) {
        fputs("Unable to calculate the area.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Area of the rhombus: %.2f\n", area) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
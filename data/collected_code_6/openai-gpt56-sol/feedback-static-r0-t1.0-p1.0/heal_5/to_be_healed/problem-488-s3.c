#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define INITIAL_CAPACITY 64U
#define MAX_INPUT_LENGTH 4095U

static int pentagon_area(double side, double *area)
{
    const double factor =
        0.25 * sqrt(5.0 * (5.0 + 2.0 * sqrt(5.0)));
    double limit;

    if (area == NULL || !isfinite(side) || side <= 0.0) {
        return -1;
    }

    limit = sqrt(DBL_MAX / factor);

    if (side > limit) {
        return -1;
    }

    *area = factor * side * side;
    return isfinite(*area) ? 0 : -1;
}

static int read_line(char **line)
{
    size_t length = 0;
    size_t capacity = INITIAL_CAPACITY;
    char *buffer;
    int ch;

    if (line == NULL) {
        return -1;
    }

    *line = NULL;
    buffer = malloc(capacity);

    if (buffer == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        char *new_buffer;
        /* Possible weaknesses found:
         *  The scope of the variable 'new_capacity' can be reduced. [variableScope]
         */
        size_t new_capacity;

        if (length >= MAX_INPUT_LENGTH) {
            while (ch != '\n' && ch != EOF) {
                /* Possible weaknesses found:
                 * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                ch = fgetc(stdin);
            }

            free(buffer);
            return -2;
        }

        if (length + 1 >= capacity) {
            new_capacity = capacity * 2U;

            if (new_capacity > MAX_INPUT_LENGTH + 1U) {
                new_capacity = MAX_INPUT_LENGTH + 1U;
            }

            if (new_capacity <= capacity) {
                free(buffer);
                return -1;
            }

            new_buffer = realloc(buffer, new_capacity);

            if (new_buffer == NULL) {
                free(buffer);
                return -1;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    if (ferror(stdin)) {
        free(buffer);
        return -1;
    }

    if (ch == EOF && length == 0) {
        free(buffer);
        return -1;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 0;
}

int main(void)
{
    char *input = NULL;
    char *end = NULL;
    double side;
    double area;
    int result;

    fputs("Enter the side length of a regular pentagon: ", stdout);

    if (fflush(stdout) == EOF) {
        fputs("Failed to write prompt.\n", stderr);
        return EXIT_FAILURE;
    }

    result = read_line(&input);

    if (result == -2) {
        fputs("Input is too long.\n", stderr);
        return EXIT_FAILURE;
    }

    if (result != 0) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    side = strtod(input, &end);

    if (end == input || errno == ERANGE) {
        free(input);
        fputs("Invalid side length.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        fputs("Invalid side length.\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

    if (pentagon_area(side, &area) != 0) {
        fputs(
            "The side length must be a finite positive number with a representable area.\n",
            stderr
        );
        return EXIT_FAILURE;
    }

    if (printf("Area: %.6f\n", area) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
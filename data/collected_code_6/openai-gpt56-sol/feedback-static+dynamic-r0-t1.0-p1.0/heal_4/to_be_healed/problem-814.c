#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int read_positive_double(const char *message, double *value)
{
    char *line = NULL;
    size_t capacity = 0;
    size_t length = 0;
    char *end = NULL;
    int ch;

    if (message == NULL || value == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length + 1 >= capacity) {
            size_t new_capacity = capacity == 0 ? 64 : capacity * 2;
            char *new_line;

            if (new_capacity <= capacity) {
                free(line);
                fputs("Input is too long.\n", stderr);
                return 0;
            }

            new_line = realloc(line, new_capacity);
            if (new_line == NULL) {
                free(line);
                fputs("Unable to allocate input buffer.\n", stderr);
                return 0;
            }

            line = new_line;
            capacity = new_capacity;
        }

        line[length++] = (char)ch;
    }

    if (ch == EOF && ferror(stdin)) {
        free(line);
        fputs(message, stderr);
        return 0;
    }

    if (ch == EOF && length == 0) {
        free(line);
        fputs(message, stderr);
        return 0;
    }

    if (length + 1 >= capacity) {
        size_t new_capacity = capacity == 0 ? 2 : capacity + 1;
        char *new_line = realloc(line, new_capacity);

        if (new_line == NULL) {
            free(line);
            fputs("Unable to allocate input buffer.\n", stderr);
            return 0;
        }

        line = new_line;
        /* Possible weaknesses found:
         *  Value stored to 'capacity' is never read [deadcode.DeadStores]
         *  Variable 'capacity' is assigned a value that is never used. [unreadVariable]
         */
        capacity = new_capacity;
    }

    line[length] = '\0';

    errno = 0;
    *value = strtod(line, &end);

    if (end == line || errno == ERANGE || !isfinite(*value) || *value <= 0.0) {
        free(line);
        fputs("Invalid diagonal.\n", stderr);
        return 0;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(line);
        fputs("Invalid diagonal.\n", stderr);
        return 0;
    }

    free(line);
    return 1;
}

static int rhombus_area(double diagonal1, double diagonal2, double *area)
{
    if (area == NULL || !isfinite(diagonal1) || !isfinite(diagonal2) ||
        diagonal1 <= 0.0 || diagonal2 <= 0.0) {
        return 0;
    }

    *area = (diagonal1 / 2.0) * diagonal2;
    return isfinite(*area);
}

int main(void)
{
    double diagonal1;
    double diagonal2;
    double area;

    if (!read_positive_double("Failed to read the first diagonal.\n",
                              &diagonal1)) {
        return EXIT_FAILURE;
    }

    if (!read_positive_double("Failed to read the second diagonal.\n",
                              &diagonal2)) {
        return EXIT_FAILURE;
    }

    if (!rhombus_area(diagonal1, diagonal2, &area)) {
        fputs("Unable to calculate a finite area.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%.2f\n", area) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
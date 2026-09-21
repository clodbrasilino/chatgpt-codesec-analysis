#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_SIZE 256

static int read_positive_double(const char *message, double *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[INPUT_SIZE];
    char *end;
    const char *newline;
    double parsed;

    if (message == NULL || value == NULL) {
        return 0;
    }

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        fputs(message, stderr);
        return 0;
    }

    newline = strchr(buffer, '\n');

    if (newline == NULL && !feof(stdin)) {
        int ch;

        do {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            ch = fgetc(stdin);
        } while (ch != '\n' && ch != EOF);

        if (ch == EOF && ferror(stdin)) {
            fputs(message, stderr);
        } else {
            fputs("Input is too long.\n", stderr);
        }

        return 0;
    }

    errno = 0;
    parsed = strtod(buffer, &end);

    if (end == buffer || errno == ERANGE || !isfinite(parsed) ||
        parsed <= 0.0) {
        fputs("Invalid diagonal.\n", stderr);
        return 0;
    }

    while (*end == ' ' || *end == '\t' || *end == '\v' ||
           *end == '\f' || *end == '\r' || *end == '\n') {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid diagonal.\n", stderr);
        return 0;
    }

    *value = parsed;
    return 1;
}

static int rhombus_area(double diagonal1, double diagonal2, double *area)
{
    double result;

    if (area == NULL || !isfinite(diagonal1) || !isfinite(diagonal2) ||
        diagonal1 <= 0.0 || diagonal2 <= 0.0) {
        return 0;
    }

    result = (diagonal1 / 2.0) * diagonal2;

    if (!isfinite(result)) {
        return 0;
    }

    *area = result;
    return 1;
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
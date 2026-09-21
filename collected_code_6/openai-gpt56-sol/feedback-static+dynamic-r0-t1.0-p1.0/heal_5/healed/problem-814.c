#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_SIZE 256

static int read_positive_double(const char *message, double *value)
{
    char buffer[INPUT_SIZE];
    char *end;
    int ch;

    if (message == NULL || value == NULL) {
        return 0;
    }

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        fputs(message, stderr);
        return 0;
    }

    if (buffer[0] == '\0') {
        fputs("Invalid diagonal.\n", stderr);
        return 0;
    }

    end = buffer;
    while (*end != '\0' && *end != '\n') {
        ++end;
    }

    if (*end != '\n' && !feof(stdin)) {
        while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        }

        if (ch == EOF && ferror(stdin)) {
            fputs(message, stderr);
        } else {
            fputs("Input is too long.\n", stderr);
        }

        return 0;
    }

    errno = 0;
    *value = strtod(buffer, &end);

    if (end == buffer || errno == ERANGE || !isfinite(*value) || *value <= 0.0) {
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
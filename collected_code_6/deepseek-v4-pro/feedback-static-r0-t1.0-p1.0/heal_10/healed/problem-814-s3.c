#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <float.h>

double rhombus_area(double diagonal1, double diagonal2) {
    return (diagonal1 * diagonal2) / 2.0;
}

int main(void) {
    double d1, d2, area;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char *endptr;

    printf("Enter first diagonal: ");
    read = getline(&line, &len, stdin);
    if (read == -1) {
        if (ferror(stdin)) {
            fprintf(stderr, "Error reading input\n");
        } else {
            fprintf(stderr, "No input provided\n");
        }
        free(line);
        return EXIT_FAILURE;
    }

    if (read > 0 && line[read - 1] == '\n') {
        line[read - 1] = '\0';
    }

    if (line[0] == '\0') {
        fprintf(stderr, "Invalid input for first diagonal\n");
        free(line);
        return EXIT_FAILURE;
    }

    errno = 0;
    d1 = strtod(line, &endptr);
    if (endptr == line || *endptr != '\0' || errno == ERANGE || d1 <= 0.0 || d1 > DBL_MAX / 2.0) {
        fprintf(stderr, "Invalid input for first diagonal\n");
        free(line);
        return EXIT_FAILURE;
    }

    printf("Enter second diagonal: ");
    read = getline(&line, &len, stdin);
    if (read == -1) {
        if (ferror(stdin)) {
            fprintf(stderr, "Error reading input\n");
        } else {
            fprintf(stderr, "No input provided\n");
        }
        free(line);
        return EXIT_FAILURE;
    }

    if (read > 0 && line[read - 1] == '\n') {
        line[read - 1] = '\0';
    }

    if (line[0] == '\0') {
        fprintf(stderr, "Invalid input for second diagonal\n");
        free(line);
        return EXIT_FAILURE;
    }

    errno = 0;
    d2 = strtod(line, &endptr);
    if (endptr == line || *endptr != '\0' || errno == ERANGE || d2 <= 0.0 || d2 > DBL_MAX / 2.0) {
        fprintf(stderr, "Invalid input for second diagonal\n");
        free(line);
        return EXIT_FAILURE;
    }

    free(line);

    area = rhombus_area(d1, d2);
    printf("Area of rhombus: %.2f\n", area);

    return EXIT_SUCCESS;
}
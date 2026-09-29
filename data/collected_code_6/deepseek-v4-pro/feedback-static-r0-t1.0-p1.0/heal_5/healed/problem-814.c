#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define INPUT_BUFFER_SIZE 128

double rhombus_area(double diagonal1, double diagonal2) {
    if (diagonal1 <= 0 || diagonal2 <= 0) {
        return -1.0;
    }
    return (diagonal1 * diagonal2) / 2.0;
}

int main(void) {
    double d1, d2, area;
    char input[INPUT_BUFFER_SIZE];
    char *endptr;
    size_t len;

    printf("Enter length of first diagonal: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    len = strlen(input);
    if (len == 0 || input[len - 1] != '\n') {
        if (len == sizeof(input) - 1) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    input[len - 1] = '\0';
    len--;

    if (len == 0) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    d1 = strtod(input, &endptr);
    if (endptr == input || *endptr != '\0' || errno == ERANGE) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    printf("Enter length of second diagonal: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    len = strlen(input);
    if (len == 0 || input[len - 1] != '\n') {
        if (len == sizeof(input) - 1) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    input[len - 1] = '\0';
    len--;

    if (len == 0) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    d2 = strtod(input, &endptr);
    if (endptr == input || *endptr != '\0' || errno == ERANGE) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    area = rhombus_area(d1, d2);
    if (area < 0) {
        fprintf(stderr, "Diagonals must be positive\n");
        return EXIT_FAILURE;
    }

    printf("Area of rhombus: %.2f\n", area);
    return EXIT_SUCCESS;
}
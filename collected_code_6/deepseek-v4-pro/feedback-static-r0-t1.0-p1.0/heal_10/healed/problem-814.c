#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stddef.h>

#define INPUT_BUFFER_SIZE 128

double rhombus_area(double diagonal1, double diagonal2) {
    if (diagonal1 <= 0 || diagonal2 <= 0) {
        return -1.0;
    }
    return (diagonal1 * diagonal2) / 2.0;
}

static int read_line(char *buffer, size_t size) {
    size_t len;

    if (fgets(buffer, size, stdin) == NULL) {
        return -1;
    }

    len = strnlen(buffer, size);
    if (len == 0) {
        return 0;
    }

    if (buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
        if (len - 1 == 0) {
            return 0;
        }
        return 1;
    }

    if (len == size - 1) {
        int c;
        while ((c = fgetc(stdin)) != '\n') {
            if (c == EOF) {
                clearerr(stdin);
                break;
            }
        }
    }

    return 0;
}

static int parse_double(const char *str, double *value) {
    char *endptr;

    errno = 0;
    *value = strtod(str, &endptr);
    if (endptr == str || *endptr != '\0' || errno == ERANGE) {
        return 0;
    }
    return 1;
}

int main(void) {
    char input[INPUT_BUFFER_SIZE];
    double d1, d2, area;
    int result;

    printf("Enter length of first diagonal: ");
    result = read_line(input, sizeof(input));
    if (result < 0) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    if (result == 0) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (!parse_double(input, &d1)) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    printf("Enter length of second diagonal: ");
    result = read_line(input, sizeof(input));
    if (result < 0) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    if (result == 0) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (!parse_double(input, &d2)) {
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
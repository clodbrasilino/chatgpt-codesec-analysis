#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <float.h>
#include <limits.h>

#define BUFFER_SIZE 512

static double calculate_parallelogram_perimeter(double base, double side) {
    if (base <= 0 || side <= 0) {
        return -1.0;
    }
    if (base > (DBL_MAX / 2.0) - side) {
        return -1.0;
    }
    return 2.0 * (base + side);
}

static void clear_input_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

static int read_double_input(const char *prompt, double *value) {
    char buffer[BUFFER_SIZE];
    char *endptr;
    size_t len;

    if (prompt == NULL || value == NULL) {
        return 0;
    }

    printf("%s", prompt);
    fflush(stdout);

    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        return 0;
    }

    len = strlen(buffer);
    if (len > 0 && buffer[len - 1] != '\n') {
        clear_input_buffer();
        return 0;
    }

    buffer[strcspn(buffer, "\n")] = '\0';

    if (buffer[0] == '\0') {
        return 0;
    }

    errno = 0;
    *value = strtod(buffer, &endptr);

    if (endptr == buffer || *endptr != '\0') {
        return 0;
    }

    if (errno == ERANGE) {
        return 0;
    }

    return 1;
}

int main(void) {
    double base = 0.0;
    double side = 0.0;
    double perimeter = 0.0;

    if (!read_double_input("Enter the base length of the parallelogram: ", &base)) {
        printf("Invalid input for base length.\n");
        return EXIT_FAILURE;
    }

    if (base <= 0.0) {
        printf("Invalid input for base length.\n");
        return EXIT_FAILURE;
    }

    if (!read_double_input("Enter the side length of the parallelogram: ", &side)) {
        printf("Invalid input for side length.\n");
        return EXIT_FAILURE;
    }

    if (side <= 0.0) {
        printf("Invalid input for side length.\n");
        return EXIT_FAILURE;
    }

    perimeter = calculate_parallelogram_perimeter(base, side);
    if (perimeter < 0.0) {
        printf("Lengths must be positive numbers.\n");
        return EXIT_FAILURE;
    }

    printf("The perimeter of the parallelogram is: %.2f\n", perimeter);

    return EXIT_SUCCESS;
}
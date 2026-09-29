#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <errno.h>

#define PI 3.14159265358979323846
#define INPUT_BUFFER_SIZE 128

double cylinder_volume(double radius, double height) {
    if (radius < 0 || height < 0) {
        return -1.0;
    }
    return PI * radius * radius * height;
}

static int read_and_validate_input(const char *prompt, double *value) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[INPUT_BUFFER_SIZE];
    char *endptr;
    size_t len;
    /* Possible weaknesses found:
     *  Unused variable: c [unusedVariable]
     */
    int c;

    printf("%s", prompt);
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 0;
    }

    len = strnlen(input, sizeof(input));
    if (len == 0) {
        fprintf(stderr, "Empty input\n");
        return 0;
    }

    if (input[len - 1] != '\n') {
        if (len == sizeof(input) - 1) {
            int ch;
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((ch = getchar()) != '\n' && ch != EOF) {
            }
            fprintf(stderr, "Input too long\n");
            return 0;
        }
    }

    errno = 0;
    *value = strtod(input, &endptr);
    if (endptr == input) {
        fprintf(stderr, "Invalid input\n");
        return 0;
    }

    while (*endptr == ' ' || *endptr == '\t') {
        endptr++;
    }

    if (*endptr != '\n' && *endptr != '\0') {
        fprintf(stderr, "Invalid input\n");
        return 0;
    }

    if (errno == ERANGE) {
        fprintf(stderr, "Input out of range\n");
        return 0;
    }

    return 1;
}

int main(void) {
    double radius, height, volume;

    if (!read_and_validate_input("Enter radius: ", &radius)) {
        return EXIT_FAILURE;
    }

    if (!read_and_validate_input("Enter height: ", &height)) {
        return EXIT_FAILURE;
    }

    volume = cylinder_volume(radius, height);
    if (volume < 0) {
        fprintf(stderr, "Radius and height must be non-negative\n");
        return EXIT_FAILURE;
    }

    printf("Volume: %.6f\n", volume);
    return EXIT_SUCCESS;
}
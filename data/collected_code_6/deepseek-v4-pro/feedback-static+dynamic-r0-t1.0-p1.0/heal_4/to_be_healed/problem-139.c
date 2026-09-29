#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <errno.h>
#include <float.h>

#define INPUT_BUFFER_SIZE 128

float calculate_circumference(float radius) {
    return 2.0f * (float)M_PI * radius;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[INPUT_BUFFER_SIZE];
    float radius;
    float circumference;
    char *endptr;
    size_t len;
    size_t i;

    if (fgets(input, sizeof(input), stdin) == NULL) {
        return EXIT_FAILURE;
    }

    input[sizeof(input) - 1] = '\0';

    len = 0;
    for (i = 0; i < sizeof(input) && input[i] != '\0'; i++) {
        len++;
    }

    if (len == sizeof(input) - 1 && input[len - 1] != '\n') {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF) {
        }
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }

    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }

    errno = 0;
    radius = strtof(input, &endptr);

    if (endptr == input || *endptr != '\0') {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (errno == ERANGE) {
        fprintf(stderr, "Number out of range\n");
        return EXIT_FAILURE;
    }

    if (radius < 0.0f) {
        fprintf(stderr, "Radius cannot be negative\n");
        return EXIT_FAILURE;
    }

    if (radius > FLT_MAX / (2.0f * (float)M_PI)) {
        fprintf(stderr, "Radius too large, circumference would overflow\n");
        return EXIT_FAILURE;
    }

    circumference = calculate_circumference(radius);

    printf("%.2f\n", circumference);

    return EXIT_SUCCESS;
}
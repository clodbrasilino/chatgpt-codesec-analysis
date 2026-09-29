#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>
#include <float.h>

float calculate_circumference(float radius) {
    return 2.0f * (float)M_PI * radius;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[72];
    float radius;
    float circumference;
    char *endptr;

    if (fgets(input, (int)sizeof(input), stdin) == NULL) {
        return EXIT_FAILURE;
    }

    errno = 0;
    radius = strtof(input, &endptr);

    if (endptr == input) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    while (*endptr == ' ' || *endptr == '\t') {
        endptr++;
    }
    if (*endptr != '\n' && *endptr != '\0') {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (errno == ERANGE) {
        fprintf(stderr, "Input out of range\n");
        return EXIT_FAILURE;
    }

    if (radius < 0.0f) {
        fprintf(stderr, "Radius cannot be negative\n");
        return EXIT_FAILURE;
    }

    circumference = calculate_circumference(radius);

    if (circumference > FLT_MAX || circumference < -FLT_MAX) {
        fprintf(stderr, "Result out of range\n");
        return EXIT_FAILURE;
    }

    printf("%.2f\n", (double)circumference);

    return EXIT_SUCCESS;
}
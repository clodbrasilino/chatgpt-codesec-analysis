#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>
#include <float.h>
#include <string.h>
#include <stdbool.h>

#define INPUT_BUFFER_SIZE 72

static float calculate_circumference(float radius) {
    return 2.0f * (float)M_PI * radius;
}

static int safe_getchar(void) {
    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    int c = getchar();
    return c;
}

static bool drain_input(void) {
    int c;
    bool truncated = false;
    while ((c = safe_getchar()) != '\n' && c != EOF) {
        truncated = true;
    }
    return truncated;
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

    if (fgets(input, (int)sizeof(input), stdin) == NULL) {
        return EXIT_FAILURE;
    }

    input[sizeof(input) - 1] = '\0';

    len = strnlen(input, sizeof(input));
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
        len--;
    }

    if (len >= (sizeof(input) - 1) && input[sizeof(input) - 2] != '\n') {
        bool truncated = drain_input();
        if (truncated) {
            fprintf(stderr, "Input too long\n");
            return EXIT_FAILURE;
        }
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
    if (*endptr != '\0') {
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

    errno = 0;
    circumference = calculate_circumference(radius);

    if (errno == ERANGE || circumference > FLT_MAX || circumference < -FLT_MAX) {
        fprintf(stderr, "Result out of range\n");
        return EXIT_FAILURE;
    }

    printf("%.2f\n", (double)circumference);

    return EXIT_SUCCESS;
}
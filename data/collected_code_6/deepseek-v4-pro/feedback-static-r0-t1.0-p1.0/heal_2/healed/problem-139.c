#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>
#include <float.h>
#include <string.h>

float calculate_circumference(float radius) {
    return 2.0f * (float)M_PI * radius;
}

int main(void) {
    char input[72];
    float radius;
    float circumference;
    char *endptr;
    size_t len;

    if (fgets(input, sizeof(input), stdin) == NULL) {
        return EXIT_FAILURE;
    }

    len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
        len--;
    }

    if (len >= sizeof(input)) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        fprintf(stderr, "Input too long\n");
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

    circumference = calculate_circumference(radius);

    if (errno == ERANGE || circumference > FLT_MAX || circumference < -FLT_MAX) {
        fprintf(stderr, "Result out of range\n");
        return EXIT_FAILURE;
    }

    printf("%.2f\n", (double)circumference);

    return EXIT_SUCCESS;
}
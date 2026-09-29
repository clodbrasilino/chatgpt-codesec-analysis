#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <errno.h>

#define PI 3.14159265358979323846

double cylinder_volume(double radius, double height) {
    if (radius < 0 || height < 0) {
        return -1.0;
    }
    return PI * radius * radius * height;
}

int main(void) {
    double radius, height, volume;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[128];
    char *endptr;
    size_t len;
    int c;

    printf("Enter radius: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    len = strnlen(input, sizeof(input));
    if (len == sizeof(input) - 1 && input[len] == '\0') {
        len = sizeof(input) - 1;
    }
    if (len > 0 && input[len] == '\0' && len == sizeof(input) - 1) {
        if (input[len - 1] != '\n') {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((c = getchar()) != '\n' && c != EOF);
            fprintf(stderr, "Input too long\n");
            return EXIT_FAILURE;
        }
    } else if (len > 0 && input[len - 1] != '\n') {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF);
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }
    errno = 0;
    radius = strtod(input, &endptr);
    if (endptr == input || (*endptr != '\n' && *endptr != '\0') || errno == ERANGE) {
        fprintf(stderr, "Invalid radius input\n");
        return EXIT_FAILURE;
    }

    printf("Enter height: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    len = strnlen(input, sizeof(input));
    if (len == sizeof(input) - 1 && input[len] == '\0') {
        len = sizeof(input) - 1;
    }
    if (len > 0 && input[len] == '\0' && len == sizeof(input) - 1) {
        if (input[len - 1] != '\n') {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((c = getchar()) != '\n' && c != EOF);
            fprintf(stderr, "Input too long\n");
            return EXIT_FAILURE;
        }
    } else if (len > 0 && input[len - 1] != '\n') {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF);
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }
    errno = 0;
    height = strtod(input, &endptr);
    if (endptr == input || (*endptr != '\n' && *endptr != '\0') || errno == ERANGE) {
        fprintf(stderr, "Invalid height input\n");
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
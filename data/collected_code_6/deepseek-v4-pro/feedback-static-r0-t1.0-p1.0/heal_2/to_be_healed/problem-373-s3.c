#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <float.h>

#define INPUT_BUFFER_SIZE 256

double calculate_cuboid_volume(double length, double width, double height) {
    return length * width * height;
}

int main(void) {
    double length, width, height, volume;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input_buffer[INPUT_BUFFER_SIZE];
    char *newline;

    printf("Enter length: ");
    if (fgets(input_buffer, INPUT_BUFFER_SIZE, stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    newline = strchr(input_buffer, '\n');
    if (newline == NULL) {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF);
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }
    *newline = '\0';
    if (sscanf(input_buffer, "%lf", &length) != 1 || length <= 0 || length > DBL_MAX / 2) {
        fprintf(stderr, "Invalid input for length\n");
        return EXIT_FAILURE;
    }

    printf("Enter width: ");
    if (fgets(input_buffer, INPUT_BUFFER_SIZE, stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    newline = strchr(input_buffer, '\n');
    if (newline == NULL) {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF);
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }
    *newline = '\0';
    if (sscanf(input_buffer, "%lf", &width) != 1 || width <= 0 || width > DBL_MAX / 2) {
        fprintf(stderr, "Invalid input for width\n");
        return EXIT_FAILURE;
    }

    printf("Enter height: ");
    if (fgets(input_buffer, INPUT_BUFFER_SIZE, stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    newline = strchr(input_buffer, '\n');
    if (newline == NULL) {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF);
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }
    *newline = '\0';
    if (sscanf(input_buffer, "%lf", &height) != 1 || height <= 0 || height > DBL_MAX / 2) {
        fprintf(stderr, "Invalid input for height\n");
        return EXIT_FAILURE;
    }

    if (length > DBL_MAX / (width * height)) {
        fprintf(stderr, "Volume calculation would overflow\n");
        return EXIT_FAILURE;
    }

    volume = calculate_cuboid_volume(length, width, height);
    printf("Volume of cuboid: %.2f\n", volume);

    return EXIT_SUCCESS;
}
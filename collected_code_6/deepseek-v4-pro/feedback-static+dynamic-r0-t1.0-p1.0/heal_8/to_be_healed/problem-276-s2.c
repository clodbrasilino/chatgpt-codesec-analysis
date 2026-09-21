#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>
#include <stddef.h>
#include <ctype.h>

#define PI 3.14159265358979323846
#define INPUT_BUFFER_SIZE 256

double cylinder_volume(double radius, double height) {
    if (radius < 0 || height < 0) {
        return -1.0;
    }
    return PI * radius * radius * height;
}

static void clear_input_buffer(void) {
    int c;
    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

static int read_and_validate_double(const char *prompt, double *value) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[INPUT_BUFFER_SIZE] = {0};
    char *endptr;
    size_t len;

    printf("%s", prompt);
    fflush(stdout);

    if (fgets(input, sizeof(input), stdin) == NULL) {
        if (ferror(stdin)) {
            fprintf(stderr, "Error reading input\n");
            clearerr(stdin);
        }
        return 0;
    }

    len = strnlen(input, sizeof(input));
    if (len == 0 || (len == 1 && input[0] == '\n')) {
        return 0;
    }

    if (len >= sizeof(input) - 1 && input[sizeof(input) - 2] != '\n') {
        fprintf(stderr, "Input too long\n");
        clear_input_buffer();
        return 0;
    }

    if (input[len - 1] == '\n') {
        input[len - 1] = '\0';
        /* Possible weaknesses found:
         *  Variable 'len' is assigned a value that is never used. [unreadVariable]
         */
        len--;
    }

    errno = 0;
    *value = strtod(input, &endptr);

    if (endptr == input) {
        fprintf(stderr, "Invalid input: no number found\n");
        return 0;
    }

    while (*endptr != '\0') {
        if (!isspace((unsigned char)*endptr)) {
            fprintf(stderr, "Invalid input: unexpected characters after number\n");
            return 0;
        }
        endptr++;
    }

    if (errno == ERANGE) {
        fprintf(stderr, "Invalid input: number out of range\n");
        return 0;
    }

    return 1;
}

int main(void) {
    double radius, height, volume;

    if (!read_and_validate_double("Enter radius: ", &radius)) {
        return EXIT_FAILURE;
    }

    if (!read_and_validate_double("Enter height: ", &height)) {
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
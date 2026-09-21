#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <errno.h>
#include <float.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_SIZE 256

double calculate_perimeter(double base, double side) {
    if (base < 0.0 || side < 0.0 || !isfinite(base) || !isfinite(side)) {
        return -1.0;
    }
    if (base > DBL_MAX / 2.0 || side > DBL_MAX / 2.0) {
        return -1.0;
    }
    return 2.0 * (base + side);
}

int read_double(const char *prompt, double *value) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[BUFFER_SIZE];
    char *endptr;
    size_t len;
    
    printf("%s", prompt);
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 0;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(buffer);
    if (len > 0 && buffer[len - 1] != '\n') {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF) {
        }
        fprintf(stderr, "Input too long\n");
        return 0;
    }
    
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
    
    endptr = buffer;
    while (isspace((unsigned char)*endptr)) {
        endptr++;
    }
    
    if (*endptr == '\0') {
        fprintf(stderr, "Invalid input\n");
        return 0;
    }
    
    errno = 0;
    *value = strtod(buffer, &endptr);
    
    if (endptr == buffer || errno == ERANGE || !isfinite(*value)) {
        fprintf(stderr, "Invalid input\n");
        return 0;
    }
    
    while (isspace((unsigned char)*endptr)) {
        endptr++;
    }
    
    if (*endptr != '\0') {
        fprintf(stderr, "Invalid input\n");
        return 0;
    }
    
    return 1;
}

int main(void) {
    double base, side;
    
    if (!read_double("Enter base: ", &base)) {
        return EXIT_FAILURE;
    }
    
    if (!read_double("Enter side: ", &side)) {
        return EXIT_FAILURE;
    }
    
    double perimeter = calculate_perimeter(base, side);
    if (perimeter < 0.0) {
        fprintf(stderr, "Invalid dimensions or overflow\n");
        return EXIT_FAILURE;
    }
    
    printf("Perimeter: %f\n", perimeter);
    return EXIT_SUCCESS;
}
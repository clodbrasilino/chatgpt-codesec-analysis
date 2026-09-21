#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

double calculate_electricity_bill(int units_consumed) {
    if (units_consumed < 0) {
        return -1;
    }
    
    if (units_consumed <= 100) {
        return units_consumed * 1.5;
    }
    else if (units_consumed <= 300) {
        return 100 * 1.5 + (units_consumed - 100) * 2.5;
    }
    else if (units_consumed <= 500) {
        return 100 * 1.5 + 200 * 2.5 + (units_consumed - 300) * 4.0;
    }
    else {
        return 100 * 1.5 + 200 * 2.5 + 200 * 4.0 + (units_consumed - 500) * 6.0;
    }
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    char *endptr;
    long val;
    size_t len;
    
    printf("Enter units consumed: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(buffer);
    if (len > 0 && buffer[len - 1] != '\n') {
        if (len == sizeof(buffer) - 1) {
            int ch;
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((ch = getchar()) != '\n' && ch != EOF) {
                if (ferror(stdin)) {
                    fprintf(stderr, "Error reading input\n");
                    return EXIT_FAILURE;
                }
            }
            fprintf(stderr, "Invalid input: line too long\n");
            return EXIT_FAILURE;
        }
    }
    
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
        len--;
    }
    
    if (len == 0) {
        fprintf(stderr, "Invalid input: empty line\n");
        return EXIT_FAILURE;
    }
    
    errno = 0;
    val = strtol(buffer, &endptr, 10);
    
    if (endptr == buffer) {
        fprintf(stderr, "Invalid input: no digits found\n");
        return EXIT_FAILURE;
    }
    
    while (*endptr != '\0') {
        if (*endptr != ' ' && *endptr != '\t') {
            fprintf(stderr, "Invalid input: non-numeric characters present\n");
            return EXIT_FAILURE;
        }
        endptr++;
    }
    
    if (errno == ERANGE || val < INT_MIN || val > INT_MAX) {
        fprintf(stderr, "Invalid input: value out of range\n");
        return EXIT_FAILURE;
    }
    
    double result = calculate_electricity_bill((int)val);
    
    if (result < 0) {
        fprintf(stderr, "Invalid input: units cannot be negative\n");
        return EXIT_FAILURE;
    }
    
    printf("Electricity bill: %.2f\n", result);
    
    return EXIT_SUCCESS;
}
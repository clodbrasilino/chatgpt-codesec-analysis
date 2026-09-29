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
    char buffer[256] = {0};
    char *endptr;
    long parsed_value;
    int input;
    double result;
    size_t len;
    int cleanup_char;

    printf("Enter units consumed: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    len = strnlen(buffer, sizeof(buffer));
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
    else if (len == sizeof(buffer) - 1 && buffer[len - 1] != '\n') {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((cleanup_char = getchar()) != '\n' && cleanup_char != EOF) {}
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }

    len = strnlen(buffer, sizeof(buffer));
    if (len == 0) {
        fprintf(stderr, "Invalid input: no digits found\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed_value = strtol(buffer, &endptr, 10);

    if (endptr == buffer) {
        fprintf(stderr, "Invalid input: no digits found\n");
        return EXIT_FAILURE;
    }

    while (*endptr == ' ' || *endptr == '\t') {
        endptr++;
    }

    if (*endptr != '\0') {
        fprintf(stderr, "Invalid input: non-numeric characters present\n");
        return EXIT_FAILURE;
    }

    if (errno == ERANGE || parsed_value > INT_MAX || parsed_value < INT_MIN) {
        fprintf(stderr, "Invalid input: number out of range\n");
        return EXIT_FAILURE;
    }

    input = (int)parsed_value;

    result = calculate_electricity_bill(input);

    if (result < 0) {
        fprintf(stderr, "Invalid input: units cannot be negative\n");
        return EXIT_FAILURE;
    }

    printf("Electricity bill: %.2f\n", result);

    return EXIT_SUCCESS;
}
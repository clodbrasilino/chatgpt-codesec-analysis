#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <string.h>

int first_digit(int num) {
    if (num == INT_MIN) {
        return 2;
    }
    if (num < 0) {
        num = -num;
    }
    while (num >= 10) {
        num /= 10;
    }
    return num;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[128];
    char *endptr;
    long input;
    int number;
    size_t len;

    printf("Enter an integer: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    len = strnlen(buffer, sizeof(buffer));

    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
        len--;
    } else {
        int c;
        int overflow = (len == sizeof(buffer) - 1) ? 1 : 0;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF) {
            overflow = 1;
        }
        if (overflow) {
            fprintf(stderr, "Input too long\n");
            return EXIT_FAILURE;
        }
    }

    if (buffer[0] == '\0') {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < len; i++) {
        if (buffer[i] == '\0') {
            fprintf(stderr, "Invalid input\n");
            return EXIT_FAILURE;
        }
    }

    errno = 0;
    input = strtol(buffer, &endptr, 10);

    if (errno == ERANGE || input < INT_MIN || input > INT_MAX) {
        fprintf(stderr, "Number out of range\n");
        return EXIT_FAILURE;
    }
    if (endptr == buffer || *endptr != '\0') {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    number = (int)input;
    printf("First digit: %d\n", first_digit(number));
    return EXIT_SUCCESS;
}
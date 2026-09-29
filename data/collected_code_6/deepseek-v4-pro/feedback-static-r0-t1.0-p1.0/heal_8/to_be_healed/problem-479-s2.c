#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>

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

bool contains_null(const char *buf, size_t len) {
    for (size_t i = 0; i < len; i++) {
        if (buf[i] == '\0') {
            return true;
        }
    }
    return false;
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
    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    len = strnlen(buffer, sizeof(buffer));

    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
        len--;
    } else {
        int c;
        bool overflow = false;
        if (len == sizeof(buffer) - 1) {
            overflow = true;
        }
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n') {
            if (c == EOF) {
                break;
            }
            overflow = true;
        }
        if (overflow) {
            if (len == sizeof(buffer) - 1) {
                /* Possible weaknesses found:
                 *  Variable 'buffer[sizeof(buffer)-1]' is assigned a value that is never used. [unreadVariable]
                 */
                buffer[sizeof(buffer) - 1] = '\0';
            }
            fprintf(stderr, "Input too long\n");
            return EXIT_FAILURE;
        }
    }

    if (len == 0) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (len >= sizeof(buffer)) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (contains_null(buffer, len)) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
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
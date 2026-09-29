#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

long long sum_of_squares(int n) {
    long long sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += (long long)i * i;
    }
    return sum;
}

static void clear_stdin_line(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

static bool has_trailing_characters(const char *input, size_t len, const char *endptr) {
    while (endptr < input + len) {
        if (*endptr != '\0' && *endptr != '\n' && *endptr != '\r') {
            return true;
        }
        endptr++;
    }
    return false;
}

int main(void) {
    char input_buffer[128];
    char *endptr;
    long val;
    size_t len;
    int n;

    printf("Enter a positive integer: ");
    if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return EXIT_FAILURE;
    }

    len = strnlen(input_buffer, sizeof(input_buffer));

    if (len == 0) {
        fprintf(stderr, "Input is empty.\n");
        return EXIT_FAILURE;
    }

    if (input_buffer[len - 1] != '\n') {
        if (len >= sizeof(input_buffer) - 1) {
            clear_stdin_line();
        }
        fprintf(stderr, "Input too long or not terminated properly.\n");
        return EXIT_FAILURE;
    }

    input_buffer[strcspn(input_buffer, "\r\n")] = '\0';

    len = strnlen(input_buffer, sizeof(input_buffer));
    if (len == 0) {
        fprintf(stderr, "Input is empty after trimming.\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    val = strtol(input_buffer, &endptr, 10);

    if (errno == ERANGE || val < 0 || val > INT_MAX) {
        fprintf(stderr, "Invalid input. Please enter a non-negative integer within range.\n");
        return EXIT_FAILURE;
    }

    if (endptr == input_buffer) {
        fprintf(stderr, "Invalid input. No digits found.\n");
        return EXIT_FAILURE;
    }

    if (has_trailing_characters(input_buffer, sizeof(input_buffer), endptr)) {
        fprintf(stderr, "Invalid input. Please enter a non-negative integer.\n");
        return EXIT_FAILURE;
    }

    n = (int)val;

    printf("Sum of squares from 1 to %d is %lld\n", n, sum_of_squares(n));

    return EXIT_SUCCESS;
}
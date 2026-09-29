#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>
#include <stdint.h>

long long sum_of_squares(int n) {
    long long sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += (long long)i * i;
    }
    return sum;
}

int main(void) {
    int n;
    char input_buffer[64];
    char *endptr;
    long val;
    size_t len;

    printf("Enter a positive integer: ");
    if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return EXIT_FAILURE;
    }

    len = strnlen(input_buffer, sizeof(input_buffer));
    if (len == 0 || (len > 0 && input_buffer[len - 1] != '\n')) {
        if (len == sizeof(input_buffer) - 1) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }
        fprintf(stderr, "Input too long or empty.\n");
        return EXIT_FAILURE;
    }

    input_buffer[strcspn(input_buffer, "\r\n")] = '\0';

    errno = 0;
    val = strtol(input_buffer, &endptr, 10);

    if (errno == ERANGE || val < 0 || val > INT_MAX) {
        fprintf(stderr, "Invalid input. Please enter a non-negative integer within range.\n");
        return EXIT_FAILURE;
    }

    if (endptr == input_buffer || *endptr != '\0') {
        fprintf(stderr, "Invalid input. Please enter a non-negative integer.\n");
        return EXIT_FAILURE;
    }

    n = (int)val;

    printf("Sum of squares from 1 to %d is %lld\n", n, sum_of_squares(n));

    return EXIT_SUCCESS;
}
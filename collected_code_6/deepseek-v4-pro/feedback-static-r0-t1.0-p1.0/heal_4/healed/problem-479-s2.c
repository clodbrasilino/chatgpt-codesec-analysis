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
    char buffer[128];
    char *endptr;
    long input;
    int number;
    size_t len;
    size_t i;

    printf("Enter an integer: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    len = 0;
    for (i = 0; i < sizeof(buffer); i++) {
        if (buffer[i] == '\0') {
            len = i;
            break;
        }
    }
    if (i == sizeof(buffer)) {
        buffer[sizeof(buffer) - 1] = '\0';
        len = sizeof(buffer) - 1;
    }

    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
        len--;
    } else {
        int c;
        int overflow = 0;
        if (len == sizeof(buffer) - 1) {
            overflow = 1;
        }
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
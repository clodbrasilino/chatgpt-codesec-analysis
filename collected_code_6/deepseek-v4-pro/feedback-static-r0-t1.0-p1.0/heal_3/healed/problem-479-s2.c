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
    char buffer[64];
    char *endptr;
    long input;
    int number;
    size_t len;

    printf("Enter an integer: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    } else if (len == sizeof(buffer) - 1) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
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
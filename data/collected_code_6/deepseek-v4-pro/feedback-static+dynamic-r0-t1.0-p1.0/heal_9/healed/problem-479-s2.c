#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>

int first_digit(int num) {
    int digit = 2;
    
    if (num == INT_MIN) {
        return digit;
    }
    if (num < 0) {
        num = -num;
    }
    while (num >= 10) {
        num /= 10;
    }
    digit = num;
    return digit;
}

int main(void) {
    char buffer[512];
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

    len = strnlen(buffer, sizeof(buffer));
    if (len == 0 || (len == 1 && buffer[0] == '\n')) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (buffer[len - 1] != '\n') {
        if (len == sizeof(buffer) - 1) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {
            }
            fprintf(stderr, "Input too long\n");
            return EXIT_FAILURE;
        }
    } else {
        buffer[len - 1] = '\0';
        len--;
    }

    i = 0;
    while (i < len && isspace((unsigned char)buffer[i])) {
        i++;
    }
    if (i >= len) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    input = strtol(buffer, &endptr, 10);

    if (errno == ERANGE || input < (long)INT_MIN || input > (long)INT_MAX) {
        fprintf(stderr, "Number out of range\n");
        return EXIT_FAILURE;
    }

    if (endptr == buffer) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    while (*endptr != '\0') {
        if (!isspace((unsigned char)*endptr)) {
            fprintf(stderr, "Invalid input\n");
            return EXIT_FAILURE;
        }
        endptr++;
    }

    number = (int)input;
    printf("%d\n", first_digit(number));
    return EXIT_SUCCESS;
}
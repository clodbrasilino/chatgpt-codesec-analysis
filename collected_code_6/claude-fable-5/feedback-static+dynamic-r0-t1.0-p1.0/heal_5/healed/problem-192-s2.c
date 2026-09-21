#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define BUFFER_SIZE 256

bool has_letter_and_digit(const char *str)
{
    bool has_letter = false;
    bool has_digit = false;

    if (str == NULL) {
        return false;
    }

    while (*str != '\0') {
        unsigned char c = (unsigned char)*str;
        if (isalpha(c)) {
            has_letter = true;
        } else if (isdigit(c)) {
            has_digit = true;
        }
        if (has_letter && has_digit) {
            return true;
        }
        str++;
    }

    return false;
}

static void flush_stdin(void)
{
    int c = 0;
    size_t guard = 0;
    const size_t max_flush = 1000000;

    while (guard < max_flush) {
        c = getchar();
        if (c == '\n' || c == EOF) {
            break;
        }
        guard++;
    }
}

int main(void)
{
    char buffer[BUFFER_SIZE];
    size_t len = 0;

    memset(buffer, 0, sizeof(buffer));

    printf("Enter a string: ");
    if (fflush(stdout) != 0) {
        fprintf(stderr, "Error flushing output\n");
        return EXIT_FAILURE;
    }

    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    buffer[sizeof(buffer) - 1] = '\0';

    len = strnlen(buffer, sizeof(buffer));
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    } else if (len == sizeof(buffer) - 1) {
        flush_stdin();
    }

    if (has_letter_and_digit(buffer)) {
        printf("The string contains at least one letter and one number.\n");
    } else {
        printf("The string does not contain both a letter and a number.\n");
    }

    return EXIT_SUCCESS;
}
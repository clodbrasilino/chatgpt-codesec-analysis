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
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

int main(void)
{
    char buffer[BUFFER_SIZE];

    printf("Enter a string: ");
    fflush(stdout);

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    buffer[sizeof(buffer) - 1] = '\0';

    size_t len = strnlen(buffer, sizeof(buffer));
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    } else {
        flush_stdin();
    }

    if (has_letter_and_digit(buffer)) {
        printf("The string contains at least one letter and one number.\n");
    } else {
        printf("The string does not contain both a letter and a number.\n");
    }

    return EXIT_SUCCESS;
}
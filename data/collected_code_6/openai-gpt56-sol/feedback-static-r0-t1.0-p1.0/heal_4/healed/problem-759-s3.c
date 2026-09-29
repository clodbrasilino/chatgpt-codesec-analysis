#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

bool is_decimal_with_precision_2(const char *text)
{
    const unsigned char *p = (const unsigned char *)text;

    if (p == NULL || *p == '\0') {
        return false;
    }

    if (*p == '+' || *p == '-') {
        ++p;
    }

    if (!isdigit(*p)) {
        return false;
    }

    while (isdigit(*p)) {
        ++p;
    }

    if (*p++ != '.') {
        return false;
    }

    if (!isdigit(p[0]) || !isdigit(p[1])) {
        return false;
    }

    return p[2] == '\0';
}

int main(void)
{
    char *input = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int ch = EOF;

    for (;;) {
        ch = fgetc(stdin);

        if (ch == EOF || ch == '\n') {
            break;
        }

        if (ch == '\r') {
            int next = fgetc(stdin);

            if (next != '\n' && next != EOF) {
                if (ungetc(next, stdin) == EOF) {
                    free(input);
                    puts("Invalid");
                    return EXIT_FAILURE;
                }
            }
            break;
        }

        if (length == capacity) {
            size_t new_capacity;
            char *new_input;

            if (capacity == 0) {
                new_capacity = 64;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(input);
                    puts("Invalid");
                    return EXIT_FAILURE;
                }
                new_capacity = capacity * 2;
            }

            new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                puts("Invalid");
                return EXIT_FAILURE;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ferror(stdin) || (ch == EOF && length == 0)) {
        free(input);
        puts("Invalid");
        return EXIT_FAILURE;
    }

    if (length == SIZE_MAX) {
        free(input);
        puts("Invalid");
        return EXIT_FAILURE;
    }

    if (capacity <= length) {
        char *new_input = realloc(input, length + 1);

        if (new_input == NULL) {
            free(input);
            puts("Invalid");
            return EXIT_FAILURE;
        }

        input = new_input;
    }

    input[length] = '\0';

    if (is_decimal_with_precision_2(input)) {
        free(input);
        puts("Valid");
        return EXIT_SUCCESS;
    }

    free(input);
    puts("Invalid");
    return EXIT_FAILURE;
}
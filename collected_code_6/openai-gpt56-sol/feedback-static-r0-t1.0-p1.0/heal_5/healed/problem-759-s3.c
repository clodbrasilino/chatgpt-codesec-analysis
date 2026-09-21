#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

bool is_decimal_with_precision_2(const char *text)
{
    if (text == NULL || *text == '\0') {
        return false;
    }

    const unsigned char *p = (const unsigned char *)text;

    if (*p == '+' || *p == '-') {
        ++p;
    }

    if (!isdigit(*p)) {
        return false;
    }

    do {
        ++p;
    } while (isdigit(*p));

    if (*p != '.') {
        return false;
    }

    ++p;

    if (!isdigit(p[0])) {
        return false;
    }

    ++p;

    if (!isdigit(p[0])) {
        return false;
    }

    ++p;

    return *p == '\0';
}

int main(void)
{
    char *input = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int ch;
    bool received_input = false;

    for (;;) {
        ch = fgetc(stdin);

        if (ch == EOF) {
            if (ferror(stdin)) {
                free(input);
                puts("Invalid");
                return EXIT_FAILURE;
            }
            break;
        }

        received_input = true;

        if (ch == '\n') {
            break;
        }

        if (ch == '\r') {
            int next = fgetc(stdin);

            if (next == EOF) {
                if (ferror(stdin)) {
                    free(input);
                    puts("Invalid");
                    return EXIT_FAILURE;
                }
            } else if (next != '\n' && ungetc(next, stdin) == EOF) {
                free(input);
                puts("Invalid");
                return EXIT_FAILURE;
            }

            break;
        }

        if (length == SIZE_MAX - 1) {
            free(input);
            puts("Invalid");
            return EXIT_FAILURE;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;

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

            char *new_input = realloc(input, new_capacity);

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

    if (!received_input) {
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
        capacity = length + 1;
    }

    input[length] = '\0';

    bool valid = is_decimal_with_precision_2(input);
    free(input);

    puts(valid ? "Valid" : "Invalid");
    return valid ? EXIT_SUCCESS : EXIT_FAILURE;
}
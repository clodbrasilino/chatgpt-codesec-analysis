#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

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

    if (*p != '.') {
        return false;
    }

    ++p;

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
    int ch;

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (ch == '\r') {
            int next = fgetc(stdin);

            if (next != '\n' && next != EOF) {
                ungetc(next, stdin);
            }
            break;
        }

        if (length == capacity) {
            size_t new_capacity = capacity == 0 ? 64 : capacity * 2;
            char *new_input;

            if (new_capacity <= capacity) {
                free(input);
                puts("Invalid");
                return 1;
            }

            new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                puts("Invalid");
                return 1;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ch == EOF && length == 0) {
        free(input);
        puts("Invalid");
        return 1;
    }

    if (length == capacity) {
        size_t new_capacity = capacity == 0 ? 1 : capacity + 1;
        char *new_input = realloc(input, new_capacity);

        if (new_input == NULL) {
            free(input);
            puts("Invalid");
            return 1;
        }

        input = new_input;
        capacity = new_capacity;
    }

    input[length] = '\0';

    if (is_decimal_with_precision_2(input)) {
        free(input);
        puts("Valid");
        return 0;
    }

    free(input);
    puts("Invalid");
    return 1;
}
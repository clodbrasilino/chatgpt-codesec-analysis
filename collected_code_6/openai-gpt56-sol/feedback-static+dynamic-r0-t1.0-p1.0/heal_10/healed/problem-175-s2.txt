#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_valid_parentheses(const char *str)
{
    if (str == NULL) {
        return false;
    }

    size_t balance = 0;

    for (; *str != '\0'; ++str) {
        if (*str == '(') {
            if (balance == SIZE_MAX) {
                return false;
            }
            ++balance;
        } else if (*str == ')') {
            if (balance == 0) {
                return false;
            }
            --balance;
        }
    }

    return balance == 0;
}

static char *read_line(FILE *stream)
{
    if (stream == NULL) {
        return NULL;
    }

    size_t capacity = 128;
    size_t length = 0;
    char *line = malloc(capacity);

    if (line == NULL) {
        return NULL;
    }

    for (;;) {
        if (length + 1 >= capacity) {
            if (capacity > SIZE_MAX / 2) {
                free(line);
                return NULL;
            }

            size_t new_capacity = capacity * 2;
            char *resized = realloc(line, new_capacity);

            if (resized == NULL) {
                free(line);
                return NULL;
            }

            line = resized;
            capacity = new_capacity;
        }

        int ch = fgetc(stream);

        if (ch == EOF) {
            if (ferror(stream)) {
                free(line);
                return NULL;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        line[length++] = (char)ch;
    }

    if (length > 0 && line[length - 1] == '\r') {
        --length;
    }

    line[length] = '\0';
    return line;
}

int main(void)
{
    char *input = read_line(stdin);

    if (input == NULL) {
        return EXIT_FAILURE;
    }

    bool valid = is_valid_parentheses(input);
    free(input);

    if (printf("%s\n", valid ? "True" : "False") < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
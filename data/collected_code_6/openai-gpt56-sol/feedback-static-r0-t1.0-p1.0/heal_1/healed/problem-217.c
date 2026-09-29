#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int find_first_repeated_character(const char *str, unsigned char *result)
{
    unsigned char seen[UCHAR_MAX + 1] = {0};

    if (str == NULL || result == NULL) {
        return 0;
    }

    while (*str != '\0') {
        unsigned char ch = (unsigned char)*str++;

        if (seen[ch]) {
            *result = ch;
            return 1;
        }

        seen[ch] = 1;
    }

    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0;
    size_t capacity = 0;
    unsigned char repeated;
    int ch;

    while ((ch = fgetc(stdin)) != EOF) {
        if (length + 1 >= capacity) {
            size_t new_capacity = capacity == 0 ? 128 : capacity * 2;
            char *new_input;

            if (new_capacity <= capacity) {
                free(input);
                return 1;
            }

            new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                return 1;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;

        if (ch == '\n') {
            break;
        }
    }

    if (ferror(stdin)) {
        free(input);
        return 1;
    }

    if (length == 0 && ch == EOF) {
        free(input);
        return 0;
    }

    if (length + 1 >= capacity) {
        size_t new_capacity = length + 1;
        char *new_input = realloc(input, new_capacity);

        if (new_input == NULL) {
            free(input);
            return 1;
        }

        input = new_input;
    }

    input[length] = '\0';

    if (find_first_repeated_character(input, &repeated)) {
        printf("%c\n", repeated);
    } else {
        puts("No repeated character");
    }

    free(input);
    return 0;
}
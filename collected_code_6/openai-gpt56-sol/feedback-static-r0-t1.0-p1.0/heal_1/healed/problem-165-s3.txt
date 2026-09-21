#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

size_t count_matching_positions(const char *str)
{
    size_t count = 0;

    if (str == NULL) {
        return 0;
    }

    for (size_t i = 0; i < 26 && str[i] != '\0'; ++i) {
        unsigned char ch = (unsigned char)str[i];

        if (isalpha(ch) && (unsigned char)tolower(ch) == (unsigned char)('a' + i)) {
            ++count;
        }
    }

    return count;
}

int main(void)
{
    size_t capacity = 128;
    size_t length = 0;
    char *input = malloc(capacity);

    if (input == NULL) {
        return 1;
    }

    for (;;) {
        int ch = fgetc(stdin);

        if (ch == EOF || ch == '\n') {
            if (ch == EOF && ferror(stdin)) {
                free(input);
                return 1;
            }
            break;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity = capacity * 2;
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
    }

    input[length] = '\0';
    printf("%zu\n", count_matching_positions(input));

    free(input);
    return 0;
}
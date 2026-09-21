#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool matches_pattern(const char *string, size_t length)
{
    return string != NULL &&
           length >= 2U &&
           string[0] == 'a' &&
           string[length - 1U] == 'b';
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0U;
    size_t length = 0U;
    int ch;

    while ((ch = fgetc(stdin)) != EOF && ch != '\n' && ch != '\r') {
        if (length == capacity) {
            size_t new_capacity = capacity == 0U ? 128U : capacity * 2U;
            char *expanded;

            if (new_capacity <= capacity) {
                free(input);
                return 1;
            }

            expanded = realloc(input, new_capacity);
            if (expanded == NULL) {
                free(input);
                return 1;
            }

            input = expanded;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ch == EOF && ferror(stdin)) {
        free(input);
        return 1;
    }

    if (matches_pattern(input, length)) {
        puts("Match");
    } else {
        puts("No match");
    }

    free(input);
    return 0;
}
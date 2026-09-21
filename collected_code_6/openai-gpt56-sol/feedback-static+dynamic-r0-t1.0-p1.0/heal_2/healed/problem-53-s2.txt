#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool first_and_last_are_equal(const char *string, size_t length)
{
    return string != NULL &&
           length > 0U &&
           string[0] == string[length - 1U];
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0U;
    size_t length = 0U;
    int character;

    while ((character = getchar()) != '\n' && character != EOF) {
        char *resized;
        size_t new_capacity;

        if (character == '\r') {
            int next = getchar();

            if (next != '\n' && next != EOF) {
                ungetc(next, stdin);
            }
            break;
        }

        if (length == capacity) {
            if (capacity > (SIZE_MAX - 1U) / 2U) {
                free(input);
                return 1;
            }

            new_capacity = capacity == 0U ? 128U : capacity * 2U;
            resized = realloc(input, new_capacity);

            if (resized == NULL) {
                free(input);
                return 1;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)character;
    }

    if (character == EOF && length == 0U) {
        free(input);
        return 1;
    }

    if (first_and_last_are_equal(input, length)) {
        puts("Equal");
    } else {
        puts("Not equal");
    }

    free(input);
    return 0;
}
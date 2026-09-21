#include <stdio.h>
#include <stdlib.h>

static int first_and_last_equal(const char *string, size_t length)
{
    return string != NULL && length > 0U && string[0] == string[length - 1U];
}

int main(void)
{
    char *string = NULL;
    size_t length = 0U;
    size_t capacity = 0U;
    int character;

    while ((character = fgetc(stdin)) != '\n' && character != EOF) {
        if (length == capacity) {
            size_t new_capacity = capacity == 0U ? 128U : capacity * 2U;
            char *new_string;

            if (new_capacity <= capacity) {
                free(string);
                return 1;
            }

            new_string = realloc(string, new_capacity);
            if (new_string == NULL) {
                free(string);
                return 1;
            }

            string = new_string;
            capacity = new_capacity;
        }

        string[length++] = (char)character;
    }

    if (character == EOF && (ferror(stdin) || length == 0U)) {
        free(string);
        return 1;
    }

    puts(first_and_last_equal(string, length) ? "Equal" : "Not equal");

    free(string);
    return 0;
}
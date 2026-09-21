#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int first_and_last_equal(const char *string, size_t length)
{
    return string != NULL && length > 0U &&
           string[0] == string[length - 1U];
}

int main(void)
{
    char *string = NULL;
    size_t length = 0U;
    size_t capacity = 0U;
    int character;

    while ((character = fgetc(stdin)) != EOF && character != '\n') {
        if (length == capacity) {
            size_t new_capacity;
            char *new_string;

            if (capacity == 0U) {
                new_capacity = 128U;
            } else {
                if (capacity > SIZE_MAX / 2U) {
                    free(string);
                    return EXIT_FAILURE;
                }
                new_capacity = capacity * 2U;
            }

            new_string = realloc(string, new_capacity);
            if (new_string == NULL) {
                free(string);
                return EXIT_FAILURE;
            }

            string = new_string;
            capacity = new_capacity;
        }

        string[length++] = (char)(unsigned char)character;
    }

    if (ferror(stdin) || (character == EOF && length == 0U)) {
        free(string);
        return EXIT_FAILURE;
    }

    puts(first_and_last_equal(string, length) ? "Equal" : "Not equal");

    free(string);
    return EXIT_SUCCESS;
}
#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

size_t count_matching_positions(const char *string)
{
    size_t count = 0;

    if (string == NULL) {
        return 0;
    }

    for (size_t i = 0; string[i] != '\0'; ++i) {
        unsigned char character = (unsigned char)string[i];

        if (isalpha(character) &&
            (size_t)(tolower(character) - 'a') == i) {
            ++count;
        }
    }

    return count;
}

int main(void)
{
    char *string = NULL;
    size_t length = 0;
    size_t capacity = 128;
    int character;

    string = malloc(capacity);
    if (string == NULL) {
        return 1;
    }

    while ((character = getchar()) != EOF && character != '\n') {
        if (length == capacity - 1) {
            size_t new_capacity;

            if (capacity > SIZE_MAX / 2) {
                free(string);
                return 1;
            }

            new_capacity = capacity * 2;
            char *temporary = realloc(string, new_capacity);
            if (temporary == NULL) {
                free(string);
                return 1;
            }

            string = temporary;
            capacity = new_capacity;
        }

        string[length++] = (char)character;
    }

    if (character == EOF && length == 0) {
        free(string);
        return 1;
    }

    string[length] = '\0';

    printf("%zu\n", count_matching_positions(string));

    free(string);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static void remove_spaces(char *string)
{
    char *source;
    char *destination;

    if (string == NULL) {
        return;
    }

    source = string;
    destination = string;

    while (*source != '\0') {
        if (*source != ' ') {
            *destination++ = *source;
        }
        ++source;
    }

    *destination = '\0';
}

int main(void)
{
    char *string;
    size_t length = 0;
    size_t capacity = 128;
    int character;
    int result = EXIT_FAILURE;

    string = malloc(capacity);
    if (string == NULL) {
        return EXIT_FAILURE;
    }

    while ((character = getchar()) != EOF && character != '\n') {
        if (length == capacity - 1) {
            size_t new_capacity;
            char *temporary;

            if (capacity > SIZE_MAX / 2) {
                goto cleanup;
            }

            new_capacity = capacity * 2;
            temporary = realloc(string, new_capacity);
            if (temporary == NULL) {
                goto cleanup;
            }

            string = temporary;
            capacity = new_capacity;
        }

        string[length++] = (char)character;
    }

    if (character == EOF) {
        if (ferror(stdin)) {
            goto cleanup;
        }

        if (length == 0) {
            result = EXIT_SUCCESS;
            goto cleanup;
        }
    }

    string[length] = '\0';
    remove_spaces(string);

    if (puts(string) == EOF) {
        goto cleanup;
    }

    result = EXIT_SUCCESS;

cleanup:
    free(string);
    return result;
}
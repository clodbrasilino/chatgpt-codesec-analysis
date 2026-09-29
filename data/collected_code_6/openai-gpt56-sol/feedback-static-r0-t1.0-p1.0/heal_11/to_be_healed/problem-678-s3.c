#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static void remove_spaces(char *string)
{
    char *source = string;
    char *destination = string;

    if (string == NULL) {
        return;
    }

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

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = getchar()) != EOF && character != '\n') {
        if (length == SIZE_MAX - 1) {
            goto cleanup;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *temporary;

            if (capacity > SIZE_MAX / 2) {
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = capacity * 2;
            }

            if (new_capacity <= length + 1) {
                goto cleanup;
            }

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
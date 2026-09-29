#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

void remove_non_alphanumeric(char *string)
{
    unsigned char *source;
    char *destination;

    if (string == NULL) {
        return;
    }

    source = (unsigned char *)string;
    destination = string;

    while (*source != '\0') {
        if (isalnum(*source) != 0) {
            *destination++ = (char)*source;
        }
        ++source;
    }

    *destination = '\0';
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int character;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stdin)) != EOF && character != '\n') {
        if (length == capacity) {
            size_t new_capacity;
            char *resized;

            if (capacity == 0) {
                new_capacity = 128;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(input);
                    return EXIT_FAILURE;
                }
                new_capacity = capacity * 2;
            }

            resized = realloc(input, new_capacity);
            if (resized == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)character;
    }

    if (ferror(stdin)) {
        free(input);
        return EXIT_FAILURE;
    }

    if (length == SIZE_MAX) {
        free(input);
        return EXIT_FAILURE;
    }

    {
        char *resized = realloc(input, length + 1);

        if (resized == NULL) {
            free(input);
            return EXIT_FAILURE;
        }

        input = resized;
    }

    input[length] = '\0';
    remove_non_alphanumeric(input);

    if (printf("%s\n", input) < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}
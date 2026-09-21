#include <stdio.h>
#include <stdlib.h>

size_t count_characters(const char *string, size_t capacity)
{
    size_t length = 0;

    if (string == NULL) {
        return 0;
    }

    while (length < capacity && string[length] != '\0') {
        ++length;
    }

    return length;
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
            size_t new_capacity = capacity == 0 ? 128 : capacity * 2;
            char *resized;

            if (new_capacity <= capacity) {
                free(input);
                return EXIT_FAILURE;
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

    if (character == EOF && ferror(stdin)) {
        free(input);
        return EXIT_FAILURE;
    }

    if (length == capacity) {
        size_t new_capacity = capacity == 0 ? 1 : capacity + 1;
        char *resized;

        if (new_capacity <= capacity) {
            free(input);
            return EXIT_FAILURE;
        }

        resized = realloc(input, new_capacity);
        if (resized == NULL) {
            free(input);
            return EXIT_FAILURE;
        }

        input = resized;
        capacity = new_capacity;
    }

    input[length] = '\0';

    if (printf("%zu\n", count_characters(input, capacity)) < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}
#include <stdio.h>
#include <stdlib.h>

size_t string_length(const char *string)
{
    const char *current;

    if (string == NULL) {
        return 0;
    }

    current = string;

    while (*current != '\0') {
        ++current;
    }

    return (size_t)(current - string);
}

int main(void)
{
    char *buffer = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int character;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stdin)) != EOF && character != '\n') {
        if (length + 1 >= capacity) {
            size_t new_capacity = capacity == 0 ? 128 : capacity * 2;
            char *new_buffer;

            if (new_capacity <= capacity) {
                free(buffer);
                return EXIT_FAILURE;
            }

            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return EXIT_FAILURE;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)character;
    }

    if (character == EOF && ferror(stdin)) {
        perror("fgetc");
        free(buffer);
        return EXIT_FAILURE;
    }

    if (character == EOF && length == 0) {
        free(buffer);
        return EXIT_SUCCESS;
    }

    if (length + 1 >= capacity) {
        char *new_buffer = realloc(buffer, length + 1);

        if (new_buffer == NULL) {
            free(buffer);
            return EXIT_FAILURE;
        }

        buffer = new_buffer;
    }

    buffer[length] = '\0';
    length = string_length(buffer);

    printf("%zu\n", length);

    free(buffer);
    return EXIT_SUCCESS;
}
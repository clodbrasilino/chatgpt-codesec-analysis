#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

size_t length_of_last_word(const char *string)
{
    size_t length = 0;

    if (string == NULL) {
        return 0;
    }

    while (*string != '\0') {
        if (isspace((unsigned char)*string)) {
            length = 0;
        } else {
            ++length;
        }
        ++string;
    }

    return length;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int character;

    while ((character = fgetc(stdin)) != EOF) {
        if (length + 1 >= capacity) {
            size_t new_capacity = capacity == 0 ? 128 : capacity * 2;

            if (new_capacity <= capacity) {
                free(input);
                fprintf(stderr, "Input is too large.\n");
                return 1;
            }

            char *resized = realloc(input, new_capacity);
            if (resized == NULL) {
                free(input);
                fprintf(stderr, "Failed to allocate memory.\n");
                return 1;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)character;

        if (character == '\n') {
            break;
        }
    }

    if (ferror(stdin)) {
        free(input);
        fprintf(stderr, "Failed to read input.\n");
        return 1;
    }

    if (length == 0 && character == EOF) {
        free(input);
        return 0;
    }

    if (length + 1 >= capacity) {
        size_t new_capacity = capacity == 0 ? 2 : capacity + 1;
        char *resized = realloc(input, new_capacity);

        if (resized == NULL) {
            free(input);
            fprintf(stderr, "Failed to allocate memory.\n");
            return 1;
        }

        input = resized;
        capacity = new_capacity;
    }

    input[length] = '\0';
    printf("%zu\n", length_of_last_word(input));

    free(input);
    return 0;
}
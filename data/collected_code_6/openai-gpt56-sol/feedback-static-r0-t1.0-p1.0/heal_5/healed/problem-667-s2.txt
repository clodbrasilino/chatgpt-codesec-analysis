#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

static int is_vowel(unsigned char character)
{
    int lower = tolower(character);

    return lower == 'a' ||
           lower == 'e' ||
           lower == 'i' ||
           lower == 'o' ||
           lower == 'u';
}

static size_t count_vowels(const char *string)
{
    size_t count = 0;

    if (string == NULL) {
        return 0;
    }

    while (*string != '\0') {
        if (is_vowel((unsigned char)*string)) {
            ++count;
        }
        ++string;
    }

    return count;
}

int main(void)
{
    char *buffer = NULL;
    size_t capacity = 0;
    size_t length = 0;
    size_t count = 0;
    int character;

    while ((character = getchar()) != EOF) {
        if (length == capacity) {
            size_t new_capacity = capacity == 0 ? 256 : capacity * 2;
            char *new_buffer;

            if (new_capacity <= capacity) {
                free(buffer);
                fputs("Input is too large.\n", stderr);
                return EXIT_FAILURE;
            }

            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                fputs("Failed to allocate memory.\n", stderr);
                return EXIT_FAILURE;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)character;

        if (character == '\n') {
            if (length == capacity) {
                size_t new_capacity = capacity + 1;
                char *new_buffer = realloc(buffer, new_capacity);

                if (new_buffer == NULL) {
                    free(buffer);
                    fputs("Failed to allocate memory.\n", stderr);
                    return EXIT_FAILURE;
                }

                buffer = new_buffer;
                capacity = new_capacity;
            }

            buffer[length] = '\0';
            count += count_vowels(buffer);
            length = 0;
        }
    }

    if (ferror(stdin)) {
        free(buffer);
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (length != 0) {
        if (length == capacity) {
            char *new_buffer = realloc(buffer, capacity + 1);

            if (new_buffer == NULL) {
                free(buffer);
                fputs("Failed to allocate memory.\n", stderr);
                return EXIT_FAILURE;
            }

            buffer = new_buffer;
        }

        buffer[length] = '\0';
        count += count_vowels(buffer);
    }

    free(buffer);

    if (printf("%zu\n", count) < 0) {
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
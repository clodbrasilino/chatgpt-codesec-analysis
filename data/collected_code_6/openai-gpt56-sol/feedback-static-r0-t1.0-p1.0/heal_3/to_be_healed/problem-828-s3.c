#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    size_t alphabets;
    size_t digits;
    size_t special_characters;
} CharacterCounts;

static CharacterCounts count_characters(const char *string)
{
    CharacterCounts counts = {0, 0, 0};

    if (string == NULL) {
        return counts;
    }

    while (*string != '\0') {
        unsigned char character = (unsigned char)*string++;

        if (isalpha(character)) {
            ++counts.alphabets;
        } else if (isdigit(character)) {
            ++counts.digits;
        } else {
            ++counts.special_characters;
        }
    }

    return counts;
}

static int read_line(char **output)
{
    char *buffer = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int character;

    if (output == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = getchar()) != EOF && character != '\n') {
        if (length == SIZE_MAX - 1) {
            free(buffer);
            return 0;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;

            if (capacity == 0) {
                new_capacity = 128;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(buffer);
                    return 0;
                }
                new_capacity = capacity * 2;
            }

            char *new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return 0;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)character;
    }

    if (character == EOF && length == 0) {
        free(buffer);
        return 0;
    }

    if (capacity <= length) {
        char *new_buffer = realloc(buffer, length + 1);
        if (new_buffer == NULL) {
            free(buffer);
            return 0;
        }

        buffer = new_buffer;
    }

    buffer[length] = '\0';
    *output = buffer;
    return 1;
}

int main(void)
{
    char *input = NULL;

    if (!read_line(&input)) {
        return EXIT_FAILURE;
    }

    CharacterCounts counts = count_characters(input);

    printf("Alphabets: %zu\n", counts.alphabets);
    printf("Digits: %zu\n", counts.digits);
    printf("Special characters: %zu\n", counts.special_characters);

    free(input);
    return EXIT_SUCCESS;
}
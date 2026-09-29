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

static char *read_line(FILE *stream)
{
    size_t length = 0;
    size_t capacity = 128;
    char *buffer;

    if (stream == NULL) {
        return NULL;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return NULL;
    }

    for (;;) {
        int character;

        if (length >= capacity - 1) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return NULL;
            }

            new_capacity = capacity * 2;
            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return NULL;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        character = fgetc(stream);

        if (character == EOF) {
            if (ferror(stream) || length == 0) {
                free(buffer);
                return NULL;
            }
            break;
        }

        buffer[length++] = (char)character;

        if (character == '\n') {
            break;
        }
    }

    buffer[length] = '\0';
    return buffer;
}

int main(void)
{
    char *input;
    CharacterCounts counts;

    input = read_line(stdin);
    if (input == NULL) {
        if (ferror(stdin)) {
            fputs("Failed to read input.\n", stderr);
        }
        return EXIT_FAILURE;
    }

    counts = count_characters(input);

    printf("Alphabets: %zu\n", counts.alphabets);
    printf("Digits: %zu\n", counts.digits);
    printf("Special characters: %zu\n", counts.special_characters);

    free(input);
    return EXIT_SUCCESS;
}
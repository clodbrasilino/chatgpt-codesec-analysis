#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    size_t alphabets;
    size_t digits;
    size_t special_characters;
} CharacterCounts;

typedef enum {
    READ_OK,
    READ_EOF,
    READ_ERROR,
    READ_NO_MEMORY,
    READ_TOO_LARGE
} ReadStatus;

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

static ReadStatus read_line(FILE *stream, char **result)
{
    size_t length = 0;
    size_t capacity = 128;
    char *buffer;

    if (stream == NULL || result == NULL) {
        return READ_ERROR;
    }

    *result = NULL;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return READ_NO_MEMORY;
    }

    for (;;) {
        int character;

        if (length >= capacity - 1) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return READ_TOO_LARGE;
            }

            new_capacity = capacity * 2;
            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return READ_NO_MEMORY;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        character = fgetc(stream);

        if (character == EOF) {
            if (ferror(stream)) {
                free(buffer);
                return READ_ERROR;
            }

            if (length == 0) {
                free(buffer);
                return READ_EOF;
            }

            break;
        }

        buffer[length++] = (char)character;

        if (character == '\n') {
            break;
        }
    }

    buffer[length] = '\0';
    *result = buffer;
    return READ_OK;
}

int main(void)
{
    char *input = NULL;
    CharacterCounts counts;
    ReadStatus status = read_line(stdin, &input);

    if (status != READ_OK) {
        switch (status) {
        case READ_EOF:
            fputs("No input provided.\n", stderr);
            break;
        case READ_ERROR:
            fputs("Failed to read input.\n", stderr);
            break;
        case READ_NO_MEMORY:
            fputs("Failed to allocate memory.\n", stderr);
            break;
        case READ_TOO_LARGE:
            fputs("Input is too large.\n", stderr);
            break;
        default:
            fputs("Unknown input error.\n", stderr);
            break;
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
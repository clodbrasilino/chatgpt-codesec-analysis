#include <stdbool.h>
#include <ctype.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    READ_OK,
    READ_END,
    READ_ERROR
} ReadResult;

static ReadResult read_token(FILE *stream, char **output)
{
    char *buffer;
    size_t length = 0;
    size_t capacity = 64;
    int character;

    if (stream == NULL || output == NULL) {
        return READ_ERROR;
    }

    *output = NULL;

    do {
        character = fgetc(stream);
        if (character == EOF) {
            return ferror(stream) ? READ_ERROR : READ_END;
        }
    } while (isspace((unsigned char)character));

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return READ_ERROR;
    }

    while (character != EOF && !isspace((unsigned char)character)) {
        char *resized_buffer;

        if (character == '\0') {
            free(buffer);
            return READ_ERROR;
        }

        if (length == capacity - 1U) {
            if (capacity > SIZE_MAX / 2U) {
                free(buffer);
                return READ_ERROR;
            }

            capacity *= 2U;
            resized_buffer = realloc(buffer, capacity);
            if (resized_buffer == NULL) {
                free(buffer);
                return READ_ERROR;
            }
            buffer = resized_buffer;
        }

        buffer[length++] = (char)character;
        character = fgetc(stream);
    }

    if (character == EOF && ferror(stream)) {
        free(buffer);
        return READ_ERROR;
    }

    buffer[length] = '\0';
    *output = buffer;
    return READ_OK;
}

static bool are_isomorphic(const char *first, const char *second)
{
    bool first_seen[UCHAR_MAX + 1U] = { false };
    bool second_seen[UCHAR_MAX + 1U] = { false };
    unsigned char first_mapping[UCHAR_MAX + 1U];
    unsigned char second_mapping[UCHAR_MAX + 1U];

    if (first == NULL || second == NULL) {
        return false;
    }

    while (*first != '\0' && *second != '\0') {
        unsigned char first_character = (unsigned char)*first;
        unsigned char second_character = (unsigned char)*second;

        if (!first_seen[first_character] && !second_seen[second_character]) {
            first_seen[first_character] = true;
            second_seen[second_character] = true;
            first_mapping[first_character] = second_character;
            second_mapping[second_character] = first_character;
        } else if (!first_seen[first_character] ||
                   !second_seen[second_character] ||
                   first_mapping[first_character] != second_character ||
                   second_mapping[second_character] != first_character) {
            return false;
        }

        ++first;
        ++second;
    }

    return *first == '\0' && *second == '\0';
}

int main(void)
{
    char *first = NULL;
    char *second = NULL;
    bool result;

    if (read_token(stdin, &first) != READ_OK) {
        return EXIT_FAILURE;
    }

    if (read_token(stdin, &second) != READ_OK) {
        free(first);
        return EXIT_FAILURE;
    }

    result = are_isomorphic(first, second);

    free(first);
    free(second);

    if (puts(result ? "true" : "false") == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
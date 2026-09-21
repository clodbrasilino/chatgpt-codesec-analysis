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

typedef struct {
    FILE *stream;
    unsigned char *buffer;
    size_t capacity;
    size_t position;
    size_t length;
    ReadResult terminal_status;
} TokenReader;

typedef struct {
    bool seen;
    unsigned int value;
} CharacterMapping;

static bool token_reader_init(TokenReader *reader, FILE *stream)
{
    const size_t capacity = 4096U;

    if (reader == NULL || stream == NULL) {
        return false;
    }

    reader->buffer = malloc(capacity);
    if (reader->buffer == NULL) {
        return false;
    }

    reader->stream = stream;
    reader->capacity = capacity;
    reader->position = 0U;
    reader->length = 0U;
    reader->terminal_status = READ_OK;

    return true;
}

static void token_reader_destroy(TokenReader *reader)
{
    if (reader != NULL) {
        free(reader->buffer);
        reader->buffer = NULL;
        reader->stream = NULL;
        reader->capacity = 0U;
        reader->position = 0U;
        reader->length = 0U;
        reader->terminal_status = READ_END;
    }
}

static ReadResult token_reader_next(TokenReader *reader,
                                    unsigned char *character)
{
    if (reader == NULL || character == NULL || reader->stream == NULL ||
        reader->buffer == NULL || reader->capacity == 0U) {
        return READ_ERROR;
    }

    if (reader->position == reader->length) {
        if (reader->terminal_status != READ_OK) {
            return reader->terminal_status;
        }

        reader->position = 0U;
        reader->length = fread(reader->buffer, 1U, reader->capacity,
                               reader->stream);

        if (reader->length < reader->capacity) {
            reader->terminal_status =
                ferror(reader->stream) ? READ_ERROR : READ_END;
        }

        if (reader->length == 0U) {
            return reader->terminal_status;
        }
    }

    *character = reader->buffer[reader->position++];
    return READ_OK;
}

static ReadResult read_token(TokenReader *reader, char **output)
{
    char *buffer;
    size_t length = 0U;
    size_t capacity = 64U;
    unsigned char character;
    ReadResult status;

    if (reader == NULL || output == NULL) {
        return READ_ERROR;
    }

    *output = NULL;

    do {
        status = token_reader_next(reader, &character);
        if (status != READ_OK) {
            return status;
        }
    } while (isspace((int)character) != 0);

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return READ_ERROR;
    }

    for (;;) {
        char *resized_buffer;

        if (character == 0U) {
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

        status = token_reader_next(reader, &character);
        if (status == READ_END) {
            break;
        }

        if (status == READ_ERROR) {
            free(buffer);
            return READ_ERROR;
        }

        if (isspace((int)character) != 0) {
            break;
        }
    }

    buffer[length] = '\0';
    *output = buffer;

    return READ_OK;
}

static bool are_isomorphic(const char *first, const char *second)
{
    CharacterMapping *forward;
    CharacterMapping *reverse;
    size_t character_count;
    bool result = true;

    if (first == NULL || second == NULL) {
        return false;
    }

    if ((uintmax_t)UCHAR_MAX >= (uintmax_t)SIZE_MAX) {
        return false;
    }

    character_count = (size_t)UCHAR_MAX + 1U;

    if (character_count > SIZE_MAX / sizeof(*forward)) {
        return false;
    }

    forward = calloc(character_count, sizeof(*forward));
    reverse = calloc(character_count, sizeof(*reverse));

    if (forward == NULL || reverse == NULL) {
        free(forward);
        free(reverse);
        return false;
    }

    while (*first != '\0' && *second != '\0') {
        unsigned char first_character = (unsigned char)*first;
        unsigned char second_character = (unsigned char)*second;
        CharacterMapping *forward_entry = &forward[first_character];
        CharacterMapping *reverse_entry = &reverse[second_character];

        if (!forward_entry->seen && !reverse_entry->seen) {
            forward_entry->seen = true;
            forward_entry->value = second_character;
            reverse_entry->seen = true;
            reverse_entry->value = first_character;
        } else if (!forward_entry->seen ||
                   !reverse_entry->seen ||
                   forward_entry->value != second_character ||
                   reverse_entry->value != first_character) {
            result = false;
            break;
        }

        ++first;
        ++second;
    }

    if (result) {
        result = (*first == '\0' && *second == '\0');
    }

    free(forward);
    free(reverse);

    return result;
}

int main(void)
{
    TokenReader reader;
    char *first = NULL;
    char *second = NULL;
    bool result;

    if (!token_reader_init(&reader, stdin)) {
        return EXIT_FAILURE;
    }

    if (read_token(&reader, &first) != READ_OK) {
        token_reader_destroy(&reader);
        return EXIT_FAILURE;
    }

    if (read_token(&reader, &second) != READ_OK) {
        free(first);
        token_reader_destroy(&reader);
        return EXIT_FAILURE;
    }

    result = are_isomorphic(first, second);

    free(first);
    free(second);
    token_reader_destroy(&reader);

    if (puts(result ? "true" : "false") == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
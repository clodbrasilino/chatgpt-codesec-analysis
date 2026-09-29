#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DICTIONARY_SIZE 5U
#define INITIAL_CAPACITY 128U
#define MAX_INPUT_LENGTH 4096U

typedef struct {
    const char *key;
} DictionaryEntry;

typedef enum {
    READ_LINE_OK,
    READ_LINE_EOF,
    READ_LINE_TOO_LONG,
    READ_LINE_IO_ERROR,
    READ_LINE_NO_MEMORY
} ReadLineStatus;

static bool dictionary_contains(const DictionaryEntry *dictionary,
                                size_t dictionary_size,
                                const char *key)
{
    if (dictionary == NULL || key == NULL) {
        return false;
    }

    for (size_t i = 0U; i < dictionary_size; ++i) {
        if (dictionary[i].key != NULL &&
            strcmp(dictionary[i].key, key) == 0) {
            return true;
        }
    }

    return false;
}

static void discard_line(FILE *stream)
{
    int ch;

    if (stream == NULL) {
        return;
    }

    while ((ch = fgetc(stream)) != '\n' && ch != EOF) {
    }
}

static ReadLineStatus read_line(FILE *stream, char **output)
{
    size_t capacity = INITIAL_CAPACITY;
    size_t length = 0U;
    char *buffer;

    if (stream == NULL || output == NULL) {
        return READ_LINE_IO_ERROR;
    }

    *output = NULL;
    buffer = malloc(capacity);

    if (buffer == NULL) {
        return READ_LINE_NO_MEMORY;
    }

    for (;;) {
        int ch = fgetc(stream);

        if (ch == EOF) {
            if (ferror(stream) != 0) {
                free(buffer);
                return READ_LINE_IO_ERROR;
            }

            if (length == 0U) {
                free(buffer);
                return READ_LINE_EOF;
            }

            break;
        }

        if (ch == '\n') {
            break;
        }

        if (ch == '\r') {
            int next = fgetc(stream);

            if (next == EOF) {
                if (ferror(stream) != 0) {
                    free(buffer);
                    return READ_LINE_IO_ERROR;
                }
            } else if (next != '\n' && ungetc(next, stream) == EOF) {
                free(buffer);
                return READ_LINE_IO_ERROR;
            }

            break;
        }

        if (length == MAX_INPUT_LENGTH) {
            discard_line(stream);

            if (ferror(stream) != 0) {
                free(buffer);
                return READ_LINE_IO_ERROR;
            }

            free(buffer);
            return READ_LINE_TOO_LONG;
        }

        if (length + 1U >= capacity) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity >= MAX_INPUT_LENGTH + 1U) {
                free(buffer);
                return READ_LINE_TOO_LONG;
            }

            if (capacity > SIZE_MAX / 2U) {
                free(buffer);
                return READ_LINE_NO_MEMORY;
            }

            new_capacity = capacity * 2U;

            if (new_capacity > MAX_INPUT_LENGTH + 1U) {
                new_capacity = MAX_INPUT_LENGTH + 1U;
            }

            new_buffer = realloc(buffer, new_capacity);

            if (new_buffer == NULL) {
                free(buffer);
                return READ_LINE_NO_MEMORY;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    buffer[length] = '\0';
    *output = buffer;
    return READ_LINE_OK;
}

int main(void)
{
    static const DictionaryEntry dictionary[DICTIONARY_SIZE] = {
        {"apple"},
        {"carrot"},
        {"blue"},
        {"dog"},
        {"table"}
    };

    char *key = NULL;
    ReadLineStatus status = read_line(stdin, &key);

    switch (status) {
        case READ_LINE_OK:
            break;
        case READ_LINE_EOF:
            fputs("No input provided.\n", stderr);
            return EXIT_FAILURE;
        case READ_LINE_TOO_LONG:
            fputs("Input is too long.\n", stderr);
            return EXIT_FAILURE;
        case READ_LINE_IO_ERROR:
            fputs("Failed to read input.\n", stderr);
            return EXIT_FAILURE;
        case READ_LINE_NO_MEMORY:
            fputs("Memory allocation failed.\n", stderr);
            return EXIT_FAILURE;
        default:
            fputs("Unexpected input error.\n", stderr);
            return EXIT_FAILURE;
    }

    if (key[0] == '\0') {
        fputs("Key must not be empty.\n", stderr);
        free(key);
        return EXIT_FAILURE;
    }

    puts(dictionary_contains(dictionary, DICTIONARY_SIZE, key)
             ? "Key is present."
             : "Key is not present.");

    free(key);
    return EXIT_SUCCESS;
}
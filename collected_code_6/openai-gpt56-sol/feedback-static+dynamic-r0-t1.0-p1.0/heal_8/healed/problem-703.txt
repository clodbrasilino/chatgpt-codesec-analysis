#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DICTIONARY_SIZE 5U
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

static ReadLineStatus discard_line(FILE *stream)
{
    int character;

    if (stream == NULL) {
        return READ_LINE_IO_ERROR;
    }

    do {
        character = fgetc(stream);
    } while (character != '\n' && character != EOF);

    if (character == EOF && ferror(stream) != 0) {
        return READ_LINE_IO_ERROR;
    }

    return READ_LINE_TOO_LONG;
}

static ReadLineStatus read_line(FILE *stream, char **output)
{
    char *buffer;
    size_t length;
    int character;

    if (stream == NULL || output == NULL) {
        return READ_LINE_IO_ERROR;
    }

    *output = NULL;

    buffer = malloc(MAX_INPUT_LENGTH + 1U);
    if (buffer == NULL) {
        return READ_LINE_NO_MEMORY;
    }

    length = 0U;

    while ((character = fgetc(stream)) != EOF) {
        if (character == '\n') {
            break;
        }

        if (length == MAX_INPUT_LENGTH) {
            ReadLineStatus status = discard_line(stream);
            free(buffer);
            return status;
        }

        buffer[length++] = (char)character;
    }

    if (character == EOF) {
        if (ferror(stream) != 0) {
            free(buffer);
            return READ_LINE_IO_ERROR;
        }

        if (length == 0U) {
            free(buffer);
            return READ_LINE_EOF;
        }
    }

    if (length > 0U && buffer[length - 1U] == '\r') {
        --length;
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
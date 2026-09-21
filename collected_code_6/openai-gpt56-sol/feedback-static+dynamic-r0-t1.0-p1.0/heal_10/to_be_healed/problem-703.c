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

static ReadLineStatus discard_remaining_line(FILE *stream)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char discard_buffer[256];

    if (stream == NULL) {
        return READ_LINE_IO_ERROR;
    }

    while (fgets(discard_buffer, sizeof discard_buffer, stream) != NULL) {
        if (strchr(discard_buffer, '\n') != NULL) {
            return READ_LINE_TOO_LONG;
        }
    }

    return ferror(stream) != 0 ? READ_LINE_IO_ERROR : READ_LINE_TOO_LONG;
}

static ReadLineStatus read_line(FILE *stream, char **output)
{
    char *buffer;
    size_t length;

    if (stream == NULL || output == NULL) {
        return READ_LINE_IO_ERROR;
    }

    *output = NULL;

    buffer = malloc(MAX_INPUT_LENGTH + 2U);
    if (buffer == NULL) {
        return READ_LINE_NO_MEMORY;
    }

    if (fgets(buffer, (int)(MAX_INPUT_LENGTH + 2U), stream) == NULL) {
        ReadLineStatus status = ferror(stream) != 0
                                    ? READ_LINE_IO_ERROR
                                    : READ_LINE_EOF;
        free(buffer);
        return status;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    length = strlen(buffer);

    if (length > 0U && buffer[length - 1U] == '\n') {
        buffer[--length] = '\0';
        if (length > 0U && buffer[length - 1U] == '\r') {
            buffer[--length] = '\0';
        }
    } else if (length > MAX_INPUT_LENGTH) {
        ReadLineStatus status = discard_remaining_line(stream);
        free(buffer);
        return status;
    } else if (!feof(stream)) {
        ReadLineStatus status = discard_remaining_line(stream);
        free(buffer);
        return status;
    }

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
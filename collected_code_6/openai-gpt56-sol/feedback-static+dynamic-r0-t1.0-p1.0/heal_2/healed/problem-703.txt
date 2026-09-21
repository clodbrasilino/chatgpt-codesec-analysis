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

static char *read_line(FILE *stream)
{
    if (stream == NULL) {
        return NULL;
    }

    size_t capacity = INITIAL_CAPACITY;
    size_t length = 0U;
    char *buffer = malloc(capacity);

    if (buffer == NULL) {
        return NULL;
    }

    for (;;) {
        int ch = fgetc(stream);

        if (ch == EOF) {
            if (ferror(stream) != 0 || length == 0U) {
                free(buffer);
                return NULL;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        if (ch == '\r') {
            int next = fgetc(stream);

            if (next != '\n' && next != EOF) {
                if (ungetc(next, stream) == EOF) {
                    free(buffer);
                    return NULL;
                }
            } else if (next == EOF && ferror(stream) != 0) {
                free(buffer);
                return NULL;
            }

            break;
        }

        if (length >= MAX_INPUT_LENGTH) {
            free(buffer);
            return NULL;
        }

        if (length + 1U >= capacity) {
            size_t new_capacity = capacity;

            if (new_capacity > SIZE_MAX / 2U) {
                free(buffer);
                return NULL;
            }

            new_capacity *= 2U;

            if (new_capacity > MAX_INPUT_LENGTH + 1U) {
                new_capacity = MAX_INPUT_LENGTH + 1U;
            }

            char *new_buffer = realloc(buffer, new_capacity);

            if (new_buffer == NULL) {
                free(buffer);
                return NULL;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    buffer[length] = '\0';
    return buffer;
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

    char *key = read_line(stdin);

    if (key == NULL) {
        if (ferror(stdin) != 0) {
            fputs("Failed to read input.\n", stderr);
        } else {
            fputs("No input provided, input too long, or memory allocation failed.\n",
                  stderr);
        }
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
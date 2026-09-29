#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DICTIONARY_SIZE 5U
#define INITIAL_CAPACITY 128U

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
    size_t capacity = INITIAL_CAPACITY;
    size_t length = 0U;
    char *buffer = malloc(capacity);

    if (buffer == NULL) {
        return NULL;
    }

    for (;;) {
        int ch = fgetc(stream);

        if (ch == EOF || ch == '\n') {
            if (ch == EOF && length == 0U) {
                free(buffer);
                return NULL;
            }
            break;
        }

        if (ch == '\r') {
            int next = fgetc(stream);

            if (next != '\n' && next != EOF) {
                ungetc(next, stream);
            }
            break;
        }

        if (length + 1U >= capacity) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2U) {
                free(buffer);
                return NULL;
            }

            new_capacity = capacity * 2U;
            new_buffer = realloc(buffer, new_capacity);

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
            fprintf(stderr, "Failed to read input.\n");
        } else {
            fprintf(stderr, "No input provided or memory allocation failed.\n");
        }
        return 1;
    }

    if (key[0] == '\0') {
        fprintf(stderr, "Key must not be empty.\n");
        free(key);
        return 1;
    }

    puts(dictionary_contains(dictionary, DICTIONARY_SIZE, key)
             ? "Key is present."
             : "Key is not present.");

    free(key);
    return 0;
}
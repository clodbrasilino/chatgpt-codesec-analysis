#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum find_result {
    FIND_ERROR = -1,
    FIND_NONE = 0,
    FIND_FOUND = 1
};

static char *duplicate_range_lower(const char *start, size_t length)
{
    if (length == SIZE_MAX) {
        return NULL;
    }

    char *word = malloc(length + 1);
    if (word == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < length; ++i) {
        word[i] = (char)tolower((unsigned char)start[i]);
    }

    word[length] = '\0';
    return word;
}

static void free_words(char **words, size_t count)
{
    for (size_t i = 0; i < count; ++i) {
        free(words[i]);
    }

    free(words);
}

static int find_first_repeated_word(const char *text, char **result)
{
    char **words = NULL;
    size_t count = 0;
    size_t capacity = 0;
    const char *cursor;

    if (text == NULL || result == NULL) {
        return FIND_ERROR;
    }

    *result = NULL;
    cursor = text;

    while (*cursor != '\0') {
        while (*cursor != '\0' && !isalnum((unsigned char)*cursor)) {
            ++cursor;
        }

        if (*cursor == '\0') {
            break;
        }

        const char *start = cursor;

        while (*cursor != '\0' && isalnum((unsigned char)*cursor)) {
            ++cursor;
        }

        size_t length = (size_t)(cursor - start);
        char *word = duplicate_range_lower(start, length);

        if (word == NULL) {
            free_words(words, count);
            return FIND_ERROR;
        }

        for (size_t i = 0; i < count; ++i) {
            if (strcmp(words[i], word) == 0) {
                free_words(words, count);
                *result = word;
                return FIND_FOUND;
            }
        }

        if (count == capacity) {
            size_t new_capacity;

            if (capacity == 0) {
                new_capacity = 8;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(word);
                    free_words(words, count);
                    return FIND_ERROR;
                }
                new_capacity = capacity * 2;
            }

            if (new_capacity > SIZE_MAX / sizeof(*words)) {
                free(word);
                free_words(words, count);
                return FIND_ERROR;
            }

            char **new_words = realloc(
                words, new_capacity * sizeof(*new_words));

            if (new_words == NULL) {
                free(word);
                free_words(words, count);
                return FIND_ERROR;
            }

            words = new_words;
            capacity = new_capacity;
        }

        words[count++] = word;
    }

    free_words(words, count);
    return FIND_NONE;
}

static int read_all(FILE *stream, char **output)
{
    char *buffer = NULL;
    size_t length = 0;
    size_t capacity = 0;

    if (stream == NULL || output == NULL) {
        return -1;
    }

    *output = NULL;

    for (;;) {
        if (capacity - length < 2) {
            size_t new_capacity;

            if (capacity == 0) {
                new_capacity = 4096;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(buffer);
                    return -1;
                }
                new_capacity = capacity * 2;
            }

            char *new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return -1;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        size_t available = capacity - length - 1;
        size_t bytes_read = fread(buffer + length, 1, available, stream);
        length += bytes_read;

        if (bytes_read < available) {
            if (ferror(stream)) {
                free(buffer);
                return -1;
            }

            if (feof(stream)) {
                break;
            }
        }
    }

    buffer[length] = '\0';
    *output = buffer;
    return 0;
}

int main(void)
{
    char *input = NULL;
    char *repeated_word = NULL;

    if (read_all(stdin, &input) != 0) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    int status = find_first_repeated_word(input, &repeated_word);
    free(input);

    if (status == FIND_ERROR) {
        fputs("Failed to process input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (status == FIND_NONE) {
        puts("None");
    } else {
        puts(repeated_word);
        free(repeated_word);
    }

    return EXIT_SUCCESS;
}
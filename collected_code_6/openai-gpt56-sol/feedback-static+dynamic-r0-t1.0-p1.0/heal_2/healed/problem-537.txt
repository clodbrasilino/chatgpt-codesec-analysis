#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

static char *find_first_repeated_word(const char *text)
{
    if (text == NULL) {
        return NULL;
    }

    char **words = NULL;
    size_t count = 0;
    size_t capacity = 0;
    const char *cursor = text;

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
            return NULL;
        }

        for (size_t i = 0; i < count; ++i) {
            if (strcmp(words[i], word) == 0) {
                free_words(words, count);
                return word;
            }
        }

        if (count == capacity) {
            size_t new_capacity = capacity == 0 ? 8 : capacity * 2;

            if ((capacity != 0 && capacity > SIZE_MAX / 2) ||
                new_capacity > SIZE_MAX / sizeof(*words)) {
                free(word);
                free_words(words, count);
                return NULL;
            }

            char **new_words = realloc(
                words, new_capacity * sizeof(*new_words));

            if (new_words == NULL) {
                free(word);
                free_words(words, count);
                return NULL;
            }

            words = new_words;
            capacity = new_capacity;
        }

        words[count++] = word;
    }

    free_words(words, count);
    return NULL;
}

static int read_all(FILE *stream, char **output)
{
    char *buffer = NULL;
    size_t length = 0;
    size_t capacity = 0;
    unsigned char block[4096];

    for (;;) {
        size_t bytes_read = fread(block, 1, sizeof(block), stream);

        if (bytes_read > 0) {
            if (length > SIZE_MAX - bytes_read - 1) {
                free(buffer);
                return -1;
            }

            size_t required = length + bytes_read + 1;

            if (required > capacity) {
                size_t new_capacity = capacity == 0 ? 4096 : capacity;

                while (new_capacity < required) {
                    if (new_capacity > SIZE_MAX / 2) {
                        new_capacity = required;
                        break;
                    }

                    new_capacity *= 2;
                }

                char *new_buffer = realloc(buffer, new_capacity);
                if (new_buffer == NULL) {
                    free(buffer);
                    return -1;
                }

                buffer = new_buffer;
                capacity = new_capacity;
            }

            memcpy(buffer + length, block, bytes_read);
            length += bytes_read;
        }

        if (bytes_read < sizeof(block)) {
            if (ferror(stream)) {
                free(buffer);
                return -1;
            }

            break;
        }
    }

    if (buffer == NULL) {
        buffer = malloc(1);
        if (buffer == NULL) {
            return -1;
        }
    }

    buffer[length] = '\0';
    *output = buffer;
    return 0;
}

int main(void)
{
    char *input = NULL;

    if (read_all(stdin, &input) != 0) {
        fprintf(stderr, "Failed to read input.\n");
        return EXIT_FAILURE;
    }

    char *repeated_word = find_first_repeated_word(input);
    free(input);

    if (repeated_word == NULL) {
        puts("None");
    } else {
        puts(repeated_word);
        free(repeated_word);
    }

    return EXIT_SUCCESS;
}
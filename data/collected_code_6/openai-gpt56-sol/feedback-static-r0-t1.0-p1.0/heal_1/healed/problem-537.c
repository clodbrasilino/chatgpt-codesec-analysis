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
    char **words = NULL;
    size_t count = 0;
    size_t capacity = 0;
    const char *cursor = text;

    if (text == NULL) {
        return NULL;
    }

    while (*cursor != '\0') {
        while (*cursor != '\0' &&
               !isalnum((unsigned char)*cursor)) {
            ++cursor;
        }

        if (*cursor == '\0') {
            break;
        }

        const char *start = cursor;

        while (*cursor != '\0' &&
               isalnum((unsigned char)*cursor)) {
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
            size_t new_capacity;

            if (capacity == 0) {
                new_capacity = 8;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(word);
                    free_words(words, count);
                    return NULL;
                }

                new_capacity = capacity * 2;
            }

            if (new_capacity > SIZE_MAX / sizeof(*words)) {
                free(word);
                free_words(words, count);
                return NULL;
            }

            char **new_words =
                realloc(words, new_capacity * sizeof(*words));

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

static char *read_line(FILE *stream)
{
    char *buffer = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int ch;

    while ((ch = fgetc(stream)) != EOF && ch != '\n') {
        if (length == capacity) {
            size_t new_capacity;

            if (capacity == 0) {
                new_capacity = 128;
            } else {
                if (capacity > (SIZE_MAX - 1) / 2) {
                    free(buffer);
                    return NULL;
                }

                new_capacity = capacity * 2;
            }

            if (new_capacity <= length) {
                free(buffer);
                return NULL;
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

    if (ferror(stream)) {
        free(buffer);
        return NULL;
    }

    if (buffer == NULL) {
        buffer = malloc(1);

        if (buffer == NULL) {
            return NULL;
        }
    } else if (length == capacity) {
        if (capacity == SIZE_MAX) {
            free(buffer);
            return NULL;
        }

        char *new_buffer = realloc(buffer, capacity + 1);

        if (new_buffer == NULL) {
            free(buffer);
            return NULL;
        }

        buffer = new_buffer;
    }

    buffer[length] = '\0';
    return buffer;
}

int main(void)
{
    char *input = read_line(stdin);

    if (input == NULL) {
        fprintf(stderr, "Failed to read input.\n");
        return EXIT_FAILURE;
    }

    char *repeated_word = find_first_repeated_word(input);
    free(input);

    if (repeated_word != NULL) {
        printf("%s\n", repeated_word);
        free(repeated_word);
    } else {
        printf("No repeated word found.\n");
    }

    return EXIT_SUCCESS;
}
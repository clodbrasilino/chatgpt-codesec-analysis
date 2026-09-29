#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *duplicate_range_lower(const char *start, size_t length)
{
    char *word;

    if (length == SIZE_MAX) {
        return NULL;
    }

    word = malloc(length + 1);
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
    const char *cursor;

    if (text == NULL) {
        return NULL;
    }

    cursor = text;

    while (*cursor != '\0') {
        const char *start;
        size_t length;
        char *word;

        while (*cursor != '\0' && !isalnum((unsigned char)*cursor)) {
            ++cursor;
        }

        if (*cursor == '\0') {
            break;
        }

        start = cursor;

        while (*cursor != '\0' && isalnum((unsigned char)*cursor)) {
            ++cursor;
        }

        length = (size_t)(cursor - start);
        word = duplicate_range_lower(start, length);

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
            char **new_words;

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

            if (new_capacity > SIZE_MAX / sizeof(*new_words)) {
                free(word);
                free_words(words, count);
                return NULL;
            }

            new_words = realloc(words, new_capacity * sizeof(*new_words));
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

int main(void)
{
    char input[4096];
    char *repeated_word;

    if (fgets(input, sizeof(input), stdin) == NULL) {
        if (ferror(stdin)) {
            fprintf(stderr, "Failed to read input.\n");
            return EXIT_FAILURE;
        }

        puts("None");
        return EXIT_SUCCESS;
    }

    if (strchr(input, '\n') == NULL && !feof(stdin)) {
        int ch;

        while ((ch = getchar()) != '\n' && ch != EOF) {
        }

        fprintf(stderr, "Input is too long.\n");
        return EXIT_FAILURE;
    }

    repeated_word = find_first_repeated_word(input);

    if (repeated_word == NULL) {
        puts("None");
    } else {
        puts(repeated_word);
        free(repeated_word);
    }

    return EXIT_SUCCESS;
}
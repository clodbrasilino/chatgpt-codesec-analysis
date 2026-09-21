#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int is_word_character(unsigned char c)
{
    return isalpha(c) != 0 || c == '\'' || c == '-';
}

static int is_adverb(const char *word, size_t length)
{
    static const char *const common_adverbs[] = {
        "almost", "always", "fast", "hard", "here", "how", "late",
        "never", "not", "now", "often", "quite", "rather", "soon",
        "there", "today", "tomorrow", "too", "very", "well",
        "when", "where", "why", "yesterday"
    };
    const size_t count = sizeof common_adverbs / sizeof common_adverbs[0];
    size_t i;

    if (length > 2U &&
        word[length - 2U] == 'l' &&
        word[length - 1U] == 'y') {
        return 1;
    }

    for (i = 0U; i < count; ++i) {
        size_t adverb_length = strlen(common_adverbs[i]);

        if (length == adverb_length &&
            memcmp(word, common_adverbs[i], length) == 0) {
            return 1;
        }
    }

    return 0;
}

static int find_adverbs(const char *sentence, size_t sentence_length)
{
    size_t position = 0U;
    size_t word_number = 0U;
    int found = 0;

    while (position < sentence_length) {
        size_t start;
        size_t length;
        char *word;
        size_t i;

        while (position < sentence_length &&
               !is_word_character((unsigned char)sentence[position])) {
            ++position;
        }

        if (position == sentence_length) {
            break;
        }

        start = position;

        while (position < sentence_length &&
               is_word_character((unsigned char)sentence[position])) {
            ++position;
        }

        length = position - start;

        if (word_number == SIZE_MAX) {
            fputs("Too many words.\n", stderr);
            return -1;
        }
        ++word_number;

        if (length == SIZE_MAX) {
            fputs("Word is too long.\n", stderr);
            return -1;
        }

        word = malloc(length + 1U);
        if (word == NULL) {
            fputs("Memory allocation failed.\n", stderr);
            return -1;
        }

        for (i = 0U; i < length; ++i) {
            word[i] = (char)tolower((unsigned char)sentence[start + i]);
        }
        word[length] = '\0';

        if (is_adverb(word, length)) {
            printf("%s: word %zu, character %zu\n",
                   word, word_number, start + 1U);
            found = 1;
        }

        free(word);
    }

    if (!found) {
        puts("No adverbs found.");
    }

    return 0;
}

static int grow_buffer(char **buffer, size_t *capacity, size_t required)
{
    size_t new_capacity;
    char *resized;

    if (buffer == NULL || capacity == NULL || required == 0U) {
        return -1;
    }

    new_capacity = *capacity == 0U ? 128U : *capacity;

    while (new_capacity < required) {
        if (new_capacity > SIZE_MAX / 2U) {
            new_capacity = required;
            break;
        }
        new_capacity *= 2U;
    }

    if (new_capacity < required) {
        return -1;
    }

    resized = realloc(*buffer, new_capacity);
    if (resized == NULL) {
        return -1;
    }

    *buffer = resized;
    *capacity = new_capacity;
    return 0;
}

static int read_line(FILE *stream, char **buffer, size_t *length)
{
    size_t capacity = 0U;
    int character;

    if (stream == NULL || buffer == NULL || length == NULL) {
        fputs("Invalid argument.\n", stderr);
        return -1;
    }

    *buffer = NULL;
    *length = 0U;

    while ((character = fgetc(stream)) != EOF && character != '\n') {
        size_t required;

        if (*length > SIZE_MAX - 2U) {
            fputs("Input is too long.\n", stderr);
            free(*buffer);
            *buffer = NULL;
            *length = 0U;
            return -1;
        }

        required = *length + 2U;

        if (required > capacity &&
            grow_buffer(buffer, &capacity, required) != 0) {
            fputs("Memory allocation failed or input is too long.\n", stderr);
            free(*buffer);
            *buffer = NULL;
            *length = 0U;
            return -1;
        }

        (*buffer)[*length] = (char)(unsigned char)character;
        ++*length;
    }

    if (ferror(stream)) {
        fputs("Failed to read input.\n", stderr);
        free(*buffer);
        *buffer = NULL;
        *length = 0U;
        return -1;
    }

    if (*buffer == NULL) {
        *buffer = malloc(1U);
        if (*buffer == NULL) {
            fputs("Memory allocation failed.\n", stderr);
            return -1;
        }
    }

    (*buffer)[*length] = '\0';
    return 0;
}

int main(void)
{
    char *sentence = NULL;
    size_t length = 0U;
    int result;

    if (read_line(stdin, &sentence, &length) != 0) {
        return EXIT_FAILURE;
    }

    result = find_adverbs(sentence, length);
    free(sentence);

    return result == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
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
    static const struct {
        const char *word;
        size_t length;
    } common_adverbs[] = {
        { "almost", 6U },
        { "always", 6U },
        { "fast", 4U },
        { "hard", 4U },
        { "here", 4U },
        { "how", 3U },
        { "late", 4U },
        { "never", 5U },
        { "not", 3U },
        { "now", 3U },
        { "often", 5U },
        { "quite", 5U },
        { "rather", 6U },
        { "soon", 4U },
        { "there", 5U },
        { "today", 5U },
        { "tomorrow", 8U },
        { "too", 3U },
        { "very", 4U },
        { "well", 4U },
        { "when", 4U },
        { "where", 5U },
        { "why", 3U },
        { "yesterday", 9U }
    };
    const size_t count = sizeof common_adverbs / sizeof common_adverbs[0];
    size_t i;

    if (length >= 2U &&
        word[length - 2U] == 'l' &&
        word[length - 1U] == 'y') {
        return 1;
    }

    for (i = 0U; i < count; ++i) {
        if (length == common_adverbs[i].length &&
            memcmp(word, common_adverbs[i].word, length) == 0) {
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
        size_t i;
        int adverb;

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

        if (length >= 2U) {
            unsigned char penultimate =
                (unsigned char)sentence[start + length - 2U];
            unsigned char last =
                (unsigned char)sentence[start + length - 1U];

            adverb = tolower(penultimate) == 'l' &&
                     tolower(last) == 'y';
        } else {
            adverb = 0;
        }

        if (!adverb) {
            static const struct {
                const char *word;
                size_t length;
            } common_adverbs[] = {
                { "almost", 6U },
                { "always", 6U },
                { "fast", 4U },
                { "hard", 4U },
                { "here", 4U },
                { "how", 3U },
                { "late", 4U },
                { "never", 5U },
                { "not", 3U },
                { "now", 3U },
                { "often", 5U },
                { "quite", 5U },
                { "rather", 6U },
                { "soon", 4U },
                { "there", 5U },
                { "today", 5U },
                { "tomorrow", 8U },
                { "too", 3U },
                { "very", 4U },
                { "well", 4U },
                { "when", 4U },
                { "where", 5U },
                { "why", 3U },
                { "yesterday", 9U }
            };
            const size_t count =
                sizeof common_adverbs / sizeof common_adverbs[0];
            size_t candidate;

            for (candidate = 0U; candidate < count; ++candidate) {
                if (length == common_adverbs[candidate].length) {
                    for (i = 0U; i < length; ++i) {
                        if (tolower((unsigned char)sentence[start + i]) !=
                            (unsigned char)common_adverbs[candidate].word[i]) {
                            break;
                        }
                    }

                    if (i == length) {
                        adverb = 1;
                        break;
                    }
                }
            }
        }

        if (adverb) {
            for (i = 0U; i < length; ++i) {
                if (putchar(tolower((unsigned char)sentence[start + i])) ==
                    EOF) {
                    fputs("Failed to write output.\n", stderr);
                    return -1;
                }
            }

            if (printf(": word %zu, character %zu\n",
                       word_number, start + 1U) < 0) {
                fputs("Failed to write output.\n", stderr);
                return -1;
            }

            found = 1;
        }
    }

    if (!found && puts("No adverbs found.") == EOF) {
        fputs("Failed to write output.\n", stderr);
        return -1;
    }

    return 0;
}

static int grow_buffer(char **buffer, size_t *capacity, size_t required)
{
    size_t new_capacity;
    char *resized;

    if (buffer == NULL || capacity == NULL) {
        return -1;
    }

    if (required <= *capacity) {
        return 0;
    }

    new_capacity = *capacity == 0U ? 128U : *capacity;

    while (new_capacity < required) {
        if (new_capacity > SIZE_MAX / 2U) {
            new_capacity = required;
            break;
        }
        new_capacity *= 2U;
    }

    resized = realloc(*buffer, new_capacity);
    if (resized == NULL) {
        return -1;
    }

    *buffer = resized;
    *capacity = new_capacity;
    return 0;
}

static int read_line(char **buffer, size_t *length)
{
    size_t capacity = 0U;
    int character;

    if (buffer == NULL || length == NULL) {
        return -1;
    }

    *buffer = NULL;
    *length = 0U;

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stdin);

        if (character == EOF || character == '\n') {
            break;
        }

        if (*length > SIZE_MAX - 2U) {
            fputs("Input is too long.\n", stderr);
            free(*buffer);
            *buffer = NULL;
            *length = 0U;
            return -1;
        }

        if (grow_buffer(buffer, &capacity, *length + 2U) != 0) {
            fputs("Memory allocation failed.\n", stderr);
            free(*buffer);
            *buffer = NULL;
            *length = 0U;
            return -1;
        }

        (*buffer)[*length] = (char)(unsigned char)character;
        ++*length;
    }

    if (character == EOF && ferror(stdin)) {
        fputs("Failed to read input.\n", stderr);
        free(*buffer);
        *buffer = NULL;
        *length = 0U;
        return -1;
    }

    if (grow_buffer(buffer, &capacity, *length + 1U) != 0) {
        fputs("Memory allocation failed.\n", stderr);
        free(*buffer);
        *buffer = NULL;
        *length = 0U;
        return -1;
    }

    (*buffer)[*length] = '\0';
    return 0;
}

int main(void)
{
    char *sentence = NULL;
    size_t length = 0U;
    int result;

    if (read_line(&sentence, &length) != 0) {
        return EXIT_FAILURE;
    }

    result = find_adverbs(sentence, length);
    free(sentence);

    if (fflush(stdout) == EOF) {
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    return result == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct adverb_entry {
    const char *word;
    size_t length;
};

static int is_adverb(const char *word, size_t length)
{
    static const struct adverb_entry exceptions[] = {
        {"daily", 5},
        {"early", 5},
        {"fast", 4},
        {"hard", 4},
        {"late", 4},
        {"long", 4},
        {"monthly", 7},
        {"straight", 8},
        {"weekly", 6},
        {"well", 4},
        {"yearly", 6}
    };

    const size_t count = sizeof exceptions / sizeof exceptions[0];

    for (size_t i = 0; i < count; ++i) {
        if (length == exceptions[i].length &&
            memcmp(word, exceptions[i].word, length) == 0) {
            return 1;
        }
    }

    return length > 2 &&
           word[length - 2] == 'l' &&
           word[length - 1] == 'y';
}

static int print_adverb(const char *word, size_t length, size_t position)
{
    if (fwrite(word, 1, length, stdout) != length ||
        fprintf(stdout, ": position %zu\n", position) < 0) {
        fputs("Output error.\n", stderr);
        return 0;
    }

    return 1;
}

static int find_adverbs(const char *sentence, size_t sentence_length)
{
    size_t i = 0;

    while (i < sentence_length) {
        while (i < sentence_length &&
               !isalnum((unsigned char)sentence[i]) &&
               sentence[i] != '\'') {
            ++i;
        }

        if (i == sentence_length) {
            break;
        }

        const size_t start = i;

        while (i < sentence_length &&
               (isalnum((unsigned char)sentence[i]) ||
                sentence[i] == '\'')) {
            ++i;
        }

        const size_t length = i - start;

        if (length < 2) {
            continue;
        }

        int adverb = 0;

        if (tolower((unsigned char)sentence[i - 2]) == 'l' &&
            tolower((unsigned char)sentence[i - 1]) == 'y') {
            adverb = 1;
        } else {
            static const struct adverb_entry exceptions[] = {
                {"daily", 5},
                {"early", 5},
                {"fast", 4},
                {"hard", 4},
                {"late", 4},
                {"long", 4},
                {"monthly", 7},
                {"straight", 8},
                {"weekly", 6},
                {"well", 4},
                {"yearly", 6}
            };

            const size_t count = sizeof exceptions / sizeof exceptions[0];

            for (size_t k = 0; k < count && !adverb; ++k) {
                if (length != exceptions[k].length) {
                    continue;
                }

                size_t j = 0;
                while (j < length &&
                       tolower((unsigned char)sentence[start + j]) ==
                           (unsigned char)exceptions[k].word[j]) {
                    ++j;
                }

                adverb = j == length;
            }
        }

        if (adverb && !print_adverb(sentence + start, length, start)) {
            return 0;
        }
    }

    return 1;
}

static int grow_buffer(char **buffer, size_t *capacity, size_t required)
{
    if (buffer == NULL || capacity == NULL || required == 0) {
        return 0;
    }

    if (*capacity >= required) {
        return 1;
    }

    size_t new_capacity = *capacity;

    if (new_capacity == 0) {
        new_capacity = required > 128 ? required : 128;
    }

    while (new_capacity < required) {
        if (new_capacity > SIZE_MAX / 2) {
            new_capacity = required;
            break;
        }

        new_capacity *= 2;
    }

    if (new_capacity < required) {
        return 0;
    }

    char *temporary = realloc(*buffer, new_capacity);

    if (temporary == NULL) {
        return 0;
    }

    *buffer = temporary;
    *capacity = new_capacity;
    return 1;
}

static int read_sentence(char **sentence, size_t *length)
{
    if (sentence == NULL || length == NULL) {
        return 0;
    }

    *sentence = NULL;
    *length = 0;

    char *buffer = NULL;
    size_t capacity = 0;
    size_t used = 0;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char chunk[4096];

    for (;;) {
        if (fgets((char *)chunk, sizeof chunk, stdin) == NULL) {
            if (ferror(stdin)) {
                free(buffer);
                fputs("Input error.\n", stderr);
                return 0;
            }
            break;
        }

        size_t count = 0;
        while (count < sizeof chunk && chunk[count] != '\0' &&
               chunk[count] != '\n') {
            ++count;
        }

        if (count > SIZE_MAX - used - 1) {
            free(buffer);
            fputs("Input is too large.\n", stderr);
            return 0;
        }

        if (!grow_buffer(&buffer, &capacity, used + count + 1)) {
            free(buffer);
            fputs("Memory allocation failed or input is too large.\n", stderr);
            return 0;
        }

        if (count != 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(buffer + used, chunk, count);
            used += count;
        }

        if (chunk[count] == '\n') {
            break;
        }
    }

    if (!grow_buffer(&buffer, &capacity, used + 1)) {
        free(buffer);
        fputs("Memory allocation failed.\n", stderr);
        return 0;
    }

    buffer[used] = '\0';
    *sentence = buffer;
    *length = used;
    return 1;
}

int main(void)
{
    char *sentence = NULL;
    size_t length = 0;

    if (!read_sentence(&sentence, &length)) {
        return EXIT_FAILURE;
    }

    const int success = find_adverbs(sentence, length);
    free(sentence);

    return success ? EXIT_SUCCESS : EXIT_FAILURE;
}
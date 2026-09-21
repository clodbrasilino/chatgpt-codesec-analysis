#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_STRING_LENGTH 4096U

struct word_count {
    char *word;
    size_t count;
};

static char *duplicate_string(const char *src)
{
    size_t len;
    char *copy;

    if (src == NULL) {
        return NULL;
    }

    len = strnlen(src, MAX_STRING_LENGTH);
    if (len >= MAX_STRING_LENGTH) {
        return NULL;
    }

    copy = malloc(len + 1U);
    if (copy == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(copy, src, len);
    copy[len] = '\0';
    return copy;
}

char *most_frequent_word(const char *const *strings, size_t num_strings)
{
    struct word_count *counts = NULL;
    size_t num_words = 0U;
    size_t capacity = 0U;
    size_t i;
    size_t j;
    char *result = NULL;
    size_t best_index = 0U;
    int found_any = 0;

    if ((strings == NULL) || (num_strings == 0U)) {
        return NULL;
    }

    for (i = 0U; i < num_strings; i++) {
        char *buffer;
        char *token;
        char *saveptr = NULL;

        if (strings[i] == NULL) {
            continue;
        }

        buffer = duplicate_string(strings[i]);
        if (buffer == NULL) {
            goto cleanup;
        }

        token = strtok_r(buffer, " \t\n\r", &saveptr);
        while (token != NULL) {
            int matched = 0;

            for (j = 0U; j < num_words; j++) {
                if (strcmp(counts[j].word, token) == 0) {
                    counts[j].count++;
                    matched = 1;
                    break;
                }
            }

            if (matched == 0) {
                if (num_words == capacity) {
                    size_t new_capacity = (capacity == 0U) ? 16U : (capacity * 2U);
                    struct word_count *tmp;

                    if (new_capacity < capacity) {
                        free(buffer);
                        goto cleanup;
                    }

                    if (new_capacity > (SIZE_MAX / sizeof(*tmp))) {
                        free(buffer);
                        goto cleanup;
                    }

                    tmp = realloc(counts, new_capacity * sizeof(*tmp));
                    if (tmp == NULL) {
                        free(buffer);
                        goto cleanup;
                    }
                    counts = tmp;
                    capacity = new_capacity;
                }

                counts[num_words].word = duplicate_string(token);
                if (counts[num_words].word == NULL) {
                    free(buffer);
                    goto cleanup;
                }
                counts[num_words].count = 1U;
                num_words++;
            }

            token = strtok_r(NULL, " \t\n\r", &saveptr);
        }

        free(buffer);
    }

    for (j = 0U; j < num_words; j++) {
        if ((found_any == 0) || (counts[j].count > counts[best_index].count)) {
            best_index = j;
            found_any = 1;
        }
    }

    if (found_any != 0) {
        result = duplicate_string(counts[best_index].word);
    }

cleanup:
    for (j = 0U; j < num_words; j++) {
        free(counts[j].word);
    }
    free(counts);

    return result;
}

int main(void)
{
    const char *const strings[] = {
        "the quick brown fox",
        "the lazy dog and the cat",
        "quick quick fox"
    };
    size_t num_strings = sizeof(strings) / sizeof(strings[0]);
    char *word;

    word = most_frequent_word(strings, num_strings);
    if (word == NULL) {
        if (fprintf(stderr, "Failed to determine most frequent word\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("Most frequent word: %s\n", word) < 0) {
        free(word);
        return EXIT_FAILURE;
    }

    free(word);
    return EXIT_SUCCESS;
}
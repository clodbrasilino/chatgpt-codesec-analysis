#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    WORD_COUNT_OK,
    WORD_COUNT_INVALID_ARGUMENT,
    WORD_COUNT_NOT_FOUND,
    WORD_COUNT_ALLOCATION_FAILURE,
    WORD_COUNT_OVERFLOW
} WordCountStatus;

typedef struct {
    char *word;
    size_t length;
    size_t count;
} WordEntry;

static void free_entries(WordEntry *entries, size_t count)
{
    size_t i;

    for (i = 0; i < count; ++i) {
        free(entries[i].word);
    }

    free(entries);
}

static int word_matches(const WordEntry *entry,
                        const unsigned char *word,
                        size_t length)
{
    size_t i;

    if (entry->length != length) {
        return 0;
    }

    for (i = 0; i < length; ++i) {
        if ((unsigned char)entry->word[i] !=
            (unsigned char)tolower(word[i])) {
            return 0;
        }
    }

    return 1;
}

static WordCountStatus get_most_frequent_word(
    const char *const strings[],
    size_t string_count,
    char **result,
    size_t *occurrences)
{
    WordEntry *entries = NULL;
    size_t entry_count = 0;
    size_t capacity = 0;
    size_t best_index = 0;
    size_t i;

    if (result == NULL || occurrences == NULL) {
        return WORD_COUNT_INVALID_ARGUMENT;
    }

    *result = NULL;
    *occurrences = 0;

    if (string_count != 0 && strings == NULL) {
        return WORD_COUNT_INVALID_ARGUMENT;
    }

    for (i = 0; i < string_count; ++i) {
        const unsigned char *cursor;

        if (strings[i] == NULL) {
            free_entries(entries, entry_count);
            return WORD_COUNT_INVALID_ARGUMENT;
        }

        cursor = (const unsigned char *)strings[i];

        while (*cursor != '\0') {
            const unsigned char *start;
            size_t length;
            size_t entry_index;

            while (*cursor != '\0' &&
                   !isalnum(*cursor) &&
                   *cursor != '_') {
                ++cursor;
            }

            if (*cursor == '\0') {
                break;
            }

            start = cursor;

            while (*cursor != '\0' &&
                   (isalnum(*cursor) || *cursor == '_')) {
                ++cursor;
            }

            length = (size_t)(cursor - start);

            for (entry_index = 0;
                 entry_index < entry_count;
                 ++entry_index) {
                if (word_matches(&entries[entry_index], start, length)) {
                    break;
                }
            }

            if (entry_index < entry_count) {
                if (entries[entry_index].count == SIZE_MAX) {
                    free_entries(entries, entry_count);
                    return WORD_COUNT_OVERFLOW;
                }

                ++entries[entry_index].count;

                if (entries[entry_index].count >
                    entries[best_index].count) {
                    best_index = entry_index;
                }
            } else {
                char *new_word;
                size_t j;

                if (entry_count == capacity) {
                    WordEntry *new_entries;
                    size_t new_capacity;

                    if (capacity == 0) {
                        new_capacity = 8;
                    } else {
                        if (capacity > SIZE_MAX / 2) {
                            free_entries(entries, entry_count);
                            return WORD_COUNT_OVERFLOW;
                        }

                        new_capacity = capacity * 2;
                    }

                    if (new_capacity > SIZE_MAX / sizeof(*entries)) {
                        free_entries(entries, entry_count);
                        return WORD_COUNT_OVERFLOW;
                    }

                    new_entries = realloc(
                        entries,
                        new_capacity * sizeof(*entries));

                    if (new_entries == NULL) {
                        free_entries(entries, entry_count);
                        return WORD_COUNT_ALLOCATION_FAILURE;
                    }

                    entries = new_entries;
                    capacity = new_capacity;
                }

                if (length == SIZE_MAX) {
                    free_entries(entries, entry_count);
                    return WORD_COUNT_OVERFLOW;
                }

                new_word = malloc(length + 1);

                if (new_word == NULL) {
                    free_entries(entries, entry_count);
                    return WORD_COUNT_ALLOCATION_FAILURE;
                }

                for (j = 0; j < length; ++j) {
                    new_word[j] = (char)tolower(start[j]);
                }

                new_word[length] = '\0';

                entries[entry_count].word = new_word;
                entries[entry_count].length = length;
                entries[entry_count].count = 1;

                if (entry_count == 0) {
                    best_index = 0;
                }

                ++entry_count;
            }
        }
    }

    if (entry_count == 0) {
        free(entries);
        return WORD_COUNT_NOT_FOUND;
    }

    *result = entries[best_index].word;
    *occurrences = entries[best_index].count;
    entries[best_index].word = NULL;

    free_entries(entries, entry_count);
    return WORD_COUNT_OK;
}

static const char *word_count_status_string(WordCountStatus status)
{
    switch (status) {
        case WORD_COUNT_OK:
            return "success";
        case WORD_COUNT_INVALID_ARGUMENT:
            return "invalid argument";
        case WORD_COUNT_NOT_FOUND:
            return "no words found";
        case WORD_COUNT_ALLOCATION_FAILURE:
            return "memory allocation failed";
        case WORD_COUNT_OVERFLOW:
            return "numeric overflow";
        default:
            return "unknown error";
    }
}

int main(void)
{
    const char *strings[] = {
        "The quick brown fox jumps over the lazy dog.",
        "The fox is quick, and the dog is lazy.",
        "The fox watches the dog."
    };
    char *word = NULL;
    size_t occurrences = 0;
    WordCountStatus status;

    status = get_most_frequent_word(
        strings,
        sizeof(strings) / sizeof(strings[0]),
        &word,
        &occurrences);

    if (status != WORD_COUNT_OK) {
        if (fprintf(stderr, "%s\n", word_count_status_string(status)) < 0) {
            return EXIT_FAILURE;
        }

        return EXIT_FAILURE;
    }

    if (printf("%s: %zu\n", word, occurrences) < 0) {
        free(word);
        return EXIT_FAILURE;
    }

    free(word);
    return EXIT_SUCCESS;
}
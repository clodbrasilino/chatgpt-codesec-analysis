#include <ctype.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    WORD_COUNT_OK,
    WORD_COUNT_INVALID_ARGUMENT,
    WORD_COUNT_NOT_FOUND,
    WORD_COUNT_ALLOCATION_FAILURE,
    WORD_COUNT_OVERFLOW
} WordCountStatus;

typedef struct {
    const char *data;
    size_t length;
} TextView;

typedef struct {
    char *word;
    size_t length;
    size_t count;
} WordEntry;

static int is_word_character(unsigned char character)
{
    return isalnum((int)character) != 0 ||
           character == (unsigned char)'_';
}

static unsigned char lowercase_character(unsigned char character)
{
    return (unsigned char)tolower((int)character);
}

static void free_entries(WordEntry *entries, size_t count)
{
    size_t index;

    if (entries == NULL) {
        return;
    }

    for (index = 0; index < count; ++index) {
        free(entries[index].word);
    }

    free(entries);
}

static int word_matches(const WordEntry *entry,
                        const unsigned char *word,
                        size_t length)
{
    size_t index;

    if (entry == NULL || word == NULL || entry->word == NULL ||
        entry->length != length) {
        return 0;
    }

    for (index = 0; index < length; ++index) {
        if ((unsigned char)entry->word[index] !=
            lowercase_character(word[index])) {
            return 0;
        }
    }

    return 1;
}

static WordCountStatus grow_entries(WordEntry **entries, size_t *capacity)
{
    WordEntry *resized_entries;
    size_t new_capacity;

    if (entries == NULL || capacity == NULL) {
        return WORD_COUNT_INVALID_ARGUMENT;
    }

    if (*capacity == 0) {
        new_capacity = 8;
    } else {
        if (*capacity > SIZE_MAX / 2) {
            return WORD_COUNT_OVERFLOW;
        }

        new_capacity = *capacity * 2;
    }

    if (new_capacity > SIZE_MAX / sizeof(*resized_entries)) {
        return WORD_COUNT_OVERFLOW;
    }

    resized_entries = realloc(
        *entries,
        new_capacity * sizeof(*resized_entries));

    if (resized_entries == NULL) {
        return WORD_COUNT_ALLOCATION_FAILURE;
    }

    *entries = resized_entries;
    *capacity = new_capacity;

    return WORD_COUNT_OK;
}

static WordCountStatus copy_normalized_word(const unsigned char *word,
                                            size_t length,
                                            char **copy)
{
    char *new_word;
    size_t index;

    if (copy == NULL) {
        return WORD_COUNT_INVALID_ARGUMENT;
    }

    *copy = NULL;

    if (word == NULL || length == 0) {
        return WORD_COUNT_INVALID_ARGUMENT;
    }

    if (length > SIZE_MAX - 1) {
        return WORD_COUNT_OVERFLOW;
    }

    new_word = malloc(length + 1);
    if (new_word == NULL) {
        return WORD_COUNT_ALLOCATION_FAILURE;
    }

    for (index = 0; index < length; ++index) {
        new_word[index] = (char)lowercase_character(word[index]);
    }

    new_word[length] = '\0';
    *copy = new_word;

    return WORD_COUNT_OK;
}

static WordCountStatus get_most_frequent_word(const TextView *strings,
                                               size_t string_count,
                                               char **result,
                                               size_t *occurrences)
{
    WordEntry *entries = NULL;
    size_t entry_count = 0;
    size_t capacity = 0;
    size_t best_index = 0;
    size_t string_index;
    WordCountStatus status = WORD_COUNT_OK;

    if (result == NULL || occurrences == NULL) {
        return WORD_COUNT_INVALID_ARGUMENT;
    }

    *result = NULL;
    *occurrences = 0;

    if (string_count != 0 && strings == NULL) {
        return WORD_COUNT_INVALID_ARGUMENT;
    }

    for (string_index = 0; string_index < string_count; ++string_index) {
        const unsigned char *text;
        size_t text_length;
        size_t position = 0;

        if (strings[string_index].length != 0 &&
            strings[string_index].data == NULL) {
            status = WORD_COUNT_INVALID_ARGUMENT;
            goto cleanup;
        }

        text = (const unsigned char *)strings[string_index].data;
        text_length = strings[string_index].length;

        while (position < text_length) {
            size_t start;
            size_t word_length;
            size_t entry_index;

            while (position < text_length &&
                   !is_word_character(text[position])) {
                ++position;
            }

            if (position >= text_length) {
                break;
            }

            start = position;

            while (position < text_length &&
                   is_word_character(text[position])) {
                ++position;
            }

            word_length = position - start;

            for (entry_index = 0;
                 entry_index < entry_count;
                 ++entry_index) {
                if (word_matches(&entries[entry_index],
                                 &text[start],
                                 word_length)) {
                    break;
                }
            }

            if (entry_index < entry_count) {
                if (entries[entry_index].count == SIZE_MAX) {
                    status = WORD_COUNT_OVERFLOW;
                    goto cleanup;
                }

                ++entries[entry_index].count;

                if (entries[entry_index].count >
                    entries[best_index].count) {
                    best_index = entry_index;
                }
            } else {
                char *new_word = NULL;

                if (entry_count == SIZE_MAX) {
                    status = WORD_COUNT_OVERFLOW;
                    goto cleanup;
                }

                if (entry_count == capacity) {
                    status = grow_entries(&entries, &capacity);
                    if (status != WORD_COUNT_OK) {
                        goto cleanup;
                    }
                }

                status = copy_normalized_word(
                    &text[start],
                    word_length,
                    &new_word);

                if (status != WORD_COUNT_OK) {
                    goto cleanup;
                }

                entries[entry_count].word = new_word;
                entries[entry_count].length = word_length;
                entries[entry_count].count = 1;

                if (entry_count == 0) {
                    best_index = 0;
                }

                ++entry_count;
            }
        }
    }

    if (entry_count == 0) {
        status = WORD_COUNT_NOT_FOUND;
        goto cleanup;
    }

    *result = entries[best_index].word;
    *occurrences = entries[best_index].count;
    entries[best_index].word = NULL;

cleanup:
    free_entries(entries, entry_count);
    return status;
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
    static const char first_text[] =
        "The quick brown fox jumps over the lazy dog.";
    static const char second_text[] =
        "The fox is quick, and the dog is lazy.";
    static const char third_text[] =
        "The fox watches the dog.";

    const TextView strings[] = {
        { first_text, sizeof(first_text) - 1 },
        { second_text, sizeof(second_text) - 1 },
        { third_text, sizeof(third_text) - 1 }
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
        if (fprintf(stderr, "%s\n",
                    word_count_status_string(status)) < 0) {
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
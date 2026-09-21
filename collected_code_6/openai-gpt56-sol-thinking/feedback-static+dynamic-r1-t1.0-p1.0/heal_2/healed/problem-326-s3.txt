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
    const unsigned char *data;
    size_t length;
} StringView;

typedef struct {
    char *word;
    size_t length;
    size_t count;
} WordEntry;

static void free_entries(WordEntry *entries, size_t count)
{
    size_t i;

    if (entries == NULL) {
        return;
    }

    for (i = 0; i < count; ++i) {
        free(entries[i].word);
    }

    free(entries);
}

static int is_word_character(unsigned char character)
{
    return isalnum((int)character) != 0 ||
           character == (unsigned char)'_';
}

static unsigned char lowercase_character(unsigned char character)
{
    return (unsigned char)tolower((int)character);
}

static int word_matches(const WordEntry *entry,
                        const unsigned char *word,
                        size_t length)
{
    size_t i;

    if (entry == NULL || word == NULL || entry->length != length) {
        return 0;
    }

    for (i = 0; i < length; ++i) {
        if ((unsigned char)entry->word[i] !=
            lowercase_character(word[i])) {
            return 0;
        }
    }

    return 1;
}

static WordCountStatus grow_entries(WordEntry **entries, size_t *capacity)
{
    WordEntry *new_entries;
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

    if (new_capacity > SIZE_MAX / sizeof(**entries)) {
        return WORD_COUNT_OVERFLOW;
    }

    new_entries = realloc(*entries, new_capacity * sizeof(**entries));
    if (new_entries == NULL) {
        return WORD_COUNT_ALLOCATION_FAILURE;
    }

    *entries = new_entries;
    *capacity = new_capacity;

    return WORD_COUNT_OK;
}

static WordCountStatus create_word(const unsigned char *source,
                                   size_t length,
                                   char **word)
{
    char *new_word;
    size_t i;

    if (source == NULL || word == NULL) {
        return WORD_COUNT_INVALID_ARGUMENT;
    }

    *word = NULL;

    if (length == SIZE_MAX) {
        return WORD_COUNT_OVERFLOW;
    }

    new_word = malloc(length + 1);
    if (new_word == NULL) {
        return WORD_COUNT_ALLOCATION_FAILURE;
    }

    for (i = 0; i < length; ++i) {
        new_word[i] = (char)lowercase_character(source[i]);
    }

    new_word[length] = '\0';
    *word = new_word;

    return WORD_COUNT_OK;
}

static WordCountStatus get_most_frequent_word(
    const StringView *strings,
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
        const unsigned char *text = strings[i].data;
        size_t text_length = strings[i].length;
        size_t position = 0;

        if (text_length != 0 && text == NULL) {
            free_entries(entries, entry_count);
            return WORD_COUNT_INVALID_ARGUMENT;
        }

        while (position < text_length) {
            size_t start;
            size_t length;
            size_t entry_index;

            while (position < text_length &&
                   !is_word_character(text[position])) {
                ++position;
            }

            if (position == text_length) {
                break;
            }

            start = position;

            while (position < text_length &&
                   is_word_character(text[position])) {
                ++position;
            }

            length = position - start;

            for (entry_index = 0;
                 entry_index < entry_count;
                 ++entry_index) {
                if (word_matches(&entries[entry_index],
                                 text + start,
                                 length)) {
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
                WordCountStatus status;
                char *new_word = NULL;

                if (entry_count == capacity) {
                    status = grow_entries(&entries, &capacity);
                    if (status != WORD_COUNT_OK) {
                        free_entries(entries, entry_count);
                        return status;
                    }
                }

                status = create_word(text + start, length, &new_word);
                if (status != WORD_COUNT_OK) {
                    free_entries(entries, entry_count);
                    return status;
                }

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
    static const unsigned char text1[] =
        "The quick brown fox jumps over the lazy dog.";
    static const unsigned char text2[] =
        "The fox is quick, and the dog is lazy.";
    static const unsigned char text3[] =
        "The fox watches the dog.";

    const StringView strings[] = {
        { text1, sizeof(text1) - 1 },
        { text2, sizeof(text2) - 1 },
        { text3, sizeof(text3) - 1 }
    };
    const size_t string_count = sizeof(strings) / sizeof(strings[0]);
    char *word = NULL;
    size_t occurrences = 0;
    WordCountStatus status;

    status = get_most_frequent_word(strings,
                                    string_count,
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
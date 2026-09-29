#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *word;
    size_t length;
    size_t count;
} WordCount;

static char *duplicate_string(const char *source, size_t length)
{
    char *copy;

    if (source == NULL || length == SIZE_MAX) {
        return NULL;
    }

    copy = malloc(length + 1U);
    if (copy == NULL) {
        return NULL;
    }

    if (length > 0U) {
        memcpy(copy, source, length);
    }

    copy[length] = '\0';
    return copy;
}

static int ensure_capacity(WordCount **items, size_t *capacity, size_t required)
{
    WordCount *resized;
    size_t maximum;
    size_t new_capacity;

    if (items == NULL || capacity == NULL) {
        return 0;
    }

    if (required <= *capacity) {
        return 1;
    }

    maximum = SIZE_MAX / sizeof **items;
    if (required > maximum) {
        return 0;
    }

    new_capacity = (*capacity == 0U) ? 8U : *capacity;

    if (new_capacity > maximum) {
        new_capacity = maximum;
    }

    while (new_capacity < required) {
        if (new_capacity > maximum / 2U) {
            new_capacity = required;
        } else {
            new_capacity *= 2U;
        }
    }

    resized = realloc(*items, new_capacity * sizeof **items);
    if (resized == NULL) {
        return 0;
    }

    *items = resized;
    *capacity = new_capacity;
    return 1;
}

static void free_word_counts(WordCount *items, size_t count)
{
    size_t index;

    if (items == NULL) {
        return;
    }

    for (index = 0U; index < count; ++index) {
        free(items[index].word);
    }

    free(items);
}

char *most_frequent_word(const char *const strings[],
                         const size_t lengths[],
                         size_t string_count)
{
    WordCount *items = NULL;
    size_t item_count = 0U;
    size_t capacity = 0U;
    size_t string_index;
    size_t best_index;
    char *result;

    if (strings == NULL || lengths == NULL || string_count == 0U) {
        return NULL;
    }

    for (string_index = 0U; string_index < string_count; ++string_index) {
        const char *current = strings[string_index];
        size_t current_length = lengths[string_index];
        size_t item_index;

        if (current == NULL || current_length == SIZE_MAX) {
            free_word_counts(items, item_count);
            return NULL;
        }

        for (item_index = 0U; item_index < item_count; ++item_index) {
            if (items[item_index].length == current_length &&
                (current_length == 0U ||
                 memcmp(items[item_index].word,
                        current,
                        current_length) == 0)) {
                if (items[item_index].count == SIZE_MAX) {
                    free_word_counts(items, item_count);
                    return NULL;
                }

                ++items[item_index].count;
                break;
            }
        }

        if (item_index == item_count) {
            char *word_copy;

            if (item_count == SIZE_MAX ||
                !ensure_capacity(&items, &capacity, item_count + 1U)) {
                free_word_counts(items, item_count);
                return NULL;
            }

            word_copy = duplicate_string(current, current_length);
            if (word_copy == NULL) {
                free_word_counts(items, item_count);
                return NULL;
            }

            items[item_count].word = word_copy;
            items[item_count].length = current_length;
            items[item_count].count = 1U;
            ++item_count;
        }
    }

    best_index = 0U;

    for (string_index = 1U; string_index < item_count; ++string_index) {
        if (items[string_index].count > items[best_index].count) {
            best_index = string_index;
        }
    }

    result = duplicate_string(items[best_index].word,
                              items[best_index].length);
    free_word_counts(items, item_count);
    return result;
}

int main(void)
{
    static const char apple[] = "apple";
    static const char banana[] = "banana";
    static const char orange[] = "orange";

    const char *strings[] = {
        apple,
        banana,
        apple,
        orange,
        banana,
        apple
    };

    const size_t lengths[] = {
        sizeof apple - 1U,
        sizeof banana - 1U,
        sizeof apple - 1U,
        sizeof orange - 1U,
        sizeof banana - 1U,
        sizeof apple - 1U
    };

    const size_t string_count = sizeof strings / sizeof strings[0];
    char *word = most_frequent_word(strings, lengths, string_count);

    if (word == NULL) {
        fputs("Unable to determine the most frequent word.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%s\n", word) < 0) {
        free(word);
        return EXIT_FAILURE;
    }

    free(word);
    return EXIT_SUCCESS;
}
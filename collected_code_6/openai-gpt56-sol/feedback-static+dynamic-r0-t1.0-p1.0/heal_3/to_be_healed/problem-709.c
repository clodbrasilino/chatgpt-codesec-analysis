#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *key;
    const char *value;
} Tuple;

typedef struct {
    char *value;
    const char **keys;
    size_t key_count;
    size_t key_capacity;
} ValueKeyCount;

static void free_counts(ValueKeyCount *counts, size_t count)
{
    size_t i;

    if (counts == NULL) {
        return;
    }

    for (i = 0; i < count; ++i) {
        free(counts[i].value);
        free(counts[i].keys);
    }

    free(counts);
}

static char *duplicate_string(const char *source, size_t length)
{
    char *copy;

    if (source == NULL || length == SIZE_MAX) {
        return NULL;
    }

    copy = malloc(length + 1);
    if (copy == NULL) {
        return NULL;
    }

    if (length != 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(copy, source, length);
    }
    copy[length] = '\0';

    return copy;
}

static int add_unique_key(ValueKeyCount *entry, const char *key)
{
    size_t i;

    if (entry == NULL || key == NULL) {
        return -1;
    }

    for (i = 0; i < entry->key_count; ++i) {
        if (strcmp(entry->keys[i], key) == 0) {
            return 0;
        }
    }

    if (entry->key_count == entry->key_capacity) {
        size_t new_capacity;
        const char **new_keys;

        if (entry->key_capacity == 0) {
            new_capacity = 4;
        } else {
            if (entry->key_capacity > SIZE_MAX / 2) {
                return -1;
            }
            new_capacity = entry->key_capacity * 2;
        }

        if (new_capacity > SIZE_MAX / sizeof(*new_keys)) {
            return -1;
        }

        new_keys = realloc(entry->keys,
                           new_capacity * sizeof(*new_keys));
        if (new_keys == NULL) {
            return -1;
        }

        entry->keys = new_keys;
        entry->key_capacity = new_capacity;
    }

    entry->keys[entry->key_count] = key;
    ++entry->key_count;

    return 0;
}

static int count_unique_keys_by_value(const Tuple *tuples,
                                      size_t tuple_count,
                                      ValueKeyCount **result,
                                      size_t *result_count)
{
    ValueKeyCount *counts = NULL;
    size_t count = 0;
    size_t capacity = 0;
    size_t i;

    if (result == NULL || result_count == NULL ||
        (tuples == NULL && tuple_count != 0)) {
        return -1;
    }

    *result = NULL;
    *result_count = 0;

    for (i = 0; i < tuple_count; ++i) {
        size_t value_index;
        size_t value_length;

        if (tuples[i].key == NULL || tuples[i].value == NULL) {
            free_counts(counts, count);
            return -1;
        }

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        value_length = strlen(tuples[i].value);

        for (value_index = 0; value_index < count; ++value_index) {
            if (strcmp(counts[value_index].value, tuples[i].value) == 0) {
                break;
            }
        }

        if (value_index == count) {
            char *value_copy;

            if (count == capacity) {
                size_t new_capacity;
                ValueKeyCount *new_counts;

                if (capacity == 0) {
                    new_capacity = 4;
                } else {
                    if (capacity > SIZE_MAX / 2) {
                        free_counts(counts, count);
                        return -1;
                    }
                    new_capacity = capacity * 2;
                }

                if (new_capacity > SIZE_MAX / sizeof(*new_counts)) {
                    free_counts(counts, count);
                    return -1;
                }

                new_counts = realloc(
                    counts, new_capacity * sizeof(*new_counts));
                if (new_counts == NULL) {
                    free_counts(counts, count);
                    return -1;
                }

                counts = new_counts;
                capacity = new_capacity;
            }

            value_copy = duplicate_string(tuples[i].value, value_length);
            if (value_copy == NULL) {
                free_counts(counts, count);
                return -1;
            }

            counts[count].value = value_copy;
            counts[count].keys = NULL;
            counts[count].key_count = 0;
            counts[count].key_capacity = 0;

            value_index = count;
            ++count;
        }

        if (add_unique_key(&counts[value_index], tuples[i].key) != 0) {
            free_counts(counts, count);
            return -1;
        }
    }

    *result = counts;
    *result_count = count;

    return 0;
}

int main(void)
{
    static const Tuple tuples[] = {
        {"key1", "value1"},
        {"key2", "value1"},
        {"key1", "value1"},
        {"key3", "value2"},
        {"key4", "value2"},
        {"key3", "value3"}
    };
    ValueKeyCount *counts = NULL;
    size_t count = 0;
    size_t i;

    if (count_unique_keys_by_value(
            tuples,
            sizeof(tuples) / sizeof(tuples[0]),
            &counts,
            &count) != 0) {
        fprintf(stderr, "Unable to count unique keys\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; ++i) {
        if (printf("%s: %zu\n",
                   counts[i].value,
                   counts[i].key_count) < 0) {
            free_counts(counts, count);
            return EXIT_FAILURE;
        }
    }

    free_counts(counts, count);
    return EXIT_SUCCESS;
}
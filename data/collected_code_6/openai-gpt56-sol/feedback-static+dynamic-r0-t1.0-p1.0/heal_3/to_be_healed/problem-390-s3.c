#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int bounded_string_length(const char *string, size_t maximum, size_t *length)
{
    const char *end;

    if (string == NULL || length == NULL) {
        return -1;
    }

    end = memchr(string, '\0', maximum);
    if (end == NULL) {
        return -1;
    }

    *length = (size_t)(end - string);
    return 0;
}

static int prefix_items(char **items, size_t count,
                        const char *prefix, size_t prefix_capacity,
                        size_t item_capacity)
{
    size_t prefix_len;
    char **replacements;

    if ((items == NULL && count != 0) || prefix == NULL ||
        prefix_capacity == 0 || item_capacity == 0) {
        return -1;
    }

    if (bounded_string_length(prefix, prefix_capacity, &prefix_len) != 0) {
        return -1;
    }

    if (count > SIZE_MAX / sizeof(*replacements)) {
        return -1;
    }

    replacements = calloc(count, sizeof(*replacements));
    if (replacements == NULL && count != 0) {
        return -1;
    }

    for (size_t i = 0; i < count; ++i) {
        size_t item_len;
        size_t allocation_size;

        if (items[i] == NULL ||
            bounded_string_length(items[i], item_capacity, &item_len) != 0) {
            goto failure;
        }

        if (prefix_len > SIZE_MAX - item_len - 1) {
            goto failure;
        }

        allocation_size = prefix_len + item_len + 1;
        replacements[i] = malloc(allocation_size);
        if (replacements[i] == NULL) {
            goto failure;
        }

        if (prefix_len > 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(replacements[i], prefix, prefix_len);
        }

        if (item_len > 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(replacements[i] + prefix_len, items[i], item_len);
        }

        replacements[i][allocation_size - 1] = '\0';
    }

    for (size_t i = 0; i < count; ++i) {
        free(items[i]);
        items[i] = replacements[i];
    }

    free(replacements);
    return 0;

failure:
    for (size_t i = 0; i < count; ++i) {
        free(replacements[i]);
    }

    free(replacements);
    return -1;
}

static void free_items(char **items, size_t count)
{
    if (items == NULL) {
        return;
    }

    for (size_t i = 0; i < count; ++i) {
        free(items[i]);
    }

    free(items);
}

static char *duplicate_string(const char *source, size_t source_capacity)
{
    size_t length;
    char *copy;

    if (source == NULL || source_capacity == 0 ||
        bounded_string_length(source, source_capacity, &length) != 0) {
        return NULL;
    }

    if (length == SIZE_MAX) {
        return NULL;
    }

    copy = malloc(length + 1);
    if (copy == NULL) {
        return NULL;
    }

    if (length > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(copy, source, length);
    }

    copy[length] = '\0';
    return copy;
}

int main(void)
{
    static const char *const initial_items[] = {
        "apple",
        "banana",
        "cherry"
    };
    static const size_t initial_capacities[] = {
        sizeof("apple"),
        sizeof("banana"),
        sizeof("cherry")
    };
    static const char prefix[] = "fruit: ";
    const size_t count = sizeof(initial_items) / sizeof(initial_items[0]);
    char **items;

    if (count > SIZE_MAX / sizeof(*items)) {
        return EXIT_FAILURE;
    }

    items = calloc(count, sizeof(*items));
    if (items == NULL && count != 0) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        items[i] = duplicate_string(initial_items[i], initial_capacities[i]);
        if (items[i] == NULL) {
            free_items(items, count);
            return EXIT_FAILURE;
        }
    }

    if (prefix_items(items, count, prefix, sizeof(prefix),
                     sizeof("banana")) != 0) {
        free_items(items, count);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        if (puts(items[i]) == EOF) {
            free_items(items, count);
            return EXIT_FAILURE;
        }
    }

    free_items(items, count);

    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
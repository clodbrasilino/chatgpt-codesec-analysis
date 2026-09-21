#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int checked_string_length(const char *string, size_t limit, size_t *length)
{
    const char *terminator;

    if (string == NULL || length == NULL) {
        return -1;
    }

    terminator = memchr(string, '\0', limit);
    if (terminator == NULL) {
        return -1;
    }

    *length = (size_t)(terminator - string);
    return 0;
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

static char *duplicate_string(const char *source)
{
    size_t length;
    char *copy;

    if (checked_string_length(source, SIZE_MAX, &length) != 0) {
        return NULL;
    }

    if (length > SIZE_MAX - 1) {
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

static int prefix_items(char **items, size_t count, const char *prefix)
{
    size_t prefix_length;
    char **replacements;

    if ((items == NULL && count != 0) || prefix == NULL) {
        return -1;
    }

    if (checked_string_length(prefix, SIZE_MAX, &prefix_length) != 0) {
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
        size_t item_length;
        size_t allocation_size;

        if (items[i] == NULL ||
            checked_string_length(items[i], SIZE_MAX, &item_length) != 0) {
            goto failure;
        }

        if (prefix_length > SIZE_MAX - item_length) {
            goto failure;
        }

        allocation_size = prefix_length + item_length;
        if (allocation_size == SIZE_MAX) {
            goto failure;
        }
        ++allocation_size;

        replacements[i] = malloc(allocation_size);
        if (replacements[i] == NULL) {
            goto failure;
        }

        if (prefix_length > 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(replacements[i], prefix, prefix_length);
        }

        if (item_length > 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(replacements[i] + prefix_length, items[i], item_length);
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
    free_items(replacements, count);
    return -1;
}

int main(void)
{
    static const char *const initial_items[] = {
        "apple",
        "banana",
        "cherry"
    };
    const size_t count = sizeof(initial_items) / sizeof(initial_items[0]);
    const char *prefix = "fruit: ";
    char **items;

    if (count > SIZE_MAX / sizeof(*items)) {
        return EXIT_FAILURE;
    }

    items = calloc(count, sizeof(*items));
    if (items == NULL && count != 0) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        items[i] = duplicate_string(initial_items[i]);
        if (items[i] == NULL) {
            free_items(items, count);
            return EXIT_FAILURE;
        }
    }

    if (prefix_items(items, count, prefix) != 0) {
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
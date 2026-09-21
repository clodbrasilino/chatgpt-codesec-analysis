#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LENGTH ((size_t)1048576)

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

static int bounded_string_length(const char *source, size_t limit,
                                 size_t *length)
{
    const char *terminator;

    if (source == NULL || length == NULL) {
        return -1;
    }

    terminator = memchr(source, '\0', limit);
    if (terminator == NULL) {
        return -1;
    }

    *length = (size_t)(terminator - source);
    return 0;
}

static char *duplicate_string(const char *source)
{
    size_t length;
    size_t allocation_size;
    char *copy;

    if (bounded_string_length(source, MAX_STRING_LENGTH, &length) != 0) {
        return NULL;
    }

    if (length > SIZE_MAX - 1) {
        return NULL;
    }

    allocation_size = length + 1;
    copy = malloc(allocation_size);
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

static int prefix_items(char **items, size_t count, const char *prefix)
{
    size_t prefix_length;
    char **replacements;

    if ((items == NULL && count != 0) || prefix == NULL) {
        return -1;
    }

    if (bounded_string_length(prefix, MAX_STRING_LENGTH,
                              &prefix_length) != 0) {
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
        size_t content_length;
        size_t allocation_size;
        char *destination;

        if (items[i] == NULL ||
            bounded_string_length(items[i], MAX_STRING_LENGTH,
                                  &item_length) != 0) {
            goto failure;
        }

        if (prefix_length > SIZE_MAX - item_length) {
            goto failure;
        }

        content_length = prefix_length + item_length;

        if (content_length > SIZE_MAX - 1) {
            goto failure;
        }

        allocation_size = content_length + 1;
        destination = malloc(allocation_size);
        if (destination == NULL) {
            goto failure;
        }

        if (prefix_length != 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(destination, prefix, prefix_length);
        }

        if (item_length != 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(destination + prefix_length, items[i], item_length);
        }

        destination[content_length] = '\0';
        replacements[i] = destination;
    }

    for (size_t i = 0; i < count; ++i) {
        free(items[i]);
        items[i] = replacements[i];
        replacements[i] = NULL;
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
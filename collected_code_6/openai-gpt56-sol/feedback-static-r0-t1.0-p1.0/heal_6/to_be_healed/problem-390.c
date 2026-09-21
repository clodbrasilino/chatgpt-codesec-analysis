#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int duplicate_string(const char *source, size_t source_size,
                            char **destination)
{
    const char *terminator;
    size_t length;
    char *copy;

    if (source == NULL || destination == NULL || source_size == 0) {
        return -1;
    }

    terminator = memchr(source, '\0', source_size);
    if (terminator == NULL) {
        return -1;
    }

    length = (size_t)(terminator - source);

    if (length > SIZE_MAX - 1) {
        return -1;
    }

    copy = malloc(length + 1);
    if (copy == NULL) {
        return -1;
    }

    if (length > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(copy, source, length);
    }
    copy[length] = '\0';

    *destination = copy;
    return 0;
}

static int prepend_to_all(char **items, size_t *item_sizes, size_t count,
                          const char *prefix, size_t prefix_size)
{
    char **updated;
    size_t *updated_sizes;
    const char *prefix_terminator;
    size_t prefix_len;
    size_t i;

    if (items == NULL || item_sizes == NULL || prefix == NULL ||
        prefix_size == 0) {
        return -1;
    }

    prefix_terminator = memchr(prefix, '\0', prefix_size);
    if (prefix_terminator == NULL) {
        return -1;
    }

    prefix_len = (size_t)(prefix_terminator - prefix);

    if (count > SIZE_MAX / sizeof(*updated) ||
        count > SIZE_MAX / sizeof(*updated_sizes)) {
        return -1;
    }

    updated = calloc(count, sizeof(*updated));
    updated_sizes = calloc(count, sizeof(*updated_sizes));

    if (count != 0 && (updated == NULL || updated_sizes == NULL)) {
        free(updated_sizes);
        free(updated);
        return -1;
    }

    for (i = 0; i < count; ++i) {
        const char *item_terminator;
        size_t item_len;
        size_t allocation_size;

        if (items[i] == NULL || item_sizes[i] == 0) {
            goto failure;
        }

        item_terminator = memchr(items[i], '\0', item_sizes[i]);
        if (item_terminator == NULL) {
            goto failure;
        }

        item_len = (size_t)(item_terminator - items[i]);

        if (prefix_len > SIZE_MAX - item_len) {
            goto failure;
        }

        allocation_size = prefix_len + item_len;

        if (allocation_size == SIZE_MAX) {
            goto failure;
        }

        ++allocation_size;

        updated[i] = malloc(allocation_size);
        if (updated[i] == NULL) {
            goto failure;
        }

        if (prefix_len > 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(updated[i], prefix, prefix_len);
        }

        if (item_len > 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(updated[i] + prefix_len, items[i], item_len);
        }

        updated[i][prefix_len + item_len] = '\0';
        updated_sizes[i] = allocation_size;
    }

    for (i = 0; i < count; ++i) {
        free(items[i]);
        items[i] = updated[i];
        item_sizes[i] = updated_sizes[i];
    }

    free(updated_sizes);
    free(updated);
    return 0;

failure:
    while (i > 0) {
        --i;
        free(updated[i]);
    }

    free(updated_sizes);
    free(updated);
    return -1;
}

int main(void)
{
    static const char *const initial[] = {
        "apple",
        "banana",
        "cherry"
    };
    static const size_t initial_sizes[] = {
        sizeof("apple"),
        sizeof("banana"),
        sizeof("cherry")
    };
    static const char prefix[] = "fresh-";
    const size_t count = sizeof(initial) / sizeof(initial[0]);
    char **items = NULL;
    size_t *item_sizes = NULL;
    size_t initialized = 0;
    size_t i;
    int result = EXIT_FAILURE;

    if (count > SIZE_MAX / sizeof(*items) ||
        count > SIZE_MAX / sizeof(*item_sizes)) {
        return EXIT_FAILURE;
    }

    items = calloc(count, sizeof(*items));
    item_sizes = calloc(count, sizeof(*item_sizes));

    if (count != 0 && (items == NULL || item_sizes == NULL)) {
        goto cleanup;
    }

    for (i = 0; i < count; ++i) {
        if (duplicate_string(initial[i], initial_sizes[i], &items[i]) != 0) {
            goto cleanup;
        }

        item_sizes[i] = initial_sizes[i];
        ++initialized;
    }

    if (prepend_to_all(items, item_sizes, count, prefix, sizeof(prefix)) != 0) {
        goto cleanup;
    }

    for (i = 0; i < count; ++i) {
        if (puts(items[i]) == EOF) {
            goto cleanup;
        }
    }

    result = EXIT_SUCCESS;

cleanup:
    for (i = 0; i < initialized; ++i) {
        free(items[i]);
    }

    free(item_sizes);
    free(items);

    return result;
}
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *duplicate_string(const char *source, size_t source_size)
{
    const char *terminator;
    size_t length;
    char *copy;

    if (source == NULL || source_size == 0) {
        return NULL;
    }

    terminator = memchr(source, '\0', source_size);
    if (terminator == NULL) {
        return NULL;
    }

    length = (size_t)(terminator - source);
    copy = malloc(length + 1);
    if (copy == NULL) {
        return NULL;
    }

    memcpy(copy, source, length);
    copy[length] = '\0';

    return copy;
}

static int prepend_to_all(char **items, const size_t *item_sizes,
                          size_t count, const char *prefix,
                          size_t prefix_size)
{
    const char *prefix_terminator;
    size_t prefix_len;
    char **updated;
    size_t i;

    if (items == NULL || prefix == NULL || prefix_size == 0 ||
        (count > 0 && item_sizes == NULL)) {
        return -1;
    }

    prefix_terminator = memchr(prefix, '\0', prefix_size);
    if (prefix_terminator == NULL) {
        return -1;
    }

    prefix_len = (size_t)(prefix_terminator - prefix);

    if (count > SIZE_MAX / sizeof(*updated)) {
        return -1;
    }

    updated = calloc(count, sizeof(*updated));
    if (count > 0 && updated == NULL) {
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

        if (item_len > SIZE_MAX - prefix_len - 1) {
            goto failure;
        }

        allocation_size = prefix_len + item_len + 1;
        updated[i] = malloc(allocation_size);
        if (updated[i] == NULL) {
            goto failure;
        }

        memcpy(updated[i], prefix, prefix_len);
        memcpy(updated[i] + prefix_len, items[i], item_len);
        updated[i][prefix_len + item_len] = '\0';
    }

    for (i = 0; i < count; ++i) {
        free(items[i]);
        items[i] = updated[i];
    }

    free(updated);
    return 0;

failure:
    while (i > 0) {
        --i;
        free(updated[i]);
    }

    free(updated);
    return -1;
}

int main(void)
{
    static const char initial[][7] = {
        "apple",
        "banana",
        "cherry"
    };
    static const char prefix[] = "fresh-";
    const size_t count = sizeof(initial) / sizeof(initial[0]);
    char **items = NULL;
    size_t *item_sizes = NULL;
    size_t i;
    int result = EXIT_FAILURE;

    if (count > SIZE_MAX / sizeof(*items) ||
        count > SIZE_MAX / sizeof(*item_sizes)) {
        return EXIT_FAILURE;
    }

    items = calloc(count, sizeof(*items));
    item_sizes = calloc(count, sizeof(*item_sizes));
    if (items == NULL || item_sizes == NULL) {
        goto cleanup;
    }

    for (i = 0; i < count; ++i) {
        items[i] = duplicate_string(initial[i], sizeof(initial[i]));
        if (items[i] == NULL) {
            goto cleanup;
        }

        item_sizes[i] = sizeof(initial[i]);
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
    if (items != NULL) {
        for (i = 0; i < count; ++i) {
            free(items[i]);
        }
    }

    free(item_sizes);
    free(items);

    return result;
}
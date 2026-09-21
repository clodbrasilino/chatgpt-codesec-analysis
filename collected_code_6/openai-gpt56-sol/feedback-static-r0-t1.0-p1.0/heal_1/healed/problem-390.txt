#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int prepend_to_all(char **items, size_t count, const char *prefix)
{
    size_t prefix_len;
    char **updated;
    size_t i;

    if (items == NULL || prefix == NULL) {
        return -1;
    }

    prefix_len = strlen(prefix);

    if (count > SIZE_MAX / sizeof(*updated)) {
        return -1;
    }

    updated = calloc(count, sizeof(*updated));
    if (count != 0 && updated == NULL) {
        return -1;
    }

    for (i = 0; i < count; ++i) {
        size_t item_len;
        size_t allocation_size;

        if (items[i] == NULL) {
            goto failure;
        }

        item_len = strlen(items[i]);

        if (prefix_len == SIZE_MAX || item_len > SIZE_MAX - prefix_len - 1) {
            goto failure;
        }

        allocation_size = prefix_len + item_len + 1;
        updated[i] = malloc(allocation_size);
        if (updated[i] == NULL) {
            goto failure;
        }

        if (prefix_len != 0) {
            memcpy(updated[i], prefix, prefix_len);
        }
        if (item_len != 0) {
            memcpy(updated[i] + prefix_len, items[i], item_len);
        }
        updated[i][prefix_len + item_len] = '\0';
    }

    for (i = 0; i < count; ++i) {
        free(items[i]);
        items[i] = updated[i];
    }

    free(updated);
    return 0;

failure:
    while (i != 0) {
        free(updated[--i]);
    }
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
    static const char prefix[] = "fresh-";
    const size_t count = sizeof(initial) / sizeof(initial[0]);
    char **items;
    size_t initialized = 0;
    size_t i;
    int result = EXIT_FAILURE;

    if (count > SIZE_MAX / sizeof(*items)) {
        return EXIT_FAILURE;
    }

    items = calloc(count, sizeof(*items));
    if (count != 0 && items == NULL) {
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; ++i) {
        size_t length = strlen(initial[i]);

        if (length == SIZE_MAX) {
            goto cleanup;
        }

        items[i] = malloc(length + 1);
        if (items[i] == NULL) {
            goto cleanup;
        }

        memcpy(items[i], initial[i], length);
        items[i][length] = '\0';
        ++initialized;
    }

    if (prepend_to_all(items, count, prefix) != 0) {
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
    free(items);

    return result;
}
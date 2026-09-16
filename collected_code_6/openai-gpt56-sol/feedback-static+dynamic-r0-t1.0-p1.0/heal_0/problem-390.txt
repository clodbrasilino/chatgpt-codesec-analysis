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

    updated = calloc(count, sizeof(*updated));
    if (count > 0 && updated == NULL) {
        return -1;
    }

    for (i = 0; i < count; ++i) {
        size_t item_len;

        if (items[i] == NULL) {
            goto failure;
        }

        item_len = strlen(items[i]);
        if (prefix_len > SIZE_MAX - item_len - 1) {
            goto failure;
        }

        updated[i] = malloc(prefix_len + item_len + 1);
        if (updated[i] == NULL) {
            goto failure;
        }

        memcpy(updated[i], prefix, prefix_len);
        memcpy(updated[i] + prefix_len, items[i], item_len + 1);
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
    const char *initial[] = {"apple", "banana", "cherry"};
    const char *prefix = "fresh-";
    const size_t count = sizeof(initial) / sizeof(initial[0]);
    char **items;
    size_t i;
    int result = EXIT_FAILURE;

    items = calloc(count, sizeof(*items));
    if (items == NULL) {
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; ++i) {
        size_t length = strlen(initial[i]);

        items[i] = malloc(length + 1);
        if (items[i] == NULL) {
            goto cleanup;
        }

        memcpy(items[i], initial[i], length + 1);
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
    for (i = 0; i < count; ++i) {
        free(items[i]);
    }
    free(items);

    return result;
}
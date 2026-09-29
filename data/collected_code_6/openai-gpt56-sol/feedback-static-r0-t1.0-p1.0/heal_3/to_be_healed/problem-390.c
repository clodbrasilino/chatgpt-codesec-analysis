#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int prepend_to_all(char **items, size_t count, const char *prefix)
{
    char **updated = NULL;
    size_t prefix_len;
    size_t i = 0;

    if (items == NULL || prefix == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
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
        int written;

        if (items[i] == NULL) {
            goto failure;
        }

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        item_len = strlen(items[i]);

        if (prefix_len > SIZE_MAX - item_len ||
            prefix_len + item_len == SIZE_MAX) {
            goto failure;
        }

        allocation_size = prefix_len + item_len + 1;
        updated[i] = malloc(allocation_size);
        if (updated[i] == NULL) {
            goto failure;
        }

        written = snprintf(updated[i], allocation_size, "%s%s",
                           prefix, items[i]);
        if (written < 0 || (size_t)written >= allocation_size) {
            goto failure;
        }
    }

    for (i = 0; i < count; ++i) {
        free(items[i]);
        items[i] = updated[i];
    }

    free(updated);
    return 0;

failure:
    for (size_t j = 0; j <= i && j < count; ++j) {
        free(updated[j]);
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
    char **items = NULL;
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
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t length = strlen(initial[i]);
        int written;

        if (length == SIZE_MAX) {
            goto cleanup;
        }

        items[i] = malloc(length + 1);
        if (items[i] == NULL) {
            goto cleanup;
        }

        written = snprintf(items[i], length + 1, "%s", initial[i]);
        if (written < 0 || (size_t)written != length) {
            free(items[i]);
            items[i] = NULL;
            goto cleanup;
        }

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
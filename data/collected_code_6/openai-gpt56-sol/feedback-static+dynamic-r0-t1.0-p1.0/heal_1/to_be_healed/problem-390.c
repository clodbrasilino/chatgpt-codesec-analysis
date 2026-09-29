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

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
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

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        item_len = strlen(items[i]);
        if (prefix_len > SIZE_MAX - item_len - 1) {
            goto failure;
        }

        updated[i] = malloc(prefix_len + item_len + 1);
        if (updated[i] == NULL) {
            goto failure;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(updated[i], prefix, prefix_len);
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
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
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t length = strlen(initial[i]);

        items[i] = malloc(length + 1);
        if (items[i] == NULL) {
            goto cleanup;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
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
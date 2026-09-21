#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    if (source == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    length = strlen(source);
    if (length == SIZE_MAX) {
        return NULL;
    }

    copy = malloc(length + 1);
    if (copy == NULL) {
        return NULL;
    }

    snprintf(copy, length + 1, "%s", source);
    return copy;
}

static int prefix_items(char **items, size_t count, const char *prefix)
{
    size_t prefix_length;
    char **replacements;

    if ((items == NULL && count != 0) || prefix == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    prefix_length = strlen(prefix);

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
        int written;

        if (items[i] == NULL) {
            goto failure;
        }

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        item_length = strlen(items[i]);

        if (prefix_length > SIZE_MAX - item_length - 1) {
            goto failure;
        }

        allocation_size = prefix_length + item_length + 1;
        replacements[i] = malloc(allocation_size);
        if (replacements[i] == NULL) {
            goto failure;
        }

        written = snprintf(replacements[i], allocation_size, "%s%s",
                           prefix, items[i]);
        if (written < 0 || (size_t)written >= allocation_size) {
            goto failure;
        }
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
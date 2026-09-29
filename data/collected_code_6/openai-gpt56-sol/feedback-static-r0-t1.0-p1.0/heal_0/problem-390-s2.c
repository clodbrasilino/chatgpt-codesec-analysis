#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static int prepend_to_all(char ***items, size_t count, const char *prefix)
{
    char **replacements;
    size_t prefix_len;
    size_t i;

    if (items == NULL || (count > 0 && *items == NULL) || prefix == NULL) {
        return -1;
    }

    prefix_len = strlen(prefix);

    if (count > SIZE_MAX / sizeof(*replacements)) {
        return -1;
    }

    replacements = calloc(count, sizeof(*replacements));
    if (count > 0 && replacements == NULL) {
        return -1;
    }

    for (i = 0; i < count; ++i) {
        size_t item_len;

        if ((*items)[i] == NULL) {
            break;
        }

        item_len = strlen((*items)[i]);

        if (prefix_len > SIZE_MAX - item_len - 1) {
            break;
        }

        replacements[i] = malloc(prefix_len + item_len + 1);
        if (replacements[i] == NULL) {
            break;
        }

        memcpy(replacements[i], prefix, prefix_len);
        memcpy(replacements[i] + prefix_len, (*items)[i], item_len + 1);
    }

    if (i != count) {
        while (i > 0) {
            free(replacements[--i]);
        }
        free(replacements);
        return -1;
    }

    for (i = 0; i < count; ++i) {
        free((*items)[i]);
        (*items)[i] = replacements[i];
    }

    free(replacements);
    return 0;
}

static void free_items(char **items, size_t count)
{
    size_t i;

    if (items == NULL) {
        return;
    }

    for (i = 0; i < count; ++i) {
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

    length = strlen(source);

    if (length == SIZE_MAX) {
        return NULL;
    }

    copy = malloc(length + 1);
    if (copy == NULL) {
        return NULL;
    }

    memcpy(copy, source, length + 1);
    return copy;
}

int main(void)
{
    static const char *const source[] = {"apple", "banana", "cherry"};
    const char *prefix = "fruit: ";
    const size_t count = sizeof(source) / sizeof(source[0]);
    char **items;
    size_t i;

    if (count > SIZE_MAX / sizeof(*items)) {
        return EXIT_FAILURE;
    }

    items = calloc(count, sizeof(*items));
    if (items == NULL) {
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; ++i) {
        items[i] = duplicate_string(source[i]);
        if (items[i] == NULL) {
            free_items(items, count);
            return EXIT_FAILURE;
        }
    }

    if (prepend_to_all(&items, count, prefix) != 0) {
        free_items(items, count);
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; ++i) {
        if (puts(items[i]) == EOF) {
            free_items(items, count);
            return EXIT_FAILURE;
        }
    }

    free_items(items, count);
    return EXIT_SUCCESS;
}
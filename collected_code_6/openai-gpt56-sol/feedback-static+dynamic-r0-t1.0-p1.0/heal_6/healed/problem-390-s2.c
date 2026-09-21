#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static char *duplicate_string(const char *source, size_t length)
{
    char *copy;

    if (source == NULL || length == SIZE_MAX) {
        return NULL;
    }

    copy = malloc(length + 1);
    if (copy == NULL) {
        return NULL;
    }

    if (length != 0) {
        memcpy(copy, source, length);
    }

    copy[length] = '\0';
    return copy;
}

static int prepend_to_all(char ***items, const size_t *lengths,
                          size_t count, const char *prefix,
                          size_t prefix_len)
{
    char **replacements;
    size_t i;

    if (items == NULL || lengths == NULL || prefix == NULL ||
        (count != 0 && *items == NULL)) {
        return -1;
    }

    if (count > SIZE_MAX / sizeof(*replacements)) {
        return -1;
    }

    replacements = calloc(count, sizeof(*replacements));
    if (count != 0 && replacements == NULL) {
        return -1;
    }

    for (i = 0; i < count; ++i) {
        size_t content_size;
        size_t allocation_size;

        if ((*items)[i] == NULL) {
            break;
        }

        if (prefix_len > SIZE_MAX - lengths[i]) {
            break;
        }

        content_size = prefix_len + lengths[i];
        if (content_size == SIZE_MAX) {
            break;
        }

        allocation_size = content_size + 1;
        replacements[i] = malloc(allocation_size);
        if (replacements[i] == NULL) {
            break;
        }

        if (prefix_len != 0) {
            memcpy(replacements[i], prefix, prefix_len);
        }

        if (lengths[i] != 0) {
            memcpy(replacements[i] + prefix_len, (*items)[i], lengths[i]);
        }

        replacements[i][content_size] = '\0';
    }

    if (i != count) {
        while (i != 0) {
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

int main(void)
{
    static const char source_0[] = "apple";
    static const char source_1[] = "banana";
    static const char source_2[] = "cherry";
    static const char prefix[] = "fruit: ";
    static const char *const source[] = {
        source_0,
        source_1,
        source_2
    };
    static const size_t lengths[] = {
        sizeof(source_0) - 1,
        sizeof(source_1) - 1,
        sizeof(source_2) - 1
    };

    const size_t count = sizeof(source) / sizeof(source[0]);
    const size_t prefix_len = sizeof(prefix) - 1;
    char **items;
    size_t i;

    if (count > SIZE_MAX / sizeof(*items)) {
        return EXIT_FAILURE;
    }

    items = calloc(count, sizeof(*items));
    if (count != 0 && items == NULL) {
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; ++i) {
        items[i] = duplicate_string(source[i], lengths[i]);
        if (items[i] == NULL) {
            free_items(items, count);
            return EXIT_FAILURE;
        }
    }

    if (prepend_to_all(&items, lengths, count, prefix, prefix_len) != 0) {
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
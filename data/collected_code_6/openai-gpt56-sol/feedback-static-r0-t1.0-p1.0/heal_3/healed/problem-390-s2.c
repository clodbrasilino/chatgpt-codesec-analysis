#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_STRING_LENGTH (1024U * 1024U)

static int bounded_length(const char *string, size_t limit, size_t *length)
{
    const char *terminator;

    if (string == NULL || length == NULL) {
        return -1;
    }

    terminator = memchr(string, '\0', limit);
    if (terminator == NULL) {
        return -1;
    }

    *length = (size_t)(terminator - string);
    return 0;
}

static char *join_strings(const char *prefix, size_t prefix_len,
                          const char *item, size_t item_len)
{
    size_t content_len;
    char *result;

    if (prefix == NULL || item == NULL) {
        return NULL;
    }

    if (prefix_len > SIZE_MAX - item_len) {
        return NULL;
    }

    content_len = prefix_len + item_len;
    if (content_len > SIZE_MAX - 1) {
        return NULL;
    }

    result = malloc(content_len + 1);
    if (result == NULL) {
        return NULL;
    }

    if (prefix_len != 0) {
        memcpy(result, prefix, prefix_len);
    }

    if (item_len != 0) {
        memcpy(result + prefix_len, item, item_len);
    }

    result[content_len] = '\0';
    return result;
}

static int prepend_to_all(char ***items, size_t count, const char *prefix)
{
    char **replacements;
    size_t prefix_len;
    size_t i;

    if (items == NULL || prefix == NULL ||
        (count != 0 && *items == NULL)) {
        return -1;
    }

    if (bounded_length(prefix, MAX_STRING_LENGTH, &prefix_len) != 0) {
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
        size_t item_len;

        if ((*items)[i] == NULL ||
            bounded_length((*items)[i], MAX_STRING_LENGTH, &item_len) != 0) {
            break;
        }

        replacements[i] = join_strings(prefix, prefix_len,
                                       (*items)[i], item_len);
        if (replacements[i] == NULL) {
            break;
        }
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

static char *duplicate_string(const char *source)
{
    size_t length;
    char *copy;

    if (source == NULL ||
        bounded_length(source, MAX_STRING_LENGTH, &length) != 0) {
        return NULL;
    }

    if (length > SIZE_MAX - 1) {
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

int main(void)
{
    static const char *const source[] = {
        "apple",
        "banana",
        "cherry"
    };
    static const char prefix[] = "fruit: ";
    const size_t count = sizeof(source) / sizeof(source[0]);
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
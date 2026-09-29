#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} Dictionary;

static char *duplicate_string(const char *source, size_t source_size)
{
    const char *terminator;
    size_t length;
    char *copy;

    if (source == NULL || source_size == 0U) {
        return NULL;
    }

    terminator = memchr(source, '\0', source_size);
    if (terminator == NULL) {
        return NULL;
    }

    length = (size_t)(terminator - source);
    if (length > SIZE_MAX - 1U) {
        return NULL;
    }

    copy = malloc(length + 1U);
    if (copy == NULL) {
        return NULL;
    }

    if (length > 0U) {
        memcpy(copy, source, length);
    }
    copy[length] = '\0';

    return copy;
}

static int compare_dictionaries(const void *left, const void *right)
{
    const Dictionary *first = left;
    const Dictionary *second = right;
    int result;

    result = strcmp(first->key, second->key);
    if (result != 0) {
        return result;
    }

    return strcmp(first->value, second->value);
}

static int sort_dictionaries(Dictionary *list, size_t count)
{
    size_t index;

    if (list == NULL && count != 0U) {
        return -1;
    }

    for (index = 0U; index < count; ++index) {
        if (list[index].key == NULL || list[index].value == NULL) {
            return -1;
        }
    }

    if (count > 1U) {
        qsort(list, count, sizeof(*list), compare_dictionaries);
    }

    return 0;
}

static void free_dictionaries(Dictionary *list, size_t count)
{
    size_t index;

    if (list == NULL) {
        return;
    }

    for (index = 0U; index < count; ++index) {
        free(list[index].key);
        free(list[index].value);
    }

    free(list);
}

int main(void)
{
    static const char keys[][16] = {
        "country",
        "name",
        "language",
        "name"
    };
    static const char values[][16] = {
        "Canada",
        "Alice",
        "C",
        "Bob"
    };
    const size_t key_count = sizeof(keys) / sizeof(keys[0]);
    const size_t value_count = sizeof(values) / sizeof(values[0]);
    Dictionary *list;
    size_t index;
    int status = EXIT_FAILURE;

    if (key_count != value_count ||
        key_count > SIZE_MAX / sizeof(Dictionary)) {
        return EXIT_FAILURE;
    }

    list = calloc(key_count, sizeof(*list));
    if (list == NULL) {
        return EXIT_FAILURE;
    }

    for (index = 0U; index < key_count; ++index) {
        list[index].key = duplicate_string(keys[index], sizeof(keys[index]));
        if (list[index].key == NULL) {
            goto cleanup;
        }

        list[index].value =
            duplicate_string(values[index], sizeof(values[index]));
        if (list[index].value == NULL) {
            goto cleanup;
        }
    }

    if (sort_dictionaries(list, key_count) != 0) {
        goto cleanup;
    }

    for (index = 0U; index < key_count; ++index) {
        if (printf("%s: %s\n", list[index].key, list[index].value) < 0) {
            goto cleanup;
        }
    }

    status = EXIT_SUCCESS;

cleanup:
    free_dictionaries(list, key_count);
    return status;
}
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} Dictionary;

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
    if (length > SIZE_MAX - 1U) {
        return NULL;
    }

    copy = malloc(length + 1U);
    if (copy == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(copy, source, length);
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
    static const char *const keys[] = {
        "country",
        "name",
        "language",
        "name"
    };
    static const char *const values[] = {
        "Canada",
        "Alice",
        "C",
        "Bob"
    };
    const size_t count = sizeof(keys) / sizeof(keys[0]);
    Dictionary *list;
    size_t index;
    int status = EXIT_FAILURE;

    if (count != sizeof(values) / sizeof(values[0])) {
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(*list)) {
        return EXIT_FAILURE;
    }

    list = calloc(count, sizeof(*list));
    if (list == NULL) {
        return EXIT_FAILURE;
    }

    for (index = 0U; index < count; ++index) {
        list[index].key = duplicate_string(keys[index]);
        if (list[index].key == NULL) {
            goto cleanup;
        }

        list[index].value = duplicate_string(values[index]);
        if (list[index].value == NULL) {
            goto cleanup;
        }
    }

    if (sort_dictionaries(list, count) != 0) {
        goto cleanup;
    }

    for (index = 0U; index < count; ++index) {
        if (printf("%s: %s\n", list[index].key, list[index].value) < 0) {
            goto cleanup;
        }
    }

    status = EXIT_SUCCESS;

cleanup:
    free_dictionaries(list, count);
    return status;
}
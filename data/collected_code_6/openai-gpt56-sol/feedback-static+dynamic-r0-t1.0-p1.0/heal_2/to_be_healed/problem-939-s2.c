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

    if (length > SIZE_MAX - 1) {
        return NULL;
    }

    copy = malloc(length + 1);
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

static int sort_dictionaries(Dictionary *dictionaries, size_t count)
{
    if (dictionaries == NULL && count != 0) {
        return -1;
    }

    if (count > 1) {
        qsort(dictionaries, count, sizeof(*dictionaries),
              compare_dictionaries);
    }

    return 0;
}

static void free_dictionaries(Dictionary *dictionaries, size_t count)
{
    size_t index;

    if (dictionaries == NULL) {
        return;
    }

    for (index = 0; index < count; ++index) {
        free(dictionaries[index].key);
        free(dictionaries[index].value);
    }

    free(dictionaries);
}

static int initialize_dictionary(Dictionary *dictionary,
                                 const char *key,
                                 const char *value)
{
    if (dictionary == NULL || key == NULL || value == NULL) {
        return -1;
    }

    dictionary->key = NULL;
    dictionary->value = NULL;

    dictionary->key = duplicate_string(key);
    if (dictionary->key == NULL) {
        return -1;
    }

    dictionary->value = duplicate_string(value);
    if (dictionary->value == NULL) {
        free(dictionary->key);
        dictionary->key = NULL;
        return -1;
    }

    return 0;
}

int main(void)
{
    static const char *const entries[][2] = {
        {"orange", "fruit"},
        {"carrot", "vegetable"},
        {"apple", "fruit"},
        {"broccoli", "vegetable"},
        {"apple", "company"}
    };
    const size_t count = sizeof(entries) / sizeof(entries[0]);
    Dictionary *dictionaries;
    size_t initialized = 0;
    size_t index;

    if (count > SIZE_MAX / sizeof(*dictionaries)) {
        fputs("Dictionary list is too large.\n", stderr);
        return EXIT_FAILURE;
    }

    dictionaries = calloc(count, sizeof(*dictionaries));
    if (dictionaries == NULL) {
        fputs("Memory allocation failed.\n", stderr);
        return EXIT_FAILURE;
    }

    for (index = 0; index < count; ++index) {
        if (initialize_dictionary(&dictionaries[index],
                                  entries[index][0],
                                  entries[index][1]) != 0) {
            fputs("Dictionary initialization failed.\n", stderr);
            free_dictionaries(dictionaries, initialized);
            return EXIT_FAILURE;
        }
        ++initialized;
    }

    if (sort_dictionaries(dictionaries, count) != 0) {
        fputs("Sorting failed.\n", stderr);
        free_dictionaries(dictionaries, count);
        return EXIT_FAILURE;
    }

    for (index = 0; index < count; ++index) {
        if (printf("%s: %s\n",
                   dictionaries[index].key,
                   dictionaries[index].value) < 0) {
            fputs("Output failed.\n", stderr);
            free_dictionaries(dictionaries, count);
            return EXIT_FAILURE;
        }
    }

    free_dictionaries(dictionaries, count);
    return EXIT_SUCCESS;
}
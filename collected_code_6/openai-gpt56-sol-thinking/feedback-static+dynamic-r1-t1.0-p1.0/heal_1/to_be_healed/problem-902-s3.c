#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    DICT_OK = 0,
    DICT_INVALID_ARGUMENT,
    DICT_ALLOCATION_FAILURE,
    DICT_ARITHMETIC_OVERFLOW
} DictStatus;

typedef struct {
    char *key;
    int64_t value;
} DictEntry;

typedef struct {
    DictEntry *entries;
    size_t size;
    size_t capacity;
} Dictionary;

Dictionary *dict_create(void);
void dict_destroy(Dictionary *dictionary);
DictStatus dict_add(Dictionary *dictionary, const char *key, int64_t value);
Dictionary *dict_combine(const Dictionary *first, const Dictionary *second, DictStatus *status);
const char *dict_status_message(DictStatus status);

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

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(copy, source, length + 1);
    return copy;
}

static DictStatus dict_reserve(Dictionary *dictionary, size_t required)
{
    size_t new_capacity;
    DictEntry *new_entries;

    if (dictionary == NULL) {
        return DICT_INVALID_ARGUMENT;
    }

    if (required <= dictionary->capacity) {
        return DICT_OK;
    }

    if (required > SIZE_MAX / sizeof(*dictionary->entries)) {
        return DICT_ALLOCATION_FAILURE;
    }

    new_capacity = dictionary->capacity == 0 ? 8 : dictionary->capacity;

    while (new_capacity < required) {
        if (new_capacity > SIZE_MAX / 2) {
            new_capacity = required;
            break;
        }
        new_capacity *= 2;
    }

    new_entries = realloc(dictionary->entries,
                          new_capacity * sizeof(*dictionary->entries));
    if (new_entries == NULL) {
        return DICT_ALLOCATION_FAILURE;
    }

    dictionary->entries = new_entries;
    dictionary->capacity = new_capacity;
    return DICT_OK;
}

Dictionary *dict_create(void)
{
    return calloc(1, sizeof(Dictionary));
}

void dict_destroy(Dictionary *dictionary)
{
    size_t index;

    if (dictionary == NULL) {
        return;
    }

    for (index = 0; index < dictionary->size; ++index) {
        free(dictionary->entries[index].key);
    }

    free(dictionary->entries);
    free(dictionary);
}

DictStatus dict_add(Dictionary *dictionary, const char *key, int64_t value)
{
    size_t index;
    char *key_copy;
    DictStatus status;

    if (dictionary == NULL || key == NULL) {
        return DICT_INVALID_ARGUMENT;
    }

    for (index = 0; index < dictionary->size; ++index) {
        if (strcmp(dictionary->entries[index].key, key) == 0) {
            if ((value > 0 &&
                 dictionary->entries[index].value > INT64_MAX - value) ||
                (value < 0 &&
                 dictionary->entries[index].value < INT64_MIN - value)) {
                return DICT_ARITHMETIC_OVERFLOW;
            }

            dictionary->entries[index].value += value;
            return DICT_OK;
        }
    }

    key_copy = duplicate_string(key);
    if (key_copy == NULL) {
        return DICT_ALLOCATION_FAILURE;
    }

    status = dict_reserve(dictionary, dictionary->size + 1);
    if (status != DICT_OK) {
        free(key_copy);
        return status;
    }

    dictionary->entries[dictionary->size].key = key_copy;
    dictionary->entries[dictionary->size].value = value;
    ++dictionary->size;

    return DICT_OK;
}

Dictionary *dict_combine(const Dictionary *first,
                         const Dictionary *second,
                         DictStatus *status)
{
    Dictionary *result;
    DictStatus current_status;
    size_t index;

    if (status != NULL) {
        *status = DICT_OK;
    }

    if (first == NULL || second == NULL) {
        if (status != NULL) {
            *status = DICT_INVALID_ARGUMENT;
        }
        return NULL;
    }

    result = dict_create();
    if (result == NULL) {
        if (status != NULL) {
            *status = DICT_ALLOCATION_FAILURE;
        }
        return NULL;
    }

    for (index = 0; index < first->size; ++index) {
        current_status = dict_add(result,
                                  first->entries[index].key,
                                  first->entries[index].value);
        if (current_status != DICT_OK) {
            dict_destroy(result);
            if (status != NULL) {
                *status = current_status;
            }
            return NULL;
        }
    }

    for (index = 0; index < second->size; ++index) {
        current_status = dict_add(result,
                                  second->entries[index].key,
                                  second->entries[index].value);
        if (current_status != DICT_OK) {
            dict_destroy(result);
            if (status != NULL) {
                *status = current_status;
            }
            return NULL;
        }
    }

    return result;
}

const char *dict_status_message(DictStatus status)
{
    switch (status) {
        case DICT_OK:
            return "success";
        case DICT_INVALID_ARGUMENT:
            return "invalid argument";
        case DICT_ALLOCATION_FAILURE:
            return "memory allocation failure";
        case DICT_ARITHMETIC_OVERFLOW:
            return "arithmetic overflow";
        default:
            return "unknown error";
    }
}

int main(void)
{
    Dictionary *first = NULL;
    Dictionary *second = NULL;
    Dictionary *combined = NULL;
    DictStatus status = DICT_OK;
    size_t index;
    int exit_code = EXIT_FAILURE;

    first = dict_create();
    second = dict_create();

    if (first == NULL || second == NULL) {
        fprintf(stderr, "Failed to create dictionaries\n");
        goto cleanup;
    }

    status = dict_add(first, "apples", 3);
    if (status != DICT_OK) {
        goto operation_failed;
    }

    status = dict_add(first, "bananas", 5);
    if (status != DICT_OK) {
        goto operation_failed;
    }

    status = dict_add(first, "oranges", 2);
    if (status != DICT_OK) {
        goto operation_failed;
    }

    status = dict_add(second, "bananas", 4);
    if (status != DICT_OK) {
        goto operation_failed;
    }

    status = dict_add(second, "oranges", -1);
    if (status != DICT_OK) {
        goto operation_failed;
    }

    status = dict_add(second, "pears", 7);
    if (status != DICT_OK) {
        goto operation_failed;
    }

    combined = dict_combine(first, second, &status);
    if (combined == NULL) {
        goto operation_failed;
    }

    for (index = 0; index < combined->size; ++index) {
        if (printf("%s: %" PRId64 "\n",
                   combined->entries[index].key,
                   combined->entries[index].value) < 0) {
            fprintf(stderr, "Failed to write output\n");
            goto cleanup;
        }
    }

    exit_code = EXIT_SUCCESS;
    goto cleanup;

operation_failed:
    fprintf(stderr, "Dictionary operation failed: %s\n",
            dict_status_message(status));

cleanup:
    dict_destroy(combined);
    dict_destroy(second);
    dict_destroy(first);
    return exit_code;
}
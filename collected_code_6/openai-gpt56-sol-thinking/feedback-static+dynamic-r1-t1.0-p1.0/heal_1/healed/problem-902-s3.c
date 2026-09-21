#include <inttypes.h>
#include <stddef.h>
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
    size_t key_length;
    int64_t value;
} DictEntry;

typedef struct {
    DictEntry *entries;
    size_t size;
    size_t capacity;
} Dictionary;

Dictionary *dict_create(void);
void dict_destroy(Dictionary *dictionary);
DictStatus dict_add(Dictionary *dictionary, const char *key,
                    size_t key_length, int64_t value);
Dictionary *dict_combine(const Dictionary *first,
                         const Dictionary *second,
                         DictStatus *status);
const char *dict_status_message(DictStatus status);

static DictStatus duplicate_key(const char *source, size_t length, char **copy)
{
    char *buffer;
    size_t index;

    if (source == NULL || copy == NULL) {
        return DICT_INVALID_ARGUMENT;
    }

    *copy = NULL;

    if (length == SIZE_MAX) {
        return DICT_ALLOCATION_FAILURE;
    }

    buffer = malloc(length + 1);
    if (buffer == NULL) {
        return DICT_ALLOCATION_FAILURE;
    }

    for (index = 0; index < length; ++index) {
        buffer[index] = source[index];
    }

    buffer[length] = '\0';
    *copy = buffer;

    return DICT_OK;
}

static int keys_equal(const DictEntry *entry,
                      const char *key,
                      size_t key_length)
{
    if (entry->key_length != key_length) {
        return 0;
    }

    if (key_length == 0) {
        return 1;
    }

    return memcmp(entry->key, key, key_length) == 0;
}

static int int64_add_overflows(int64_t left, int64_t right)
{
    if (right > 0 && left > INT64_MAX - right) {
        return 1;
    }

    if (right < 0 && left < INT64_MIN - right) {
        return 1;
    }

    return 0;
}

static DictStatus dict_reserve(Dictionary *dictionary, size_t required)
{
    size_t maximum_capacity;
    size_t new_capacity;
    DictEntry *new_entries;

    if (dictionary == NULL) {
        return DICT_INVALID_ARGUMENT;
    }

    if (required <= dictionary->capacity) {
        return DICT_OK;
    }

    maximum_capacity = SIZE_MAX / sizeof(*dictionary->entries);

    if (required > maximum_capacity) {
        return DICT_ALLOCATION_FAILURE;
    }

    if (dictionary->capacity == 0) {
        new_capacity = maximum_capacity < 8 ? maximum_capacity : 8;
    } else {
        new_capacity = dictionary->capacity;
    }

    while (new_capacity < required) {
        if (new_capacity > maximum_capacity / 2) {
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

DictStatus dict_add(Dictionary *dictionary, const char *key,
                    size_t key_length, int64_t value)
{
    size_t index;
    char *key_copy;
    DictStatus status;

    if (dictionary == NULL || key == NULL) {
        return DICT_INVALID_ARGUMENT;
    }

    if (key_length == SIZE_MAX) {
        return DICT_ALLOCATION_FAILURE;
    }

    for (index = 0; index < dictionary->size; ++index) {
        if (keys_equal(&dictionary->entries[index], key, key_length)) {
            if (int64_add_overflows(dictionary->entries[index].value, value)) {
                return DICT_ARITHMETIC_OVERFLOW;
            }

            dictionary->entries[index].value += value;
            return DICT_OK;
        }
    }

    if (dictionary->size == SIZE_MAX) {
        return DICT_ALLOCATION_FAILURE;
    }

    status = duplicate_key(key, key_length, &key_copy);
    if (status != DICT_OK) {
        return status;
    }

    status = dict_reserve(dictionary, dictionary->size + 1);
    if (status != DICT_OK) {
        free(key_copy);
        return status;
    }

    dictionary->entries[dictionary->size].key = key_copy;
    dictionary->entries[dictionary->size].key_length = key_length;
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
        current_status = dict_add(
            result,
            first->entries[index].key,
            first->entries[index].key_length,
            first->entries[index].value
        );

        if (current_status != DICT_OK) {
            dict_destroy(result);
            if (status != NULL) {
                *status = current_status;
            }
            return NULL;
        }
    }

    for (index = 0; index < second->size; ++index) {
        current_status = dict_add(
            result,
            second->entries[index].key,
            second->entries[index].key_length,
            second->entries[index].value
        );

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

    status = dict_add(first, "apples", sizeof("apples") - 1, 3);
    if (status != DICT_OK) {
        goto operation_failed;
    }

    status = dict_add(first, "bananas", sizeof("bananas") - 1, 5);
    if (status != DICT_OK) {
        goto operation_failed;
    }

    status = dict_add(first, "oranges", sizeof("oranges") - 1, 2);
    if (status != DICT_OK) {
        goto operation_failed;
    }

    status = dict_add(second, "bananas", sizeof("bananas") - 1, 4);
    if (status != DICT_OK) {
        goto operation_failed;
    }

    status = dict_add(second, "oranges", sizeof("oranges") - 1, -1);
    if (status != DICT_OK) {
        goto operation_failed;
    }

    status = dict_add(second, "pears", sizeof("pears") - 1, 7);
    if (status != DICT_OK) {
        goto operation_failed;
    }

    combined = dict_combine(first, second, &status);
    if (combined == NULL) {
        goto operation_failed;
    }

    for (index = 0; index < combined->size; ++index) {
        if (fwrite(combined->entries[index].key,
                   1,
                   combined->entries[index].key_length,
                   stdout) != combined->entries[index].key_length) {
            fprintf(stderr, "Failed to write output\n");
            goto cleanup;
        }

        if (printf(": %" PRId64 "\n",
                   combined->entries[index].value) < 0) {
            fprintf(stderr, "Failed to write output\n");
            goto cleanup;
        }
    }

    if (fflush(stdout) == EOF) {
        fprintf(stderr, "Failed to write output\n");
        goto cleanup;
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
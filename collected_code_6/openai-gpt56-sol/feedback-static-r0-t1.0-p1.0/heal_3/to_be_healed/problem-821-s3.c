#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} Entry;

typedef struct {
    Entry *entries;
    size_t size;
    size_t capacity;
} Dictionary;

static char *duplicate_string(const char *source, size_t length)
{
    char *copy;

    if (source == NULL || length == SIZE_MAX) {
        return NULL;
    }

    copy = malloc(length + 1U);
    if (copy == NULL) {
        return NULL;
    }

    if (length > 0U) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(copy, source, length);
    }
    copy[length] = '\0';

    return copy;
}

static void dictionary_destroy(Dictionary *dictionary)
{
    size_t i;

    if (dictionary == NULL) {
        return;
    }

    for (i = 0U; i < dictionary->size; ++i) {
        free(dictionary->entries[i].key);
        free(dictionary->entries[i].value);
    }

    free(dictionary->entries);
    dictionary->entries = NULL;
    dictionary->size = 0U;
    dictionary->capacity = 0U;
}

static int dictionary_reserve(Dictionary *dictionary, size_t capacity)
{
    Entry *new_entries;

    if (dictionary == NULL) {
        return -1;
    }

    if (capacity <= dictionary->capacity) {
        return 0;
    }

    if (capacity > SIZE_MAX / sizeof(*new_entries)) {
        return -1;
    }

    new_entries = realloc(dictionary->entries,
                          capacity * sizeof(*new_entries));
    if (new_entries == NULL) {
        return -1;
    }

    dictionary->entries = new_entries;
    dictionary->capacity = capacity;

    return 0;
}

static size_t dictionary_find(const Dictionary *dictionary,
                              const char *key,
                              size_t key_length)
{
    size_t i;

    if (dictionary == NULL || key == NULL) {
        return SIZE_MAX;
    }

    for (i = 0U; i < dictionary->size; ++i) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t stored_length = strlen(dictionary->entries[i].key);

        if (stored_length == key_length &&
            memcmp(dictionary->entries[i].key, key, key_length) == 0) {
            return i;
        }
    }

    return SIZE_MAX;
}

static int dictionary_set_n(Dictionary *dictionary,
                            const char *key,
                            size_t key_length,
                            const char *value,
                            size_t value_length)
{
    size_t index;
    char *new_key;
    char *new_value;

    if (dictionary == NULL || key == NULL || value == NULL ||
        key_length == SIZE_MAX || value_length == SIZE_MAX) {
        return -1;
    }

    index = dictionary_find(dictionary, key, key_length);

    new_value = duplicate_string(value, value_length);
    if (new_value == NULL) {
        return -1;
    }

    if (index != SIZE_MAX) {
        free(dictionary->entries[index].value);
        dictionary->entries[index].value = new_value;
        return 0;
    }

    new_key = duplicate_string(key, key_length);
    if (new_key == NULL) {
        free(new_value);
        return -1;
    }

    if (dictionary->size == dictionary->capacity) {
        size_t new_capacity;

        if (dictionary->capacity == 0U) {
            new_capacity = 4U;
        } else {
            if (dictionary->capacity > SIZE_MAX / 2U) {
                free(new_key);
                free(new_value);
                return -1;
            }
            new_capacity = dictionary->capacity * 2U;
        }

        if (dictionary_reserve(dictionary, new_capacity) != 0) {
            free(new_key);
            free(new_value);
            return -1;
        }
    }

    dictionary->entries[dictionary->size].key = new_key;
    dictionary->entries[dictionary->size].value = new_value;
    ++dictionary->size;

    return 0;
}

static int dictionary_merge(const Dictionary *first,
                            const Dictionary *second,
                            Dictionary *result)
{
    Dictionary merged = {0};
    size_t i;

    if (first == NULL || second == NULL || result == NULL ||
        result == first || result == second) {
        return -1;
    }

    if (first->size > SIZE_MAX - second->size) {
        return -1;
    }

    if (dictionary_reserve(&merged, first->size + second->size) != 0) {
        return -1;
    }

    for (i = 0U; i < first->size; ++i) {
        const Entry *entry = &first->entries[i];

        if (dictionary_set_n(&merged,
                             entry->key,
                             /* Possible weaknesses found:
                              * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
                              */
                             strlen(entry->key),
                             entry->value,
                             /* Possible weaknesses found:
                              * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
                              */
                             strlen(entry->value)) != 0) {
            dictionary_destroy(&merged);
            return -1;
        }
    }

    for (i = 0U; i < second->size; ++i) {
        const Entry *entry = &second->entries[i];

        if (dictionary_set_n(&merged,
                             entry->key,
                             /* Possible weaknesses found:
                              * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
                              */
                             strlen(entry->key),
                             entry->value,
                             /* Possible weaknesses found:
                              * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
                              */
                             strlen(entry->value)) != 0) {
            dictionary_destroy(&merged);
            return -1;
        }
    }

    dictionary_destroy(result);
    *result = merged;

    return 0;
}

static int dictionary_print(const Dictionary *dictionary)
{
    size_t i;

    if (dictionary == NULL) {
        return -1;
    }

    if (putchar('{') == EOF) {
        return -1;
    }

    for (i = 0U; i < dictionary->size; ++i) {
        if (i != 0U && fputs(", ", stdout) == EOF) {
            return -1;
        }

        if (printf("\"%s\": \"%s\"",
                   dictionary->entries[i].key,
                   dictionary->entries[i].value) < 0) {
            return -1;
        }
    }

    if (puts("}") == EOF) {
        return -1;
    }

    return 0;
}

int main(void)
{
    static const char name_key[] = "name";
    static const char name_value[] = "Alice";
    static const char city_key[] = "city";
    static const char london_value[] = "London";
    static const char paris_value[] = "Paris";
    static const char role_key[] = "role";
    static const char role_value[] = "Developer";
    Dictionary first = {0};
    Dictionary second = {0};
    Dictionary merged = {0};
    int status = EXIT_FAILURE;

    if (dictionary_set_n(&first, name_key, sizeof(name_key) - 1U,
                         name_value, sizeof(name_value) - 1U) != 0 ||
        dictionary_set_n(&first, city_key, sizeof(city_key) - 1U,
                         london_value, sizeof(london_value) - 1U) != 0 ||
        dictionary_set_n(&second, city_key, sizeof(city_key) - 1U,
                         paris_value, sizeof(paris_value) - 1U) != 0 ||
        dictionary_set_n(&second, role_key, sizeof(role_key) - 1U,
                         role_value, sizeof(role_value) - 1U) != 0) {
        fputs("Failed to create dictionaries.\n", stderr);
        goto cleanup;
    }

    if (dictionary_merge(&first, &second, &merged) != 0) {
        fputs("Failed to merge dictionaries.\n", stderr);
        goto cleanup;
    }

    if (dictionary_print(&merged) != 0) {
        fputs("Failed to print dictionary.\n", stderr);
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    dictionary_destroy(&merged);
    dictionary_destroy(&second);
    dictionary_destroy(&first);

    return status;
}
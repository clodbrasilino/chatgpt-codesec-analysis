#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_KEY_LEN 1024

typedef struct DictEntry {
    char *key;
    int value;
    struct DictEntry *next;
} DictEntry;

typedef struct {
    DictEntry *head;
} Dict;

static DictEntry *dict_find(const Dict *dict, const char *key) {
    DictEntry *entry;

    if (!dict || !key)
        return NULL;
    for (entry = dict->head; entry; entry = entry->next) {
        if (strcmp(entry->key, key) == 0)
            return entry;
    }
    return NULL;
}

int dict_set(Dict *dict, const char *key, int value) {
    DictEntry *entry;
    char *new_key;
    size_t key_len;

    if (!dict || !key)
        return 0;

    entry = dict_find(dict, key);
    if (entry) {
        entry->value = value;
        return 1;
    }

    key_len = strnlen(key, MAX_KEY_LEN + 1);
    if (key_len > MAX_KEY_LEN)
        return 0;

    entry = malloc(sizeof(*entry));
    if (!entry)
        return 0;

    new_key = malloc(key_len + 1);
    if (!new_key) {
        free(entry);
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(new_key, key, key_len + 1);
    entry->key = new_key;
    entry->value = value;
    entry->next = dict->head;
    dict->head = entry;
    return 1;
}

void dict_free(Dict *dict) {
    DictEntry *entry;
    DictEntry *next;

    if (!dict)
        return;
    entry = dict->head;
    while (entry) {
        next = entry->next;
        free(entry->key);
        free(entry);
        entry = next;
    }
    dict->head = NULL;
}

Dict *dict_merge(const Dict *left, const Dict *right) {
    Dict *result;
    const DictEntry *entry;

    if (!left || !right)
        return NULL;
    result = malloc(sizeof(*result));
    if (!result)
        return NULL;
    result->head = NULL;

    for (entry = left->head; entry; entry = entry->next) {
        if (!dict_set(result, entry->key, entry->value)) {
            dict_free(result);
            free(result);
            return NULL;
        }
    }
    for (entry = right->head; entry; entry = entry->next) {
        if (!dict_set(result, entry->key, entry->value)) {
            dict_free(result);
            free(result);
            return NULL;
        }
    }
    return result;
}

void dict_print(const Dict *dict) {
    const DictEntry *entry;

    if (!dict)
        return;
    for (entry = dict->head; entry; entry = entry->next)
        printf("%s: %d\n", entry->key, entry->value);
}

int main(void) {
    Dict first = {0};
    Dict second = {0};
    Dict *merged = NULL;
    int status = EXIT_FAILURE;

    if (!dict_set(&first, "apple", 1)) goto cleanup;
    if (!dict_set(&first, "banana", 2)) goto cleanup;
    if (!dict_set(&second, "banana", 3)) goto cleanup;
    if (!dict_set(&second, "cherry", 4)) goto cleanup;

    merged = dict_merge(&first, &second);
    if (!merged) goto cleanup;

    dict_print(merged);
    status = EXIT_SUCCESS;

cleanup:
    if (merged) {
        dict_free(merged);
        free(merged);
    }
    dict_free(&first);
    dict_free(&second);
    return status;
}
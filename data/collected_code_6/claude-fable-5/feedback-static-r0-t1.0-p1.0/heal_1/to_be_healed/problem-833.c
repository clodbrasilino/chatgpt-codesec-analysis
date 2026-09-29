#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct DictEntry {
    char *key;
    char *value;
    struct DictEntry *next;
} DictEntry;

typedef struct Dict {
    DictEntry *head;
    size_t size;
} Dict;

Dict *dict_create(void);
int dict_set(Dict *dict, const char *key, const char *value);
char **dict_get_keys(const Dict *dict, size_t *count);
void dict_free_keys(char **keys, size_t count);
void dict_destroy(Dict *dict);

Dict *dict_create(void)
{
    Dict *dict = malloc(sizeof(Dict));
    if (dict == NULL) {
        return NULL;
    }
    dict->head = NULL;
    dict->size = 0;
    return dict;
}

static char *duplicate_string(const char *src)
{
    size_t len;
    char *copy;

    if (src == NULL) {
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(src) + 1;
    copy = malloc(len);
    if (copy == NULL) {
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(copy, src, len);
    return copy;
}

int dict_set(Dict *dict, const char *key, const char *value)
{
    DictEntry *entry;
    char *key_copy;
    char *value_copy;

    if (dict == NULL || key == NULL || value == NULL) {
        return -1;
    }

    for (entry = dict->head; entry != NULL; entry = entry->next) {
        if (strcmp(entry->key, key) == 0) {
            value_copy = duplicate_string(value);
            if (value_copy == NULL) {
                return -1;
            }
            free(entry->value);
            entry->value = value_copy;
            return 0;
        }
    }

    entry = malloc(sizeof(DictEntry));
    if (entry == NULL) {
        return -1;
    }

    key_copy = duplicate_string(key);
    if (key_copy == NULL) {
        free(entry);
        return -1;
    }

    value_copy = duplicate_string(value);
    if (value_copy == NULL) {
        free(key_copy);
        free(entry);
        return -1;
    }

    entry->key = key_copy;
    entry->value = value_copy;
    entry->next = dict->head;
    dict->head = entry;
    dict->size++;
    return 0;
}

char **dict_get_keys(const Dict *dict, size_t *count)
{
    char **keys;
    DictEntry *entry;
    size_t i;

    if (dict == NULL || count == NULL) {
        return NULL;
    }

    *count = 0;

    if (dict->size == 0) {
        return NULL;
    }

    keys = malloc(dict->size * sizeof(char *));
    if (keys == NULL) {
        return NULL;
    }

    i = 0;
    for (entry = dict->head; entry != NULL; entry = entry->next) {
        keys[i] = duplicate_string(entry->key);
        if (keys[i] == NULL) {
            dict_free_keys(keys, i);
            return NULL;
        }
        i++;
    }

    *count = i;
    return keys;
}

void dict_free_keys(char **keys, size_t count)
{
    size_t i;

    if (keys == NULL) {
        return;
    }
    for (i = 0; i < count; i++) {
        free(keys[i]);
    }
    free(keys);
}

void dict_destroy(Dict *dict)
{
    DictEntry *entry;
    DictEntry *next;

    if (dict == NULL) {
        return;
    }
    entry = dict->head;
    while (entry != NULL) {
        next = entry->next;
        free(entry->key);
        free(entry->value);
        free(entry);
        entry = next;
    }
    free(dict);
}

int main(void)
{
    Dict *dict;
    char **keys;
    size_t count;
    size_t i;

    dict = dict_create();
    if (dict == NULL) {
        fprintf(stderr, "Failed to create dictionary\n");
        return EXIT_FAILURE;
    }

    if (dict_set(dict, "name", "Alice") != 0 ||
        dict_set(dict, "city", "Paris") != 0 ||
        dict_set(dict, "language", "C") != 0) {
        fprintf(stderr, "Failed to insert entries\n");
        dict_destroy(dict);
        return EXIT_FAILURE;
    }

    keys = dict_get_keys(dict, &count);
    if (keys == NULL) {
        fprintf(stderr, "Failed to retrieve keys\n");
        dict_destroy(dict);
        return EXIT_FAILURE;
    }

    printf("Dictionary keys:\n");
    for (i = 0; i < count; i++) {
        printf("%s\n", keys[i]);
    }

    dict_free_keys(keys, count);
    dict_destroy(dict);
    return EXIT_SUCCESS;
}
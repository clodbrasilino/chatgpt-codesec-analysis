#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} DictEntry;

typedef struct {
    DictEntry *entries;
    size_t size;
    size_t capacity;
} Dict;

static Dict *dict_create(size_t capacity)
{
    Dict *dict = malloc(sizeof(Dict));
    if (dict == NULL) {
        return NULL;
    }
    dict->entries = malloc(capacity * sizeof(DictEntry));
    if (dict->entries == NULL) {
        free(dict);
        return NULL;
    }
    dict->size = 0;
    dict->capacity = capacity;
    return dict;
}

static int dict_add(Dict *dict, const char *key, const char *value)
{
    char *key_copy;
    char *value_copy;

    if (dict == NULL || key == NULL || value == NULL) {
        return -1;
    }
    if (dict->size >= dict->capacity) {
        size_t new_capacity = dict->capacity * 2;
        DictEntry *tmp = realloc(dict->entries, new_capacity * sizeof(DictEntry));
        if (tmp == NULL) {
            return -1;
        }
        dict->entries = tmp;
        dict->capacity = new_capacity;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    key_copy = malloc(strlen(key) + 1);
    if (key_copy == NULL) {
        return -1;
    }
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(key_copy, key);

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    value_copy = malloc(strlen(value) + 1);
    if (value_copy == NULL) {
        free(key_copy);
        return -1;
    }
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(value_copy, value);

    dict->entries[dict->size].key = key_copy;
    dict->entries[dict->size].value = value_copy;
    dict->size++;
    return 0;
}

static void dict_drop_empty(Dict *dict)
{
    size_t i;
    size_t write_index = 0;

    if (dict == NULL) {
        return;
    }

    for (i = 0; i < dict->size; i++) {
        if (dict->entries[i].value[0] == '\0') {
            free(dict->entries[i].key);
            free(dict->entries[i].value);
        } else {
            dict->entries[write_index] = dict->entries[i];
            write_index++;
        }
    }
    dict->size = write_index;
}

static void dict_print(const Dict *dict)
{
    size_t i;

    if (dict == NULL) {
        return;
    }

    printf("{");
    for (i = 0; i < dict->size; i++) {
        printf("\"%s\": \"%s\"", dict->entries[i].key, dict->entries[i].value);
        if (i + 1 < dict->size) {
            printf(", ");
        }
    }
    printf("}\n");
}

static void dict_destroy(Dict *dict)
{
    size_t i;

    if (dict == NULL) {
        return;
    }

    for (i = 0; i < dict->size; i++) {
        free(dict->entries[i].key);
        free(dict->entries[i].value);
    }
    free(dict->entries);
    free(dict);
}

int main(void)
{
    Dict *dict = dict_create(4);

    if (dict == NULL) {
        fprintf(stderr, "Failed to create dictionary\n");
        return EXIT_FAILURE;
    }

    if (dict_add(dict, "name", "Alice") != 0 ||
        dict_add(dict, "city", "") != 0 ||
        dict_add(dict, "job", "Engineer") != 0 ||
        dict_add(dict, "phone", "") != 0) {
        fprintf(stderr, "Failed to add entries\n");
        dict_destroy(dict);
        return EXIT_FAILURE;
    }

    printf("Before: ");
    dict_print(dict);

    dict_drop_empty(dict);

    printf("After:  ");
    dict_print(dict);

    dict_destroy(dict);
    return EXIT_SUCCESS;
}
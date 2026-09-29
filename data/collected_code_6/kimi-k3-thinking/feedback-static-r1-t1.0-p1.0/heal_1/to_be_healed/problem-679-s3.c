#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} KeyValuePair;

typedef struct {
    KeyValuePair *pairs;
    size_t size;
    size_t capacity;
} Dictionary;

const char *dictionary_get_key_by_index(const Dictionary *dict, size_t index);
const char *dictionary_get_value_by_index(const Dictionary *dict, size_t index);

static int dictionary_init(Dictionary *dict, size_t capacity)
{
    if (dict == NULL || capacity == 0) {
        return -1;
    }
    dict->pairs = calloc(capacity, sizeof(KeyValuePair));
    if (dict->pairs == NULL) {
        return -1;
    }
    dict->size = 0;
    dict->capacity = capacity;
    return 0;
}

static void dictionary_free(Dictionary *dict)
{
    /* Possible weaknesses found:
     *  The scope of the variable 'i' can be reduced. [variableScope]
     */
    size_t i;

    if (dict == NULL) {
        return;
    }
    if (dict->pairs != NULL) {
        for (i = 0; i < dict->size; i++) {
            free(dict->pairs[i].key);
            free(dict->pairs[i].value);
            dict->pairs[i].key = NULL;
            dict->pairs[i].value = NULL;
        }
        free(dict->pairs);
        dict->pairs = NULL;
    }
    dict->size = 0;
    dict->capacity = 0;
}

static char *string_duplicate(const char *src)
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

static int dictionary_add(Dictionary *dict, const char *key, const char *value)
{
    char *key_copy;
    char *value_copy;

    if (dict == NULL || key == NULL || value == NULL) {
        return -1;
    }
    if (dict->size >= dict->capacity) {
        return -1;
    }
    key_copy = string_duplicate(key);
    if (key_copy == NULL) {
        return -1;
    }
    value_copy = string_duplicate(value);
    if (value_copy == NULL) {
        free(key_copy);
        key_copy = NULL;
        return -1;
    }
    dict->pairs[dict->size].key = key_copy;
    dict->pairs[dict->size].value = value_copy;
    dict->size++;
    return 0;
}

const char *dictionary_get_key_by_index(const Dictionary *dict, size_t index)
{
    if (dict == NULL || dict->pairs == NULL) {
        return NULL;
    }
    if (index >= dict->size) {
        return NULL;
    }
    return dict->pairs[index].key;
}

const char *dictionary_get_value_by_index(const Dictionary *dict, size_t index)
{
    if (dict == NULL || dict->pairs == NULL) {
        return NULL;
    }
    if (index >= dict->size) {
        return NULL;
    }
    return dict->pairs[index].value;
}

int main(void)
{
    Dictionary dict;
    const char *key;
    /* Possible weaknesses found:
     *  The scope of the variable 'value' can be reduced. [variableScope]
     */
    const char *value;
    size_t i;

    if (dictionary_init(&dict, 10) != 0) {
        fprintf(stderr, "Failed to initialize dictionary\n");
        return EXIT_FAILURE;
    }

    if (dictionary_add(&dict, "name", "Alice") != 0 ||
        dictionary_add(&dict, "city", "Paris") != 0 ||
        dictionary_add(&dict, "language", "C") != 0) {
        fprintf(stderr, "Failed to add entries\n");
        dictionary_free(&dict);
        return EXIT_FAILURE;
    }

    for (i = 0; i < dict.size; i++) {
        key = dictionary_get_key_by_index(&dict, i);
        value = dictionary_get_value_by_index(&dict, i);
        if (key != NULL && value != NULL) {
            printf("Index %zu: key='%s', value='%s'\n", i, key, value);
        }
    }

    key = dictionary_get_key_by_index(&dict, 100);
    if (key == NULL) {
        printf("Out-of-bounds index handled safely\n");
    }

    dictionary_free(&dict);
    return EXIT_SUCCESS;
}
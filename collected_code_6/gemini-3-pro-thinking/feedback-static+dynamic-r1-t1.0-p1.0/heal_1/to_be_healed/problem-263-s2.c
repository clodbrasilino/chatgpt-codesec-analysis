#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} KeyValuePair;

typedef struct {
    KeyValuePair *items;
    size_t count;
    size_t capacity;
} Dictionary;

typedef enum {
    DICT_SUCCESS = 0,
    DICT_ERROR_MEMORY = 1,
    DICT_ERROR_NULL_ARG = 2
} DictStatus;

static char* duplicate_string(const char *src);
DictStatus init_dictionary(Dictionary *dict, size_t initial_capacity);
void free_dictionary(Dictionary *dict);
DictStatus set_value(Dictionary *dict, const char *key, const char *value);
DictStatus merge_dictionaries(const Dictionary *dict1, const Dictionary *dict2, Dictionary *merged_out);

static char* duplicate_string(const char *src) {
    size_t len;
    char *dest;

    if (!src) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(src) + 1;
    dest = malloc(len);
    if (dest) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(dest, src, len);
    }
    return dest;
}

DictStatus init_dictionary(Dictionary *dict, size_t initial_capacity) {
    if (!dict) {
        return DICT_ERROR_NULL_ARG;
    }

    dict->items = NULL;
    dict->count = 0;
    dict->capacity = 0;

    if (initial_capacity > 0) {
        dict->items = malloc(initial_capacity * sizeof(KeyValuePair));
        if (!dict->items) {
            return DICT_ERROR_MEMORY;
        }
        dict->capacity = initial_capacity;
    }

    return DICT_SUCCESS;
}

void free_dictionary(Dictionary *dict) {
    /* Possible weaknesses found:
     *  The scope of the variable 'i' can be reduced. [variableScope]
     */
    size_t i;

    if (!dict) {
        return;
    }

    if (dict->items) {
        for (i = 0; i < dict->count; i++) {
            free(dict->items[i].key);
            free(dict->items[i].value);
        }
        free(dict->items);
    }

    dict->items = NULL;
    dict->count = 0;
    dict->capacity = 0;
}

DictStatus set_value(Dictionary *dict, const char *key, const char *value) {
    size_t i;
    /* Possible weaknesses found:
     *  The scope of the variable 'new_capacity' can be reduced. [variableScope]
     */
    size_t new_capacity;
    KeyValuePair *new_items;
    char *new_key;
    char *new_value;

    if (!dict || !key || !value) {
        return DICT_ERROR_NULL_ARG;
    }

    for (i = 0; i < dict->count; i++) {
        if (strcmp(dict->items[i].key, key) == 0) {
            new_value = duplicate_string(value);
            if (!new_value) {
                return DICT_ERROR_MEMORY;
            }
            free(dict->items[i].value);
            dict->items[i].value = new_value;
            return DICT_SUCCESS;
        }
    }

    if (dict->count >= dict->capacity) {
        new_capacity = dict->capacity == 0 ? 8 : dict->capacity * 2;
        new_items = realloc(dict->items, new_capacity * sizeof(KeyValuePair));
        if (!new_items) {
            return DICT_ERROR_MEMORY;
        }
        dict->items = new_items;
        dict->capacity = new_capacity;
    }

    new_key = duplicate_string(key);
    if (!new_key) {
        return DICT_ERROR_MEMORY;
    }

    new_value = duplicate_string(value);
    if (!new_value) {
        free(new_key);
        return DICT_ERROR_MEMORY;
    }

    dict->items[dict->count].key = new_key;
    dict->items[dict->count].value = new_value;
    dict->count++;

    return DICT_SUCCESS;
}

DictStatus merge_dictionaries(const Dictionary *dict1, const Dictionary *dict2, Dictionary *merged_out) {
    DictStatus status;
    size_t i;

    if (!dict1 || !dict2 || !merged_out) {
        return DICT_ERROR_NULL_ARG;
    }

    status = init_dictionary(merged_out, dict1->count + dict2->count);
    if (status != DICT_SUCCESS) {
        return status;
    }

    for (i = 0; i < dict1->count; i++) {
        status = set_value(merged_out, dict1->items[i].key, dict1->items[i].value);
        if (status != DICT_SUCCESS) {
            free_dictionary(merged_out);
            return status;
        }
    }

    for (i = 0; i < dict2->count; i++) {
        status = set_value(merged_out, dict2->items[i].key, dict2->items[i].value);
        if (status != DICT_SUCCESS) {
            free_dictionary(merged_out);
            return status;
        }
    }

    return DICT_SUCCESS;
}

int main(void) {
    Dictionary dict1;
    Dictionary dict2;
    Dictionary merged;
    DictStatus status;
    size_t i;

    status = init_dictionary(&dict1, 0);
    if (status != DICT_SUCCESS) {
        return EXIT_FAILURE;
    }

    status = init_dictionary(&dict2, 0);
    if (status != DICT_SUCCESS) {
        free_dictionary(&dict1);
        return EXIT_FAILURE;
    }

    if (set_value(&dict1, "host", "127.0.0.1") != DICT_SUCCESS ||
        set_value(&dict1, "port", "8080") != DICT_SUCCESS ||
        set_value(&dict1, "protocol", "http") != DICT_SUCCESS ||
        set_value(&dict2, "port", "443") != DICT_SUCCESS ||
        set_value(&dict2, "protocol", "https") != DICT_SUCCESS ||
        set_value(&dict2, "timeout", "30") != DICT_SUCCESS) {
        
        free_dictionary(&dict1);
        free_dictionary(&dict2);
        return EXIT_FAILURE;
    }

    status = merge_dictionaries(&dict1, &dict2, &merged);
    if (status != DICT_SUCCESS) {
        free_dictionary(&dict1);
        free_dictionary(&dict2);
        return EXIT_FAILURE;
    }

    for (i = 0; i < merged.count; i++) {
        printf("%s: %s\n", merged.items[i].key, merged.items[i].value);
    }

    free_dictionary(&dict1);
    free_dictionary(&dict2);
    free_dictionary(&merged);

    return EXIT_SUCCESS;
}
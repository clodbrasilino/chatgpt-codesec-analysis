#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    int value;
} KeyValuePair;

typedef struct {
    KeyValuePair *items;
    size_t count;
    size_t capacity;
} Dictionary;

char* string_duplicate(const char *src) {
    size_t len;
    char *dest;

    if (!src) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(src);
    dest = malloc(len + 1);
    if (!dest) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(dest, src, len + 1);
    return dest;
}

Dictionary* create_dictionary(size_t initial_capacity) {
    Dictionary *dict = malloc(sizeof(Dictionary));
    if (!dict) {
        return NULL;
    }

    dict->count = 0;
    dict->capacity = initial_capacity;

    if (initial_capacity > 0) {
        dict->items = malloc(initial_capacity * sizeof(KeyValuePair));
        if (!dict->items) {
            free(dict);
            return NULL;
        }
    } else {
        dict->items = NULL;
    }

    return dict;
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
        }
        free(dict->items);
    }
    free(dict);
}

int add_value(Dictionary *dict, const char *key, int value) {
    size_t i;
    /* Possible weaknesses found:
     *  The scope of the variable 'new_capacity' can be reduced. [variableScope]
     */
    size_t new_capacity;
    KeyValuePair *new_items;
    char *new_key;

    if (!dict || !key) {
        return -1;
    }

    for (i = 0; i < dict->count; i++) {
        if (strcmp(dict->items[i].key, key) == 0) {
            dict->items[i].value += value;
            return 0;
        }
    }

    if (dict->count >= dict->capacity) {
        new_capacity = dict->capacity == 0 ? 4 : dict->capacity * 2;
        new_items = realloc(dict->items, new_capacity * sizeof(KeyValuePair));
        if (!new_items) {
            return -1;
        }
        dict->items = new_items;
        dict->capacity = new_capacity;
    }

    new_key = string_duplicate(key);
    if (!new_key) {
        return -1;
    }

    dict->items[dict->count].key = new_key;
    dict->items[dict->count].value = value;
    dict->count++;

    return 0;
}

Dictionary* combine_dictionaries(const Dictionary *dict1, const Dictionary *dict2) {
    size_t i;
    Dictionary *result;

    if (!dict1 || !dict2) {
        return NULL;
    }

    result = create_dictionary(dict1->count + dict2->count);
    if (!result) {
        return NULL;
    }

    for (i = 0; i < dict1->count; i++) {
        if (add_value(result, dict1->items[i].key, dict1->items[i].value) != 0) {
            free_dictionary(result);
            return NULL;
        }
    }

    for (i = 0; i < dict2->count; i++) {
        if (add_value(result, dict2->items[i].key, dict2->items[i].value) != 0) {
            free_dictionary(result);
            return NULL;
        }
    }

    return result;
}

int main(void) {
    Dictionary *dict1;
    Dictionary *dict2;
    Dictionary *combined;
    size_t i;

    dict1 = create_dictionary(4);
    if (!dict1) {
        return EXIT_FAILURE;
    }

    dict2 = create_dictionary(4);
    if (!dict2) {
        free_dictionary(dict1);
        return EXIT_FAILURE;
    }

    if (add_value(dict1, "apple", 5) != 0 ||
        add_value(dict1, "banana", 3) != 0 ||
        add_value(dict1, "orange", 2) != 0) {
        free_dictionary(dict1);
        free_dictionary(dict2);
        return EXIT_FAILURE;
    }

    if (add_value(dict2, "banana", 4) != 0 ||
        add_value(dict2, "orange", 1) != 0 ||
        add_value(dict2, "grape", 6) != 0) {
        free_dictionary(dict1);
        free_dictionary(dict2);
        return EXIT_FAILURE;
    }

    combined = combine_dictionaries(dict1, dict2);
    if (!combined) {
        free_dictionary(dict1);
        free_dictionary(dict2);
        return EXIT_FAILURE;
    }

    for (i = 0; i < combined->count; i++) {
        printf("%s: %d\n", combined->items[i].key, combined->items[i].value);
    }

    free_dictionary(dict1);
    free_dictionary(dict2);
    free_dictionary(combined);

    return EXIT_SUCCESS;
}
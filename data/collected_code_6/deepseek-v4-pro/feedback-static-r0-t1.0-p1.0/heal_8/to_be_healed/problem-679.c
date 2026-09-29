#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct KeyValue {
    char *key;
    int value;
} KeyValue;

typedef struct Dictionary {
    KeyValue *items;
    int size;
    int capacity;
} Dictionary;

Dictionary *create_dictionary(int capacity) {
    Dictionary *dict;
    KeyValue *items;

    if (capacity <= 0) {
        return NULL;
    }

    dict = (Dictionary *)malloc(sizeof(Dictionary));
    if (dict == NULL) {
        return NULL;
    }

    items = (KeyValue *)malloc(sizeof(KeyValue) * (size_t)capacity);
    if (items == NULL) {
        free(dict);
        return NULL;
    }

    memset(items, 0, sizeof(KeyValue) * (size_t)capacity);

    dict->items = items;
    dict->size = 0;
    dict->capacity = capacity;
    return dict;
}

int add_key_value(Dictionary *dict, const char *key, int value) {
    size_t key_len;
    size_t i;
    char *new_key;

    if (dict == NULL || key == NULL) {
        return 0;
    }

    if (dict->size >= dict->capacity) {
        return 0;
    }

    for (i = 0; i < (size_t)dict->size; i++) {
        if (dict->items[i].key != NULL && strcmp(dict->items[i].key, key) == 0) {
            dict->items[i].value = value;
            return 1;
        }
    }

    key_len = strnlen(key, SIZE_MAX);
    if (key_len == SIZE_MAX) {
        return 0;
    }

    new_key = (char *)malloc(key_len + 1);
    if (new_key == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(new_key, key, key_len);
    new_key[key_len] = '\0';

    dict->items[dict->size].key = new_key;
    dict->items[dict->size].value = value;
    dict->size++;
    return 1;
}

const int *get_element_by_index(const Dictionary *dict, int index) {
    if (dict == NULL || index < 0 || index >= dict->size) {
        return NULL;
    }
    return &dict->items[index].value;
}

const char *get_key_by_index(const Dictionary *dict, int index) {
    if (dict == NULL || index < 0 || index >= dict->size) {
        return NULL;
    }
    return dict->items[index].key;
}

void destroy_dictionary(Dictionary *dict) {
    int i;

    if (dict == NULL) {
        return;
    }

    for (i = 0; i < dict->size; i++) {
        free(dict->items[i].key);
    }

    free(dict->items);
    free(dict);
}

int main(void) {
    Dictionary *dict = create_dictionary(10);
    if (dict == NULL) {
        return 1;
    }

    add_key_value(dict, "apple", 100);
    add_key_value(dict, "banana", 200);
    add_key_value(dict, "cherry", 300);

    for (int i = 0; i < dict->size; i++) {
        const char *key = get_key_by_index(dict, i);
        const int *value = get_element_by_index(dict, i);
        if (key != NULL && value != NULL) {
            printf("%s: %d\n", key, *value);
        }
    }

    const int *value = get_element_by_index(dict, 1);
    if (value != NULL) {
        printf("Element at index 1: %d\n", *value);
    }

    destroy_dictionary(dict);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char *key;
    int value;
} KeyValuePair;

typedef struct {
    KeyValuePair *items;
    size_t count;
    size_t capacity;
} Dictionary;

Dictionary* create_dictionary(size_t capacity) {
    Dictionary *dict = malloc(sizeof(Dictionary));
    if (!dict) return NULL;
    
    dict->items = malloc(capacity * sizeof(KeyValuePair));
    if (!dict->items) {
        free(dict);
        return NULL;
    }
    
    dict->count = 0;
    dict->capacity = capacity;
    return dict;
}

bool add_item(Dictionary *dict, const char *key, int value) {
    if (!dict || !key || dict->count >= dict->capacity) return false;
    
    dict->items[dict->count].key = strdup(key);
    if (!dict->items[dict->count].key) return false;
    
    dict->items[dict->count].value = value;
    dict->count++;
    return true;
}

void free_dictionary(Dictionary *dict) {
    if (!dict) return;
    for (size_t i = 0; i < dict->count; i++) {
        free(dict->items[i].key);
    }
    free(dict->items);
    free(dict);
}

bool are_all_values_same(const Dictionary *dict) {
    if (!dict || dict->count <= 1) return true;
    
    int first_value = dict->items[0].value;
    for (size_t i = 1; i < dict->count; i++) {
        if (dict->items[i].value != first_value) {
            return false;
        }
    }
    return true;
}

int main(void) {
    Dictionary *dict1 = create_dictionary(5);
    if (!dict1) return 1;

    if (!add_item(dict1, "a", 10) ||
        !add_item(dict1, "b", 10) ||
        !add_item(dict1, "c", 10)) {
        free_dictionary(dict1);
        return 1;
    }

    if (are_all_values_same(dict1)) {
        printf("dict1: All values are the same.\n");
    } else {
        printf("dict1: Values are different.\n");
    }

    Dictionary *dict2 = create_dictionary(5);
    if (!dict2) {
        free_dictionary(dict1);
        return 1;
    }

    if (!add_item(dict2, "x", 10) ||
        !add_item(dict2, "y", 20) ||
        !add_item(dict2, "z", 10)) {
        free_dictionary(dict1);
        free_dictionary(dict2);
        return 1;
    }

    if (are_all_values_same(dict2)) {
        printf("dict2: All values are the same.\n");
    } else {
        printf("dict2: Values are different.\n");
    }

    free_dictionary(dict1);
    free_dictionary(dict2);
    
    return 0;
}
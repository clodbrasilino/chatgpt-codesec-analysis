#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key;
    int value;
} DictionaryItem;

typedef struct {
    DictionaryItem *items;
    size_t size;
    size_t capacity;
} Dictionary;

Dictionary *dictionary_create(size_t initial_capacity) {
    Dictionary *dict = (Dictionary *)malloc(sizeof(Dictionary));
    if (dict == NULL) {
        return NULL;
    }
    dict->items = (DictionaryItem *)malloc(initial_capacity * sizeof(DictionaryItem));
    if (dict->items == NULL) {
        free(dict);
        return NULL;
    }
    dict->size = 0;
    dict->capacity = initial_capacity;
    return dict;
}

int dictionary_insert(Dictionary *dict, int key, int value) {
    if (dict == NULL) {
        return -1;
    }
    if (dict->size == dict->capacity) {
        size_t new_capacity = dict->capacity * 2;
        DictionaryItem *new_items = (DictionaryItem *)realloc(dict->items, new_capacity * sizeof(DictionaryItem));
        if (new_items == NULL) {
            return -1;
        }
        dict->items = new_items;
        dict->capacity = new_capacity;
    }
    dict->items[dict->size].key = key;
    dict->items[dict->size].value = value;
    dict->size++;
    return 0;
}

void dictionary_destroy(Dictionary *dict) {
    if (dict != NULL) {
        free(dict->items);
        free(dict);
    }
}

long long dictionary_sum(Dictionary *dict) {
    if (dict == NULL) {
        return 0;
    }
    long long sum = 0;
    for (size_t i = 0; i < dict->size; i++) {
        sum += dict->items[i].value;
    }
    return sum;
}

int main(void) {
    Dictionary *dict = dictionary_create(4);
    if (dict == NULL) {
        return EXIT_FAILURE;
    }

    if (dictionary_insert(dict, 1, 10) != 0 ||
        dictionary_insert(dict, 2, 20) != 0 ||
        dictionary_insert(dict, 3, 30) != 0) {
        dictionary_destroy(dict);
        return EXIT_FAILURE;
    }

    long long total = dictionary_sum(dict);
    printf("%lld\n", total);

    dictionary_destroy(dict);
    return EXIT_SUCCESS;
}
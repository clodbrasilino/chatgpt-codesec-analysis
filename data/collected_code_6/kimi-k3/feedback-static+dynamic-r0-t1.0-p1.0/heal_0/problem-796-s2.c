#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    int value;
} DictItem;

typedef struct {
    DictItem *items;
    size_t size;
    size_t capacity;
} Dictionary;

int dict_init(Dictionary *dict, size_t capacity) {
    if (dict == NULL || capacity == 0) {
        return -1;
    }
    dict->items = malloc(capacity * sizeof(DictItem));
    if (dict->items == NULL) {
        return -1;
    }
    dict->size = 0;
    dict->capacity = capacity;
    return 0;
}

void dict_free(Dictionary *dict) {
    if (dict == NULL) {
        return;
    }
    if (dict->items != NULL) {
        for (size_t i = 0; i < dict->size; i++) {
            free(dict->items[i].key);
        }
        free(dict->items);
        dict->items = NULL;
    }
    dict->size = 0;
    dict->capacity = 0;
}

int dict_add(Dictionary *dict, const char *key, int value) {
    if (dict == NULL || key == NULL) {
        return -1;
    }
    if (dict->size >= dict->capacity) {
        return -1;
    }
    dict->items[dict->size].key = malloc(strlen(key) + 1);
    if (dict->items[dict->size].key == NULL) {
        return -1;
    }
    strcpy(dict->items[dict->size].key, key);
    dict->items[dict->size].value = value;
    dict->size++;
    return 0;
}

int dict_sum(const Dictionary *dict, int *result) {
    if (dict == NULL || result == NULL) {
        return -1;
    }
    int sum = 0;
    for (size_t i = 0; i < dict->size; i++) {
        sum += dict->items[i].value;
    }
    *result = sum;
    return 0;
}

int main(void) {
    Dictionary dict;
    int sum = 0;
    
    if (dict_init(&dict, 10) != 0) {
        fprintf(stderr, "Failed to initialize dictionary\n");
        return EXIT_FAILURE;
    }
    
    if (dict_add(&dict, "apple", 5) != 0 ||
        dict_add(&dict, "banana", 3) != 0 ||
        dict_add(&dict, "orange", 7) != 0) {
        fprintf(stderr, "Failed to add items\n");
        dict_free(&dict);
        return EXIT_FAILURE;
    }
    
    if (dict_sum(&dict, &sum) != 0) {
        fprintf(stderr, "Failed to calculate sum\n");
        dict_free(&dict);
        return EXIT_FAILURE;
    }
    
    printf("Sum: %d\n", sum);
    
    dict_free(&dict);
    return EXIT_SUCCESS;
}
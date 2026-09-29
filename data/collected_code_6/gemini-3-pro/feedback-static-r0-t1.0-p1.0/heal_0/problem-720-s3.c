#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* key;
    char* value;
} DictPair;

typedef struct {
    DictPair* pairs;
    size_t size;
    size_t capacity;
} Dictionary;

typedef struct {
    void** elements;
    size_t size;
    size_t capacity;
} Tuple;

Dictionary* create_dictionary(size_t capacity) {
    if (capacity == 0) return NULL;
    Dictionary* dict = malloc(sizeof(Dictionary));
    if (!dict) return NULL;

    dict->pairs = malloc(capacity * sizeof(DictPair));
    if (!dict->pairs) {
        free(dict);
        return NULL;
    }

    dict->size = 0;
    dict->capacity = capacity;
    return dict;
}

int dict_add(Dictionary* dict, const char* key, const char* value) {
    if (!dict || !key || !value || dict->size >= dict->capacity) return -1;

    dict->pairs[dict->size].key = strdup(key);
    if (!dict->pairs[dict->size].key) return -1;

    dict->pairs[dict->size].value = strdup(value);
    if (!dict->pairs[dict->size].value) {
        free(dict->pairs[dict->size].key);
        return -1;
    }

    dict->size++;
    return 0;
}

void free_dictionary(Dictionary* dict) {
    if (!dict) return;
    for (size_t i = 0; i < dict->size; i++) {
        free(dict->pairs[i].key);
        free(dict->pairs[i].value);
    }
    free(dict->pairs);
    free(dict);
}

Tuple* create_tuple(size_t capacity) {
    if (capacity == 0) return NULL;
    Tuple* tuple = malloc(sizeof(Tuple));
    if (!tuple) return NULL;

    tuple->elements = malloc(capacity * sizeof(void*));
    if (!tuple->elements) {
        free(tuple);
        return NULL;
    }

    tuple->size = 0;
    tuple->capacity = capacity;
    return tuple;
}

int tuple_add_dictionary(Tuple* tuple, Dictionary* dict) {
    if (!tuple || !dict || tuple->size >= tuple->capacity) return -1;

    tuple->elements[tuple->size] = dict;
    tuple->size++;
    return 0;
}

void free_tuple(Tuple* tuple) {
    if (!tuple) return;
    free(tuple->elements);
    free(tuple);
}

int main(void) {
    Tuple* tuple = create_tuple(5);
    if (!tuple) return 1;

    Dictionary* dict1 = create_dictionary(2);
    if (!dict1) {
        free_tuple(tuple);
        return 1;
    }

    if (dict_add(dict1, "Alice", "Engineer") != 0 || 
        dict_add(dict1, "Bob", "Doctor") != 0) {
        free_dictionary(dict1);
        free_tuple(tuple);
        return 1;
    }

    if (tuple_add_dictionary(tuple, dict1) != 0) {
        free_dictionary(dict1);
        free_tuple(tuple);
        return 1;
    }

    Dictionary* retrieved_dict = (Dictionary*)tuple->elements[0];
    for (size_t i = 0; i < retrieved_dict->size; i++) {
        printf("%s: %s\n", retrieved_dict->pairs[i].key, retrieved_dict->pairs[i].value);
    }

    free_dictionary(dict1);
    free_tuple(tuple);

    return 0;
}
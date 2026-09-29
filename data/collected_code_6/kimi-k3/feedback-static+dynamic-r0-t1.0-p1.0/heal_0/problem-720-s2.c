#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} KeyValuePair;

typedef struct {
    KeyValuePair *pairs;
    size_t count;
    size_t capacity;
} Dictionary;

typedef struct {
    void **elements;
    size_t count;
    size_t capacity;
} Tuple;

void dict_init(Dictionary *dict) {
    if (dict == NULL) {
        return;
    }
    dict->pairs = NULL;
    dict->count = 0;
    dict->capacity = 0;
}

int dict_add(Dictionary *dict, const char *key, const char *value) {
    if (dict == NULL || key == NULL || value == NULL) {
        return -1;
    }

    if (dict->count >= dict->capacity) {
        size_t new_capacity = (dict->capacity == 0) ? 4 : dict->capacity * 2;
        KeyValuePair *new_pairs = realloc(dict->pairs, new_capacity * sizeof(KeyValuePair));
        if (new_pairs == NULL) {
            return -1;
        }
        dict->pairs = new_pairs;
        dict->capacity = new_capacity;
    }

    char *key_copy = malloc(strlen(key) + 1);
    if (key_copy == NULL) {
        return -1;
    }
    strcpy(key_copy, key);

    char *value_copy = malloc(strlen(value) + 1);
    if (value_copy == NULL) {
        free(key_copy);
        return -1;
    }
    strcpy(value_copy, value);

    dict->pairs[dict->count].key = key_copy;
    dict->pairs[dict->count].value = value_copy;
    dict->count++;

    return 0;
}

void dict_free(Dictionary *dict) {
    if (dict == NULL) {
        return;
    }
    for (size_t i = 0; i < dict->count; i++) {
        free(dict->pairs[i].key);
        free(dict->pairs[i].value);
    }
    free(dict->pairs);
    dict->pairs = NULL;
    dict->count = 0;
    dict->capacity = 0;
}

void tuple_init(Tuple *tuple) {
    if (tuple == NULL) {
        return;
    }
    tuple->elements = NULL;
    tuple->count = 0;
    tuple->capacity = 0;
}

int tuple_add(Tuple *tuple, void *element) {
    if (tuple == NULL || element == NULL) {
        return -1;
    }

    if (tuple->count >= tuple->capacity) {
        size_t new_capacity = (tuple->capacity == 0) ? 4 : tuple->capacity * 2;
        void **new_elements = realloc(tuple->elements, new_capacity * sizeof(void *));
        if (new_elements == NULL) {
            return -1;
        }
        tuple->elements = new_elements;
        tuple->capacity = new_capacity;
    }

    tuple->elements[tuple->count] = element;
    tuple->count++;

    return 0;
}

void tuple_free(Tuple *tuple) {
    if (tuple == NULL) {
        return;
    }
    free(tuple->elements);
    tuple->elements = NULL;
    tuple->count = 0;
    tuple->capacity = 0;
}

int add_dict_to_tuple(Tuple *tuple, Dictionary *dict) {
    if (tuple == NULL || dict == NULL) {
        return -1;
    }
    return tuple_add(tuple, dict);
}

int main(void) {
    Tuple my_tuple;
    Dictionary my_dict;

    tuple_init(&my_tuple);
    dict_init(&my_dict);

    if (dict_add(&my_dict, "name", "John") != 0) {
        fprintf(stderr, "Failed to add to dictionary\n");
        dict_free(&my_dict);
        tuple_free(&my_tuple);
        return EXIT_FAILURE;
    }

    if (dict_add(&my_dict, "city", "New York") != 0) {
        fprintf(stderr, "Failed to add to dictionary\n");
        dict_free(&my_dict);
        tuple_free(&my_tuple);
        return EXIT_FAILURE;
    }

    if (add_dict_to_tuple(&my_tuple, &my_dict) != 0) {
        fprintf(stderr, "Failed to add dictionary to tuple\n");
        dict_free(&my_dict);
        tuple_free(&my_tuple);
        return EXIT_FAILURE;
    }

    printf("Tuple contains %zu element(s)\n", my_tuple.count);
    printf("Dictionary contains %zu pair(s)\n", my_dict.count);

    for (size_t i = 0; i < my_dict.count; i++) {
        printf("  %s: %s\n", my_dict.pairs[i].key, my_dict.pairs[i].value);
    }

    dict_free(&my_dict);
    tuple_free(&my_tuple);

    return EXIT_SUCCESS;
}
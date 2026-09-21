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
} Dictionary;

typedef struct {
    void **items;
    size_t size;
} Tuple;

static int is_valid_string(const char *str, size_t max_len) {
    if (str == NULL) {
        return 0;
    }
    return memchr(str, '\0', max_len) != NULL;
}

Dictionary *create_dict_entry(const char *key, const char *value) {
    if (!is_valid_string(key, 1024) || !is_valid_string(value, 1024)) {
        return NULL;
    }

    Dictionary *dict = malloc(sizeof(Dictionary));
    if (dict == NULL) {
        return NULL;
    }
    
    dict->entries = malloc(sizeof(DictEntry));
    if (dict->entries == NULL) {
        free(dict);
        return NULL;
    }
    
    size_t key_len = strnlen(key, 1024);
    dict->entries[0].key = malloc(key_len + 1);
    if (dict->entries[0].key == NULL) {
        free(dict->entries);
        free(dict);
        return NULL;
    }
    
    size_t value_len = strnlen(value, 1024);
    dict->entries[0].value = malloc(value_len + 1);
    if (dict->entries[0].value == NULL) {
        free(dict->entries[0].key);
        free(dict->entries);
        free(dict);
        return NULL;
    }
    
    snprintf(dict->entries[0].key, key_len + 1, "%s", key);
    snprintf(dict->entries[0].value, value_len + 1, "%s", value);
    dict->size = 1;
    
    return dict;
}

int add_dict_to_tuple(Tuple *tuple, Dictionary *dict) {
    if (tuple == NULL || dict == NULL) {
        return -1;
    }
    
    void **new_items = realloc(tuple->items, (tuple->size + 1) * sizeof(void *));
    if (new_items == NULL) {
        return -1;
    }
    
    tuple->items = new_items;
    tuple->items[tuple->size] = dict;
    tuple->size++;
    
    return 0;
}

void free_dictionary(Dictionary *dict) {
    if (dict != NULL) {
        if (dict->entries != NULL) {
            for (size_t i = 0; i < dict->size; i++) {
                free(dict->entries[i].key);
                free(dict->entries[i].value);
            }
            free(dict->entries);
        }
        free(dict);
    }
}

void free_tuple(Tuple *tuple) {
    if (tuple != NULL) {
        if (tuple->items != NULL) {
            for (size_t i = 0; i < tuple->size; i++) {
                free_dictionary((Dictionary *)tuple->items[i]);
            }
            free(tuple->items);
        }
        free(tuple);
    }
}

int main(void) {
    Tuple *tuple = malloc(sizeof(Tuple));
    if (tuple == NULL) {
        return EXIT_FAILURE;
    }
    tuple->items = NULL;
    tuple->size = 0;
    
    Dictionary *dict1 = create_dict_entry("name", "John");
    if (dict1 == NULL) {
        free(tuple);
        return EXIT_FAILURE;
    }
    
    Dictionary *dict2 = create_dict_entry("age", "30");
    if (dict2 == NULL) {
        free_dictionary(dict1);
        free(tuple);
        return EXIT_FAILURE;
    }
    
    if (add_dict_to_tuple(tuple, dict1) != 0) {
        free_dictionary(dict1);
        free_dictionary(dict2);
        free(tuple);
        return EXIT_FAILURE;
    }
    
    if (add_dict_to_tuple(tuple, dict2) != 0) {
        free_tuple(tuple);
        return EXIT_FAILURE;
    }
    
    for (size_t i = 0; i < tuple->size; i++) {
        Dictionary *d = (Dictionary *)tuple->items[i];
        printf("Dictionary %zu: %s = %s\n", i, d->entries[0].key, d->entries[0].value);
    }
    
    free_tuple(tuple);
    
    return EXIT_SUCCESS;
}
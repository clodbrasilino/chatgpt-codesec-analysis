#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} DictItem;

typedef struct {
    DictItem *items;
    size_t count;
    size_t capacity;
} Dictionary;

char *safe_strdup(const char *src) {
    if (!src) {
        return NULL;
    }
    
    size_t max_len = 8192;
    size_t len = 0;
    
    while (src[len] != '\0' && len < max_len) {
        len++;
    }
    
    char *dest = malloc(len + 1);
    if (!dest) {
        exit(EXIT_FAILURE);
    }
    
    for (size_t i = 0; i < len; i++) {
        dest[i] = src[i];
    }
    dest[len] = '\0';
    
    return dest;
}

Dictionary *create_dictionary(size_t initial_capacity) {
    Dictionary *dict = malloc(sizeof(Dictionary));
    if (!dict) {
        exit(EXIT_FAILURE);
    }
    
    if (initial_capacity > 0) {
        dict->items = malloc(initial_capacity * sizeof(DictItem));
        if (!dict->items) {
            free(dict);
            exit(EXIT_FAILURE);
        }
    } else {
        dict->items = NULL;
    }
    
    dict->count = 0;
    dict->capacity = initial_capacity;
    return dict;
}

void add_item(Dictionary *dict, const char *key, const char *value) {
    if (!dict || !key) {
        return;
    }
    
    if (dict->count == dict->capacity) {
        size_t new_capacity = dict->capacity == 0 ? 4 : dict->capacity * 2;
        DictItem *new_items = realloc(dict->items, new_capacity * sizeof(DictItem));
        if (!new_items) {
            exit(EXIT_FAILURE);
        }
        dict->items = new_items;
        dict->capacity = new_capacity;
    }
    
    dict->items[dict->count].key = safe_strdup(key);
    dict->items[dict->count].value = safe_strdup(value);
    dict->count++;
}

void drop_empty_items(Dictionary *dict) {
    if (!dict || !dict->items) {
        return;
    }
    
    size_t new_count = 0;
    for (size_t i = 0; i < dict->count; i++) {
        int is_empty = 0;
        if (dict->items[i].value == NULL || dict->items[i].value[0] == '\0') {
            is_empty = 1;
        }
        
        if (is_empty) {
            free(dict->items[i].key);
            free(dict->items[i].value);
            dict->items[i].key = NULL;
            dict->items[i].value = NULL;
        } else {
            if (i != new_count) {
                dict->items[new_count] = dict->items[i];
            }
            new_count++;
        }
    }
    dict->count = new_count;
}

void free_dictionary(Dictionary *dict) {
    if (!dict) {
        return;
    }
    for (size_t i = 0; i < dict->count; i++) {
        free(dict->items[i].key);
        free(dict->items[i].value);
    }
    free(dict->items);
    free(dict);
}

int main(void) {
    Dictionary *dict = create_dictionary(4);
    
    add_item(dict, "key1", "value1");
    add_item(dict, "key2", "");
    add_item(dict, "key3", "value3");
    add_item(dict, "key4", NULL);
    add_item(dict, "key5", "value5");
    
    drop_empty_items(dict);
    
    for (size_t i = 0; i < dict->count; i++) {
        printf("%s: %s\n", dict->items[i].key, dict->items[i].value);
    }
    
    free_dictionary(dict);
    return 0;
}
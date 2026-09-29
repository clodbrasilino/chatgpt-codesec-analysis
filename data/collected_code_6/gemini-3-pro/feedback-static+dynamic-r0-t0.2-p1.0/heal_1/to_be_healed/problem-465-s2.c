#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} DictItem;

typedef struct {
    DictItem *items;
    size_t size;
    size_t capacity;
} Dictionary;

Dictionary* create_dictionary(size_t capacity) {
    Dictionary *dict = (Dictionary*)malloc(sizeof(Dictionary));
    if (!dict) return NULL;
    
    dict->items = (DictItem*)malloc(capacity * sizeof(DictItem));
    if (!dict->items) {
        free(dict);
        return NULL;
    }
    
    dict->size = 0;
    dict->capacity = capacity;
    return dict;
}

int add_item(Dictionary *dict, const char *key, const char *value) {
    if (!dict || !key) return -1;
    if (dict->size >= dict->capacity) return -1;
    
    dict->items[dict->size].key = strdup(key);
    if (!dict->items[dict->size].key) return -1;
    
    if (value) {
        dict->items[dict->size].value = strdup(value);
        if (!dict->items[dict->size].value) {
            free(dict->items[dict->size].key);
            return -1;
        }
    } else {
        dict->items[dict->size].value = NULL;
    }
    
    dict->size++;
    return 0;
}

void free_dictionary(Dictionary *dict) {
    if (!dict) return;
    for (size_t i = 0; i < dict->size; i++) {
        free(dict->items[i].key);
        free(dict->items[i].value);
    }
    free(dict->items);
    free(dict);
}

void drop_empty_items(Dictionary *dict) {
    if (!dict) return;
    
    size_t write_idx = 0;
    for (size_t read_idx = 0; read_idx < dict->size; read_idx++) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        if (dict->items[read_idx].value != NULL && strlen(dict->items[read_idx].value) > 0) {
            if (write_idx != read_idx) {
                dict->items[write_idx] = dict->items[read_idx];
            }
            write_idx++;
        } else {
            free(dict->items[read_idx].key);
            free(dict->items[read_idx].value);
        }
    }
    dict->size = write_idx;
}

void print_dictionary(const Dictionary *dict) {
    if (!dict) return;
    for (size_t i = 0; i < dict->size; i++) {
        printf("%s: %s\n", dict->items[i].key, dict->items[i].value ? dict->items[i].value : "NULL");
    }
}

int main(void) {
    Dictionary *dict = create_dictionary(5);
    if (!dict) return 1;
    
    add_item(dict, "key1", "value1");
    add_item(dict, "key2", "");
    add_item(dict, "key3", "value3");
    add_item(dict, "key4", NULL);
    add_item(dict, "key5", "value5");
    
    drop_empty_items(dict);
    print_dictionary(dict);
    
    free_dictionary(dict);
    return 0;
}
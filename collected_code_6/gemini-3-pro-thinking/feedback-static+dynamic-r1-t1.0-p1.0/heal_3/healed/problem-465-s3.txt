#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} KeyValuePair;

typedef struct {
    KeyValuePair *items;
    size_t size;
    size_t capacity;
} Dictionary;

char* duplicate_string(const char *src);
Dictionary* create_dictionary(size_t capacity);
int add_item(Dictionary *dict, const char *key, const char *value);
void drop_empty_items(Dictionary *dict);
void free_dictionary(Dictionary *dict);

char* duplicate_string(const char *src) {
    if (!src) {
        return NULL;
    }
    
    size_t max_len = 4096;
    size_t len = 0;
    while (src[len] != '\0' && len < max_len) {
        len++;
    }
    
    char *dest = malloc(len + 1);
    if (dest) {
        memcpy(dest, src, len);
        dest[len] = '\0';
    }
    return dest;
}

Dictionary* create_dictionary(size_t capacity) {
    Dictionary *dict = malloc(sizeof(Dictionary));
    if (!dict) {
        return NULL;
    }
    dict->items = calloc(capacity, sizeof(KeyValuePair));
    if (!dict->items) {
        free(dict);
        return NULL;
    }
    dict->size = 0;
    dict->capacity = capacity;
    return dict;
}

int add_item(Dictionary *dict, const char *key, const char *value) {
    if (!dict || !key) {
        return -1;
    }
    if (dict->size >= dict->capacity) {
        size_t new_cap = dict->capacity > 0 ? dict->capacity * 2 : 4;
        KeyValuePair *new_items = realloc(dict->items, new_cap * sizeof(KeyValuePair));
        if (!new_items) {
            return -1;
        }
        dict->items = new_items;
        dict->capacity = new_cap;
    }
    
    char *dup_key = duplicate_string(key);
    if (!dup_key) {
        return -1;
    }
    
    char *dup_val = NULL;
    if (value) {
        dup_val = duplicate_string(value);
        if (!dup_val) {
            free(dup_key);
            return -1;
        }
    }

    dict->items[dict->size].key = dup_key;
    dict->items[dict->size].value = dup_val;
    dict->size++;
    
    return 0;
}

void drop_empty_items(Dictionary *dict) {
    if (!dict || !dict->items) {
        return;
    }
    
    size_t write_index = 0;
    for (size_t read_index = 0; read_index < dict->size; read_index++) {
        const char *val = dict->items[read_index].value;
        if (val == NULL || val[0] == '\0') {
            free(dict->items[read_index].key);
            free(dict->items[read_index].value);
        } else {
            if (write_index != read_index) {
                dict->items[write_index] = dict->items[read_index];
            }
            write_index++;
        }
    }
    dict->size = write_index;
}

void free_dictionary(Dictionary *dict) {
    if (!dict) {
        return;
    }
    for (size_t i = 0; i < dict->size; i++) {
        free(dict->items[i].key);
        free(dict->items[i].value);
    }
    free(dict->items);
    free(dict);
}

int main(void) {
    Dictionary *dict = create_dictionary(5);
    if (!dict) {
        fprintf(stderr, "Failed to create dictionary\n");
        return EXIT_FAILURE;
    }

    if (add_item(dict, "key1", "value1") != 0 ||
        add_item(dict, "key2", "") != 0 ||
        add_item(dict, "key3", "value3") != 0 ||
        add_item(dict, "key4", NULL) != 0 ||
        add_item(dict, "key5", "value5") != 0) {
        fprintf(stderr, "Failed to add items to dictionary\n");
        free_dictionary(dict);
        return EXIT_FAILURE;
    }

    drop_empty_items(dict);

    for (size_t i = 0; i < dict->size; i++) {
        printf("%s: %s\n", dict->items[i].key, dict->items[i].value);
    }

    free_dictionary(dict);
    return EXIT_SUCCESS;
}
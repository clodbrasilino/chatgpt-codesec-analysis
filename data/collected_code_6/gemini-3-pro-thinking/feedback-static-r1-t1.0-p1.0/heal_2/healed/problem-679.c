#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 4096

typedef struct {
    char *key;
    char *value;
} KeyValuePair;

typedef struct {
    KeyValuePair *items;
    size_t size;
    size_t capacity;
} Dictionary;

static char *duplicate_string(const char *src) {
    if (!src) {
        return NULL;
    }
    size_t len = 0;
    while (len < MAX_STR_LEN && src[len] != '\0') {
        len++;
    }
    char *dest = malloc(len + 1);
    if (!dest) {
        return NULL;
    }
    for (size_t i = 0; i < len; i++) {
        dest[i] = src[i];
    }
    dest[len] = '\0';
    return dest;
}

Dictionary *create_dictionary(size_t capacity) {
    if (capacity == 0) {
        return NULL;
    }
    if (capacity > ((size_t)-1) / sizeof(KeyValuePair)) {
        return NULL;
    }
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

void free_dictionary(Dictionary *dict) {
    if (!dict) {
        return;
    }
    if (dict->items) {
        for (size_t i = 0; i < dict->size; i++) {
            free(dict->items[i].key);
            free(dict->items[i].value);
        }
        free(dict->items);
    }
    free(dict);
}

int add_item(Dictionary *dict, const char *key, const char *value) {
    if (!dict || !key || !value) {
        return -1;
    }
    if (dict->size >= dict->capacity) {
        if (dict->capacity > ((size_t)-1) / 2) {
            return -1;
        }
        size_t new_capacity = dict->capacity * 2;
        if (new_capacity == 0) {
            new_capacity = 1;
        }
        if (new_capacity > ((size_t)-1) / sizeof(KeyValuePair)) {
            return -1;
        }
        KeyValuePair *new_items = realloc(dict->items, new_capacity * sizeof(KeyValuePair));
        if (!new_items) {
            return -1;
        }
        dict->items = new_items;
        dict->capacity = new_capacity;
    }
    char *dup_key = duplicate_string(key);
    if (!dup_key) {
        return -1;
    }
    char *dup_val = duplicate_string(value);
    if (!dup_val) {
        free(dup_key);
        return -1;
    }
    dict->items[dict->size].key = dup_key;
    dict->items[dict->size].value = dup_val;
    dict->size++;
    return 0;
}

const KeyValuePair *get_entry_by_index(const Dictionary *dict, size_t index) {
    if (!dict || !dict->items || index >= dict->size) {
        return NULL;
    }
    return &dict->items[index];
}

int main(void) {
    Dictionary *dict = create_dictionary(10);
    if (!dict) {
        return 1;
    }

    if (add_item(dict, "server_ip", "192.168.1.10") != 0) {
        free_dictionary(dict);
        return 1;
    }
    if (add_item(dict, "server_port", "8080") != 0) {
        free_dictionary(dict);
        return 1;
    }

    const KeyValuePair *entry = get_entry_by_index(dict, 1);
    if (entry) {
        printf("%s: %s\n", entry->key, entry->value);
    } else {
        printf("Error: Invalid dictionary index.\n");
    }

    free_dictionary(dict);
    return 0;
}
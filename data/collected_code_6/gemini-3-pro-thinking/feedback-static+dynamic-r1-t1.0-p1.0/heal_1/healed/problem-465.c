#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_STR_LEN 4096

typedef struct {
    char *key;
    char *value;
} dict_item_t;

typedef struct {
    dict_item_t *items;
    size_t count;
    size_t capacity;
} dict_t;

static char *safe_strdup(const char *s) {
    if (!s) {
        return NULL;
    }
    
    size_t len = 0;
    while (len < MAX_STR_LEN && s[len] != '\0') {
        len++;
    }
    
    char *dup = malloc(len + 1);
    if (dup) {
        memcpy(dup, s, len);
        dup[len] = '\0';
    }
    return dup;
}

dict_t *dict_create(size_t capacity) {
    if (capacity == 0 || capacity > SIZE_MAX / sizeof(dict_item_t)) {
        return NULL;
    }
    dict_t *d = malloc(sizeof(dict_t));
    if (!d) {
        return NULL;
    }
    d->items = malloc(capacity * sizeof(dict_item_t));
    if (!d->items) {
        free(d);
        return NULL;
    }
    d->count = 0;
    d->capacity = capacity;
    return d;
}

int dict_add(dict_t *d, const char *key, const char *value) {
    if (!d || !key) {
        return -1;
    }
    if (d->count >= d->capacity) {
        if (d->capacity > SIZE_MAX / 2) {
            return -1;
        }
        size_t new_cap = d->capacity * 2;
        if (new_cap == 0) {
            new_cap = 1;
        }
        if (new_cap > SIZE_MAX / sizeof(dict_item_t)) {
            return -1;
        }
        dict_item_t *new_items = realloc(d->items, new_cap * sizeof(dict_item_t));
        if (!new_items) {
            return -1;
        }
        d->items = new_items;
        d->capacity = new_cap;
    }
    
    char *k = safe_strdup(key);
    if (!k) {
        return -1;
    }
    
    char *v = NULL;
    if (value) {
        v = safe_strdup(value);
        if (!v) {
            free(k);
            return -1;
        }
    }
    
    d->items[d->count].key = k;
    d->items[d->count].value = v;
    d->count++;
    
    return 0;
}

void dict_destroy(dict_t *d) {
    if (!d) {
        return;
    }
    for (size_t i = 0; i < d->count; i++) {
        free(d->items[i].key);
        free(d->items[i].value);
    }
    free(d->items);
    free(d);
}

void dict_drop_empty(dict_t *d) {
    if (!d) {
        return;
    }
    
    size_t write_idx = 0;
    for (size_t read_idx = 0; read_idx < d->count; read_idx++) {
        dict_item_t *item = &d->items[read_idx];
        int is_empty = 0;
        
        if (!item->value || item->value[0] == '\0') {
            is_empty = 1;
        }
        
        if (is_empty) {
            free(item->key);
            free(item->value);
        } else {
            if (write_idx != read_idx) {
                d->items[write_idx] = d->items[read_idx];
            }
            write_idx++;
        }
    }
    d->count = write_idx;
}

int main(void) {
    dict_t *my_dict = dict_create(5);
    if (!my_dict) {
        return EXIT_FAILURE;
    }
    
    if (dict_add(my_dict, "key1", "value1") != 0 ||
        dict_add(my_dict, "key2", "") != 0 ||
        dict_add(my_dict, "key3", "value3") != 0 ||
        dict_add(my_dict, "key4", NULL) != 0 ||
        dict_add(my_dict, "key5", "value5") != 0) {
        dict_destroy(my_dict);
        return EXIT_FAILURE;
    }
    
    dict_drop_empty(my_dict);
    
    for (size_t i = 0; i < my_dict->count; i++) {
        printf("%s: %s\n", my_dict->items[i].key, my_dict->items[i].value);
    }
    
    dict_destroy(my_dict);
    return EXIT_SUCCESS;
}
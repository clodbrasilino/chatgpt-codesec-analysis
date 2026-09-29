#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    char *key;
    int value;
} dict_t;

typedef struct {
    dict_t *items;
    size_t count;
} dict_list_t;

static int compare_dicts(const void *a, const void *b) {
    const dict_t *da = (const dict_t *)a;
    const dict_t *db = (const dict_t *)b;
    int key_cmp = strcmp(da->key, db->key);
    if (key_cmp != 0) {
        return key_cmp;
    }
    if (da->value < db->value) return -1;
    if (da->value > db->value) return 1;
    return 0;
}

int sort_dict_list(dict_list_t *list) {
    if (list == NULL || list->items == NULL || list->count == 0) {
        return -1;
    }
    qsort(list->items, list->count, sizeof(dict_t), compare_dicts);
    return 0;
}

int add_dict(dict_list_t *list, const char *key, int value) {
    if (list == NULL || key == NULL) {
        return -1;
    }
    
    size_t key_len = strnlen(key, SIZE_MAX);
    if (key_len == SIZE_MAX) {
        return -1;
    }
    
    if (list->count >= SIZE_MAX / sizeof(dict_t) - 1) {
        return -1;
    }
    
    size_t new_size = list->count + 1;
    if (new_size > SIZE_MAX / sizeof(dict_t)) {
        return -1;
    }
    
    dict_t *new_items = realloc(list->items, new_size * sizeof(dict_t));
    if (new_items == NULL) {
        return -1;
    }
    list->items = new_items;
    
    size_t alloc_size = key_len + 1;
    if (alloc_size < key_len) {
        return -1;
    }
    
    char *new_key = malloc(alloc_size);
    if (new_key == NULL) {
        return -1;
    }
    
    if (alloc_size > 0) {
        new_key[alloc_size - 1] = '\0';
        if (key_len > 0) {
            memcpy(new_key, key, key_len);
        }
    }
    
    list->items[list->count].key = new_key;
    list->items[list->count].value = value;
    list->count++;
    return 0;
}

void free_dict_list(dict_list_t *list) {
    if (list == NULL) {
        return;
    }
    for (size_t i = 0; i < list->count; i++) {
        free(list->items[i].key);
    }
    free(list->items);
    list->items = NULL;
    list->count = 0;
}

int main(void) {
    dict_list_t list = {NULL, 0};
    
    if (add_dict(&list, "banana", 3) != 0) {
        free_dict_list(&list);
        return 1;
    }
    if (add_dict(&list, "apple", 2) != 0) {
        free_dict_list(&list);
        return 1;
    }
    if (add_dict(&list, "cherry", 1) != 0) {
        free_dict_list(&list);
        return 1;
    }
    if (add_dict(&list, "apple", 1) != 0) {
        free_dict_list(&list);
        return 1;
    }
    
    if (sort_dict_list(&list) != 0) {
        free_dict_list(&list);
        return 1;
    }
    
    for (size_t i = 0; i < list.count; i++) {
        printf("%s: %d\n", list.items[i].key, list.items[i].value);
    }
    
    free_dict_list(&list);
    return 0;
}
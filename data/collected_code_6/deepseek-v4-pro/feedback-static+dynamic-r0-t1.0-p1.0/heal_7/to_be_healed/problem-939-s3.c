#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>

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

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t key_len = strlen(key);
    
    if (key_len >= SIZE_MAX) {
        return -1;
    }
    
    char *key_copy = malloc(key_len + 1);
    if (key_copy == NULL) {
        return -1;
    }
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(key_copy, key, key_len + 1);
    
    if (list->count >= SIZE_MAX / sizeof(dict_t) - 1) {
        free(key_copy);
        return -1;
    }
    
    size_t new_count = list->count + 1;
    size_t new_size = new_count * sizeof(dict_t);
    
    dict_t *new_items = realloc(list->items, new_size);
    if (new_items == NULL) {
        free(key_copy);
        return -1;
    }
    list->items = new_items;
    list->items[list->count].key = key_copy;
    list->items[list->count].value = value;
    list->count = new_count;
    return 0;
}

void free_dict_list(dict_list_t *list) {
    if (list == NULL) {
        return;
    }
    for (size_t i = 0; i < list->count; i++) {
        free(list->items[i].key);
        list->items[i].key = NULL;
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
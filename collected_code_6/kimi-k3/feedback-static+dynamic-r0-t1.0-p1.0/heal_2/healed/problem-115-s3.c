#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char *key;
    char *value;
} DictEntry;

typedef struct {
    DictEntry *entries;
    size_t size;
    size_t capacity;
} Dictionary;

typedef struct {
    Dictionary *dicts;
    size_t count;
} DictList;

bool all_dicts_empty(const DictList *list) {
    if (list == NULL || list->dicts == NULL || list->count == 0) {
        return true;
    }
    for (size_t i = 0; i < list->count; i++) {
        if (list->dicts[i].entries != NULL && list->dicts[i].size > 0) {
            return false;
        }
    }
    return true;
}

bool dict_init(Dictionary *dict, size_t capacity) {
    if (dict == NULL || capacity == 0) {
        return false;
    }
    dict->entries = calloc(capacity, sizeof(DictEntry));
    if (dict->entries == NULL) {
        return false;
    }
    dict->size = 0;
    dict->capacity = capacity;
    return true;
}

void dict_free(Dictionary *dict) {
    if (dict != NULL) {
        if (dict->entries != NULL) {
            for (size_t i = 0; i < dict->size; i++) {
                free(dict->entries[i].key);
                free(dict->entries[i].value);
            }
            free(dict->entries);
            dict->entries = NULL;
        }
        dict->size = 0;
        dict->capacity = 0;
    }
}

bool dict_add(Dictionary *dict, const char *key, const char *value) {
    if (dict == NULL || key == NULL || value == NULL || dict->entries == NULL) {
        return false;
    }
    if (dict->size >= dict->capacity) {
        return false;
    }
    
    size_t key_len = strlen(key) + 1;
    size_t value_len = strlen(value) + 1;
    
    dict->entries[dict->size].key = malloc(key_len);
    if (dict->entries[dict->size].key == NULL) {
        return false;
    }
    
    dict->entries[dict->size].value = malloc(value_len);
    if (dict->entries[dict->size].value == NULL) {
        free(dict->entries[dict->size].key);
        dict->entries[dict->size].key = NULL;
        return false;
    }
    
    memcpy(dict->entries[dict->size].key, key, key_len);
    memcpy(dict->entries[dict->size].value, value, value_len);
    
    dict->size++;
    return true;
}

int main(void) {
    DictList list = {0};
    list.count = 3;
    list.dicts = calloc(list.count, sizeof(Dictionary));
    if (list.dicts == NULL) {
        return 1;
    }

    for (size_t i = 0; i < list.count; i++) {
        if (!dict_init(&list.dicts[i], 10)) {
            for (size_t j = 0; j < i; j++) {
                dict_free(&list.dicts[j]);
            }
            free(list.dicts);
            return 1;
        }
    }

    printf("All empty: %s\n", all_dicts_empty(&list) ? "true" : "false");

    if (!dict_add(&list.dicts[1], "key1", "value1")) {
        for (size_t i = 0; i < list.count; i++) {
            dict_free(&list.dicts[i]);
        }
        free(list.dicts);
        return 1;
    }

    printf("All empty: %s\n", all_dicts_empty(&list) ? "true" : "false");

    for (size_t i = 0; i < list.count; i++) {
        dict_free(&list.dicts[i]);
    }
    free(list.dicts);

    return 0;
}
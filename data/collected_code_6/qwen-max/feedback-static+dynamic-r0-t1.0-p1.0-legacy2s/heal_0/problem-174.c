#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct KeyValue {
    char *key;
    char *value;
} KeyValue;

typedef struct List {
    char *item;
    struct List *next;
} List;

typedef struct {
    char *key;
    List *values;
} DictItem;

typedef struct Dictionary {
    DictItem **items;
    int size;
    int capacity;
} Dictionary;

List* list_create(char *value) {
    List *node = (List*)malloc(sizeof(List));
    node->item = strdup(value);
    node->next = NULL;
    return node;
}

List* list_append(List *list, char *value) {
    if (!list) {
        return list_create(value);
    }
    list->next = list_append(list->next, value);
    return list;
}

DictItem* dict_item_create(char *key, char *value) {
    DictItem *item = (DictItem*)malloc(sizeof(DictItem));
    item->key = strdup(key);
    item->values = list_create(value);
    return item;
}

int dict_resize(Dictionary *dict) {
    dict->capacity *= 2;
    DictItem **new_items = (DictItem**)realloc(dict->items, sizeof(DictItem*) * dict->capacity);
    if (!new_items) {
        return -1;
    }
    for (int i = dict->size; i < dict->capacity; ++i) {
        new_items[i] = NULL;
    }
    dict->items = new_items;
    return 0;
}

int hash_function(const char *key, int capacity) {
    unsigned long hash = 5381;
    int c;
    while ((c = *key++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % capacity;
}

void dict_insert(Dictionary *dict, char *key, char *value) {
    int index = hash_function(key, dict->capacity);
    while (dict->items[index]) {
        if (strcmp(dict->items[index]->key, key) == 0) {
            dict->items[index]->values = list_append(dict->items[index]->values, value);
            return;
        }
        if (++index == dict->capacity) {
            index = 0;
        }
    }
    if (dict->size >= dict->capacity) {
        if (dict_resize(dict) != 0) {
            return;
        }
    }
    dict->items[index] = dict_item_create(key, value);
    dict->size++;
}

Dictionary* dictionary_create() {
    Dictionary *dict = (Dictionary*)malloc(sizeof(Dictionary));
    dict->capacity = 8;
    dict->size = 0;
    dict->items = (DictItem**)calloc(dict->capacity, sizeof(DictItem*));
    return dict;
}

void print_dictionary(Dictionary *dict) {
    for (int i = 0; i < dict->size; ++i) {
        if (dict->items[i]) {
            printf("%s: ", dict->items[i]->key);
            for (List *list = dict->items[i]->values; list; list = list->next) {
                printf("%s -> ", list->item);
            }
            printf("\n");
        }
    }
}

void free_list(List *list) {
    if (list) {
        free_list(list->next);
        free(list->item);
        free(list);
    }
}

void free_dictionary(Dictionary *dict) {
    if (dict) {
        for (int i = 0; i < dict->capacity; ++i) {
            if (dict->items[i]) {
                free_list(dict->items[i]->values);
                free(dict->items[i]->key);
                free(dict->items[i]);
            }
        }
        free(dict->items);
        free(dict);
    }
}

int main() {
    Dictionary *dict = dictionary_create();
    
    KeyValue data[] = {{"apple", "red"}, {"banana", "yellow"}, {"apple", "green"}};
    int n = sizeof(data) / sizeof(data[0]);
    
    for (int i = 0; i < n; ++i) {
        dict_insert(dict, data[i].key, data[i].value);
    }
    
    print_dictionary(dict);
    
    free_dictionary(dict);
    
    return 0;
}
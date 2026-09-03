#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int *keys;
    int *values;
    int size;
    int capacity;
} Dictionary;

typedef struct {
    Dictionary *dicts;
    int size;
} DictionaryList;

Dictionary *create_dictionary(int capacity) {
    Dictionary *dict = (Dictionary *)malloc(sizeof(Dictionary));
    if (dict == NULL) {
        return NULL;
    }
    dict->keys = (int *)malloc(sizeof(int) * capacity);
    dict->values = (int *)malloc(sizeof(int) * capacity);
    if (dict->keys == NULL || dict->values == NULL) {
        free(dict->keys);
        free(dict->values);
        free(dict);
        return NULL;
    }
    dict->size = 0;
    dict->capacity = capacity;
    return dict;
}

void destroy_dictionary(Dictionary *dict) {
    if (dict != NULL) {
        free(dict->keys);
        free(dict->values);
        free(dict);
    }
}

DictionaryList *create_dictionary_list(int size) {
    DictionaryList *list = (DictionaryList *)malloc(sizeof(DictionaryList));
    if (list == NULL) {
        return NULL;
    }
    list->dicts = (Dictionary *)malloc(sizeof(Dictionary) * size);
    if (list->dicts == NULL) {
        free(list);
        return NULL;
    }
    list->size = size;
    for (int i = 0; i < size; i++) {
        list->dicts[i].keys = NULL;
        list->dicts[i].values = NULL;
        list->dicts[i].size = 0;
        list->dicts[i].capacity = 0;
    }
    return list;
}

void destroy_dictionary_list(DictionaryList *list) {
    if (list != NULL) {
        for (int i = 0; i < list->size; i++) {
            free(list->dicts[i].keys);
            free(list->dicts[i].values);
        }
        free(list->dicts);
        free(list);
    }
}

bool are_all_dictionaries_empty(DictionaryList *list) {
    if (list == NULL || list->dicts == NULL) {
        return true;
    }
    for (int i = 0; i < list->size; i++) {
        if (list->dicts[i].size > 0) {
            return false;
        }
    }
    return true;
}

int main(void) {
    DictionaryList *list = create_dictionary_list(3);
    if (list == NULL) {
        return 1;
    }

    list->dicts[0].keys = (int *)malloc(sizeof(int) * 5);
    list->dicts[0].values = (int *)malloc(sizeof(int) * 5);
    if (list->dicts[0].keys == NULL || list->dicts[0].values == NULL) {
        destroy_dictionary_list(list);
        return 1;
    }
    list->dicts[0].size = 0;
    list->dicts[0].capacity = 5;

    list->dicts[1].keys = (int *)malloc(sizeof(int) * 3);
    list->dicts[1].values = (int *)malloc(sizeof(int) * 3);
    if (list->dicts[1].keys == NULL || list->dicts[1].values == NULL) {
        destroy_dictionary_list(list);
        return 1;
    }
    list->dicts[1].size = 2;
    list->dicts[1].capacity = 3;

    list->dicts[2].keys = NULL;
    list->dicts[2].values = NULL;
    list->dicts[2].size = 0;
    list->dicts[2].capacity = 0;

    if (are_all_dictionaries_empty(list)) {
        printf("All dictionaries are empty\n");
    } else {
        printf("Not all dictionaries are empty\n");
    }

    destroy_dictionary_list(list);
    return 0;
}
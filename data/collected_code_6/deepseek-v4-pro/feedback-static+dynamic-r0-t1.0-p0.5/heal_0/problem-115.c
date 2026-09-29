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

Dictionary* create_dictionary(int capacity) {
    Dictionary *dict = (Dictionary*)malloc(sizeof(Dictionary));
    if (dict == NULL) {
        return NULL;
    }
    dict->keys = (int*)malloc(sizeof(int) * capacity);
    if (dict->keys == NULL) {
        free(dict);
        return NULL;
    }
    dict->values = (int*)malloc(sizeof(int) * capacity);
    if (dict->values == NULL) {
        free(dict->keys);
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

DictionaryList* create_dictionary_list(int size) {
    DictionaryList *list = (DictionaryList*)malloc(sizeof(DictionaryList));
    if (list == NULL) {
        return NULL;
    }
    list->dicts = (Dictionary*)malloc(sizeof(Dictionary) * size);
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
            if (list->dicts[i].keys != NULL) {
                free(list->dicts[i].keys);
            }
            if (list->dicts[i].values != NULL) {
                free(list->dicts[i].values);
            }
        }
        free(list->dicts);
        free(list);
    }
}

bool are_all_dictionaries_empty(DictionaryList *list) {
    if (list == NULL) {
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

    Dictionary *dict1 = create_dictionary(5);
    if (dict1 == NULL) {
        destroy_dictionary_list(list);
        return 1;
    }
    list->dicts[0] = *dict1;
    free(dict1);

    Dictionary *dict2 = create_dictionary(5);
    if (dict2 == NULL) {
        destroy_dictionary_list(list);
        return 1;
    }
    list->dicts[1] = *dict2;
    free(dict2);

    Dictionary *dict3 = create_dictionary(5);
    if (dict3 == NULL) {
        destroy_dictionary_list(list);
        return 1;
    }
    list->dicts[2] = *dict3;
    free(dict3);

    if (are_all_dictionaries_empty(list)) {
        printf("All dictionaries are empty\n");
    } else {
        printf("Not all dictionaries are empty\n");
    }

    list->dicts[1].size = 2;

    if (are_all_dictionaries_empty(list)) {
        printf("All dictionaries are empty\n");
    } else {
        printf("Not all dictionaries are empty\n");
    }

    destroy_dictionary_list(list);
    return 0;
}
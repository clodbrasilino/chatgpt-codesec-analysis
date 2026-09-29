#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char **keys;
    char **values;
    size_t size;
} Dictionary;

typedef struct {
    Dictionary **items;
    size_t count;
} DictionaryList;

Dictionary* create_empty_dictionary(void) {
    Dictionary *dict = (Dictionary*)malloc(sizeof(Dictionary));
    if (!dict) {
        return NULL;
    }
    dict->keys = NULL;
    dict->values = NULL;
    dict->size = 0;
    return dict;
}

void free_dictionary(Dictionary *dict) {
    if (!dict) {
        return;
    }
    free(dict->keys);
    free(dict->values);
    free(dict);
}

DictionaryList* create_dictionary_list(size_t count) {
    DictionaryList *list = (DictionaryList*)malloc(sizeof(DictionaryList));
    if (!list) {
        return NULL;
    }

    list->count = count;
    if (count == 0) {
        list->items = NULL;
        return list;
    }

    list->items = (Dictionary**)malloc(count * sizeof(Dictionary*));
    if (!list->items) {
        free(list);
        return NULL;
    }

    for (size_t i = 0; i < count; i++) {
        list->items[i] = create_empty_dictionary();
        if (!list->items[i]) {
            for (size_t j = 0; j < i; j++) {
                free_dictionary(list->items[j]);
            }
            free(list->items);
            free(list);
            return NULL;
        }
    }

    return list;
}

void free_dictionary_list(DictionaryList *list) {
    if (!list) {
        return;
    }
    if (list->items) {
        for (size_t i = 0; i < list->count; i++) {
            free_dictionary(list->items[i]);
        }
        free(list->items);
    }
    free(list);
}

int main(void) {
    size_t num_dicts = 5;
    DictionaryList *my_list = create_dictionary_list(num_dicts);

    if (!my_list) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    free_dictionary_list(my_list);
    return EXIT_SUCCESS;
}
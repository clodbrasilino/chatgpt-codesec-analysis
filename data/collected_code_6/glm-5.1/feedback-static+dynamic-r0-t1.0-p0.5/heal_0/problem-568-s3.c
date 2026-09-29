#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *entries;
    int size;
    int capacity;
} Dictionary;

typedef struct {
    Dictionary **items;
    int size;
    int capacity;
} List;

Dictionary *create_dictionary() {
    Dictionary *dict = (Dictionary *)malloc(sizeof(Dictionary));
    if (dict == NULL) {
        return NULL;
    }
    dict->entries = NULL;
    dict->size = 0;
    dict->capacity = 0;
    return dict;
}

List *create_list_of_dicts(int count) {
    if (count < 0) {
        return NULL;
    }
    List *list = (List *)malloc(sizeof(List));
    if (list == NULL) {
        return NULL;
    }
    list->items = (Dictionary **)malloc(sizeof(Dictionary *) * count);
    if (list->items == NULL) {
        free(list);
        return NULL;
    }
    list->size = 0;
    list->capacity = count;
    for (int i = 0; i < count; i++) {
        Dictionary *dict = create_dictionary();
        if (dict == NULL) {
            for (int j = 0; j < list->size; j++) {
                free(list->items[j]->entries);
                free(list->items[j]);
            }
            free(list->items);
            free(list);
            return NULL;
        }
        list->items[i] = dict;
        list->size++;
    }
    return list;
}

void free_list_of_dicts(List *list) {
    if (list == NULL) {
        return;
    }
    for (int i = 0; i < list->size; i++) {
        free(list->items[i]->entries);
        free(list->items[i]);
    }
    free(list->items);
    free(list);
}

int main() {
    int count = 5;
    List *list = create_list_of_dicts(count);
    if (list == NULL) {
        return EXIT_FAILURE;
    }
    for (int i = 0; i < list->size; i++) {
        printf("Dictionary %d: size=%d, capacity=%d\n", i, list->items[i]->size, list->items[i]->capacity);
    }
    free_list_of_dicts(list);
    return EXIT_SUCCESS;
}
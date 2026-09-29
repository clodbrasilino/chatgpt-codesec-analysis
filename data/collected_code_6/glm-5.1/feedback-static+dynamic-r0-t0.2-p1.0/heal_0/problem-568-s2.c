#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *keys;
    int *values;
    size_t size;
    size_t capacity;
} Dictionary;

Dictionary* create_dictionary() {
    Dictionary *dict = (Dictionary*)malloc(sizeof(Dictionary));
    if (dict == NULL) {
        return NULL;
    }
    dict->keys = NULL;
    dict->values = NULL;
    dict->size = 0;
    dict->capacity = 0;
    return dict;
}

Dictionary** create_empty_dictionaries(size_t count) {
    if (count == 0) {
        return NULL;
    }
    Dictionary **list = (Dictionary**)malloc(count * sizeof(Dictionary*));
    if (list == NULL) {
        return NULL;
    }
    for (size_t i = 0; i < count; i++) {
        list[i] = create_dictionary();
        if (list[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(list[j]->keys);
                free(list[j]->values);
                free(list[j]);
            }
            free(list);
            return NULL;
        }
    }
    return list;
}

void free_dictionaries(Dictionary **list, size_t count) {
    if (list == NULL) {
        return;
    }
    for (size_t i = 0; i < count; i++) {
        if (list[i] != NULL) {
            free(list[i]->keys);
            free(list[i]->values);
            free(list[i]);
        }
    }
    free(list);
}

int main() {
    size_t count = 5;
    Dictionary **dict_list = create_empty_dictionaries(count);
    if (dict_list == NULL) {
        fprintf(stderr, "Failed to allocate dictionary list\n");
        return 1;
    }
    for (size_t i = 0; i < count; i++) {
        printf("Dictionary %zu: size=%zu, capacity=%zu\n", i, dict_list[i]->size, dict_list[i]->capacity);
    }
    free_dictionaries(dict_list, count);
    return 0;
}